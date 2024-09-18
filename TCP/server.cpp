#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <cstring>
#include <netdb.h>
#include "error_handling.h"
#include "../src/integral.cpp"

void fd_errorcheck(int fd,const char* error_message);

int main(int argc, char** argv){

    if (argc < 2){
        std::cout << "Please enter a port number between 2000 and 16000" << "\n";
        exit(1);
    }

    int socket_fd, client_fd, port_no;
    port_no = atoi(argv[1]);

    if (2000 > port_no || port_no > 16000) {
        std::cout << "Please enter a port number between 2000 and 16000" << "\n";
        exit(1);
    }

    

    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    fd_errorcheck(socket_fd,"Error on creating socket");

    int reuse = 1;
    int option_fd = setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    fd_errorcheck(option_fd,"Error on changing reuse options");

    struct sockaddr_in server_adress;
    server_adress.sin_family = AF_INET;
    server_adress.sin_addr.s_addr = INADDR_ANY;
    server_adress.sin_port = htons(port_no);

    int bind_fd = bind(socket_fd, (struct sockaddr *) &server_adress, sizeof(server_adress));

    if (bind_fd != 0){
        std::cerr << "Can't bind to port " << port_no << "\n";
        exit(1);
    }

    int listen_fd = listen(socket_fd, 2);
    if (listen_fd != 0){
        std::cerr << "Can't listen for a client to connect...\n";
        exit(1);
    }
    else{
        std::cout << "Listening for a client to connect...\n";
    }

    struct sockaddr_in client_addr;
    int client_addr_len = sizeof(client_addr);

    client_fd = accept(socket_fd, (struct sockaddr *) &client_addr,(socklen_t *) &client_addr_len);
    fd_errorcheck(client_fd, "Client can't connect to server");

    int choosen_function;
    float lower_bound;
    float upper_bound;

    recv(client_fd,&choosen_function,sizeof(choosen_function),0);
    recv(client_fd,&lower_bound,sizeof(lower_bound),0);
    recv(client_fd,&upper_bound,sizeof(upper_bound),0);

    float integral_solution = integral_calculations(lower_bound,upper_bound,choosen_function);

    send(client_fd,&integral_solution,sizeof(integral_solution),0);


    return(0);
}

