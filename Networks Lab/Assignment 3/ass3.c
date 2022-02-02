#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/tcp.h>
#include<netinet/ip.h>
#include<netinet/if_ether.h>
#include<net/ethernet.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<netinet/in.h>

#define SIZE 65536

int data_size;

void print_ethernet_header(char *buff){
    struct ethhdr *eth=(struct ethhdr *)buff;
    printf("\nEthernet Header");
    printf("\n   |-Destination Address : %X",eth->h_dest);
    printf("\n   |-Source Address      : %X",eth->h_source);
    printf("\n   |-Protocol            : %d",eth->h_proto);
}


void print_tcp_packet(char *buff,int len){
	struct tcphdr *tcph=(struct tcphdr*)(buff+len+sizeof(struct ethhdr));
	printf("\nTCP Header");
	printf("\n   |-Source Port : %d",ntohs(tcph->source));
	printf("\n   |-Destination Port : %d",ntohs(tcph->dest));
	printf("\n   |-Sequence Number : %u",ntohl(tcph->seq));
	printf("\n   |-Acknowledge Number : %u",ntohl(tcph->ack_seq));
	printf("\n   |-Header Length : %d bytes",tcph->doff*4);
	printf("\n   |-Urgent Flag : %d",tcph->urg);
	printf("\n   |-Acknowledgement Flag : %d",tcph->ack);
	printf("\n   |-Push Flag : %d",tcph->psh);
	printf("\n   |-Reset Flag : %d",tcph->rst);
	printf("\n   |-Synchronise Flag : %d",tcph->syn);
	printf("\n   |-Finish Flag : %d",tcph->fin);
	printf("\n   |-Window : %d",tcph->window);
	printf("\n   |-Checksum : %d",tcph->check);
	printf("\n   |-Urgent Pointer : %d\n",tcph->urg_ptr);
}

void printheaders(char *buff,int data_size){
    print_ethernet_header(buff);

    struct iphdr *iph=(struct iphdr*)(buff+sizeof(struct ethhdr));
    
    struct sockaddr_in source,dest;
    memset(&source,0,sizeof(source));
    memset(&dest,0,sizeof(dest));
    source.sin_addr.s_addr=iph->saddr;
    dest.sin_addr.s_addr=iph->daddr;

    printf("\nIP Header");
    printf("\n   |-IP Version       : %d",(unsigned int)iph->version);
    printf("\n   |-IP Header Length : %d bytes",(iph->ihl*4));
    printf("\n   |-Type of Service  : %d",iph->tos);
    printf("\n   |-IP Total Length  : %d bytes",ntohs(iph->tot_len));
    printf("\n   |-Identification   : %d",ntohs(iph->id));
    printf("\n   |-Time To Live     : %d",iph->ttl);
    printf("\n   |-Protocol         : %d",iph->protocol);
    printf("\n   |-Checksum         : %d",ntohs(iph->check));
    printf("\n   |-Source IP        : %s",inet_ntoa(source.sin_addr));
    printf("\n   |-Destination IP   : %s\n",inet_ntoa(dest.sin_addr));
    if(iph->protocol==6){
        print_tcp_packet(buff,iph->ihl*4);
    }else{
        printf("\nProtocol used for the packet: %d , which is not tcp",iph->protocol);
    }
}

int main(){
    char buff[SIZE];
    int raw_socket=socket(AF_PACKET,SOCK_RAW,htons(ETH_P_ALL));
    if(raw_socket<0){
        printf("\nSocket could not be created!!\n");
        return 1;
    }
    struct sockaddr saddr;
    int saddr_size,cnt=10;
    while(cnt--){
        data_size=recvfrom(raw_socket,buff,SIZE,0,&saddr,(socklen_t*)&saddr_size);
        if(data_size<0){
            printf("Error in receiving packet!!");
            return 1;
        }
        printheaders(buff,data_size);
    }

    close(raw_socket);
    return 0;
}
