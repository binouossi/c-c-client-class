#ifndef CLIENT_H
#define CLIENT_H


//a supprimer pour eviter les redefinition
#define IMAGE_SIZE 230400
#define IMAGE_WIDTH 320
#define IMAGE_HEIGHT 240

//standar
#include <fstream>
#include <unistd.h>

#include <arpa/inet.h>

//opencv
#include <opencv/cv.h>
#include <opencv/highgui.h>

using namespace std;

class client
{
public:
    client(char* user);
    ~client();
    char* lire();
    int IplImagesender(IplImage* im);
    IplImage* IplImageRecv();
    int stringsender(char *fi);
    IplImage* get_im();
    int receive_int(int *num);
    int send_int(int num);


private:
    int sock;
    char IplsendBuff[sizeof(IplImage)];
    char recvBuff[1024];
    char* user;
    struct sockaddr_in serv_addr;
    char* lu;
    string getaddr(char* path);
    int readLine(char data[],int maxlen);
};

#endif  CLIENT_H
