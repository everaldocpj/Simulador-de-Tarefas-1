#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "lista_enc.h"
#include "no.h"

#define TRUE 1
#define FALSE 0


void print_list(lista_enc_t *list);
void print_list_back(lista_enc_t *list);

void free_data(lista_enc_t *list);

lista_enc_t * read_data_file();

void bubble_sort(lista_enc_t *string_list);

struct tarefas {
    int id;
    int  c;
    int  t;
};
typedef struct tarefas tarefa_t;

tarefa_t* task;


int main(int argc, char** argv)
{
   lista_enc_t *data_list;
    
    data_list = read_data_file();
   puts("Lista lida:");
   print_list(data_list);
    
     


   
  //  puts("==================");
   //  puts("Ordenada");
  //  bubble_sort(data_list);
   // print_list(data_list);
   // puts("==================");
   // print_list_back(data_list);


    free_data(data_list);

    return 0;
}

// Ordena lista em ordem alfabética
void bubble_sort(lista_enc_t *string_list)
{
    no_t *meu_no;
    no_t *pro_no;

    char *data_a;
    char *data_b;

    int i = 0;

    int swaped = TRUE;

    while (swaped == TRUE)
    {
        swaped = FALSE;
        meu_no = obter_cabeca(string_list);

        while (obtem_proximo(meu_no) != NULL) {

            pro_no = obtem_proximo(meu_no);
            data_a = obtem_dado(meu_no);
            data_b = obtem_dado(pro_no);

            printf("\ti: %d\n",i);

            if (strcmp(data_b, data_a) < 0) {
                puts("SWAP");
                swap_list(string_list, meu_no, pro_no);

                swaped = TRUE;
                meu_no = obtem_proximo(pro_no);
            }
            else
                meu_no = pro_no;

            printf("\t%s", data_a);
            printf("\t%s", data_b);

            i++;
        }
        puts("==================");
        print_list(string_list);
        getchar();
    }

}

void free_data(lista_enc_t *list)
{
    no_t *no;
    no_t *no_;
    char *data;

    if (list == NULL) {
        fprintf(stderr, "free_data: Invalid pointer\n");
        exit(EXIT_FAILURE);
    }
    // Free all strings
    no = obter_cabeca(list);

    while (no) {
        data = obtem_dado(no);
        free(data);
        no = obtem_proximo(no);
    }
    //free all nodes
    no = obter_cabeca(list);
    while (no) {
        no_ = no;
        no = obtem_proximo(no);
        free(no_);
    }
    //free list
    free(list);
}

void print_list(lista_enc_t *list)
{
    no_t *no;
    tarefa_t *data;

    if (list == NULL) {
        fprintf(stderr, "free_data: Invalid pointer\n");
        exit(EXIT_FAILURE);
    }
    printf("id - C - T\n ");
    //get head
    no = obter_cabeca(list);

    //print them all
    while (no) {
        data = obtem_dado(no);
        
        
        
        printf("%d - %d - %d\n ",  data->id,data->c,data->t);
        no = obtem_proximo(no);
    }
}

void print_list_back(lista_enc_t *list)
{
    no_t *no;
    char *data;

    if (list == NULL) {
        fprintf(stderr, "free_data: Invalid pointer\n");
        exit(EXIT_FAILURE);
    }

    //get head
    no = obter_cauda(list);

    //print them all
    while (no) {
        data = obtem_dado(no);
        printf("%s", data);
        no = obtem_anterior(no);
    }
}
lista_enc_t * read_data_file()
{
    FILE *fp = NULL;
    lista_enc_t *list = NULL;
    char buffer[100];
    int n = 0;
    tarefa_t* task;
    no_t *no;
    int  id = 0 ;
    char *tokenPtr;
    int line = 0;
   
    list = cria_lista_enc();

    if (list == NULL) {
        fprintf(stderr, "read_data_file: Error creating list\n");
        exit(EXIT_FAILURE);
    }

    //try open input_file
    fp = fopen("arqTarefas2.txt", "r");

    if (fp == NULL) {
        fprintf(stderr, "read_data_file: Error opening file\n");
        exit(EXIT_FAILURE);
    }

    while (fgets(buffer, 128, fp)!=0) {
        if (buffer == NULL)
        {   fprintf(stderr, "read_data_file: Error reading file\n");
            exit(EXIT_FAILURE);
        }
        printf("buffer\n%s\n",buffer);
        
       
        n  = 0;
        if(line > 0){
            
         tokenPtr = strtok(buffer, ";");
         task =  malloc(sizeof(tarefa_t) );
        
        
    
            while(tokenPtr != NULL)
                
            {
               
                  if ( n == 0){
                      printf("id %d\n",id);
                      printf("C  %s\n",tokenPtr);
                    task->id = id;
                    task->c =  atoi(tokenPtr);
                    
                    id++;
                      n++;}
                      else {
                          printf("T  %s\n",tokenPtr);
                          task->t = atoi(tokenPtr);
                          n = 0;
                          no = cria_no(task);
                          add_cauda(list, no);
                      }
                
        
        
        
                tokenPtr = strtok(NULL, ";");}
        
            
        
        }
        line = line + 1;
    }

    fclose(fp);

    return list;
}
