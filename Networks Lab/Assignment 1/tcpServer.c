#include<stdio.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(){
    int sd,port,returnStatus;
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
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(port);
    returnStatus = bind(sd,(struct sockaddr *)&server,sizeof(server));

    if(returnStatus==0) printf("\nBind Completed");
    else {
        printf("\nCould not Bind to address");
        close(sd);
        exit(1);
    }

    returnStatus = listen(sd,5);
    if(returnStatus == -1){
        printf("\nCannot Listen on Socket!!");
        close(sd);
        exit(1);
    }else {
        printf("\nlistening for connections\n");
        fflush(0);
    }

    while(1){
        struct sockaddr_in child = {0};
        int childSocket = 0,sizeofChild=sizeof(child);
        childSocket = accept(sd,(struct sockaddr*)&child,&sizeofChild);
        printf("\nConnected to: %s",inet_ntoa(child.sin_addr));
        char ch[256];
        while(1){
            printf("\nServer: ");
            bzero(ch,256);
            fgets(ch,256,stdin);
            if(strcmp(ch,"exit")==0){
                break;
            }
            write(childSocket,ch,strlen(ch));
            bzero(ch,256);
            read(childSocket,ch,256);
            printf("\nClient: %s",ch);
        }
    }
    close(sd);
    return 0;
}
