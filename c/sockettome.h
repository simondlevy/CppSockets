// Adapted from http://web.eecs.utk.edu/~plank/plank/classes/cs360/360/notes/Sockets/sockettome.h

#pragma once

extern int serve_socket(int port);
extern int accept_connection(int s);
extern int request_connection(char *hn, int port);
