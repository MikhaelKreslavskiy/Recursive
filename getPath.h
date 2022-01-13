#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <alloca.h>
char* getPath(void)
{
    struct stat sb;
    char *linkname;
    ssize_t r;

    if (stat("/proc/self/exe", &sb) == -1) {
        perror("fstat");
        exit(EXIT_FAILURE);
    }
    linkname = (char*)malloc(sb.st_size+1);
    if (linkname == NULL) {
        fprintf(stderr, "недостаточно памяти\n");
        exit(EXIT_FAILURE);
    }
    r = readlink("/proc/self/exe", linkname, sb.st_size +1);
    if (r == -1) {
        perror("readlink");
        exit(EXIT_FAILURE);
    }
    linkname[r] = '\0';
    for (int i = strlen(linkname) - 1;;i--)
    {
        if (linkname[i] == '/')
        {
            linkname = (char*)realloc(linkname, i* sizeof(char) +1);
            linkname[i] = '\0';
            break;
        }
         
    }
    return(linkname);
}