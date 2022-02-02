#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<netinet/ip_icmp.h>
#include<time.h>
#include<fcntl.h>


#define PORT 0
#define RECV_TIMEOUT 2
#define PACKET_SIZE 32

typedef struct packet{
    struct icmphdr hdr;
    char msg[PACKET_SIZE-sizeof(struct icmphdr)];
}packet;


unsigned short checksum(void *b, int len){    
    unsigned short *buf = b;
    unsigned int sum=0;
    unsigned short result;
  
    for ( sum = 0; len > 1; len -= 2 )
        sum += *buf++;
    if ( len == 1 )
        sum += *(unsigned char*)buf;
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    result = ~sum;
    return result;
}

char *dns_lookup(char *dest, struct sockaddr_in *dest_info){
    struct hostent *host;
    host=gethostbyname(dest);

    if(!host){
        printf("\nNo ip address found for the given hostname\n");
        exit(1);
    }

    char *ip=malloc(NI_MAXHOST*sizeof(char));
    strcpy(ip,inet_ntoa(*(struct in_addr *)host->h_addr));
    (*dest_info).sin_family=host->h_addrtype;
    (*dest_info).sin_port=htons(PORT);
    (*dest_info).sin_addr.s_addr=*(long *)host->h_addr;

    return ip;
}

void trace(int sockfd,struct sockaddr_in dest,char *host,char *ip){
    int ttl=1,len;
    
    struct timeval timeout;
    timeout.tv_sec=RECV_TIMEOUT;
    timeout.tv_usec=0;
    setsockopt(sockfd,SOL_SOCKET,SO_RCVTIMEO,(char *)&timeout,sizeof(timeout));

    struct sockaddr_in r_addr;
    packet pckt;
    while(1){
        packet pckt;
        bzero(&pckt,sizeof(pckt));
        pckt.hdr.type=ICMP_ECHO;
        pckt.hdr.un.echo.id=getpid();
        pckt.hdr.un.echo.sequence=ttl;
        pckt.hdr.checksum=checksum(&pckt,sizeof(pckt));

        if(setsockopt(sockfd,SOL_IP,IP_TTL,&ttl,sizeof(ttl))!=0){
            printf("\nSetting TTL option failed!");
            exit(1);
        }

        if(sendto(sockfd,&pckt,sizeof(pckt),0,(struct sockaddr*)&dest,sizeof(dest))<=0){
            printf("\nError in sending packet!!");
            exit(1);
        }
    
        len=sizeof(r_addr);
        if(recvfrom(sockfd,&pckt,sizeof(pckt),0,(struct sockaddr*)&r_addr,&len)<=0){
            printf("\n%d Timeout",ttl);
        }else{
            char addr[256];
            inet_ntop(AF_INET,&(r_addr.sin_addr),addr,sizeof(addr));
            printf("\n%d %s",ttl,addr);
            if(strcmp(addr,ip)==0) break;
        }
        ttl++;
    }
}

int main(int argc,char *argv[]){
    if(argc!=2){
        printf("\nFormat %s <address>\n",argv[0]);
        return 0;
    }
    
    struct sockaddr_in dest_adr;
    char *ip_addr=dns_lookup(argv[1],&dest_adr);

    if(!ip_addr){
        printf("\nDNS lookup failed!!!");
        exit(1);
    }

    printf("\nTracing '%s' having IP: %s",argv[1],ip_addr);
    int sockfd=socket(AF_INET,SOCK_RAW,IPPROTO_ICMP);
    if(sockfd<0){
        printf("\nCould not create socket!!");
        exit(1);
    }
    trace(sockfd,dest_adr,argv[1],ip_addr);
}
