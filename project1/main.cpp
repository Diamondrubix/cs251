#include "List.h"

#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;

List<int> * slow_list(int n) {
    List<int> *list = new List<int>();
    int i;
    for(i=0;i<20;i++){
        list->push_back(i);
    }
    return list;
    // placeholder
    //return nullptr;
}

int main(int argc, char *argv[]){
    List<int> *list = new List<int>();
    List<int> *list4 = new List<int>();
    List<string> *list2 = new List<string>();
    List<string> *list3 = new List<string>();
    int x;
    int n, ndel;

    n = 1000;

    if(argc == 2) {
        n = atoi(argv[1]);
    }


    for(x=1; x<=4; x++) {
        //list->push_front(x);
    }
    //list->print();

    for(x=1; x<=4; x++) {
        list->push_back(x);
    }
    for(x=1; x<=8; x++) {
        list4->push_back(x);
    }


    //list->print();
    //list->push_back(2);
    list->push_back(7);
    list->push_back(9);
    list->print();
    list4->print();
    list->merge_with(*list4);
    //List<int> *nl = list->filter_leq(5);
    list->print();
    list4->print();
    //nl->print();
    //list->concat(*list4);
    //list->print();

    /*rev test
    list->print();
    list->reverse();
    list->print();
     */
    //printf("%d",list->equal_to(*list4));


    /*suffix maxes test
    list->print();
    list->push_back(6);
    list->push_back(-18);
    list->push_back(12);
    list->push_back(4);
    list->push_back(1);
    list->push_back(7);
    list->push_back(2);
    list->push_back(5);
    list->push_back(4);
    list->print();
    list->suffix_maxes()->print();
    //*/

    /*merge test
    list->print();
    list4->print();
    list->merge_with(*list4);
    printf("after sort\n");
    list->print();
    /*insert_sortet Test
    //list->push_back(7);
    //list->push_front(2);
    list->print();
    list->insert_sorted(6);
    //list->reverse();;p
    printf("after sort\n");
    list->print();
    //*/

    /*

    list->pop_front(x);
    cout << "popped " << x <<endl;
    list->print();

    list->slow_remove_all(2);
    cout << "after remove-all(2):\n";
    list->print();

    // string words[] = {"hello", "goodbye", "sunrise", "sunset"};
    string words[] = {"alice", "bob", "cathy", "donald"};


    for(int i=0; i<4; i++) {
        list2->push_front(words[i]);
        list3->push_back(words[i]);
    }

    list2->print();
    list3->print();

    cout << "list  sorted?  " << list->is_sorted() << endl;
    cout << "list2 sorted?  " << list2->is_sorted() << endl;
    cout << "list3 sorted?  " << list3->is_sorted() << endl;


    // list2->front = NULL;


    delete list;
    delete list2;
    delete list3;

    ///***  UNCOMMENT THIS CODE ONCE YOU HAVE WRITTEN YOUR
     //*     slow_list FUNCTION

    list = slow_list(n);

    cout << "starting slow_remove_all (n=" << n << ")" << endl;
    ndel = list->slow_remove_all(0);
    cout << "slow_remove_all done!" << endl;
    cout << "    num-deleted:    " << ndel << endl;
    cout << "    list-len after: " << list->length()   << endl;

    delete list;
     */

    //***/

    return 0;
}
