//
// Created by 任齐轩 on 2022/12/4.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "struct_define.h"
#include "checksum_utils.h"

#ifndef COMPUTER_NETWORK_PROJECT_PRINT_UTILS_H
#define COMPUTER_NETWORK_PROJECT_PRINT_UTILS_H

void data_link_layer_print(ethernet_frame *data_link) {
    printf("Data Link Layer:\n");
    printf(" - Source MAC: %02x:%02x:%02x:%02x:%02x:%02x\n", data_link->src_mac[0], data_link->src_mac[1], data_link->src_mac[2], data_link->src_mac[3], data_link->src_mac[4], data_link->src_mac[5]);
    printf(" - Destination MAC: %02x:%02x:%02x:%02x:%02x:%02x\n", data_link->dst_mac[0], data_link->dst_mac[1], data_link->dst_mac[2], data_link->dst_mac[3], data_link->dst_mac[4], data_link->dst_mac[5]);
    printf(" - Type: %02x%02x\n", data_link->type[0], data_link->type[1]);
    printf(" - CRC: %u\n\n", data_link->crc);
}

void ip_print(ipv4_frame *ip) {
    printf("IP Layer:\n");
    printf(" - Version: %d\n", ip->version);
    printf(" - Header Length: %d\n", ip->header_length);
    printf(" - Type of Service: %d\n", ip->type_of_service);
    printf(" - Total Length: %d\n", ip->total_length);
    printf(" - Identification: %d\n", ip->identification);
    printf(" - Flags: %d\n", ip->flags);
    printf(" - Fragment Offset: %d\n", ip->fragment_offset);
    printf(" - Time to Live: %d\n", ip->time_to_live);
    printf(" - Protocol: %d\n", ip->protocol);
    printf(" - Header Checksum: %d\n", ip->header_checksum);
    printf(" - Source IP: %d.%d.%d.%d\n", ip->src_ip[0], ip->src_ip[1], ip->src_ip[2], ip->src_ip[3]);
    printf(" - Destination IP: %d.%d.%d.%d\n\n", ip->dst_ip[0], ip->dst_ip[1], ip->dst_ip[2], ip->dst_ip[3]);
}

void udp_print(udp_frame *udp) {
    printf("UDP Layer:\n");
    printf(" - Source Port: %d\n", udp->src_port);
    printf(" - Destination Port: %d\n", udp->dst_port);
    printf(" - Length: %d\n", udp->length);
    printf(" - Checksum: %d\n\n", udp->checksum);
}

void application_layer_print(application_frame *app_layer) {
    printf("Application Layer:\n");
    printf(" - Length: %d\n", app_layer->length);
    printf(" - Data: ");
    int i;
    for (i = 0; i < app_layer->length; i++) {
        printf("%c", app_layer->data[i]);
    }
    printf("\n\n");
}

#endif //COMPUTER_NETWORK_PROJECT_PRINT_UTILS_H
