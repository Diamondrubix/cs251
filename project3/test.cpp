#include <iostream>
#include "bst.h"
//#include "tinytest.h"

bool massInsert(bst<int> *t,int* x, int size){
    for(int i = 0; i<size;i++){
        t->insert(x[i]);
    }
}

//void _inorder(bst<)

void inorder(bst<int>*t){
    std::vector<int>* v= t->to_vector();
    for(int i = 0; i<v->size();i++){
        printf("%d ",v->at(i));
    }
    printf("\n");

}


void orders(bst<int>*t){
    if(t->size() <= 20) {
        t->inorder();
        t->preorder();
        t->postorder();
    }
}

void testInsert(bst<int>*t){
    std::vector<int>* v1 = t->to_vector();
    //std::vector<int>* v2 = inorder;
    //for(int i = 0;i<v->size();i++) {
    //    ASSERT_EQUALS(v[i],)
    //}
}

int main(){
    int x;
    int nleaves;
    int h;

    bst<int> *t = new bst<int>();


    /*
    while( (std::cin >> x))
        t->insert(x);
    */


    printf("\nmy test\n");
    int size = 10;
    int arr[size] = {111,22,17,88,33,88,19,91,11,26}; //6
    //int arr[size] = {5, 6, 8, 7, 9, 2, 3, 1, 11, -5}; //10
    massInsert(t,arr,size);
    int num = 6;
    t->remove(num);
    inorder(t);
    orders(t);
    printf("\end tests\n");

    h = t->height();
    std::cout << "\n#### Reported height of tree:   " << h << "\n";

    nleaves = t->num_leaves();
    std::cout << "\n#### Reported number of leaves:   " << nleaves  << "\n";

    delete t;

    
    return 0;
}
