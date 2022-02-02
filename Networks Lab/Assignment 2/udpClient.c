#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>

#define MAXBUF 1024

int main(){
    int udpSocket,returnStatus,addrlen;
    struct sockaddr_in udpClient,udpServer;
    char buf[MAXBUF];
    udpSocket=socket(AF_INET,SOCK_DGRAM,0);
    if(udpSocket == -1){
        printf("Error Creating the socket!!");
        exit(1);
    }else{
        printf("Socket Created: %d",udpSocket);
    }

    udpClient.sin_family=AF_INET;
    udpClient.sin_addr.s_addr=INADDR_ANY;
    udpClient.sin_port=0;
    returnStatus=bind(udpSocket,(struct sockaddr*)&udpClient,sizeof(udpClient));
    
    if(returnStatus==0){
        printf("\nBind Completed!");
    }else{
        printf("Could not bind to the address!");
        close(udpSocket);
        exit(1);
    }

    strcpy(buf,"Hello from the client");
    udpServer.sin_family=AF_INET;
    udpServer.sin_addr.s_addr=inet_addr("127.0.0.1");
    udpServer.sin_port=htons(8080);

    returnStatus=sendto(udpSocket,buf,strlen(buf),0,(struct sockaddr*)&udpServer,sizeof(udpServer));
    if(returnStatus==-1){
        printf("\nCould not send message!!");
        close(udpSocket);
        exit(1);
    }else{
        printf("\nmessage sent to the server");
    }
    addrlen=sizeof(udpServer);
    returnStatus=recvfrom(udpSocket,buf,MAXBUF,0,(struct sockaddr*)&udpServer,&addrlen);
    if(returnStatus==-1){
        printf("\nError in receiving the message from server!");
        close(udpSocket);
        exit(1);
    }else{
        printf("\n%s\n",buf);
    }
    close(udpSocket);
    return 0;
}
