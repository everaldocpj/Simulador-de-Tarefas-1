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
    unsigned int c; //tempo de computac˜ao da tarefa. E o tempo que processo leva para ser executado completamente
    unsigned int t; //perıodo de ativac˜ao
    TASK_STATE_T state;

/*
//estado atual
 //   TASK_STATE uc_status;
//tempo do sistema na ´ ultima execuc¸˜ ao
    unsigned long ul_ticks;
//Per´ ıodo de execuc¸˜ ao, rotinas temporizadas, bloqueio por tempo
    unsigned long ul_period_ticks;
//Quantidade de tempo restante para bloqueio
    unsigned long l_ticks2block;
// Quantidade de tempo executado
    unsigned long l_exec_ticks;
// Tempo de execuc¸˜ ao
    unsigned long ul_comp_time;
    */
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
    p->prior = 0;
    p->c = c;
    p->t = t;
    p->state = 0;

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

int mmc(lista_enc_t* list)
{
    return 12;
}
