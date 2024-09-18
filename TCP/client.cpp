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

void fd_errorcheck(int fd,const char* error_message);

int main(int argc, char** argv){

    int socket_fd, client_fd, port_no;
    port_no = atoi(argv[1]);

    client_fd = socket(AF_INET, SOCK_STREAM,0);
    fd_errorcheck(client_fd, "Could not set up client socket");

    struct sockaddr_in server_adress;
    server_adress.sin_family = AF_INET;
    server_adress.sin_port = htons(port_no);
    int server_addr_len = sizeof(server_adress);

    if (inet_pton(AF_INET, "127.0.0.1", &server_adress.sin_addr) <= 0) {
        std::cerr << "Invalid address / Address not supported\n";
        return 1;
    }


    int connect_fd = connect(client_fd, (struct sockaddr *)&server_adress,sizeof(server_adress));
    //fd_errorcheck(connect_fd, "Could not connect to server");

    std::cout << "Connected sucessfully\n";

    int choosen_number;
    std::cout << "Which integral do you want to calculate? Enter the number :\n"
             "1. Quadratic integral\n"
             "2. Exponential integral\n"
             "3. Gaussian integral\n";
    std::cin >> choosen_number;

    float lower_bound;
    float upper_bound;
    float integral_solution;

    std::cout << "What is the lower bound supossed to be?\n";
    std::cin >> lower_bound;

    std::cout << "What is the upper bound supossed to be?\n";
    std::cin >> upper_bound;
    float z = 12.43;

    send(client_fd, &choosen_number, sizeof(choosen_number), 0);
    send(client_fd, &lower_bound, sizeof(lower_bound), 0);
    send(client_fd, &upper_bound, sizeof(upper_bound), 0);

    std::cout << "Data is sent, waiting for calculations \n";

    recv(client_fd,&integral_solution,sizeof(integral_solution),0);

    std::cout << "Finished calculating. The soulution is " << integral_solution << std::endl;
    
    close(client_fd);

}

