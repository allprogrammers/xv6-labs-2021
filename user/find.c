#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

void
find(char *path,char* filename)
{
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if((fd = open(path, 0)) < 0){
    fprintf(2, "Error");
    return;
  }

  if(fstat(fd, &st) < 0){
    fprintf(2, "Error");
    close(fd);
    return;
  }

  switch(st.type){
  case T_FILE:
    //what to do with the file
    for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
    p++;
    if(!strcmp(p,filename))
    {
        printf("%s\n",path);
    }
    break;

  case T_DIR:
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf("Error");
      break;
    }
    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';
    int i = 0;
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      if(i<2)
      {
        i++;
        continue;
      }
      if(de.inum == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if(stat(buf, &st) < 0){
        printf("Error");
        continue;
      }
      //what to do with the directory
      find(buf,filename);
    }
    break;
  }
  close(fd);
}

int main (int argc,char* argv[])
{
    if(argc<3)
    {
        printf("Error s");
    }
    find(argv[1],argv[2]);
    exit(0);
}