//
// Created by 任齐轩 on 2022/12/3.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "struct_define.h"
#include "checksum_utils.h"
#include "print_utils.h"


/*
 ============================================================================
                               Application Layer
 ============================================================================
*/

void application_layer_init(unsigned char* buffer, application_frame *app_layer, unsigned char *data, unsigned short length) {
    app_layer->length = length;
    app_layer->data = (char*) malloc(sizeof(char) * length);
    memcpy(app_layer->data, data, length);

    memcpy(&buffer[0], data, length);
    memcpy(&buffer[length], &app_layer->length, 2);
}



/*
 ============================================================================
                               Transport Layer
 ============================================================================
*/
void udp_init(unsigned char* buffer, udp_frame *udp, unsigned short src_port, unsigned short dst_port, unsigned short data_len, unsigned char src_ip[4], unsigned char dst_ip[4]) {
    udp->src_port = src_port;
    udp->dst_port = dst_port;
    udp->length = data_len + 8;
    udp->checksum = 0;

    unsigned char pesudo_header_udp[12 + 65515];
    unsigned char UDP_protocol = 11;
    unsigned short UDP_length = data_len + 8;

    /* calculate UDP checksum for pesudo header */
    memcpy(&pesudo_header_udp[0], src_ip,4);
    memcpy(&pesudo_header_udp[4], dst_ip,4);
    pesudo_header_udp[8] = 0x00;
    memcpy(&pesudo_header_udp[9], &UDP_protocol, 1);
    memcpy(&pesudo_header_udp[10], &UDP_length, 2);

    memcpy(&pesudo_header_udp[12], &udp->src_port, 2);
    memcpy(&pesudo_header_udp[14], &udp->dst_port, 2);
    memcpy(&pesudo_header_udp[16], &udp->length, 2);
    memcpy(&pesudo_header_udp[18], &udp->checksum, 2);
    memcpy(&pesudo_header_udp[20], &buffer[0], data_len);

    udp->checksum = Checksum(pesudo_header_udp, 12 + udp->length);
    memcpy(&buffer[data_len], &udp->checksum, 2);
    memcpy(&buffer[data_len + 2], &udp->length, 2);
    memcpy(&buffer[data_len + 4], &udp->dst_port, 2);
    memcpy(&buffer[data_len + 6], &udp->src_port, 2);
}


/*
 ============================================================================
                               Network Layer
 ============================================================================
*/
void ip_init(unsigned char* buffer, ipv4_frame *ip, unsigned char src_ip[4], unsigned char dst_ip[4], unsigned data_len) {
    ip->version = 4;
    ip->header_length = 5;
    ip->type_of_service = 0;
    ip->total_length = 20 + data_len;
    ip->identification = 0;
    ip->flags = 0;
    ip->fragment_offset = 0;
    ip->time_to_live = 255;
    ip->protocol = 17;
    ip->header_checksum = 0;
    memcpy(ip->src_ip, src_ip, 4);
    memcpy(ip->dst_ip, dst_ip, 4);

    // checksum header build
    unsigned char checksum_header[20];
    unsigned char version_hdlen = (ip->version << 4) | ip->header_length;
    unsigned short flag_offset = (ip->flags << 13) | ip->fragment_offset;

    memcpy(&checksum_header[0], &version_hdlen, 1);
    memcpy(&checksum_header[1], &ip->type_of_service, 1);
    memcpy(&checksum_header[2], &ip->total_length, 2);
    memcpy(&checksum_header[4], &ip->identification, 2);
    memcpy(&checksum_header[6], &flag_offset, 2);
    memcpy(&checksum_header[8], &ip->time_to_live, 1);
    memcpy(&checksum_header[9], &ip->protocol, 1);
    memcpy(&checksum_header[10], &ip->header_checksum, 2);
    memcpy(&checksum_header[12], src_ip, 4);
    memcpy(&checksum_header[16], dst_ip, 4);
    // header checksum
    ip->header_checksum = Checksum(checksum_header, 20);

    // copy to buffer
    memcpy(&buffer[data_len], dst_ip, 4);
    memcpy(&buffer[data_len + 4], src_ip, 4);
    memcpy(&buffer[data_len + 8], &ip->header_checksum, 2);
    memcpy(&buffer[data_len + 10], &ip->protocol, 1);
    memcpy(&buffer[data_len + 11], &ip->time_to_live, 1);
    memcpy(&buffer[data_len + 12], &flag_offset, 2);
    memcpy(&buffer[data_len + 14], &ip->identification, 2);
    memcpy(&buffer[data_len + 16], &ip->total_length, 2);
    memcpy(&buffer[data_len + 18], &ip->type_of_service, 1);
    memcpy(&buffer[data_len + 19], &version_hdlen, 1);
}


/*
 ============================================================================
                               Data Link Layer
 ============================================================================
*/
void data_link_layer_init(unsigned char* buffer, ethernet_frame *data_link, unsigned char src_mac[6], unsigned char dst_mac[6], unsigned data_len) {
    memcpy(data_link->src_mac, src_mac, 6);
    memcpy(data_link->dst_mac, dst_mac, 6);
    data_link->type[0] = 0x08;
    data_link->type[1] = 0x00;
    data_link->crc = 0;

    unsigned char pesudo_header[12 + 65535];
    memcpy(&pesudo_header[0], src_mac, 6);
    memcpy(&pesudo_header[6], dst_mac, 6);
    memcpy(&pesudo_header[12], data_link->type, 2);
    memcpy(&pesudo_header[14], &buffer[0], data_len);

    data_link->crc = crc32(pesudo_header, 14 + data_len);

    memcpy(&buffer[data_len], data_link->type, 2);
    memcpy(&buffer[data_len + 2], dst_mac, 6);
    memcpy(&buffer[data_len + 8], src_mac, 6);
    memcpy(&buffer[data_len + 14], &data_link->crc, 4);
}


int main() {
    // struct define
    application_frame app;
    udp_frame udp;
    ipv4_frame ip;
    ethernet_frame eth;

    // data define
    unsigned char buffer[2000];
    unsigned char src_mac[6] = {0x00, 0x0c, 0x29, 0x1a, 0x2b, 0x3c};
    unsigned char dst_mac[6] = {0x00, 0x0c, 0x29, 0x1a, 0x2b, 0x3d};
    unsigned char src_ip[4] = {192, 168, 1, 1};
    unsigned char dst_ip[4] = {192, 168, 1, 2};
    unsigned short src_port = 8080;
    unsigned short dst_port = 8081;

    // transport process
    char data[100];
    printf("please input data: ");
    fgets(data,sizeof(data),stdin);
    unsigned short data_len = strlen(data) - 1;
    printf("================= Application Layer Pack =================\n");
    application_layer_init(&buffer[0], &app, data, data_len);
    application_layer_print(&app);

    printf("================= UDP Layer Pack Pack ====================\n");
    udp_init(&buffer[0], &udp, src_port, dst_port, data_len+2, src_ip, dst_ip);
    udp_print(&udp);

    printf("================= IP Layer Pack =================\n");
    ip_init(&buffer[0], &ip, src_ip, dst_ip, data_len+2+8);
    ip_print(&ip);

    printf("================= Data Link Layer Pack =================\n");
    data_link_layer_init(&buffer[0], &eth, src_mac, dst_mac, data_len+2+8+20);
    data_link_layer_print(&eth);

    printf("Data Link Transmit Success!\n\n");
    printf("================= Full Payload =================");
    int i;
    for (i = data_len+2+8+20+14+4 - 1; i >= 0; i--) {
        if ((data_len+2+8+20+14+4 - 1 - i) % 16 == 0) {
            printf("\n");
        }
        printf(" %02x |", buffer[i]);
    }

    printf("\n\n");

    // data link result print
    FILE *outfile;
    outfile = fopen("./message.txt","wb+");
    if(outfile==NULL) {
        printf("Can't open the file!\n");
    }
    fwrite(buffer,sizeof(char),data_len+2+8+20+14+4,outfile);
    fclose(outfile);
    return 0;
}

