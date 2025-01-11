#include "TcpNewConnectionAcceptor.h"

TcpNewConnectionAcceptor::TcpNewConnectionAcceptor(TcpServerController *tcp_ctrl) {
    this->tcp_ctrl = tcp_ctrl;
}

TcpNewConnectionAcceptor::~TcpNewConnectionAcceptor(){}