# c/c++ socket client class

# Presentation
This is the client part of a c/c++ library, which makes easier the use the socket connection. It contains a **class** to initiate communication, methods and operators to send and receive data, over a network.

# Usage
This class is named **client** and the methods are as follows:

## Public methods

- client()
It creates the socket and connects it to the socket server. The server address and port can be configured on ``client.h`` using the preprocessing ADDR and PORT variables. You can also read the server address from a file. For that, you can uncomment the lines about it in the constructor. If there is enough data in this file, you can customize the ``getaddr()`` method to fit your file.

- string get_addr(char* path)
This method takes the path of a file parameter and read the server address from this file. In the next version, the port number should also be considered


- bool file_reader(char* destination)
As it's name implies, it allows you to receive the contents of a file, from socket, and write it to a file whose name has been passed with the destination parameter. If the file does not exist, it is created. The function returns a boolean. 

- int file_sender(char *foo)
It allows you to send the contents of a file, through the socket. It takes in parameter the path of the file. It returns -2 if the file does not exist and -1 if the send fails and 0 if all goes well.

- char* getall()
This method allows you to receive a string from the network. It returns the string received as ``char *`` if all is well, and NULL on error.

## Operators

- bool operator<<(Type &data)
This operator is similar to the standard output stream operator. It allows you to send primary data types on the network. You could watch it as a network output stream. It only handles the main type, and strings like ``char *``

- stringstream& operator>>(Type &data);
This operator is similar to the standard input stream operator. It allows you to receive data from the network. It only handles the primary types and can not receive a string like ``char*``. To obtain strings from the network, you must use the ``getall()`` function.

# Version (1.0.0)
This is the beta version
# License

This library, is offer as **LGPL License**. Than, it's free for personal and commercial uses.
<!--# Author
**name: *Emmanuel TACOLODJOU* **
**Email: _tacolodjounini@gmail.com_**

Je ne sais pas si tu l'as remarqué mais en géneral on s'en fout de l'auteur.
-->

# Contributions

Any contributions are welcome on this project. You can contribute by creating github issue or helping in the improvement of the algorithm. 
<!--  I invite everyone, to help me, in the development of this class, by sending feedback, and by proposing better algorithms.-->