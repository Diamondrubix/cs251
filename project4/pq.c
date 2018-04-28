#include "pq.h"
#include <stdlib.h> //for malloc
#include <stdio.h>
struct pq_struct {
    double priority;
    int id;
    int loc;
    int real;
};

//struct pq_struct* pq;
struct pq_struct** id_pq;
int size;
int heapType;//if 1 min heap if 0 max heap
int num_nodes;


// YOU IMPLEMENT ALL OF THE FUNCTIONS SPECIFIED IN
//   pq.h BELOW!

PQ * pq_create(int capacity, int min_heap){
    capacity++;
    size = capacity;
    num_nodes = 0;
    heapType = min_heap;
    struct pq_struct* pq = (struct pq_struct *) malloc (capacity * sizeof(struct pq_struct) );
    id_pq= (struct pq_struct**) malloc (capacity * sizeof(struct pq_struct*) );

    for(int i = 1; i<capacity;i++){
        pq[i].real =0;
        pq[i].id = 0;
        pq[i].priority = 0;
        pq[i].loc=i;
        //printf("%d\n",pq[i].id);
    }

    return pq;
}

//double check that this does what you think it does.
void pq_free(PQ * pq){

    ///for(int i = 0; i <size;i++){
        //free(pq[i]);
        //free(id_pq[i]);
    //}
    free(pq);
    //free(id_pq);
}



void percDown(PQ * pq, int loc){
    if(loc > 0){
        struct pq_struct temp;
        //double tempPriority;
        //int tempID;
        if(heapType){
            double tempP = (pq[loc*2].priority<pq[loc*2+1].priority ? pq[loc*2].priority: pq[loc*2+1].priority);
            int newLoc = (pq[loc*2].priority<pq[loc*2+1].priority ? loc*2 : loc*2+1);
            if(pq[loc].priority >tempP &&newLoc<=num_nodes){
                temp = pq[loc];
                pq[loc] = pq[newLoc];
                pq[newLoc] = temp;
                percDown(pq,newLoc);
            }

        }else{
            if(pq[loc].priority > pq[loc/2].priority){
                temp = pq[loc/2];
                pq[loc/2] = pq[loc];
                pq[loc] = temp;
                //recursive call to make sure new tree is balanced.
                //percUp(pq,loc/2);
            }
        }
    }
}

void percUp(PQ * pq, int loc){
    if(loc > 1){
        struct pq_struct temp;
        //double tempPriority;
        //int tempID;
        if(heapType){
            if(pq[loc].priority < pq[loc/2].priority){
                //swaps the values
                temp = pq[loc/2];
                pq[loc/2] = pq[loc];
                pq[loc] = temp;
                //recursive call to make sure new tree is balanced.
                percUp(pq,loc/2);
            }
        }else{
            if(pq[loc].priority > pq[loc/2].priority){
                temp = pq[loc/2];
                pq[loc/2] = pq[loc];
                pq[loc] = temp;
                //recursive call to make sure new tree is balanced.
                percUp(pq,loc/2);
            }
        }
    }
}

void balance(PQ * pq, int loc){
    if(heapType){
        if(pq[loc].priority<pq[loc/2].priority){
            percUp(pq,loc);
        }else{
            percDown(pq,loc);
        }
    }else{
        if(pq[loc].priority>pq[loc/2].priority){
            percUp(pq,loc);
        }else{
            percDown(pq,loc);
        }
    }
}


int pq_insert(PQ * pq, int id, double priority){
    if(num_nodes == size){
        return 0;
    }
    num_nodes++;
    pq[num_nodes].id = id;
    pq[num_nodes].priority = priority;
    pq[num_nodes].loc = num_nodes;
    id_pq[id] = &pq[num_nodes];
    percUp(pq, num_nodes);
    return 1;

}


//done
int pq_change_priority(PQ * pq, int id, double new_priority){
    if(id_pq[id] ==NULL){return 0;}
    //gotta make sure id is in the heap
    id_pq[id]->priority = new_priority;
    balance(pq,id_pq[id]->loc);
    return 1;
}


int pq_remove_by_id(PQ * pq, int id){
    if(id<0 || id>num_nodes){return 0;}

    int loc = id_pq[id]->loc;
    pq[loc] = pq[num_nodes];
    pq[num_nodes].real = 0; //probably not nessesary, i dont use real
    pq[loc].loc = loc;
    num_nodes--;
    percDown(pq,loc);
    id_pq[id] = NULL;

    return 1;

}

int pq_get_priority(PQ * pq, int id, double *priority){
    if(id<1 || id>num_nodes ){return 0;}
    if(id_pq[id]!=NULL){
        *priority= id_pq[id]->priority;
    }

}

int pq_delete_top(PQ * pq, int *id, double *priority){
    if(pq_peek_top(pq,id,priority)){
        pq_remove_by_id(pq,1);
        return 1;
    }else{return 0;}
}

int pq_peek_top(PQ * pq, int *id, double *priority){
    if(num_nodes == 0){return 0;}
    *id = pq[1].id;
    *priority = pq[1].priority;
    return 1;
}

int pq_capacity(PQ * pq){
    return size;
}

int pq_size(PQ * pq){
    return num_nodes;
}


void printPQ(PQ* pq){
    for(int i =1; i <=num_nodes;i++){
        printf("%f\n",pq[i].priority);
    }
}

void printIDS(){
    for(int i =1; i<=4;i++){
        printf("%f\n", id_pq[i]->priority);
    }
}













