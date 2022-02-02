#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>

int main(){
    int sd,port,returnStatus;
    char buff[256]="";
    struct sockaddr_in server={0};
    sd=socket(AF_INET,SOCK_STREAM,0);

    if(sd==-1){
        printf("Error Creating the socket!!");
        exit(1);
    }else{
        printf("Socket Created: %d",sd);
    }

    port=8080;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(port);
    returnStatus = connect(sd,(struct sockaddr *)&server,sizeof(server));

    if(returnStatus==0) printf("\nConnection Succesful\n");
    else {
        printf("\nCould not Connect to address");
        close(sd);
        exit(1);
    }
    while(1){
        bzero(buff,256);
        read(sd,buff,sizeof(buff));
        printf("\nServer: %s",buff);
        printf("\nClient: ");
        bzero(buff,256);
        fgets(buff,256,stdin);
        if(strcmp(buff,"exit")==0){
            break;
        }
        write(sd,buff,sizeof(buff));
    }
    close(sd);
    return 0;
}
