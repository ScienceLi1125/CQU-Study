//
// Created by 任齐轩 on 2022/12/3.
//

#ifndef COMPUTER_NETWORK_PROJECT_STRUCT_DEFINE_H
#define COMPUTER_NETWORK_PROJECT_STRUCT_DEFINE_H

/*
 struct define
 */

// application layer
typedef struct {
    char* data;
    unsigned short length;
} application_frame;


// transport layer - UDP
typedef struct {
    unsigned short src_port;
    unsigned short dst_port;
    unsigned short length;
    unsigned short checksum;
} udp_frame;


// network layer - IP
typedef struct {
    unsigned char version; // 4 bits
    unsigned char header_length; // 4 bits
    unsigned char type_of_service;
    unsigned short total_length;
    unsigned short identification;
    unsigned char flags; // 3 bits
    unsigned char fragment_offset; // 13 bits
    unsigned char time_to_live;
    unsigned char protocol;
    unsigned short header_checksum;
    unsigned char src_ip[4];
    unsigned char dst_ip[4];
} ipv4_frame;


// data link layer - Ethernet
typedef struct {
    unsigned char dst_mac[6];
    unsigned char src_mac[6];
    unsigned char type[2];
    unsigned int crc;
} ethernet_frame;


#endif //COMPUTER_NETWORK_PROJECT_STRUCT_DEFINE_H
