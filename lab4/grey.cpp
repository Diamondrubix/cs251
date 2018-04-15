#include <string>
#include <vector>
#include <iostream>
#include <stdlib.h>
using std::vector;
using std::string;
using std::cout;
using std::endl;

/**
 * this function returns (as a pointer), a
 * vector of strings representing a valid
 * grey code of lengh n
 */
vector<string> * grey(unsigned int n) {
  vector<string> *codes;

  // base-case:  for n==0, there is (technically)
  //   one bit-string - the empty string
  if(n==0) {
    codes = new vector<string>();
    codes->push_back("");
    return codes;
  }
  else {
    // YOUR CODE HERE!!!
  }

}

int main(int argc, char *argv[]){
  vector<string> *codes;
  unsigned int n = 4;

  if(argc==2)
    n = atoi(argv[1]);

  codes = grey(n);

  for(string c : *codes) {
    cout <<   c <<  endl;
  }
  return 0;
}
