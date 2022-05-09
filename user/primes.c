#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void onlyfork(int p[2])
{
    close(p[1]);
    int first;
    int ans = read(p[0],&first,4);
    

    if(ans==0)
    {
        close(p[1]);
        close(p[0]);
        return;
    }
    printf("prime %d\n",first);
    
    int p2[2];
    pipe(p2);

    int pid = fork();
    if(pid==0)
    {
        onlyfork(p2);
        return;
    }

    close(p2[0]);
    
    int n;

    while(read(p[0],&n,4)!=0)
    {
        if(n%first!=0)
        {
            write(p2[1],&n,4);
        }
    }
    close(p[0]);
    close(p2[1]);
    while(wait(0)!=-1){}
}

int main(void)
{
    
    int start = 2;

    int end = 36;

    int p[2];

    pipe(p);
    int pid = fork();
    if(pid==0)
    {
        onlyfork(p);
        exit(0);
    }
    close(p[0]);

    for(int i = start;i<end;i++)
    {
        write(p[1],&i,4);
    }
    close(p[1]);
    while(wait(0)!=-1){}
    
    exit(0);
}