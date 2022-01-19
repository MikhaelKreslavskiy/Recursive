
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <string.h>
//#include"countFile.h"
#include "_PLUGIN_API.h"


extern int count_of_plugs;
extern void** array_of_plugins;


 extern int nplug;
 
char* concat(char *s1, char *s2);

void countPlug(char* path) {
    DIR *dir = opendir(path);
    struct dirent *ent;
    void* hand;
    
    
    if (dir == NULL)
    {
        perror("opendir() ");
    }
    
    while ((ent=readdir(dir)) != NULL)
    {
        if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0 || strcmp(ent->d_name, ".vscode")  == 0)
            continue;
        struct stat sb;
      
        char *s = concat(path, ent->d_name);
       
        if (stat(s, &sb) == -1)
            perror("stat()");
        if (S_ISDIR(sb.st_mode))  {
            /// printf("%s\n",ent->d_name);
            countPlug(s);
            } 
      
        free(s);
        char *str = ent->d_name;
            if (str[strlen(str)-1] == 'o')
                if (str[strlen(str)-2] == 's')
                    if (str[strlen(str)-3] == '.')
                    {
                       
                    
                   

                    
                   
                     char* dimom_str= concat(path, ent->d_name);
                   
                    hand=dlopen(dimom_str,RTLD_LAZY);
                    
                    if(hand==NULL)
                     {
                         fprintf(stderr, "Ошибка в открытии плагина: %s", dimom_str);
                         continue;
                     }
                     array_of_plugins = (void**)realloc(array_of_plugins,sizeof(void*)*(count_of_plugs+1));
                   array_of_plugins[count_of_plugs]=hand;
                   count_of_plugs++;

                    void* hand_info= dlsym(hand, "plugin_get_info");
                    char* error;
                    if ((error = dlerror()) != NULL)  {
                            
                            ///puts("Here is a mistake");
                            /// fprintf (stderr, "%s\n", error);
                             count_of_plugs--;
                             array_of_plugins = (void**)realloc(array_of_plugins,sizeof(void*)*(count_of_plugs));

                                     continue;
                    }
                     struct  plugin_info ppi ={0};
                 
                   typedef int(*plugin_info_i)(struct plugin_info*) ;
                   
                     plugin_info_i get_info= (plugin_info_i)hand_info;
                    
                    int res = get_info(&ppi); 
                    printf("Найден плагин: %s\n", dimom_str);
                    printf("Автор :%s\n", ppi.plugin_author);
                    printf("Цель плагина: %s\n", ppi.plugin_purpose);
                    printf("\n");
                    free(dimom_str);
                
                    nplug++;
                    if(res==-1)
                    {
                         /// puts("Here is a mistake");
                          fprintf(stderr, "Ошибка вызова plugin_get_info \n");
                          count_of_plugs--;
                          array_of_plugins = (void**)realloc(array_of_plugins,sizeof(void*)*(count_of_plugs));
                          continue;
                    }
                   
                    
                   /// free(dimom_str);
                    ///free(error);
        
                    }
                   
    }
    closedir(dir);
}

char* concat(char *s1, char *s2) {

        size_t len1 = strlen(s1);
        size_t len2 = strlen(s2);                      

        char *result = (char*) malloc(strlen(s1) + strlen(s2) + 2);

        if (!result) {
            fprintf(stderr, "malloc() failed: insufficient memory!\n");
            return NULL;
        }

        memcpy(result, s1, len1);
        memcpy(result + len1, "/", 1);
        memcpy(result + len1 +1, s2, len2 + 1);    

        return result;
    }
