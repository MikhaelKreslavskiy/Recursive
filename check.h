


#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include<dlfcn.h>

extern void** array_need_plugins;
extern void** array_of_plugins;
extern struct option long_options[];
extern int mas[20];
extern int count_of_plugs;
extern int count_need;


int check()
{
  for(int i=0;i<count_of_plugs;i++)
  {
    
     void* hand_info= dlsym(array_of_plugins[i], "plugin_get_info");
     
      struct  plugin_info ppi ={0};
      typedef int(*plugin_info_i)(struct plugin_info*) ;
    plugin_info_i get_info= (plugin_info_i)hand_info;
    get_info(&ppi);
    

      for(int j=0;j<20;j++)
      {
         ///printf("%s\n", long_options[j].name);
         ///printf("%s\n", ppi.sup_opts->opt.name);
         if((mas[j]==1) && (strcmp(long_options[j].name,ppi.sup_opts->opt.name)==0))
         {
           ///printf("%s\n", ppi.sup_opts->opt.name);
            array_need_plugins=(void**)realloc(array_need_plugins, sizeof(void*)*(count_need+1));
          
            array_need_plugins[count_need]=array_of_plugins[i];
           
            count_need++;

         }
      }
  }
  
   return 0;
}