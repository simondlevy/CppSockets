class ThreadedSocketServer {

    private:

       void * _support; 

    public:

        ThreadedSocketServer(int port) ;

        void start(void);

        void stop(void);

        bool connected(void);

        int send(char * buf, int len);

        int recv(char * buf, int len);
};
