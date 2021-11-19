#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <sys/types.h>
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <pwd.h>
 
int main(int argc, char const *argv[]) {  

    struct passwd* passwd_ptr;
    int valread;
    char buffer[1024] = {0}; 
    char *hello = "Hello from server";
// fork returns 0 inside child process
    if(argc!=2){
        perror("Log: inside child.c: Not all arguments are provided\n ");
        _exit(2);
    }
    printf("Log: inside child.c: Current pid = %d\n",getpid());
    printf("Log: inside child.c: Current uid = %ld\n", (long) getuid()); 
    passwd_ptr = getpwnam("nobody");
    printf("Log: inside child.c: UID of nobody=%ld\n",(long) passwd_ptr->pw_uid);
    if (setuid(passwd_ptr->pw_uid) != 0) {
        perror("Log: inside child.c: setuid() error\n");
        _exit(2);
    }
    else
        printf("Log: inside child.c: UID after setuid() = %ld\n",(long) getuid());
    valread = read((int)*argv[1], buffer, 1024);
    printf("%s\n",buffer ); 
    send((int)*argv[1], hello , strlen(hello) , 0 ); 
    printf("Hello message sent\n");
    return 0;
}