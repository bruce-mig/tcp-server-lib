#include <iostream>
#include <assert.h>
#include "TcpServerController.h"
#include "TcpClientDBManager.h"
#include "TcpClientServiceManager.h"
#include "TcpNewConnectionAcceptor.h"
#include "network_utils.h"

TcpServerController::TcpServerController(
    std::string ip_addr, uint16_t port_no, std::string name) {

    this->ip_addr = network_convert_ip_p_to_n(ip_addr.c_str());
    this->port_no = port_no;
    this->name = name;

    this->tcp_new_conn_acc = new TcpNewConnectionAcceptor(this);
    this->tcp_client_db_mgr = new TcpClientDbManager(this);
    this->tcp_client_svc_mgr = new TcpClientServiceManager(this);
}

/** 
 * Start the CAS thread
 * Start the DRS thread
 * Initialize the DBMS
*/
void TcpServerController::Start() {

    this->tcp_new_conn_acc->StartTcpNewConnectionAcceptorThread();
    this->tcp_client_svc_mgr->StartTcpClientServiceManagerThread();
    this->tcp_client_db_mgr->StartTcpClientDbMgrInit();

    std::cout<<"TCP Server is UP and RUNNING ["<< network_convert_ip_n_to_p(this->ip_addr,0)<<":"<<this->port_no<<"]\n";
    std::cout<< "OK\n";

}

void TcpServerController::ProcessNewClient(TcpClient *tcp_client) {
    
    this->tcp_client_db_mgr->AddClientToDB(tcp_client);
    this->tcp_client_svc_mgr->ClientFDStartListen(tcp_client);

}

void TcpServerController::SetServerNotifCallbacks(
            void (*client_connected)(const TcpServerController*, const TcpClient*),
            void (*client_disconnected)(const TcpServerController*, const TcpClient*),
            void (*client_msg_recvd)(const TcpServerController*, const TcpClient*, unsigned char*, uint16_t)){
    
    this->client_connected = client_connected;
    this->client_disconnected = client_disconnected;
    this->client_msg_recvd = client_msg_recvd;

}

void TcpServerController::Display(){
    std::cout << "Server Name: " << this->name.c_str() << "\n";
    std::cout << "Listening on: " << network_convert_ip_n_to_p(this->ip_addr,0) << ":"
              << this->port_no << "\n";

    this->tcp_client_db_mgr->DisplayClientDb();
}