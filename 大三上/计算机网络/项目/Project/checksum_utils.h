//
// Created by 任齐轩 on 2022/12/3.
//

#ifndef COMPUTER_NETWORK_PROJECT_CHECKSUM_H
#define COMPUTER_NETWORK_PROJECT_CHECKSUM_H

// calculate checksum
unsigned short Checksum(unsigned char* buffer, unsigned short size){
    unsigned int sum = 0;
    unsigned short cksum;
    unsigned char lower,higher;
    unsigned short temp;
    if(size%2 == 1) {
        higher= buffer[size-1];
        lower = 0x00;
        temp = higher;
        temp = (temp << 8) + lower;
        sum += temp;
        size--;
    }
    while(size > 1) {
        lower = buffer[size-1];
        higher = buffer[size - 2];
        temp = higher;
        temp = (temp << 8) + lower;
        sum += temp;
        size -= 2;
    }

    cksum = (sum >> 16) + (sum & 0xffff);
    cksum = ~cksum;
    cksum = (cksum>>8) + (cksum << 8);
    return cksum;
}

// crc check
unsigned int crc32_table[256];

void make_crc32_table() {
    unsigned int c;
    int i = 0;
    int bit = 0;

    for (i = 0; i < 256; i++) {
        c = (unsigned int)i;
        for (bit = 0; bit < 8; bit++){
            if (c & 1) {
                c = (c >> 1) ^ (0xEDB88320);
            }
            else {
                c = c >> 1;
            }
        }
        crc32_table[i] = c;
    }
}

unsigned int crc32(unsigned char *string, unsigned int size) {
    make_crc32_table();
    unsigned int crc = 0xffffffff;
    while (size--)
        crc = (crc >> 8) ^ (crc32_table[(crc ^ *string++) & 0xff]);
    return crc;
}

#endif //COMPUTER_NETWORK_PROJECT_CHECKSUM_H
