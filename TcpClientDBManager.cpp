#include "TcpServerController.h"
#include "TcpClientDBManager.h"

TcpClientDbManager::TcpClientDbManager(TcpServerController *tcp_ctrl) {
    this->tcp_ctrl = tcp_ctrl;
}

TcpClientDbManager::~TcpClientDbManager(){}

void TcpClientDbManager::StartTcpClientDbMgrInit(){}