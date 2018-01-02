#include "client.h"

client::client(char* user)
{
    this->user=user;

      if((this->sock = socket(AF_INET, SOCK_STREAM, 0))< 0)
        {
          perror("Error : Could not create socket \n");
        }
      this->serv_addr.sin_family = AF_INET;
      this->serv_addr.sin_port = htons(5000);
      serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

/* to read address from file
      const char* addr;
      addr=this->getaddr("/etc/Face_client").c_str();
      this->serv_addr.sin_addr.s_addr = inet_addr(addr);*/

      if(connect(this->sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
        {
          perror("Error : Connect Failed");
          exit(1);
        }
}

string client::getaddr(char* path)
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

char* client::lire()
{
    int n = NULL;
    this->receive_int(&n);
//    this->receive_int(n);
    if(n==0||n==NULL)
    {
        return NULL;
    }

//    std::cout<<n<<std::endl;

    this->lu=(char*)std::realloc(this->lu,(n*sizeof(char)));

    if(this->lu==NULL)
    {
        perror("Memiorie allocation error, for socket reader");
        return NULL;
    }

    this->lu[0]='\0';

    int a=this->readLine(this->lu,n);

      if( a < n-1)
      {
        fprintf(stderr,"Read Error");
        return NULL;
      }

      this->lu[n]='\0';
      return this->lu;
}

int client::stringsender(char fi[])
{

    int a=strlen(fi);

    this->send_int(a);

    int n=write(this->sock,fi,std::strlen(fi));

    if(n<0)
        perror("Error while sending");
    return n;
}

IplImage* client::IplImageRecv()
{
    int H=NULL,W=NULL;
    this->receive_int(&H);
    this->receive_int(&W);

/*        this->receive_int(H);
        this->receive_int(W);*/

    if(W==0||W==NULL)
        W=IMAGE_WIDTH;

    if(H==0||H==NULL)
      H=IMAGE_HEIGHT;

    cv::Mat  img = cv::Mat::zeros(H,W, CV_8UC3);

       int  imgSize = img.total()*img.elemSize();
       uchar sockData[imgSize];

      //Receive data here
       int bytes=0;

       for (int i = 0; i < imgSize; i = i + bytes) {
       if ((bytes = recv(this->sock, sockData +i, imgSize  - i, 0)) == -1)
       {
           perror("Image reception failed");
           return NULL;
        }
       }

     int ptr=0;
     for (int i = 0;  i < img.rows; i++)
     {
      for (int j = 0; j < img.cols; j++)
      {
       img.at<cv::Vec3b>(i,j) = cv::Vec3b(sockData[ptr+ 0],sockData[ptr+1],sockData[ptr+2]);
       ptr=ptr+3;
      }
     }

     IplImage* im= cvCreateImage(cvSize(img.cols, img.rows), 8, 3);

     IplImage tmp=img;

     cvCopy(&tmp,im);

     return im;
}

int client::IplImagesender(IplImage* im)
{
    this->send_int(im->height);

    this->send_int(im->width);

    int bytes=0;
    cv::Mat frame=cv::Mat(im,true);
    frame = (frame.reshape(0,1)); // to make it continuous

    int  imgSize = frame.total()*frame.elemSize();

    // Send data here
    bytes = send(this->sock, frame.data, imgSize, 0);

    return bytes;
}

client::~client()
{
    if(close(this->sock)==0)
    {
        std::cout<<"connection ended"<<std::endl;
    }

    free(this->lu);
}

IplImage* client::get_im()
{
    IplImage* hi;
    CvCapture* capture =cvCreateCameraCapture(-1);
    if (!capture)
    {
       perror("Error. Cannot capture.");
    }
    hi = cvQueryFrame(capture);
    if(!hi)
    {
        perror("Error. Cannot get the frame.");
    }

    return hi;
}

int client::receive_int(int* num)
{
    char buf[10] = "";

    recv( sock , buf , sizeof buf , 0 );

    sscanf( buf , "%d" , num );

//    recv(this->sock, (char*)num, sizeof(int), NULL);

    return 0;
}

int client::send_int(int num)
{
    char buf[10] = "";

    sprintf( buf , "%d" , num );

    send( this->sock , buf , sizeof buf , 0 );

    //recv(this->sock, (char*)num, sizeof(int), NULL);

    return 0;
}

int client::readLine(char data[],int maxlen)
{
   size_t len = 0;
   while (len < maxlen)
   {
      char c;
      int ret = read(this->sock, &c, 1);
      if (ret < 0)
      {
          data[len] = 0;
          return len; // EOF reached
      }
      if (c == '\n')
      {
          data[len] = 0;
          return -2; // EOF reached
      }
      data[len++] = c;
   }
}
