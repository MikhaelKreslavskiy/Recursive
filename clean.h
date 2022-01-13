#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>

extern void ** array_of_plugins;
extern void** array_need_plugins;
extern struct option* long_options;
extern int count_need;
extern int count_of_plugs;
extern int* mas;
extern int number_long_opt;

int clean()
{
   /*
    for(int i=0;i<number_long_opt;i++)
       {
        dlclose(array_need_plugins[i]);

       
       } 
       
       free(array_need_plugins);
   */
     free(array_need_plugins);
    for(int i=0;i<count_of_plugs;i++){
    dlclose(array_of_plugins[i]);
    
    }
    
    free(array_of_plugins);

     free(long_options);
     free(mas);
   return 0;
}