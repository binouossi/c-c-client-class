#include "client.h"

client::client()
{
 //   this->user=user;

      if((this->sock = socket(AF_INET, SOCK_STREAM, 0))< 0)
        {
          perror("Error : Could not create socket \n");
        }
      this->serv_addr.sin_family = AF_INET;
      this->serv_addr.sin_port = htons(5000);
      serv_addr.sin_addr.s_addr = inet_addr( ADDR);

/* to read address from file
      const char* addr;
      ADDR=this->getaddr("/etc/Face_client").c_str();
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

    this->lu=(char*)std::realloc(this->lu,(n*sizeof(char)));

    if(this->lu==NULL)
    {
        std::cout<<"Allocation error"<<std::endl;
        return NULL;
    }

    this->lu[0]='\0';

    int a=this->readLine(this->lu,n);

      if( a < n-1)
      {
        cout<<"Read Error"<<endl;
        return NULL;
      }

      this->lu[n]='\0';
      return this->lu;
}

int client::str_sender(char fi[])
{

    int a=strlen(fi);

    this->int_sender(strlen(fi));

    int n=write(this->sock,fi,std::strlen(fi));

    if(n<0)
        perror("Error while sending");
    return n;
}

IplImage* client::IplImg_reader()
{
    int H=NULL,W=NULL;
    this->int_reader(&H);
    this->int_reader(&W);

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

int client::IplImg_sender(IplImage* im)
{
    this->int_sender(im->height);

    this->int_sender(im->width);

    int bytes=0;
    cv::Mat frame=cv::Mat(im,true);
    frame = (frame.reshape(0,1)); // to make it continuous

    int  imgSize = frame.total()*frame.elemSize();

    // Send data here
    bytes = send(this->sock, frame.data, imgSize, 0);

    return bytes;
}


/*IplImage* client::get_im()
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
*/
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

int client::int_reader(int* num)
{
    char buf[10] = "";

    int rest=recv( this->sock , buf , sizeof buf , 0 );

    sscanf( buf , "%d" , num );

//    recv(this->sock, (char*)num, sizeof(int), NULL);

    return rest;
}

int client::int_sender(int num)
{
    char buf[10] = "";

    sprintf( buf , "%d" , num );

    int rest=send( this->sock , buf , sizeof buf , 0 );

    //recv(this->sock, (char*)num, sizeof(int), NULL);

    return rest;
}

int client::file_sender(char* path)
{
    ssize_t len;
    int fd;
    int sent_bytes = 0;
    char file_size[256];
    struct stat file_stat;
    int offset;
    int remain_data;

    fd = open(path, O_RDONLY);

    if (fd == -1)
    {
        fprintf(OUTPUT, "Error opening file --> %s", strerror(errno));
        return -1;
     }

            /* Get file stats */
     if (fstat(fd, &file_stat) < 0)
     {
            fprintf(stderr, "Error fstat --> %s", strerror(errno));
            return -1;
     }

     fprintf(OUTPUT, "File Size: \n%d bytes\n", file_stat.st_size);

     sprintf(file_size, "%d", file_stat.st_size);

     len = send(this->sock, file_size, sizeof(file_size), 0);
     if (len < 0)
     {
        fprintf(OUTPUT, "Error on sending greetings --> %s", strerror(errno));
        return -1;
     }

     fprintf(stdout, "Server sent %d bytes for the size\n", len);

     offset = 0;
     remain_data = file_stat.st_size;
            /* Sending file data */
     while (((sent_bytes = sendfile(this->sock, fd, (off_t *)&offset, BUFSIZ)) > 0) && (remain_data > 0))
     {
        fprintf(OUTPUT, "1. Server sent %d bytes from file's data, offset is now : %d and remaining data = %d\n", sent_bytes, offset, remain_data);
        remain_data -= sent_bytes;
        fprintf(OUTPUT, "2. Server sent %d bytes from file's data, offset is now : %d and remaining data = %d\n", sent_bytes, offset, remain_data);
     }

     return 0;

}

int client::file_reader(char* destination)
{
    size_t len;
    char buffer[BUFSIZ];
    int file_size;
   int remain_data = 0;
   FILE* received_file ;

    recv(this->sock, buffer, BUFSIZ, 0);
    file_size = atoi(buffer);

     received_file=fopen(destination, "w");

     if (received_file == NULL)
     {
        fprintf(OUTPUT, "Failed to open file foo --> %s\n", strerror(errno));
        return -1;
     }

     remain_data = file_size;

     while (((len = recv(this->sock, buffer, BUFSIZ, 0)) > 0) && (remain_data > 0))
    {
        fwrite(buffer, sizeof(char), len, received_file);
        remain_data -= len;
  //      fprintf(stdout, "Receive %d bytes and we hope :- %d bytes\n", len, remain_data);
    }
    fclose(received_file);

     return 0;
}

OM_uint32 client::token_reader(gss_buffer_t tok)
{
    int ret, len;
    ret = this->int_reader(&len);

    if (ret < 0)
    {
        perror("reading token length");
        return -1;
    } else if (ret != 4)
    {
        if (OUTPUT)
            fprintf(OUTPUT,"reading token length: %d of %d bytes read\n", ret, 4);
        return -1;
    }
    tok->length = len;
    tok->value = (char *) malloc(tok->length);
    if (tok->value == NULL)
    {
        if (OUTPUT)
        fprintf(OUTPUT,"Out of memory allocating token data\n");
        return -1;
    }
     tok->value= this->str_reader();
    if (tok->value==NULL)
    {
        perror("reading token data");
        free(tok->value);
        return -1;
    } else if (ret != tok->length)
    {
        fprintf(OUTPUT, "sending token data: %d of %d bytes written\n", ret, tok->length);
        free(tok->value);
        return -1;
    }
    return 0;
}

OM_uint32 client::token_sender(gss_buffer_t tok)
{
    int len, ret;
    len = htonl((OM_uint32)tok->length);
    ret = this->int_sender((OM_uint32)tok->length);
    if (ret < 0)
    {
        perror("sending token length");
        return -1;
    } else if (ret != 4)
    {
        if (OUTPUT)
            fprintf(OUTPUT, "sending token length: %d of %d bytes written\n", ret, 4);
        return -1;
    }
    ret = str_sender((char*)tok->value);
    if (ret < 0)
    {
        perror("sending token data");
        return -1;
    } else if (ret != tok->length)
    {
    if (OUTPUT)
        fprintf(OUTPUT, "sending token data: %d of %d bytes written\n", ret, tok->length);
        return -1;
    }
    return 0;
}
















client::~client()
{
    if(close(this->sock)==0)
    {
        std::cout<<"connection ended"<<std::endl;
    }

    free(this->lu);
}


