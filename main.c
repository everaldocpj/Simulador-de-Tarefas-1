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

void print_list(lista_enc_t *list);
void print_list_back(lista_enc_t *list);

void free_data(lista_enc_t *list);
lista_enc_t * read_data_file(char* input_file);

void bubble_sort(lista_enc_t *string_list);

int salvaAquivo (lista_enc_t *list, int numTarefas, int mmc );

static const struct option long_options[] = {
    { "list", required_argument, NULL, 'l'},
    { "help", no_argument, NULL, 'h'},
    { NULL, no_argument, NULL, 0}
};

int main(int argc, char** argv)
{
    char * input_file = argv[1];
    int hipert;
    lista_enc_t *data_list;
    escalonador_t* escalonador;

    if (argc<=1)
    {
        printf("Faltou informar o nome do arquivo");
        exit(1);
    }

//    fp = fopen(argv[1], "r");    //abre o arquivo
//
//    if (fp == NULL){
//        printf("Arquivo não pode ser aberto");
//        exit(1);
//    }
//    fclose(fp);	// fecha o arquivo arq.

    data_list = read_data_file(input_file);

    bubble_sort(data_list);


    puts("Lista lida:");
    print_list(data_list);
    puts("\n==================");
    //print_list_back(data_list);


    hipert = mmc(data_list);   // tempo total da CPU (mmc dos periodos)
    printf("Hiper periodo de tarefas: %d\n",hipert);

     salvaAquivo (data_list, 3, 24 );

    //escalonador = escal_task(data_list);


    free_data(data_list);

return 0;

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
    task_t* task;

    if (list == NULL)
    {
        fprintf(stderr, "free_data: Invalid pointer\n");
        exit(EXIT_FAILURE);
    }

    //get head
    no = obter_cabeca(list);

    //print them all
    while (no){
        task = obtem_dado(no);
        id = obtem_id(task);
        c = obtem_c(task);
        t = obtem_t(task);
        printf("id: %d, C: %d, T: %d\n", id,c,t);
        no = obtem_proximo(no);
    }
}


void print_list_back(lista_enc_t *list){
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


lista_enc_t * read_data_file(char* input_file){
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
    //printf("buffer: %s\n", buffer);
    fgets(buffer,100,fp);   // le a 2a linha
    //printf("buffer: %s\n", buffer);

    while(!feof(fp))
    {

        fgets(buffer,100,fp);   //pega uma linha ou 100 caracteres
        sscanf(buffer, "T%d;%d;%d", &id,&c,&t);
        //printf("id: %d, c: %d, t: %d\n",id,c,t);

        task = cria_task(id,c,t);

        no = cria_no(task);
        add_cauda(list, no);

    }

    fclose(fp);

    return list;
}

void bubble_sort(lista_enc_t *string_list)
 {
     no_t *meu_no;
     no_t *pro_no;

    int data_a;
    int data_b;

    int i = 0;

    int swaped = TRUE;

    task_t * task;


    while (swaped == TRUE)
    {
        swaped = FALSE;
        meu_no = obter_cabeca(string_list);

        while (obtem_proximo(meu_no) != NULL)
        {
            pro_no = obtem_proximo(meu_no);
            task = obtem_dado(meu_no);

            data_a = obtem_t(task);
            task = obtem_dado(pro_no);
            data_b = obtem_t(task);

            if (data_b < data_a)
            {
                //puts("SWAP");
                swap_list(string_list, meu_no, pro_no);

                swaped = TRUE;
                meu_no = obtem_proximo(pro_no);
            }
            else
                meu_no = pro_no;

             //printf("\t%d", data_a);
             //printf("\t%d", data_b);

             i++;
         }
         //puts("==================");
         //print_list(string_list);
         //getchar();
     }
    printf("ti: %d, dataA: %d, dataB: %d\n",i, data_a,data_b);


 }

 int salvaAquivo (lista_enc_t *list, int numTarefas, int mmc ){

    FILE *fp = NULL;
    int i,j;
    int T = 0;
    int numT = 0;
    int executeIn = 0;
    int executeOut = 0;


    fp = fopen("simuladorTarefasSaida.tex", "w");

    if (fp == NULL) {
        fprintf(stderr, "read_data_file: Error opening file\n");
        exit(EXIT_FAILURE);
    }


    fprintf (fp, "\\documentclass[a4paper,10pt]{article}\n\\usepackage[utf8]{inputenc}\n\\usepackage[brazil]{babel}\n\n\\usepackage{listings}\n\\usepackage{listingsutf8}\n\\usepackage{rtsched}\n\n%%opening\n\\title{Diagrama de execução}\n\\author{Everaldo\\_1\\\
                 \nJose Nicolau\\_2}\n\n\\begin{document}\n\n\\maketitle\n\n\\begin{figure}[h]\n\\centering %%Cria ambiente, tarefas, escala de tempo\n\n ");

          fprintf (fp, "\\begin{RTGrid}[nosymbols=1,width=10cm]{%d}{%d}\n\n",numTarefas + 1,mmc);
          fprintf (fp, "\\RowLabel{1}{$\tau_1$}\n");
          //for aqui//
          //tarefa #
    for (i= 0; i < (numTarefas + 1); i++){
         // fprintf (fp, "tarefa %d\n\n",i);
    for (j= 0; j < numTarefas; j++){

        fprintf (fp, "\\TaskArrDead{%d}{%d}{%d}\n",i,T,numT);}
          //talvez outro for aqui//
          // execução da tarefa
        // fprintf (fp, "execução da tarefa %d\n\n", i);


    for (j= 0; j < numTarefas; j++){


        fprintf (fp, "\\TaskExecution{%d}{%d}{%d}\n",i,executeIn,executeOut);}
    }
          // Utilização do processador
          fprintf (fp, "\\RowLabel{%d}{CPU}\n",numTarefas + 1);

          //outro for
          fprintf (fp, "\\TaskExecution{%d}{%d}{%d}\n",numTarefas + 1, executeIn,executeOut);


    //final do arquivo
    fprintf (fp, "\\end{RTGrid}\n");
    fprintf (fp, "\\caption{Exemplo de escalonamento para duas tarefas.}\n");
    fprintf (fp, "\\label{fig:ex1}\n");
    fprintf (fp ,"\\end{figure}\n");
    fprintf (fp, "\\end{document}\n");

    fclose(fp);
    system("pause");
    return 0;



}
