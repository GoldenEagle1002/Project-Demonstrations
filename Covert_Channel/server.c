#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> // to use close()
#include <pthread.h>

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t fil = PTHREAD_MUTEX_INITIALIZER;

int messages_rec;
int last_message;
FILE* out;
char finished = 'n';
int end = 0;

void *recieve(void *args)
{
    int* arguments = (int (*)[2]) args;
    int thread_number = arguments[0];
    int port_number = arguments[1];
    char binary_bit;
    char buf[4096];

    int sock = socket(AF_INET,SOCK_STREAM,0);
    if(sock == -1) 
    {
        perror("socket not made");
        exit(1);
    }

    struct sockaddr_in server_address;
    memset(&server_address,0,sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port_number);
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(sock,(struct sockaddr *)&server_address, sizeof(server_address)) == -1) 
    {

        perror("bind failed");
        exit(1);
    }

    if(listen(sock,1) == -1) 
    {
        perror("listen failed");
        exit(1);
    }


    struct sockaddr_in client_address;
    socklen_t client_address_len = sizeof(client_address);

    printf("Waiting for the connection in thread %d on port %d\n", thread_number, port_number );

    int connection = accept(sock, (struct sockaddr *)&client_address, &client_address_len);
    if(connection == -1)
    {
        perror("accept failed");
        exit(1);
    }


    printf("Found connection in thread %d\n", thread_number );

    //code to recieve a packet 

    while(finished != 'q')
    {
        
        size_t bytes_received = recv(connection,buf,4096,0);
        if(bytes_received == -1)
        {
            perror("recieving message failed");
            exit(1);
        }
        
        printf("Recieved packet from %d with string %s\n", thread_number,buf );

        if(end == 1) 
        {
            break;
        }
        
        printf("entered\n");

        if(pthread_mutex_lock(&mut) != 0) 
        {
            perror("lock");
            exit(1);
        }



        messages_rec++;
        if(messages_rec == 2)
        {
            if(last_message == thread_number && thread_number == 2) 
            {
                end = 1;
            }
            else if(last_message == thread_number)
            {
                binary_bit = '1';
                fwrite(&binary_bit,1,1,out)==0;
            }
            else
            {
                binary_bit = '0';
                fwrite(&binary_bit,1,1,out)==0;
            }
            messages_rec = 0;
        }
        last_message = thread_number;
        pthread_mutex_unlock(&mut);

        if(send(connection, "rec",sizeof("rec"),0) == -1)
        {
            perror("sending message failed");
            exit(1);
        }
        printf("Finished\n");

        if(end == 1) 
        {
            break;
        }
    }

    
    void* filler = (void*) (&port_number);

    close(connection);
    close(sock);
    return filler;
}

int main()
{
    out = fopen("output.txt","w");
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    int messages_rec = 0;
    int ports[] = {9200, 8124};
    int args[2], args2[2];
    int ret;
    
    pthread_t threads[2];

    args[0] = 1;
    args[1] = ports[0];
    printf("PORT IN USE %d\n", ports[0]);

    ret = pthread_create( &(threads[0]),NULL,recieve,args);

    args2[0] = 2;
    args2[1] = ports[1];

    printf("PORT IN USE %d\n", ports[1]);
    ret = pthread_create( &(threads[1]),NULL,recieve,args2);
    if(ret != 0) 
    {
        perror("THREAD CREATION");
        exit(1);
    }

    printf("input 'q' to end connection after next message\n");

    while(finished != 'q') 
    {
        if(finished != '\n')
        {
            printf("user input: %c\n",finished);
        }
        finished = getchar();
    }

    for(int i = 0;i < 2; i++) 
    {
        printf("waiting to end\n");

        if(pthread_join(threads[i],NULL) != 0)
        {
            perror("ERROR JOINING");
            exit(1);
        }

        printf("joined thread: %d\n",i);

    }


    fclose(out);
    pthread_mutex_destroy(&mut);
}