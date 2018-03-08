
#include "GWInterface.h"
#include <vector>
#include <iostream>
#include <stdlib.h> //with maloc
using namespace std;
//using std::vector;


class GridWorld : public GWInterface {
private:
    typedef struct person{
        int id;
        int row;
        int col;
        person* next;
        person* prev;
        bool alive; // idk if this is nessesary
    }person;

    typedef struct district{
        person* head;
        person* back;
        int population; //population
    }district;

    vector<person*> totalPop;

    district ghost;

    district** world;
    int rows;
    int cols;
    /*pops the oldest ghost off the stack
    but lets be honest, ghostbuster sounds a whole lot cooler
    than popGhost*/
    int ghostBuster(){
        int ret = ghost.head->id;
        person* temp = ghost.head->next;
        free(ghost.head);
        ghost.population--;
        ghost.head = temp;
        return ret;

    }
    int getNewId(){
        if(ghost.population==0){
            return totalPop.size();
        }
        return ghostBuster();
    }
    //pushes to the back
    void pushDistrict(district* d, person* p){
        d->population++;
        if(d->head ==nullptr){
            d->head = p;
            d->back = p;
            p->next = nullptr;
            p->prev = nullptr;
            return;
        }
        if(d->head == d->back){
            d->back = p;
            d->head->next = p;
            p->prev = d->head;
        }else {
            d->back->next = p;
            p->prev = d->back;
            p->next = nullptr;
            d->back = d->back->next;
        }

    }

    bool moveT(person* n, district* d, district* dest){
        //district* d = &world[n->row][n->col];
        d->population--;
        if(d->population==1){ //replace the thing with d later. or not, shouldn't matter
            world[n->row][n->col].head = nullptr;
            world[n->row][n->col].back = nullptr;
            world[n->row][n->col].population=0;
            pushDistrict(dest, n);
            return true;
        }
        if(n->prev ==nullptr){
            d->head = n->next;
            pushDistrict(dest, n);
            return true;
        }
        person* temp = n->prev;
        person* temp2 = n->next;
        temp->next = temp2;
        temp2->prev = temp;
        pushDistrict(dest, n);
        return true;
    }


public:
    GridWorld(unsigned nrows, unsigned ncols)   {
        rows = nrows;
        cols = ncols;
        world = (district**) malloc (nrows * sizeof(district*) );
        int i,j;
        for(i=0; i<ncols;i++){
            world[i] = (district*) malloc (ncols * sizeof(district) );
        }


      // your constructor code here!
    }
    ~GridWorld(){
      // your destructor code here.
    }
    //const time
    bool birth(int row, int col, int &id){
        if(this->rows>=row && this->cols>=col) {
            person *n = new person;
            n->id = getNewId();
            n->alive = true;
            n->row = row;
            n->col = col;
            pushDistrict(&world[row][col],n);
            if(n->id ==totalPop.size()) {
                totalPop.push_back(n);
            }else{
                totalPop[n->id] = n;
            }
            id = n->id;
            return true;
        }

      return false;
    }
    //const time
    bool death(int personID){
        if(personID>totalPop.size()){
            return false;
        }
        person* n = totalPop[personID];
        if(n->alive) {
            n->alive = false;
            district* d = &world[n->row][n->col];
            d->population--;
            if(d->population==1){ //replace the thing with d later. or not, shouldn't matter
                world[n->row][n->col].head = nullptr;
                world[n->row][n->col].back = nullptr;
                world[n->row][n->col].population=0;
                pushDistrict(&ghost, n);
                return true;
            }
            if(n->prev ==nullptr){
                d->head = n->next;
                pushDistrict(&ghost, n);
                return true;
            }
            person* temp = n->prev;
            person* temp2 = n->next;
            temp->next = temp2;
            temp2->prev = temp;
            pushDistrict(&ghost, n);
            return true;
        }

      return false;
    }
    //const
    bool whereis(int id, int &row, int &col)const{
        if(id>totalPop.size()){
            return false;
        }
        person* p = totalPop[id];
        if(p->alive){
            row = p->row;
            col = p->col;
            return true;
        }
      return false;
    }


    bool move(int id, int targetRow, int targetCol){
        if(id>totalPop.size()){
            return false;
        }

      return false;
    }

    std::vector<int> * members(int row, int col)const{

      return nullptr;
    }

    int population()const{
      return 0;
    }
    
    int population(int row, int col)const{
      return 0;
    }

    int num_rows()const {
      return 0;
    }
    int num_cols()const {
      return 0;
    }

};
