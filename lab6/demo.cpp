#include "List.h"

#include <stdlib.h>
#include <iostream>
#include <string>



using namespace std;


int main(int argc, char *argv[]){
  List<string> *words = new List<string>;
  string s;

  //while(cin >> s ) {
  //for(int i = 5; i >0;i--)
  words->push_back("test");
  words->push_back("what");
  words->push_back("apple");
  words->push_back("bunny");
  words->push_back("test");
  words->push_back("juice");
  //}
  cout << "BEFORE SORTING:\n";
  words->print();

  words->qsort();
  cout << "AFTER SORTING:\n";
  words->print();

  delete words;

  return 0;
}
