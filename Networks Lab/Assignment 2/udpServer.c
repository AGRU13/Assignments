#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include<unistd.h>
#include<string.h>

#define MAXBUF 1024

int main(){
    int udpSocket,addrlen;
    struct sockaddr_in udpServer,udpClient;
    char buf[MAXBUF];
    udpSocket=socket(AF_INET,SOCK_DGRAM,0);
    
    if(udpSocket==-1){
        printf("Error Creating the socket!!");
        exit(1);
    }else{
        printf("Socket Created: %d",udpSocket);
    }

    udpServer.sin_family=AF_INET;
    udpServer.sin_addr.s_addr=INADDR_ANY;
    udpServer.sin_port=htons(8080);

    int returnStatus=bind(udpSocket,(struct sockaddr*)&udpServer,sizeof(udpServer));
    if(returnStatus==0) printf("\nBind Completed");
    else {
        printf("\nCould not Bind to address");
        close(udpSocket);
        exit(1);
    }
    
    while(1){
        addrlen=sizeof(udpClient);
        returnStatus=recvfrom(udpSocket,buf,MAXBUF,0,(struct sockaddr*)&udpClient,&addrlen);
        if(returnStatus==-1){
            printf("\nCould not receive message!!\n");
            exit(1);
        }else{
            printf("\n%s",buf);
            strcpy(buf,"Hello from the server");
            returnStatus=sendto(udpSocket,buf,strlen(buf),0,(struct sockaddr*)&udpClient,sizeof(udpClient));
            if(returnStatus==-1){
                printf("\nCould not send message to the client!!");
                exit(1);
            }else{
                printf("\nMessage sent to the client\n");
            }
        }
        close(udpSocket);
        return 0;
    }
    return 0;
}

