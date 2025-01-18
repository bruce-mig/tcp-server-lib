#include "TcpClient.h"
#include <iostream>
#include "network_utils.h"
#include <arpa/inet.h>

TcpClient::TcpClient(uint32_t ip_addr, uint16_t port_no)  {
    this->ip_addr = ip_addr;
    this->port_no = port_no;
}

void TcpClient::Display() {
    std::cout << "TCP Client: ["<< network_convert_ip_n_to_p(htonl(this->ip_addr),0) << ":"
              << htons(this->port_no) <<"]\n";
}