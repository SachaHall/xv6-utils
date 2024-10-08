#include "user/user.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fs.h"

char*
getFileName(char *path)
{
    static char buf[256];
    char *p;

    // Find first character after last slash.
    for(p=path+strlen(path); p >= path && *p != '/'; p--)
        ;
    p++;

    memmove(buf, p, strlen(p));
    buf[strlen(p)] = 0;
    return buf;
}

void find(char *path, char *name) {
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;

    if((fd = open(path, 0)) < 0){
        fprintf(2, "find: cannot open %s\n", path);
        return;
    }

    if(fstat(fd, &st) < 0){
        fprintf(2, "find: cannot stat %s\n", path);
        close(fd);
        return;
    }

    switch(st.type){
        case T_DEVICE:
        case T_FILE:
            //if (strcmp(st.))
            if (!strcmp(getFileName(path), name)) printf("%s\n", path);
            break;

        case T_DIR:
            if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){

                printf("find: path too long\n");
                break;
            }
            strcpy(buf, path);
            p = buf+strlen(buf);
            *p++ = '/';
            while(read(fd, &de, sizeof(de)) == sizeof(de)){
                if(de.inum == 0)
                    continue;
                memmove(p, de.name, DIRSIZ);
                p[DIRSIZ] = 0;
                if(stat(buf, &st) < 0){
                    printf("find: cannot stat %s\n", buf);
                    continue;
                }
                char filename[256];
                strcpy(filename, getFileName(buf));
                if (!strcmp(filename, ".")) continue;
                if (!strcmp(filename, "..")) continue;
                find(buf, name);
                //printf("%s\n", name);
                //printf("%s %d %d %d\n", name, st.type, st.ino, st.size);
            }
            break;
    }
    close(fd);
}

int main(int argc, char **argv) {
    if (argc !=  3) {
        printf("ERROR: incorrect number of parameters\n");
    }
    find(argv[1], argv[2]);
}

