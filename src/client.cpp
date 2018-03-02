#include "client.h"

client::client()
{
 //   this->user=user;

      if((this->sock = socket(AF_INET, SOCK_STREAM, 0))< 0)
        {
          perror("Error : Could not create socket \n");
        }
      this->serv_addr.sin_family = AF_INET;
      this->serv_addr.sin_port = htons(PORT);
      serv_addr.sin_addr.s_addr = inet_addr( ADDR);

/* to read address from file
      const char* addr;
      ADDR=this->getaddr(CONFIG).c_str();
      this->serv_addr.sin_addr.s_addr = inet_addr(addr);*/

      if(connect(this->sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
        {
          perror("Error : Connect Failed");
          exit(1);
        }
}

string client::get_addr(char* path)
{
    std::ifstream monFlux(path);
    if(monFlux)
    {
        std::string ligne;
        std::getline(monFlux, ligne);
        return ligne;
    }
    else
    {
        fprintf(stderr,"ERREUR: Impossible d'ouvrir le fichier de configuration.");
        exit(1);
    }
}

char* client::str_reader()
{

    int n = NULL;
    this->int_reader(&n);

    if(n==0||n==NULL)
    {
        return NULL;
    }

//    std::cout<<n<<std::endl;
    char lu[n];

//    lu=(char*)std::realloc(lu,(n*sizeof(char)));

    if(lu==NULL)
    {
        fprintf(OUTPUT,"Allocation error" , strerror(errno));

        return NULL;
    }

    lu[0]='\0';

//    int a=this->readLine(lu,n);

    int a=recv(this->sock,lu,n,0);

      if( a < n-1)
      {
          fprintf(OUTPUT,"Read Error" , strerror(errno));

        return NULL;
      }

      lu[n]='\0';
      return lu;
}

char* client::str_reader(int n)
{

    char* lu=NULL;

    if(n==0||n==NULL)
    {
        return NULL;
    }

    lu=(char*)std::realloc(lu,(n*sizeof(char)));

    if(lu==NULL)
    {
        fprintf(OUTPUT,"Allocation error" , strerror(errno));

        return NULL;
    }

    lu[0]='\0';

//    int a=this->readLine(lu,n);

    int a=recv(this->sock,lu,n,0);


      if( a < n-1)
      {

          fprintf(OUTPUT,"Read Error" , strerror(errno));

        return NULL;
      }

      lu[n]='\0';
      return lu;
}

int client::str_sender(char* fi)
{

    int a=strlen(fi);

    this->int_sender(strlen(fi));

    int n=send(this->sock,fi,a,0);

    if(n<0)
        perror("Error while sending");
    return n;
}

int client::str_sender(char* fi,int size)
{
    this->int_sender(size);

    int n=send( this->sock , fi , size, 0 );

    if(n<0)
        perror("Error while sending");
    return n;
}

int client::int_reader(int* num)
{
    char buf[10] = "";

    int rest=recv( this->sock , buf , sizeof buf , 0 );

    sscanf( buf , "%d" , num );

    return rest;
}

int client::int_sender(int num)
{
    char buf[10] = "";

    sprintf( buf , "%d" , num );

    int rest=send( this->sock , buf , sizeof buf , 0 );

    return rest;
}

int client::file_sender(char* path)
{

    fstream file(path);

        stringstream hi;
    if(file.is_open())
    {

        hi<<file.rdbuf();

        file.close();
    }
    else
        return -2;
string kol=hi.str();

char* bi=const_cast<char*>(kol.c_str());

    if(this->str_sender(bi)<0)
        return -1;

     return 0;
}

bool client::file_reader(char* destination)
{

    char*gi=this->getall();

    ofstream file(destination);

    if(!file.is_open())
    {
        return false;
    }

    file<<gi;

    return true;

}

char* client::getall()
{
    int size=NULL;

    this->int_reader(&size);

    if(size<=0)
    {
        return NULL;
    }

    char* data= this->str_reader(size);

    return data;
}

client::~client()
{
    if(close(this->sock)==0)
    {
        fprintf(OUTPUT,"connection ended\n" , strerror(errno));

    }

}


