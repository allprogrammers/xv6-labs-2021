#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(void)
{
    int p1[2];
    int p2[2];
    pipe(p1);
    pipe(p2);
    
    char byte[1];
    byte[0] = 'a';
    
    int pid = fork();
    if(pid==0)
    {
        read(p1[0],byte,1);
        printf("%d: received ping\n",getpid());
        write(p2[1],byte,1);
        
    }else{
        write(p1[1],byte,1);
        read(p2[0],byte,1);
        printf("%d: received pong\n",getpid());
    }
    exit(0);
}