#include <iostream>
#include "bst.h"
#include "tinytest.h"

int main(){
    int x;
    int nleaves;
    int h;

    bst<int> *t = new bst<int>();


    /*
    while( (std::cin >> x))
        t->insert(x);
    */
    int arr[10] = {5, 6, 8, 7, 9, 2, 3, 1, 11, -5};
    t->massInsert(arr,10);



    if(t->size() <= 20) {
      t->inorder();
	    t->preorder();
	    t->postorder();
    }
    printf("\nmy test\n");
    int num = 9;

    //t->remove(num);
    //num = 10;
    //t->remove(num);

    //printf("%d", t->num_geq(10));
    printf("%d", t->num_range(4,5));

    printf("\n end my tests\n");

    h = t->height();
    std::cout << "\n#### Reported height of tree:   " << h << "\n";

    nleaves = t->num_leaves();
    std::cout << "\n#### Reported number of leaves:   " << nleaves  << "\n";

    delete t;

    
    return 0;
}
