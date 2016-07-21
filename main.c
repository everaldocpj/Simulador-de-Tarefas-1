#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "lista_enc.h"
#include "no.h"
#include "task.h"

#define TRUE 1
#define FALSE 0

static void usage(void);

void print_list(lista_enc_t *list);
void print_list_back(lista_enc_t *list);

void free_data(lista_enc_t *list);
lista_enc_t * read_data_file(char* input_file);

static const struct option long_options[] = {
    { "list", required_argument, NULL, 'l'},
    { "help", no_argument, NULL, 'h'},
    { NULL, no_argument, NULL, 0}
};

int main(int argc, char** argv)
{
//    FILE *fp;
//    char ch;
    char * input_file = argv[1];
    int cpu;
    lista_enc_t *data_list;

    if (argc<=1){
        printf("Faltou informar o nome do arquivo");
        exit(1);
    }

//    fp = fopen(argv[1], "r");    //abre o arquivo
//
//    if (fp == NULL){
//        printf("Arquivo não pode ser aberto");
//        exit(1);
//    }
    data_list = read_data_file(input_file);


    puts("Lista lida:");
    print_list(data_list);
    puts("\n==================");
    //print_list_back(data_list);


    cpu = mmc(data_list);   // tempo total da CPU
    printf("CPU: %d",cpu);


//    fclose(fp);	// fecha o arquivo arq.

    free_data(data_list);

return 0;

}

static void usage(void) {
    puts("Simulador de tarefas");
        puts("--------------------------------");

    exit(EXIT_FAILURE);
}


void free_data(lista_enc_t *list)
{
    no_t *no;
    no_t *no_;
    char *data;

    if (list == NULL)
    {
        fprintf(stderr, "free_data: Invalid pointer\n");
        exit(EXIT_FAILURE);
    }
    // Free all strings
    no = obter_cabeca(list);

    while (no)
    {
        data = obtem_dado(no);
        free(data);
        no = obtem_proximo(no);
    }
    //free all nodes
    no = obter_cabeca(list);
    while (no)
    {
        no_ = no;
        no = obtem_proximo(no);
        free(no_);
    }
    //free list
    free(list);
}

void print_list(lista_enc_t *list)
{
    int id, c, t;
    no_t *no;
    char *data;

    task_t* task;

    if (list == NULL)
    {
        fprintf(stderr, "free_data: Invalid pointer\n");
        exit(EXIT_FAILURE);
    }

    //get head
    no = obter_cabeca(list);

    //print them all
    while (no)
    {
        task = (char*)obtem_dado(no);
        id = obtem_id(task);
        printf("id: %d\n", id);
        no = obtem_proximo(no);
    }
}


void print_list_back(lista_enc_t *list)
{
    no_t *no;
    char *data;

    if (list == NULL)
    {
        fprintf(stderr, "free_data: Invalid pointer\n");
        exit(EXIT_FAILURE);
    }

    //get head
    no = obter_cauda(list);

    //print them all
    while (no)
    {
        data = obtem_dado(no);
        printf("%s", data);
        no = obtem_anterior(no);
    }
}
lista_enc_t * read_data_file(char* input_file)
{
    FILE *fp = NULL;
    char buffer[100];   //leitura de dados
    int id, c, t;

    lista_enc_t *list = NULL;
    task_t* task;
    no_t* no;

    list = cria_lista_enc();

    if (list == NULL)
    {
        fprintf(stderr, "read_data_file: Error creating list\n");
        exit(EXIT_FAILURE);
    }

    //try open input_file
    fp = fopen(input_file, "r");

    if (fp == NULL)
    {
        fprintf(stderr, "read_data_file: Error opening file\n");
        exit(EXIT_FAILURE);
    }

    fgets(buffer,100,fp);   // le a 1a linha
    printf("buffer: %s\n", buffer);
    fgets(buffer,100,fp);   // le a 2a linha
    printf("buffer: %s\n", buffer);

    while(!feof(fp))
    {

        fgets(buffer,100,fp);   //pega uma linha ou 100 caracteres
        sscanf(buffer, "T%d;%d;%d", &id,&c,&t);
        printf("id: %d, c: %d, t: %d\n",id,c,t);

        task = cria_task(id,c,t);

        no = cria_no(task);
        add_cauda(list, no);

    }

    fclose(fp);

    return list;
}
