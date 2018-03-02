#ifndef CLIENT_H
#define CLIENT_H


#define ADDR "127.0.0.1"
#define PORT 5000
#define CONFIG "/etc/Face_client" //just for who those want to use a config file to manage server's information
#define OUTPUT stderr

#include <fstream>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <sstream>

#include "function.h"

using namespace std;

class client
{
public:
    client();

    ~client();

    char* getall();

    bool file_reader(char* destination);

    int file_sender(char* path);

    template <typename Type>
    bool operator<<(Type &data);

    template <typename Type>
    stringstream& operator>>(Type &data);

    string get_addr(char* path);

private:
    int sock;

protected:

    char* str_reader();

    char* str_reader(int size);
    
    int int_reader(int *num);

    int int_sender(int num);

    int str_sender(char *fi);

    struct sockaddr_in serv_addr;

    int str_sender(char* fi, int size);
};

template <typename Type>
stringstream& client::operator>> (Type& don)
{
    int size=NULL;

    stringstream nin;

    nin.flush();

    this->int_reader(&size);

    char* data= this->str_reader(size);

    nin<<data;

    nin>>don;

    return nin;
}

template <typename Type>
bool client::operator<<(Type &data)
{
    stringstream nout;

    nout<<data;

    char* buf=const_cast<char*>(nout.str().c_str());

    int size=strlen(buf);

    if(this->str_sender(buf,size)<0)
    {
        return false;
    }

    return true;
}

#endif CLIENT_H
