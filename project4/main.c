#include <stdio.h>
#include "pq.h"
#include <stdlib.h>



int main() {
    printf("Hello, World!\n");
    PQ *pq;
    pq = pq_create(20,1);
    pq_insert(pq,1,1); //id priority
    pq_insert(pq,2,2);
    pq_insert(pq,5,5);
    pq_insert(pq,7,7);
    pq_insert(pq,6,6);
    pq_insert(pq,8,8);

    //pq_change_priority(pq,8,100);
    int testId;
    double testPriority;
    pq_delete_top(pq,&testId,&testPriority);
    printf("%d %f\n",testId,testPriority);
    //pq_delete_top(pq,&testId,&testPriority);
    //printf("%d %f\n",testId,testPriority);

    //pq_remove_by_id(pq,2);

    //printIDS();
    printPQ(pq);
    return 0;
}


