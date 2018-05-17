/*

   Class declaration for threaded socket server

   Adapted from http://web.eecs.utk.edu/~huangj/cs360/360/notes/Sockets/socketfun.c
 
   Copyright Simon D. Levy 2018

   MIT License
*/

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
