This repository contains C++ classes and example code for using sockets on
Linux and Windows.  The classes hide the details that you don't need to worry about
for many applications, providing a simple API for rapid prototyping; for example:

```
    TcpSocketClient client("localhost", 5000);

    client.openConnection();

    char message[100] = "Hello from client!";

    client.sendData(message, strlen(message));

    client.receiveData(message, 100);
```
 
The class header and implementation code is in the <b>sockets</b> folder, which
you can copy/paste into your own project.
