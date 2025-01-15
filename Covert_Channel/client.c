#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

void send_data(char *secret_data, char *destination, int port_1, int port_2) //expansion idea make it so data is auto translated to binary
{
    int sock_1 = socket(AF_INET, SOCK_STREAM, 0);
    char buf[4096];

    if(sock_1 == -1)
    {
        perror("socket creation failed");
        exit(1);
    }

    printf("%s\n",destination);



    struct sockaddr_in server_address_1;
    memset(&server_address_1,0,sizeof(server_address_1));
    server_address_1.sin_family = AF_INET;
    server_address_1.sin_port = htons(port_1);
    server_address_1.sin_addr.s_addr = inet_addr(destination);

    //second socket

    int sock_2 = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_1 == -1)
    {
        perror("socket creation failed");
        exit(1);
    }

    struct sockaddr_in server_address_2;
    memset(&server_address_2,0,sizeof(server_address_2));
    server_address_2.sin_family = AF_INET;
    server_address_2.sin_port = htons(port_2);
    server_address_2.sin_addr.s_addr = inet_addr(destination);




    //connect the sockets

    if(connect(sock_1,(struct sockaddr *)&server_address_1,sizeof(server_address_1)) == -1)
    {
        perror("first connection failed");
        exit(1);
    }

    if(connect(sock_2,(struct sockaddr *)&server_address_2, sizeof(server_address_2)) == -1) 
    {
        perror("second connection failed");
        exit(1);
    }




    int counter = 0;
    while(counter <= strlen(secret_data)) 
    {
        printf("%d %s\n",counter, secret_data);

        if(counter == strlen(secret_data)) 
        {
            send(sock_2,"placeholder5",strlen("placeholder5"),0);
            recv(sock_2,buf,4096,0);
            send(sock_2,"placeholder5",strlen("placeholder5"),0);
            recv(sock_2,buf,4096,0);
            send(sock_1,"placeholder6",strlen("placeholder5"),0);
            break;
        }

        if(secret_data[counter] == '1') 
        {
            send(sock_1,"placeholder1",strlen("placeholder1"),0);
            recv(sock_1,buf,4096,0);
            send(sock_1,"placeholder2",strlen("placeholder2"),0);
            recv(sock_1,buf,4096,0);
        }

        if(secret_data[counter] == '0') 
        {
            send(sock_1,"placeholder3",strlen("placeholder3"),0);
            recv(sock_1,buf,4096,0);
            send(sock_2,"placeholder4",strlen("placeholder4"),0);
            recv(sock_2,buf,4096,0);
        }
        counter++;
    }
    close(sock_1);
    close(sock_2);
    printf("Message send\n");
    return;
}

int main(int argc, char *argv[])  //expansion idea make this fork to multiple processes to be stealther
{
    char* secret_data;
    if(argc >= 2)
    {
        secret_data = argv[1];
    }
    else 
    {
        secret_data = "101";
    }
     
    char* destination_address = malloc(sizeof(char)*20); //creates a buffer for the address
    memset(destination_address,0,20);
    int ports[2];
    ports[0] = 9200;
    ports[1] =8124;
    

    destination_address = "127.0.0.1";
    send_data(secret_data,destination_address,ports[0],ports[1]);

    return 0;
}