#ifndef __TCPSERVERCONTROLLER__
#define __TCPSERVERCONTROLLER__

#include <stdint.h>
#include <string>

class TcpNewConnectionAcceptor;
class TcpClientDbManager;
class TcpClientServiceManager; // forward referencing classes
class TcpClient;

class TcpServerController {
    private:
        TcpNewConnectionAcceptor *tcp_new_conn_acc;
        TcpClientDbManager *tcp_client_db_mgr;
        TcpClientServiceManager *tcp_client_svc_mgr;

    public:
        uint32_t ip_addr;
        uint16_t port_no;
        std::string name;

        /* Function pointers */
        void (*client_connected)(const TcpServerController*, const TcpClient*);
        void (*client_disconnected)(const TcpServerController*, const TcpClient*);
        void (*client_msg_recvd)(const TcpServerController*, const TcpClient*, unsigned char*, uint16_t);

        /* API to Register user application callback functions with server function pointers. */
        void SetServerNotifCallbacks(
            void (*client_connected)(const TcpServerController*, const TcpClient*),
            void (*client_disconnected)(const TcpServerController*, const TcpClient*),
            void (*client_msg_recvd)(const TcpServerController*, const TcpClient*, unsigned char*, uint16_t)
        );

        /* Constructors and Destructors */
        TcpServerController(std::string ip_addr,
            uint16_t port_no, std::string name);
        ~TcpServerController();

        void Start();
        void Stop();
        void ProcessNewClient(TcpClient *tcp_client);
        void Display();

};


#endif