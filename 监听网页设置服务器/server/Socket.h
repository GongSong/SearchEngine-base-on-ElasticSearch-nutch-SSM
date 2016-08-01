#ifndef SOCKET_H_INCLUDED
#define SOCKET_H_INCLUDED

//#include "commen.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
using namespace std;

#define MESSAGEMAX 1024

/*���ݰ�����*/
typedef struct _Packet
{
    unsigned int    msgLen;     //���ݲ��ֵĳ���(�����ֽ���)
    char            text[1024]; //���ĵ����ݲ���
}Packet;


/*---------------���ඨ��----------------*/
class TCPSocket
{
public:
    TCPSocket();
    ~TCPSocket();

    bool create();
    bool bind(unsigned short int port, const char *ip = NULL);
    bool reuseaddr();    
    bool setNonBlocking(bool flag);  //flag: true=SetNonBlock, false=SetBlock;
    int  getfd();
    bool isValid();    
    bool close(); 
    
    /**ע��: TCPSocket���ಢû��send/receive����**/
    int read(void *buf, int count);
    int write(const void *buf, int count);
    int readn(int fd, void *buf, int count);
    int writen(int fd, const void *buf, int count);

//protected:
    int m_sockfd;
    struct sockaddr_in server_addr; 
    struct sockaddr_in client_addr; //���ڷ�����������
};


/** --------------������TCP Client ----------------**/
class TCPClient : public TCPSocket
{        
public:
    TCPClient(unsigned short int port, const char *ip);
    TCPClient();
    TCPClient(int clientfd);
    ~TCPClient();

    bool connect(unsigned short int port, const char *ip); 
    int send(const std::string &message);
    int receive(std::string &message);

    
    int read(void *buf, int count);
    void write(const void *buf, int count);
    int write(const char *msg);
    
private:

};


/** --------------------������ TCP Server ----------------- **/
class TCPServer : public TCPSocket
{
public:
    TCPServer(unsigned short int port, const char *ip = NULL, int backlog = SOMAXCONN);
    TCPServer();
    ~TCPServer(); 

    bool listen(int backlog = SOMAXCONN);
    int accept();  //�����½����ӵ�������
    int send(int fd,const std::string &message);
    int receive(int fd, std::string &message);
    
    TCPSocket m_newSocket;  //�����µĿͻ�������������
};


#endif // SOCKET_H_INCLUDED

