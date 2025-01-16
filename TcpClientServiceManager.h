#ifndef __TcpClientServiceManager__
#define __TcpClientServiceManager__

class TcpServerController;
class TcpClient;

class TcpClientServiceManager {
    private:
        /* data */
    public:
        TcpServerController *tcp_ctrl;
        TcpClientServiceManager(TcpServerController*);
        ~TcpClientServiceManager();

        void StartTcpClientServiceManagerThread();
        void ClientFDStartListen(TcpClient *tcp_client);
 };



#endif