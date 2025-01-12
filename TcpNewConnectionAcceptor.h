#ifndef __TcpNewConnectionAcceptor__
#define __TcpNewConnectionAcceptor__

#include <pthread.h>

class TcpServerController;

/**
 * New connections are accepted using 'accept()' sys call
 * We need to create an 'accept_fd' file descriptor using 'socket()'
 */
class TcpNewConnectionAcceptor {
    private:
    int accept_fd;
    pthread_t *accept_new_conn_thread;

    public:
        TcpServerController *tcp_ctrl;

        TcpNewConnectionAcceptor(TcpServerController *);
        ~TcpNewConnectionAcceptor();

        void StartTcpNewConnectionAcceptorThread();
        void StartTcpNewConnectionAcceptorThreadIntenal();
};

#endif