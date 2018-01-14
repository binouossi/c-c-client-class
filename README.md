# c/c++ socket client class

# Author
**NAME: _TACOLODJOU Emmanuel_**
**Email: _tacolodjounini@gmail.com_**

# Presentation
This is the client part of a c/c++ library make, to help the develloppers to create and use socket connection. it contain some a **class** to initiate conmunication and there methods to send and receve data, other network

# usage
This class name is **client** and there methods are:

* ## client()
It create the socket, and connect it to the server. The server address can be set up on **client.h** ADDR deefined variable. You can also read the server address from a file. For this, you can uncomment the lines about this on the constructor. if there are not only the address in this file, you can rewrite the **getaddr()** method, to customis it for you file.The PORT defined variable, is used to set up the connection port.

* ##  string get_addr(char* path)
This method take the path of a file as parameter and write the server address from this file.


* ## char* str_reader()
As it name, it allow you to read a string, comming from socket, and return it.

* ## int str_sender(char *fi)
As it name, it allow you to send a string, other the socket.

* ## int IplImg_sender(IplImage* im)
This method send the **cv images** other the network. It use **open_cv** library to work. So, if you don't need to use it, please comment/remove the code about those methods and the call of library.
then, it return the number of bytes sended.

* ## IplImage* IplImg_reader()
This is used to receve **cv image** from network. it return a poimter to the receved image if succesfull done, and **_NULL_** pointer, if error.

* ## int int_reader(int *num)
This read the int comming from network socket, and put it in int pointer passed as parmeter. It return the nomber of byte realy sended.

* ## int int_sender(int num)
This send the int passed as parameter, other the network. It return the number of byte realy sended.

* ## int file_reader(char* destination)
This method read a file comming from network and put it in this file given as parameter.

* ## int file_sender(char* path)
This method send a file other network and put it in this file given as parameter.

# Licence

This library, is offert as **LGPL Licence**. Than, it's free usefull and shareless. You can sell a software maked with the library.

## Invitation

I invite every body, to help me, in this class development, sendind the feedback, and perform the better algorithms.