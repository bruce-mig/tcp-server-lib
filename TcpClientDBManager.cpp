#include "TcpServerController.h"
#include "TcpClientDBManager.h"
#include "TcpClient.h"

TcpClientDbManager::TcpClientDbManager(TcpServerController *tcp_ctrl) {
    this->tcp_ctrl = tcp_ctrl;
}

TcpClientDbManager::~TcpClientDbManager(){}

void TcpClientDbManager::StartTcpClientDbMgrInit(){}

void TcpClientDbManager::AddClientToDB(TcpClient *tcp_client) {
   
    this->tcp_client_db.push_back(tcp_client);
    
}