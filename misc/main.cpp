#include <iostream>

typedef struct node{
    int val;
    node* next;
}node;

void addNode(node* h,int v){
    if(h->next!=NULL) {
        addNode(h,v);
    }else{
        node n;
        n.val = v;
    }
}

int main() {


    return 0;
}