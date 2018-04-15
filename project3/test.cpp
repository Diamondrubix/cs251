#include <iostream>
#include "bst.h"

int main(){
    int x;
    int nleaves;
    int h;

    bst<int> *t = new bst<int>();

    while( (std::cin >> x))
        t->insert(x);

    if(t->size() <= 20) {
      t->inorder();
	    t->preorder();
	    t->postorder();
    }
    printf("\nmy test\n");
    int num = -999;
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
