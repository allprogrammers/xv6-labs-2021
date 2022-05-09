#include "kernel/types.h"
#include "kernel/param.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char* argv[])
{
    char buff[512];
    char* args[MAXARG];

    for(int i = 1;i<argc;i++)
    {
        args[i-1] = argv[i];
    }
    int nargc = argc-1;
    int i = 0;
    int pid = 0;

    while(read(0,&buff[i],1)!=0)
    {
        if(buff[i] == ' ' || buff[i] == '\n')
        {
            char temp = buff[i];
            buff[i] = '\0';
            args[nargc] = malloc(sizeof(char)*(strlen(buff)+1));
            strcpy(args[nargc],buff);
            nargc++;
            i=0;
            if(temp=='\n')
            {
                pid = fork();
                if(pid==0)
                {
                    break;
                }
                for(int j=argc-1;j<nargc;j++)
                {
                    free(args[j]);
                }
                nargc=argc-1;
                i=0;
            }
        }else
        {
            i++;
        }

    }
    if(pid==0)
    {
        exec(argv[1],args);
    }else
    {
        close(0);
    }
    while(wait(0)!=-1){}
    exit(0);
}