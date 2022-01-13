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


extern struct option* long_options;
extern int nplug;
extern int number_long_opt;
extern void** array_of_plugins;
extern void** array_need_plugins;
extern int count_need;

int find_opt()
{
    for(int i=0;i<nplug;i++)
    {
        void *func = dlsym(array_of_plugins[i],"plugin_get_info");
        typedef int (*get_info)(struct plugin_info*);
        get_info plugin_ginfo = (get_info)func;

         struct plugin_info ppi = {0};
        if (plugin_ginfo(&ppi) == -1)
        fprintf(stderr, "Ошибка вызова plugin_get_info \n");
        for(size_t j=0;j<ppi.sup_opts_len;j++)
        {
            array_need_plugins=(void**)realloc(array_need_plugins, sizeof(void*)*(count_need+1));
            long_options=(struct option*)realloc(long_options, (number_long_opt+1)*sizeof(struct option));
            array_need_plugins[count_need]=array_of_plugins[i];
            long_options[number_long_opt].name= ppi.sup_opts[j].opt.name;
            long_options[number_long_opt].flag= 0;
            long_options[number_long_opt].has_arg= ppi.sup_opts[j].opt.has_arg;
            long_options[number_long_opt].val= 0;
            number_long_opt++;
            count_need++;
        }


    }

     long_options = (struct option*)realloc(long_options, (number_long_opt+1)*sizeof(struct option));
    long_options[number_long_opt].name = NULL;
    long_options[number_long_opt].has_arg = 0;
    long_options[number_long_opt].flag = NULL;
    long_options[number_long_opt].val = 0;
return 0;
}