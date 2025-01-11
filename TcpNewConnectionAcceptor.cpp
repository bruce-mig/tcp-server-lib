#include <sys/socket.h>
#include <netinet/in.h> // for IPPRORO_TCP
#include <memory.h>
#include "TcpServerController.h"
#include "TcpNewConnectionAcceptor.h"

TcpNewConnectionAcceptor::TcpNewConnectionAcceptor(TcpServerController *tcp_ctrl) {
    this->accept_fd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if (this->accept_fd < 0) {
        printf("Error: Could not create Accept FD\n");
        exit(0);
    }

    this->accept_new_conn_thread = (pthread_t *)calloc(1, sizeof(pthread_t));
    this->tcp_ctrl = tcp_ctrl;

}

TcpNewConnectionAcceptor::~TcpNewConnectionAcceptor(){}

void TcpNewConnectionAcceptor::StartTcpNewConnectionAcceptorThread(){}