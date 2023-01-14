//
// Created by 任齐轩 on 2022/12/3.
//
#include <stdio.h>
#include <string.h>
#include "struct_define.h"
#include "checksum_utils.h"
#include "print_utils.h"


/*
 ============================================================================
                                Data Link Layer
 ============================================================================
*/

void ethernet_receiver(unsigned char* buffer, ethernet_frame *ethernet_frame, unsigned short data_len) {
    memcpy(&ethernet_frame->crc, &buffer[data_len-4], 4);
    memcpy(&ethernet_frame->src_mac, &buffer[data_len-10], 6);
    memcpy(&ethernet_frame->dst_mac, &buffer[data_len-16], 6);
    memcpy(&ethernet_frame->type, &buffer[data_len-18], 2);

    unsigned char pesudo_header[65535];
    memcpy(&pesudo_header[0], ethernet_frame->src_mac, 6);
    memcpy(&pesudo_header[6], ethernet_frame->dst_mac, 6);
    memcpy(&pesudo_header[12], ethernet_frame->type, 2);
    memcpy(&pesudo_header[14], &buffer[0], data_len - 18);

    unsigned int crc_result = crc32(pesudo_header, data_len-4);
    unsigned int crc_received = ethernet_frame->crc;
    printf("================= Data Link Layer Unpack =================\n");
    if (crc_result == crc_received) {
        printf("- CRC check passed!\n");
    } else {
        printf("- CRC check failed!\n");
    }
    data_link_layer_print(ethernet_frame);
}


/*
 ============================================================================
                                Network Layer
 ============================================================================
*/
void ipv4_receiver(unsigned char* buffer, ipv4_frame *ip, unsigned short data_len) {
    unsigned char version_hdlen = buffer[data_len-1];
    ip->version = version_hdlen >> 4;
    ip->header_length = version_hdlen & 15;
    ip->type_of_service = buffer[data_len-2];
    memcpy(&ip->total_length, &buffer[data_len-4], 2);
    memcpy(&ip->identification, &buffer[data_len-6], 2);
    unsigned short flag_offset;
    memcpy(&flag_offset, &buffer[data_len-8], 2);
    ip->flags = flag_offset >> 13;
    ip->fragment_offset = flag_offset & 8191;
    ip->time_to_live = buffer[data_len-9];
    ip->protocol = buffer[data_len-10];
    memcpy(&ip->header_checksum, &buffer[data_len-12], 2);
    memcpy(ip->src_ip, &buffer[data_len-16], 4);
    memcpy(ip->dst_ip, &buffer[data_len-20], 4);


    unsigned char checksum_header[20];
    memcpy(&checksum_header[0], &version_hdlen, 1);
    memcpy(&checksum_header[1], &ip->type_of_service, 1);
    memcpy(&checksum_header[2], &ip->total_length, 2);
    memcpy(&checksum_header[4], &ip->identification, 2);
    memcpy(&checksum_header[6], &flag_offset, 2);
    memcpy(&checksum_header[8], &ip->time_to_live, 1);
    memcpy(&checksum_header[9], &ip->protocol, 1);
    memcpy(&checksum_header[10], &ip->header_checksum, 2);
    memcpy(&checksum_header[12], &ip->src_ip, 4);
    memcpy(&checksum_header[16], &ip->dst_ip, 4);

    unsigned int checksum_result = Checksum(checksum_header, 20);
    printf("================= Network Layer Unpack =================\n");
    printf("Checksum: %d\n", checksum_result);
    if (checksum_result == 0) {
        printf("Checksum check passed!\n");
    } else {
        printf("Checksum check failed!\n");
    }
    ip_print(ip);
}


/*
 ============================================================================
                                Transport Layer
 ============================================================================
*/
void udp_receiver(unsigned char* buffer, udp_frame *udp, unsigned short data_len, unsigned char src_ip[4], unsigned char dst_ip[4]) {
    memcpy(&udp->src_port, &buffer[data_len-2], 2);
    memcpy(&udp->dst_port, &buffer[data_len-4], 2);
    memcpy(&udp->length, &buffer[data_len-6], 2);
    memcpy(&udp->checksum, &buffer[data_len-8], 2);

    unsigned char pesudo_header[12 + 65535];
    memcpy(&pesudo_header[0], src_ip,4);
    memcpy(&pesudo_header[4], dst_ip,4);
    pesudo_header[8] = 0x00;
    unsigned char UDP_protocol = 11;
    memcpy(&pesudo_header[9], &UDP_protocol, 1);
    memcpy(&pesudo_header[10], &udp->length, 2);

    memcpy(&pesudo_header[12], &udp->src_port, 2);
    memcpy(&pesudo_header[14], &udp->dst_port, 2);
    memcpy(&pesudo_header[16], &udp->length, 2);
    memcpy(&pesudo_header[18], &udp->checksum, 2);
    memcpy(&pesudo_header[20], &buffer[0], data_len - 8);

    unsigned int check_result = Checksum(pesudo_header, 12 + udp->length);
    printf("================= Transport Layer Unpack =================\n");
    printf("Checksum result: %d\n", check_result);
    if (check_result == 0) {
        printf("Checksum check passed!\n");
    } else {
        printf("Checksum check failed!\n");
    }
    udp_print(udp);
}


/*
 ============================================================================
                                Application Layer
 ============================================================================
*/
void application_receiver(unsigned char* buffer, application_frame *app, unsigned short data_len) {
    memcpy(&app->length, &buffer[data_len-2], 2);
    app->data = (char*)malloc(sizeof(char) *  app->length);
    memcpy(app->data, &buffer[0], app->length);
    printf("================= Application Layer Unpack =================\n");
    application_layer_print(app);
}

int main() {
    FILE *infile;
    infile = fopen("message.txt","r");
    if(infile==NULL){
        printf("Can't open the file!\n");
    }
    unsigned char buffer[65535];
    int data_len = 0;
    unsigned char c;
    while(!feof(infile)){
        c = getc(infile);
        buffer[data_len] = c;
        data_len++;
    }
    fclose(infile);
    data_len--;

    printf("================= Full Payload Received =================");
    int j;
    for (j = data_len-1; j >= 0; j--) {
        if ((data_len-1-j) % 16 == 0) {
            printf("\n");
        }
        printf(" %02x |", buffer[j]);
    }
    printf("\n");

    // struct define
    ethernet_frame ethernet_frame;
    ipv4_frame ipv4_frame;
    udp_frame udp_frame;
    application_frame application_frame;

    // unpack the data
    ethernet_receiver(&buffer[0], &ethernet_frame, data_len);

    ipv4_receiver(&buffer[0], &ipv4_frame, data_len-18);

    udp_receiver(&buffer[0], &udp_frame, data_len-38, ipv4_frame.src_ip, ipv4_frame.dst_ip);

    application_receiver(&buffer[0], &application_frame, data_len-46);
    return 0;
}

