#include "pq.h"
#include <stdlib.h> //for malloc
#include <stdio.h>
struct pq_struct {
    struct pq_part* val;
    struct pq_part** id_pq;
    int size;
    int heapType;//if 1 min heap if 0 max heap
    int num_nodes;
};

struct pq_part{
    double priority;
    int id;
    int loc;
};



// YOU IMPLEMENT ALL OF THE FUNCTIONS SPECIFIED IN
//   pq.h BELOW!

PQ * pq_create(int capacity, int min_heap){
    capacity++;
    int size = capacity-1;
    int num_nodes = 0;
    int heapType = min_heap;
    struct pq_part* pq = (struct pq_part *) malloc (capacity * sizeof(struct pq_part) );
    struct pq_part** id= (struct pq_part**) malloc (capacity * sizeof(struct pq_part*) );

    for(int i = 1; i<capacity;i++){
        pq[i].id = 0;
        pq[i].priority = 0;
        pq[i].loc=i;
        //printf("%d\n",pq[i].id);
    }
    PQ* p = (PQ *) malloc (sizeof(PQ) );

    p->val = pq;
    p->id_pq = id;
    p->size = size;
    p->num_nodes = num_nodes;
    p->heapType = heapType;

    return p;
}

void swap(PQ* pq, struct pq_part x, struct pq_part y){
    struct pq_part temp = x;
    pq->val[x.loc] = y;
    pq->val[x.loc].loc = temp.loc;
    int loc = y.loc;
    pq->val[y.loc] = temp;
    pq->val[y.loc].loc = loc;

    pq->id_pq[pq->val[x.loc].id] = &pq->val[x.loc];
    pq->id_pq[pq->val[y.loc].id] = &pq->val[y.loc];


}

//double check that this does what you think it does.
void pq_free(PQ * pq){
    free(pq->val);
    //free(pq);
    //pq->id_pq= NULL;
    //free(pq);
    //free(pq->id_pq);
    //free(pq->val);
    //free(pq);

}



void percDown(PQ * pq, int loc){
    if(loc > 0){
        struct pq_struct temp;
        //double tempPriority;
        //int tempID;
        if(pq->heapType){
            double tempP = (pq->val[loc*2].priority<pq->val[loc*2+1].priority ? pq->val[loc*2].priority: pq->val[loc*2+1].priority);
            int newLoc = (pq->val[loc*2].priority<pq->val[loc*2+1].priority ? loc*2 : loc*2+1);
            if(pq->val[loc].priority >tempP &&newLoc<=pq->num_nodes){
                swap(pq,pq->val[loc],pq->val[newLoc]);
                percDown(pq,newLoc);
            }

        }else{
            double tempP = (pq->val[loc*2].priority>pq->val[loc*2+1].priority ? pq->val[loc*2].priority: pq->val[loc*2+1].priority);
            int newLoc = (pq->val[loc*2].priority>pq->val[loc*2+1].priority ? loc*2 : loc*2+1);
            if(pq->val[loc].priority <tempP &&newLoc<=pq->num_nodes){
                swap(pq,pq->val[loc],pq->val[newLoc]);
                percDown(pq,newLoc);
            }
        }
    }
}

void percUp(PQ * pq, int loc){
    if(loc > 1){
        struct pq_struct temp;
        //double tempPriority;
        //int tempID;
        if(pq->heapType){
            if(pq->val[loc].priority < pq->val[loc/2].priority){
                //swaps the values
                swap(pq,pq->val[loc],pq->val[loc/2]);
                /*
                temp = pq[loc/2];
                pq[loc/2] = pq[loc];
                pq[loc] = temp;

                pq->id_pq[pq->val[loc/2].id] = &pq->val[loc/2];
                pq->id_pq[pq->val[loc].id] = &pq->val[loc];
                // /*
                //recursive call to make sure new tree is balanced.
                percUp(pq,loc/2);
            }
        }else{
            if(pq->val[loc].priority > pq->val[loc/2].priority){
               swap(pq,pq->val[loc],pq->val[loc/2]);
                /*
                temp = pq[loc/2];
                pq[loc/2] = pq[loc];
                pq[loc] = temp;
                 */

                //recursive call to make sure new tree is balanced.
                percUp(pq,loc/2);
            }
        }
    }
}

void balance(PQ * pq, int loc){
    if(pq->heapType){
        if(pq->val[loc].priority<pq->val[loc/2].priority){
            percUp(pq,loc);
        }else{
            percDown(pq,loc);
        }
    }else{
        if(pq->val[loc].priority>pq->val[loc/2].priority){
            percUp(pq,loc);
        }else{
            percDown(pq,loc);
        }
    }
}


int pq_insert(PQ * pq, int id, double priority){
    if(pq->num_nodes == pq->size){
        return 0;
    }
    pq->num_nodes++;
    pq->val[pq->num_nodes].id = id;
    pq->val[pq->num_nodes].priority = priority;
    pq->val[pq->num_nodes].loc = pq->num_nodes;
    pq->id_pq[id] = &pq->val[pq->num_nodes];
    percUp(pq, pq->num_nodes);
    return 1;

}


//done
int pq_change_priority(PQ * pq, int id, double new_priority){
    if(pq->id_pq[id] ==NULL){return 0;}
    //gotta make sure id is in the heap
    pq->id_pq[id]->priority = new_priority;
    balance(pq,pq->id_pq[id]->loc);
    return 1;
}


int pq_remove_by_id(PQ * pq, int id){
    int t1 = id;
    int t2 = pq->num_nodes;
    struct pq_part** deleteme = pq->id_pq;
    if(id<0 || id>pq->size || pq->num_nodes == 0 || pq->id_pq[id]==NULL){return 0;}
    int loc = pq->id_pq[id]->loc;
    swap(pq,*pq->id_pq[id],pq->val[pq->num_nodes]);
    /*
    pq[loc] = pq[num_nodes];
    pq[num_nodes].real = 0; //probably not nessesary, i dont use real
    pq[loc].loc = loc;
     */
    pq->num_nodes--;
    percDown(pq,loc);
    pq->id_pq[id] = NULL;

    return 1;

}

int pq_get_priority(PQ * pq, int id, double *priority){
    if(id<0 || id>pq->num_nodes ){return 0;}
    if(pq->id_pq[id]!=NULL){
        *priority= pq->id_pq[id]->priority;
        return 1;
    }

}

int pq_delete_top(PQ * pq, int *id, double *priority){
    if(pq_peek_top(pq,id,priority)){
        pq_remove_by_id(pq,pq->val[1].id);
        return 1;
    }else{return 0;}
}

int pq_peek_top(PQ * pq, int *id, double *priority){
    if(pq->num_nodes == 0){return 0;}
    *id = pq->val[1].id;
    *priority = pq->val[1].priority;
    return 1;
}

int pq_capacity(PQ * pq){
    return pq->size;
}

int pq_size(PQ * pq){
    if(pq == NULL){return 0;}
    int test =pq->num_nodes;
    return pq->num_nodes;
}


void printPQ(PQ* pq){
    int DELETEME = pq->num_nodes;
    for(int i =1; i <=pq->num_nodes;i++){
        printf("%f\n",pq->val[i].priority);
    }

}

void printIDS(PQ* pq){
    for(int i =1; i<=4;i++){
        printf("%f\n", pq->id_pq[i]->priority);
    }
}













