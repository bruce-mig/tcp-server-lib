/*
 * =====================================================================================
 *
 *       Filename:  network_utils.c
 *
 *    Description: This file contains routines to work with Network sockets programs 
 *
 *        Version:  1.0
 *        Created:  11/01/2025 05:24:57 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  BRUCE MIGERI (), bmigeri@gmail.com
 *
 * =====================================================================================
 */

#include <stdint.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <memory.h>
#include "network_utils.h"

char * network_convert_ip_n_to_p(uint32_t ip_addr,
                    char *output_buffer){

    char *out = NULL;
    static char str_ip[16];
    out = !output_buffer ? str_ip : output_buffer;
    memset(out, 0, 16);
    ip_addr = htonl(ip_addr);
    inet_ntop(AF_INET, &ip_addr, out, 16);
    out[15] = '\0';
    return out;
}

uint32_t network_covert_ip_p_to_n(const char *ip_addr){

    uint32_t binary_prefix = 0;
    inet_pton(AF_INET, ip_addr, &binary_prefix);
    binary_prefix = htonl(binary_prefix);
    return binary_prefix;
}
