#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<signal.h>
#include<fcntl.h>

#define BUFFSIZE 64
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define STYLE_BOLD         "\033[1m"
#define STYLE_NO_BOLD      "\033[22m"
#define MAX_HISTORY 20

char *historyarray[MAX_HISTORY];
char *delim=" \t\n\a\r";
int recent=0,numofhistory=0,flag;
char path[1024];

char *read_command(){
    getcwd(path,sizeof(path));
    printf(ANSI_COLOR_CYAN STYLE_BOLD "%s>" ANSI_COLOR_RESET STYLE_NO_BOLD,path);
    char *cmd=NULL;
    size_t cmdsize=0;
    getline(&cmd,&cmdsize,stdin);
    return cmd;
}

char **command_split_pipe(char *cmd,int *n){
    char **tokens=malloc(BUFFSIZE*sizeof(char*));
    char *token;
    int idx=0,tokensize=BUFFSIZE;
    if(!tokens){
        printf("memory allocation error, exiting!!\n");
        exit(1);
    }
    token=strtok(cmd,"|");
    while(token!=NULL){
        tokens[idx++]=token;
        if(idx>=tokensize){
            tokensize+=tokensize;
            tokens=realloc(tokens,tokensize*sizeof(char *));
            if(!tokens){
                printf("memory allocation error, exiting!!");
                exit(1);
            }
        }
        token=strtok(NULL,"|");
    }
    tokens[idx]=NULL;
    *n=idx;
    return tokens;
}

char *find_redirections(char *cmd,char direction){
    int i,pos=-1,len=0,st,en,j=0;
    char *filename=NULL;
    for(i=0;cmd[i];i++)
        if(cmd[i]==direction) {
        	pos=i;
        	break;
        }
    
    if(pos>-1){
        i=pos+1;
        while(cmd[i]==' '||cmd[i]=='\t') i++;
        st=i;
    
        while(cmd[i]&&strchr(delim,cmd[i])==NULL) {
        	len++;
        	i++;
        }
        en=i-1;

        filename=malloc((len+1)*sizeof(char));
        for(i=st;i<=en;i++) 
            filename[j++]=cmd[i];
    
        filename[j]='\0';
        for(i=en+1;cmd[i];i++)
            cmd[pos++]=cmd[i];
    
        cmd[pos]='\0';
    }

    if(pos>-1&&filename==NULL) flag=1;
    // insert error checking for no file
    return filename;
}

char **command_split_space(char *cmd){
    char **tokens=malloc(BUFFSIZE*sizeof(char*));
    char *token;
    int idx=0,argsize=BUFFSIZE;
    if(!tokens){
        printf("memory allocation error, exiting!!\n");
        exit(1);
    }

    token=strtok(cmd,delim);
    while(token!=NULL){
        tokens[idx++]=token;
        if(idx>=argsize){
            argsize+=argsize;
            tokens=realloc(tokens,argsize*sizeof(char*));
            if(!tokens){
                printf("memory allocation error, exiting!!\n");
                exit(1);
            }
        }
        token=strtok(NULL,delim);
    }
    tokens[idx]=NULL;
    return tokens;
}

void launch_command(char **args,char *inputfile,char *outputfile,int inputfd,int outputfd){
    pid_t pid;
    int status;
    pid=fork();
    if(pid==0){
        signal(SIGINT,SIG_DFL);
	int fd;
        if(inputfile){
            close(0);
            fd=open(inputfile,O_RDONLY);
            if(fd<0){
            	perror(NULL);
            	printf("\n");
            	exit(1);
            }
        }else if(inputfd>=0){
            dup2(inputfd,0);
        }

        if(outputfile){
            close(1);
            //clear the openend file
            fd=open(outputfile,O_WRONLY|O_CREAT|O_TRUNC);
            if(fd<0){
            	perror(NULL);
            	printf("\n");
            	exit(1);
            }
        }else if(outputfd>=0){
            dup2(outputfd,1);
        }
        
        execvp(args[0],args);
        perror(NULL);
        printf("\n");
        exit(1);
    }else if(pid<0){
        perror("fork");
        printf("\n");
    }else{
        do{
            waitpid(pid,&status,WUNTRACED);
        }while(!WIFEXITED(status)&&!WIFSIGNALED(status));
    }
}

char* recent_command(){
    if(!numofhistory){
        flag=1;
        printf("no history to show!!\n");
        return NULL;
    }
    int i=recent-1;
    if(i<0) i+=MAX_HISTORY;
    printf(ANSI_COLOR_CYAN STYLE_BOLD "%s>" ANSI_COLOR_RESET STYLE_NO_BOLD"%s\n",path,historyarray[i]);
    return historyarray[i];
}

char* get_command(char *str){
    int num=0,i=1;
    while(str[i]>='0'&&str[i]<='9') {
        num=num*10+str[i]-'0';
        i++;
    }
    printf("%d\n",num);
    if(numofhistory<num){
        flag=1;
        printf("command not available!!\n");
        return NULL;
    }
    i=recent-numofhistory;
    if(i<0) i+=MAX_HISTORY;
    i+=num-1;
    if(i>=MAX_HISTORY) i-=MAX_HISTORY;
    printf("%d,\n",i);
    printf(ANSI_COLOR_CYAN STYLE_BOLD "%s>" ANSI_COLOR_RESET STYLE_NO_BOLD"%s\n",path,historyarray[i]);
    return historyarray[i];
}

//Function declarations for builtin shell commands
void cd(char **args);
void help(char **args);
void exitshell(char **args);
void history(char **args);

//List of builtin commands, followed by their corresponding functions.
char *builtin_str[]={
    "cd","help","exitshell","history"
};

int (*builtin_func[]) (char **)={
    &cd,&help,&exitshell,&history
};

int num_builtins(){
    return sizeof(builtin_str)/sizeof(char *);
}

//Builtin function implementations.
void cd(char **args){
    if(args[1]==NULL) return ;
    else if(args[2]!=NULL) {
        printf("Too many arguments!!\n");
    }else {
        if(chdir(args[1])!=0)
            perror("cd");
    }
}

void history(char **args){
    if(!numofhistory) {
        printf("no history to show!!\n");
        return ;
    }
    int i=recent-numofhistory;
    if(i<0) i+=MAX_HISTORY;
    while(i!=recent){
        printf("%s",historyarray[i]);
        i=(i+1)%MAX_HISTORY;
    }
}

void help(char **args){
    int i;
    printf("Type program names and arguments, and hit enter to run.\n");;
    printf("The following are built in:\n");

    for(i=0;i<num_builtins();i++){
        printf(" %s\n",builtin_str[i]);
    }

    printf("To use a recent command either use '!!' or '! and a number without giving space.'\n");
}

void exitshell(char **args){
    exit(0);
}

int main(){
    signal(SIGINT,SIG_IGN);
    signal(SIGTSTP,SIG_IGN);
    char *cmd,*inputfile,*outputfile,*temp;
    char **cmdlist,**arglist;
    int numberofcommands=0,i,prevfd=-1,j;
    while(1){
        cmd=read_command();
        flag=0;
        temp=strdup(cmd);
        if(strlen(cmd)==3&&cmd[0]=='!'&&cmd[1]=='!') cmd=recent_command();
        else if(strlen(cmd)==3&&cmd[0]=='!') cmd=get_command(cmd);
      	
        if(flag){
        	printf("command format not correct!!\n");
            	free(cmd);
         	continue;
        }
        
        cmdlist=command_split_pipe(cmd,&numberofcommands);
        for(i=0;i<numberofcommands;i++){
            int pipefd[2]={-1,-1};
            if(i<numberofcommands-1){
            	if(pipe(pipefd)==-1){
                	perror("pipe");
               		printf("\n");
                	goto label;
            	}
            }
            
            inputfile=find_redirections(cmdlist[i],'<');
            outputfile=find_redirections(cmdlist[i],'>');
            arglist=command_split_space(cmdlist[i]);
	    if(arglist[0]==NULL) goto label;
            if(flag){
                printf("command format not correct!!\n");
                goto label;
            }
            
            for (j = 0; j < num_builtins(); j++) {
    		    if (strcmp(arglist[0], builtin_str[j]) == 0) {
      			    (*builtin_func[j])(arglist);
      			    flag=1;
    		    }
  	        }
            if(flag==0)
            	launch_command(arglist,inputfile,outputfile,prevfd,pipefd[1]);
           
            if(pipefd[1]>=0)close(pipefd[1]);
            if(prevfd) close(prevfd);
            prevfd=pipefd[0];  
            free(arglist);
        }
        
        if(numofhistory<MAX_HISTORY) numofhistory++;
        historyarray[recent]=temp;
        if(historyarray[recent]==NULL){
       		printf("Memory error, exiting!!");
       		exit(1);
       	}
        recent++; 
        if(recent>=MAX_HISTORY) recent-=MAX_HISTORY;
 	    label:           
        free(cmd);
        free(cmdlist);  
        free(inputfile);
        free(outputfile);   
    }
    return 0;
}