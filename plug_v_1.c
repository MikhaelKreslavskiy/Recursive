#include "_PLUGIN_API.h"

#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <string.h>



extern int nplug;
 void *dir_names_plugins;
///static char* concat(const char *s1, char *s2);
static char* purp="поиск файлов, содержащих четных и нечетных байтов в отношении,заданном значением опции .";
static char* auth="Креславский Михаэль, N3248";
static struct plugin_option MyOption[] =  {{{"parity",required_argument,0,1}, "Looking for parity"}};



int plugin_get_info(struct plugin_info* ppi)
{
  if (!ppi) {
        fprintf(stderr, "ERROR: invalid argument\n");
        return -1;
    }

    
    ppi -> plugin_author = auth;
   
    ppi->plugin_purpose=purp;
   
    ppi->sup_opts_len=1;
   
    ppi->sup_opts=MyOption;
    
    ///ppi->sup_opts->opt_descr="dfdsfdssdg";
    

  
    return 0;


    }
  
int plugin_process_file( const char* fname, struct option in_opts[], size_t in_opts_len)


{
    
    
     
     if (in_opts_len > 1)
        {
            fprintf (stderr,"Plugin: Слишком много опций, я планировал с одной работать");
            return -1;
        }

    
    
    int odds=0;
    int evens=0;
    FILE *file;
   /// printf("Your flag in file %s\n", in_opts->flag );
   /// puts("Still here");
    file=fopen(fname, "rb");
   //// puts("Again");
    if(!file)
    {
    printf("Error, cant read this file");
   exit(1);
    }
    if(in_opts==NULL)
    {
         fprintf (stderr,"libkmN3248.so: ошибка в опциях у плагина");
            return -1;
    }

     fseek(file,0,SEEK_END);

   int file_length=ftell(file);
  
      int i=0;
     fseek(file,0,SEEK_SET);
     while(i<file_length-1)
     {
         unsigned char my_byte=getc(file)&1;
        
         if(my_byte==1) odds++;
         else evens++;
         i++;

     }
     fclose(file);
     
  
    
if(strcmp("odds", (char*)in_opts->flag)==0)
{
     
    if(odds> evens)
    {
       
       

        if(getenv("LAB1DEBUG"))
       {
            fprintf(stderr, "In file : %s\n", fname);
            fprintf(stderr, "Odds - %d  ; Evens - %d\n", odds, evens);
       }
      
        return 0;
    }
    else 
    {
       
        return 1;
    }
}


if(strcmp("evens", (char*)in_opts->flag)==0)
{
   
    if(odds< evens)
    {
       
       

        if(getenv("LAB1DEBUG"))
       {
            fprintf(stderr, "In file : %s\n", fname);
            fprintf(stderr, "Odds - %d  ; Evens - %d\n", odds, evens);
       }
        return 0;
    }
    else 
    {
       
        return 1;
    }
}

if(strcmp("eq", (char*)in_opts->flag)==0)
{
    //// free(file);
    if(evens==odds)
    {
        if(getenv("LAB1DEBUG"))
       {     
          
            fprintf(stderr, "In file : %s\n", fname);
            fprintf(stderr, "Odds - %d  ; Evens - %d\n", odds, evens);
       }
        return 0;
    }
    else 
    {
       
        return 1;
    }
}
     


return -1;
    
} 
    

