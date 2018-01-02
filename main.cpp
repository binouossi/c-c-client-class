#include "client.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    printf("bout");
    client* nini=new client("nini");
    for(int i=0;i<25;i++)
    {
        nini->stringsender("suis la!");
        char* gi=nini->lire();
        cout<<gi<<endl;
        int hi;
        nini->receive_int(&hi);
//        nini->receive_int(hi);

        cout<<hi<<endl;
        nini->send_int(3);
    }

    printf("fin\n");
    return 0;
}
