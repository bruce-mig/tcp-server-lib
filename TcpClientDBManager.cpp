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

void TcpClientDbManager::DisplayClientDb() {
    std::list<TcpClient*>::iterator it;
    TcpClient *tcp_client;

    for(it = this->tcp_client_db.begin();it != this->tcp_client_db.end();++it) {
        tcp_client = *it;
        tcp_client->Display();
    }
}