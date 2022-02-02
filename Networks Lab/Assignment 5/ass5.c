#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<netinet/ip_icmp.h>
#include<time.h>
#include<fcntl.h>
#include<signal.h>

#define PORT 0
#define RECV_TIMEOUT 2
#define PACKET_SIZE 32

typedef struct packet{
    struct icmphdr hdr;
    char msg[PACKET_SIZE-sizeof(struct icmphdr)];
}packet;

unsigned short checksum(void *b, int len)
{    unsigned short *buf = b;
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

void ping(int sockfd,struct sockaddr_in dest,char *host,char *ip){
    int ttl=64,len;
    double rtt,trtt=0;
   
    FILE *fptr;
    fptr=fopen("rtt-readings","w");
    if(!fptr){
        printf("\nError while opening file!!");
    }

    if(setsockopt(sockfd,SOL_IP,IP_TTL,&ttl,sizeof(ttl))!=0){
        printf("\nSetting TTL option failed!");
        exit(1);
    }

    struct timeval timeout;
    timeout.tv_sec=RECV_TIMEOUT;
    timeout.tv_usec=0;
    setsockopt(sockfd,SOL_SOCKET,SO_RCVTIMEO,(char *)&timeout,sizeof(timeout));

    struct timespec time_start,time_end;
    struct sockaddr_in r_addr;
    packet pckt;
    
    for(int j=1;j<=12;j++){
    	for(int i=1;i<=100;i++){
        	bzero(&pckt,sizeof(pckt));
        	pckt.hdr.type=ICMP_ECHO;
        	pckt.hdr.un.echo.id=getpid();
        	pckt.hdr.un.echo.sequence=i;
            pckt.hdr.checksum=checksum(&pckt,sizeof(pckt));

            clock_gettime(CLOCK_MONOTONIC,&time_start);
            if(sendto(sockfd,&pckt,sizeof(pckt),0,(struct sockaddr*)&dest,sizeof(dest))<=0){
                printf("\nError in sending packet!!");
                exit(1);
            }
    
            len=sizeof(r_addr);
            if(recvfrom(sockfd,&pckt,sizeof(pckt),0,(struct sockaddr*)&r_addr,&len)<=0){
                printf("\nError in receiving packet");
                exit(1);
            }
            clock_gettime(CLOCK_MONOTONIC,&time_end);
            double time_elapsed=((double)(time_end.tv_nsec-time_start.tv_nsec))/1000000;
            rtt=(time_end.tv_sec-time_start.tv_sec)*1000+time_elapsed;
            trtt+=rtt;
        }
        trtt/=100;
        fprintf(fptr,"%d %lf\n",j,trtt);
        printf("\nApprox round trip time in milli-secons: %lf",trtt);
        fflush(0);
        sleep(300);
    }
    fclose(fptr);
}

int main(int argc, char *argv[]){
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

    printf("\nPinging '%s' having IP: %s",argv[1],ip_addr);
    int sockfd=socket(AF_INET,SOCK_RAW,IPPROTO_ICMP);
    if(sockfd<0){
        printf("\nCould not create socket!!");
        exit(1);
    }
    ping(sockfd,dest_adr,argv[1],ip_addr);
    return 0;
}

