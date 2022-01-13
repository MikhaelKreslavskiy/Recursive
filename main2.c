
#include <ftw.h>
#include "countPlug.h"
#include"countFile.h"
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <bits/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "getPath.h"
#include<dlfcn.h>
#include "longopt.h"
///#include"check.h"
#include "clean.h"
///char* mass_paths[50];
int count_of_plugs;
void ** array_of_plugins;
void** array_need_plugins;
int nplug = 0;
//количество найденных плагинов
int *mas;

int count_of_entry_opts;
int number_long_opt=0;
int count_need=0, AND, OR, NOT;
void countFile(char* path);
void countPlug(char* path);
int clean();
char* getPath(void);
int find_opt();
 struct option* long_options;

    

    
    
int main (int argc, char* argv[]) 
{

    
   /// long_options=(struct option*)malloc(sizeof(struct option));
    printf("Lab1 - %s", getenv("LAB1DEBUG"));

    char* my_path=getPath();

    for(int i = 0; i < argc -1; i++)
    {
        if (argv[i][0] == '-' && argv[i][1] == 'P')
        {
            if (argv[i+1]==NULL)
            {
                fprintf(stderr, "Аргумент опции -Р не введен\n");
               goto END;
            }
            struct stat st;
            if(stat(argv[i+1],&st) == -1)
            {
                fprintf(stderr, "Аргумент опции -Р не определен\n");
                goto END;
            }
           if((st.st_mode & S_IFMT) == S_IFDIR)
            {
                ////puts("Iam here");
                my_path = argv[i+1];
                break;
            }
        else 
                fprintf(stderr, "Аргумент опции -Р не является каталогом\n");
            goto END;
        }
    }
   


   printf("%s\n", my_path);
   countPlug(my_path);
   find_opt();

int n;
 int option_index = 0;

mas=(int*)malloc(sizeof(int)*number_long_opt);
for(int i=0;i<number_long_opt;i++)
{
    mas[i]=0;
}
while ((n = getopt_long(argc,argv,"P:AONvh",long_options,&option_index))!=-1)
    {
        
        switch(n)
        {
            case 0:
            {  

               
               mas[option_index]=1;
               long_options[option_index].flag=(int*)optarg;
              break;
              
            }
            
            case 'v':
            {
                printf("Креславский Михаэль, N3248, вариант 6 \n");
                break;
            }
            case 'h':
            {
                printf("Вывод справки по опциям:\n");
                printf("-A -- Объединение опций плагинов с помощью операции «И» (действует по умолчанию).\n");
                printf("-O -- Объединение опций плагинов с помощью операции «ИЛИ»\n");
                printf("-N -- Инвертирование условия поиска (после объединения опций плагинов с помощью -A или -O)\n");
                printf("-h -- Вывод справки по опциям\n");
                printf("-v -- Вывод версии программы и информации о программе (ФИО исполнителя, номер группы, номер варианта лабораторной)\n");
                printf("-P dir -- Каталог с плагинами\n");
                break;
            }
            case 'O':
            {
                OR=1;
                break;
            }
            case 'A':
            {
                AND=1;
                break;
            }
            case 'N':
            {
                NOT=1;
                break;
            }
         case 'P':
           {
               break;
            }
            case '?':
            {
                fprintf(stderr, "I don't understand\n");
                goto END;
            }
            default:
            {
                fprintf(stderr, "Strange\n");
               goto END;
            }
        }
    }
     for (int i = 0; i <number_long_opt; i++)
    {
        if (mas[i] == 1)
            break;
        if (i == number_long_opt-1)
        {
           //// fprintf(stderr, "Ошибка: нет введенных опций\n");
            goto END;
        }
    }

    if((OR==1)&&(AND==1))
    {
        printf("%s\n", "Нельзя одновременно вводить AND и OR");
        goto END;
    }

     if (OR == 0 && AND == 0)
        AND = 1;
   
    countFile(my_path);
    END:
   
    free(my_path);
    clean();
     my_path=NULL;
    
    return 0;
}

