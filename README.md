This repository contains header-only C++ classes and example code for using sockets on
Linux and Windows.  The classes hide the details that you don't need to worry about
for many applications, providing a simple API for rapid prototyping. For example:

```
    TcpSocketClient client("localhost", 5000);

    client.openConnection();

    char message[100] = "Hello from client!";

    client.sendData(message, strlen(message));

    client.receiveData(message, 100);
```
 
The class header code is in the <b>sockets</b> folder, which you can copy/paste
into your own project.

## Testing on Windows

```
% git clone -b test_windows https://github.com/simondlevy/CppSockets
% cd CppSockets
% git clone https://github.com/simondlevy/CppSockets sockets

```

Then open the <b>UdpClient</b> and <b>UdpServer</b> projects, and run them in Release mode.

## Testing on Linux

```
% git clone -b test_linux https://github.com/simondlevy/CppSockets
% cd CppSockets
% git clone https://github.com/simondlevy/CppSockets sockets
% make
```
Then you can run one of the two pairs of resulting test programs (<b>udpsever</b>/<b>udpclient</b>, 
<b>tcpsever</b>/<b>tcpclient</b>).

