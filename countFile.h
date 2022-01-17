#include<dirent.h>
#include "_PLUGIN_API.h"
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include<string.h>
#include <sys/types.h>

///#include"check.h"

char* concat_f(char*, char*);

extern void** array_need_plugins;
extern struct option* long_options;
extern int* mas;
////extern int count_need;
extern int number_long_opt;
extern int AND, OR, NOT;
void countFile( char* path)
{
    
     
     
     DIR *dir = opendir(path);
    struct dirent *ent;
    ////char *s=NULL;
    
    if (dir == NULL)
    {
        if(getenv("LAB1DEBUG"))
        perror("opendir() ");
    }
    
    while ((ent=readdir(dir)) != NULL)
    {
        if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0 || strcmp(ent->d_name, ".vscode")  == 0)
            continue;
        struct stat sb;
        
       char* s = concat_f(path, ent->d_name);
       
        if (stat(s, &sb) == -1)
        {
             if(getenv("LAB1DEBUG"))
            perror("stat()");
        }
       /// free(s);
        if (S_ISDIR(sb.st_mode))  
            {
             
            countFile(s);
            } 
            free(s);
            if(S_ISREG(sb.st_mode))
         {
                 
                 int res=-2;
                 int min_or=0,min_and=1; 
                char* str= concat_f(path,ent->d_name);
             for(int i=0;i<number_long_opt;i++)
            {   
                                 
                              
                 if(mas[i]==1){
                struct option *in_opt = (struct option*)malloc(sizeof(struct option));
                size_t leno = 0;
                                   
                in_opt = (struct option*)realloc(in_opt, sizeof(struct option)*(leno+1));
                in_opt[leno] = long_options[i];
                leno++;
                               
              void* hand= dlsym(array_need_plugins[i], "plugin_process_file");
                                 
                typedef int(*plugin_process)(const char* fname,struct option in_opts[],size_t len);
                plugin_process get_process= (plugin_process)hand;
                                 
                res=get_process(str, in_opt, 1);
                
                  /// free(hand);             

                            if(res==-1)
                               { 
                                 
                                min_and=0;
                                if (getenv("LAB1DEBUG"))
                                fprintf(stderr, "Ошибка вызова plugin_process_file, первая переданная опция: %s\n", long_options[i].name);
                
                                }
                                free(in_opt);
                                
                                if(res==0)
                                {
                                     min_or = 1 + min_or;
                                     min_and = 1*min_and;
                                }
                                if(res>0)
                                {
                                    min_and=0;
                                }

                        }
                          
                   }   
         
            ///if((AND==0)&&(OR==0)&&(res==0)) printf("%s\n", s);
             if((AND==1)&&(NOT==0))
            {  
                if(min_and==1)
                {
                printf(" %s\n", str);
                
                
                }
                free(str);
                continue;
              ///  break;
            }
            if((OR==1)&&(NOT==0))
            {
                if(min_or==1)
                {

                printf(" %s\n", str);
                
               
                }
                free(str);

                continue;
                
            }

            if((OR==1)&&(NOT==1))
            {
                if(min_or==0)
                {
                    printf(" %s\n", str);
                   
                   
                }
                 free(str);
                continue;
            }
           
            if((AND==1)&&(NOT==1))
            {
                if(min_and==0)
                {
                    printf("%s\n", str);
                    
                  
                }
                free(str);
                continue;
            }
            free(str);
        }
        
         }
         
               
    
    
closedir(dir);
///free(s);


}


char* concat_f(char *s1, char *s2) {

        size_t len1 = strlen(s1);
        size_t len2 = strlen(s2);                      

        char *result = (char*) malloc(strlen(s1) + strlen(s2) + 2);

        if (!result) {
          ///  if(getenv("LAB1DEBUG"))
          ///  {
            fprintf(stderr, "malloc() failed: insufficient memory!\n");
            return NULL;
           /// }
        }

        memcpy(result, s1, len1);
        memcpy(result + len1, "/", 1);
        memcpy(result + len1 +1, s2, len2 + 1);  

        return result;
    }


