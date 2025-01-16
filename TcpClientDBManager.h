#ifndef __TcpClientDbManager__
#define __TcpClientDbManager__

#include <list>

class TcpClient;
class TcpServerController;

class TcpClientDbManager {
    private:
        std::list<TcpClient*> tcp_client_db;

    public:
        TcpServerController *tcp_ctrl;

        TcpClientDbManager(TcpServerController*);
        ~TcpClientDbManager();

        void StartTcpClientDbMgrInit();
        void AddClientToDB(TcpClient *tcp_client);
        
};

#endif