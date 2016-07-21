#ifndef TASK_H_INCLUDED
#define TASK_H_INCLUDED

typedef struct task task_t;

typedef enum TASK_STATE TASK_STATE_T;

task_t *cria_task(int id, int c, int t);
int obtem_id(task_t* task);
int obtem_prior(task_t* task);
int mmc(lista_enc_t* lista);

#endif // TASK_H_INCLUDED
