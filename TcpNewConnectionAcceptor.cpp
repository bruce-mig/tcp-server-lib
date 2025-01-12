#include <sys/socket.h>
#include <netinet/in.h> // for IPPRORO_TCP
#include <memory.h>
#include <iostream>
#include "TcpServerController.h"
#include "TcpNewConnectionAcceptor.h"
#include "network_utils.h"

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

static void* tcp_listen_for_new_connections(void *arg){
	TcpNewConnectionAcceptor *tcp_new_conn_acc = (TcpNewConnectionAcceptor *)arg;

	tcp_new_conn_acc->StartTcpNewConnectionAcceptorThreadIntenal();
	return NULL;
}

/* Start thread */
void TcpNewConnectionAcceptor::StartTcpNewConnectionAcceptorThread(){

	if (pthread_create(this->accept_new_conn_thread, NULL, tcp_listen_for_new_connections,(void *)this)) {
		std::cout << __FUNCTION__ << "() Thread Creation failed, error = " << errno << "\n";
		exit(0);
	}

	std::cout << "Service Started: TcpNewConnectionAcceptorThread\n";

}

/**
  * 1. Create an infinite loop
 *  2. Invoke 'accept()' to accept new connections
 *  3. Notify the application for new connections
 */
void TcpNewConnectionAcceptor::StartTcpNewConnectionAcceptorThreadIntenal(){
    
	int opt = 1;
	struct sockaddr_in server_addr;

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(this->tcp_ctrl->port_no);
	server_addr.sin_addr.s_addr = htonl(this->tcp_ctrl->ip_addr);

	if(setsockopt(this->accept_fd, SOL_SOCKET,
					SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0) {
			std::cout << "sectsockopt Failed\n";
			exit(0);
		}

	if(setsockopt(this->accept_fd, SOL_SOCKET,
					SO_REUSEPORT, (char *)&opt, sizeof(opt)) < 0) {
			std::cout << "sectsockopt Failed\n";
			exit(0);
		}

	/* Binding socket*/
	if(bind(this->accept_fd, (struct sockaddr *)&server_addr,
					sizeof(struct sockaddr)) == -1) {
			printf("Error: Acceptor socket bind failed [%s(0x%x), %d], error = %d\n",
				network_convert_ip_n_to_p(this->tcp_ctrl->ip_addr, 0),
				this->tcp_ctrl->ip_addr,
				this->tcp_ctrl->port_no, errno);
			exit(0);
		}

	if(listen(this->accept_fd,5) < 0) {
		std::cout << "listen failed \n";
		exit(0);
	}

	struct sockaddr_in client_addr;
	socklen_t addr_len = sizeof(client_addr);
	int comm_sock_fd;

	while(true) {
		comm_sock_fd = accept(this->accept_fd,
					(struct sockaddr *)&client_addr, &addr_len);
		if(comm_sock_fd < 0) {
			std::cout << "Error in Accepting New Connections \n";
			continue;
		}

		std::cout << "Connection Accepted from Client [" 
					 << network_convert_ip_n_to_p(client_addr.sin_addr.s_addr, 0) << ":" 
					 << htons(client_addr.sin_port) << "]\n";
				;
	}

}