#include <stdio.h>
#include <stdlib.h>

#include "lista_enc.h"
#include "no.h"

#include "task.h"


// Estados das tarefas
enum TASK_STATE
{
    P_STOPPED, /* Nada a fazer */
    P_RUNNIG, /* Rodando */
    P_READY, /* Pronta para executar */
    P_BLOCKED /* Bloqueda, tempo */
};

struct task
{
    unsigned int id;   // identificador
    unsigned int prior; // prioridade
    TASK_STATE_T state; //estado atual
    unsigned long int ticks; //tempo do sistema na ultima execucao
    unsigned long int t; //perıodo de ativac˜ao //Perıodo de execucao, rotinas temporizadas, bloqueio por tempo
    unsigned long ticks2block;  //Quantidade de tempo restante para bloqueio
    unsigned long int exec_ticks; // Quantidade de tempo executado
    unsigned long int c; //tempo de computac˜ao da tarefa. E o tempo que processo leva para ser executado completamente
};


// Cria uma nova tarefa
task_t *cria_task(int id, int c, int t)
{
    task_t *p = malloc(sizeof(task_t));

    if (p == NULL){
        perror("cria_task:");
        exit(EXIT_FAILURE);
    }

    p->id = id;
    p->c = c;
    p->t = t;
    p->state = 2;

    return p;
}

int obtem_id(task_t* task)
{
    int x = task->id;
    return x;
}

int obtem_prior(task_t* task)
{
    int x = task->prior;
    return x;
}

int obtem_c(task_t* task)   //tempo de computac˜ao tarefa
{
    int x = task->c;
    return x;
}

int obtem_t(task_t* task)   //perıodo de ativac˜ao
{
    int x = task->t;
    return x;
}

int obtem_state(task_t* task)   //state
{
    int x = task->state;
    return x;
}

void ver_c_t(lista_enc_t* lista)
{
    unsigned int c,t;
    float ver_ct=0;
    no_t *no = NULL;
    task_t* task;

    if (lista == NULL)
    {
        fprintf(stderr,"mmc: ponteiros invalidos");
        exit(EXIT_FAILURE);
    }

    no = obter_cabeca(lista);    //get head

    while(no)
    {
        task = obtem_dado(no);
        c = obtem_c(task);
        t = obtem_t(task);
        ver_ct = ver_ct + c/t;

        no = obtem_proximo(no);
    }
    if(ver_ct>1)
    {
        printf("Relacao C/T superior a 1");
        exit(1);
    }
}

int mmc(lista_enc_t* lista)
{
    unsigned int resto, a,b, x, y, mmc=1;
    no_t *no = NULL;
    task_t* task;

    if (lista == NULL)
    {
        fprintf(stderr,"mmc: ponteiros invalidos");
        exit(EXIT_FAILURE);
    }

    no = obter_cabeca(lista);    //get head

    while(no)
    {
        task = obtem_dado(no);
        a = obtem_t(task);
        b = mmc;
        x = a;
        y = b;

        do{
            resto = x%y;
            x = y;
            y = resto;

        } while(resto != 0);

        mmc = a*b/x;

        no = obtem_proximo(no);
    }
    return mmc;
}

task_t* escal_task(int i, lista_enc_t* lista)
{
    no_t* no;
    task_t* task;

    no = obter_cabeca(lista);
    while(no)
    {
        task = obtem_dado(no);
        if((i%task->t)==0){
            printf("No tempo %d a tarefa %d esta pronta\n",i,task->id);
            if(task->state == P_STOPPED)
                task->state = P_READY;
            if(task->state == P_RUNNIG)
                task->ticks++;
        }
        no = obtem_proximo(no);
    }
    return task;
}

