#ifndef CLIENT_H
#define CLIENT_H


//a supprimer pour eviter les redefinition
#define IMAGE_SIZE 230400
#define IMAGE_WIDTH 320
#define IMAGE_HEIGHT 240\

#define ADDR "127.0.0.1"

//standar
#include <fstream>
#include <unistd.h>
#include <arpa/inet.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sendfile.h>

#include "function.h"

//opencv
#include <opencv/cv.h>
#include <opencv/highgui.h>

// gssapi

#include <gss.h>

using namespace std;

class client
{
public:
    client();
    ~client();

    char* str_reader();
    int str_sender(char *fi);

    int IplImg_sender(IplImage* im);
    IplImage* IplImg_reader();

//    IplImage* get_im();
    int int_reader(int *num);
    int int_sender(int num);


    int file_reader(char* destination);
    int file_sender(char* path);

    OM_uint32 token_reader(gss_buffer_t tok);
    OM_uint32 token_sender(gss_buffer_t tok);

private:
    int sock;
    char IplsendBuff[sizeof(IplImage)];
//    char recvBuff[1024];
//    char* user;
    struct sockaddr_in serv_addr;
    char* lu=NULL;
    string get_addr(char* path);
    int readLine(char data[],int maxlen);
};

#endif CLIENT_H
