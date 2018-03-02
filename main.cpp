#include "client.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{


    client nini;

    char* msg="suis la! ah la!";
    cout<<msg<<endl;
    nini<<msg;
    char* rest=nini.getall();

    cout<<rest<<endl;

    double hi=5.256;
    cout<<hi<<endl;
    nini<<hi;
    nini>>hi;
    cout<<hi<<endl;
    nini.file_reader("/home/cani/test01");
    nini.file_sender("/home/cani/test01");

    printf("fin\n");

    return 0;
}
