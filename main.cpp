#include "client.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    client* nini=new client();
    for(int i=0;i<25;i++)
    {
        nini->str_sender("suis la!");

        char* gi=nini->str_reader();
        cout<<gi<<endl;
        int hi;
        nini->int_reader(&hi);    printf("bout\n");

//        nini->receive_int(hi);

        cout<<hi<<endl;
        nini->int_sender(3);
    }

    printf("fin\n");
    return 0;
}
