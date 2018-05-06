#include <stdio.h>
#include "pq.h"
#include <stdlib.h>



int main() {
    printf("Hello, World!\n");
    int testId;
    double testPriority;
    PQ *pq;
    pq = pq_create(20,1); //if 1 min heap if 0 max heap
    int arr[20] = {8,4,7,5,9,3,10,2,0,1,9,4,7,5,8,2,3,4,5,9};
    for(int i = 0;i<5;i++){
        pq_insert(pq,i,arr[i]);
    }


    //pq_insert(pq,1,1);
    pq_change_priority(pq,3, 100);
    pq_delete_top(pq,&testId,&testPriority);


    //pq_change_priority()
    //pq_change_priority(pq,8,100);

    //printf("%d\n",pq_size(pq));

    /*
    pq_delete_top(pq,&testId,&testPriority);
    pq_delete_top(pq,&testId,&testPriority);
    pq_delete_top(pq,&testId,&testPriority);
    pq_delete_top(pq,&testId,&testPriority);
    pq_delete_top(pq,&testId,&testPriority);
    pq_delete_top(pq,&testId,&testPriority);
    pq_delete_top(pq,&testId,&testPriority);
     */

    //pq_insert(pq,8,8);
    //pq_insert(pq,8,8);
    //pq_insert(pq,1,2);

    //printf("%d %f\n",testId,testPriority);

    //pq_remove_by_id(pq,2);


    //printIDS();
    printPQ(pq);
    pq_free(pq);
    return 0;
}



