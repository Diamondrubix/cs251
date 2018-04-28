
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
    int totalPopulation;
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
        if(d->head ==nullptr || d->population==1){
            d->head = p;
            d->back = p;
            p->next = nullptr;
            p->prev = nullptr;
            return;
        }
        if(d->population==2){
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
        if(d->population==0){ //replace the thing with d later. or not, shouldn't matter
            world[n->row][n->col].head = nullptr;
            world[n->row][n->col].back = nullptr;
            //world[n->row][n->col].population=0;
            pushDistrict(dest, n);
            return true;
        }
        if(n->prev ==nullptr){
            d->head = n->next;
            d->head->prev = nullptr;
            pushDistrict(dest, n);
            return true;
        }
        person* temp = n->prev;
        if(n->next ==nullptr){
            d->back = d->back->prev;
            temp->next = nullptr;
        }else {
            person *temp2 = n->next;
            temp->next = temp2;
            temp2->prev = temp;
        }
        pushDistrict(dest, n);
        return true;
    }

    void deleteDistrict(district* d){

        person* p = d->head;
        person* temp = p;
        while(temp!= nullptr){
            p = p->next;
            delete temp;
            temp = p;
        }
    }


public:
    GridWorld(unsigned nrows, unsigned ncols)   {
        rows = nrows;
        cols = ncols;
        totalPopulation = 0;
        world = (district**) malloc (nrows * sizeof(district*) );
        int i,j;
        for(i=0; i<nrows;i++){
            world[i] = (district*) malloc (ncols * sizeof(district) );
        }


        // your constructor code here!
    }



    ~GridWorld(){
        int i,j;

        for(i=0; i<rows;i++){
            for(j=0; j<cols;j++){
                deleteDistrict(&world[i][j]);
            }
            free(world[i]);
        }
        totalPop.clear();
        //delete(&totalPop);
        free(world);

        // your destructor code here.
    }

    //const time
    bool birth(int row, int col, int &id){
        if(this->rows>=row && this->cols>=col && row>=0 && col>=0) {
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
            totalPopulation++;
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
            if(moveT(n,d,&ghost)){
                totalPopulation--;
                return true;
            }else {
                return false;
            }
        }

        return false;
    }
    //const
    bool whereis(int id, int &row, int &col)const{
        if(id>totalPop.size()-1 || id<0){
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

    //const
    bool move(int id, int targetRow, int targetCol){
        if(targetRow<0 || targetCol<0 || targetCol>=this->cols || targetRow>=this->rows){
            return false;
        }
        if(id<0||id>totalPop.size()-1){
            return false;
        }

        person* p = totalPop[id];
        if(p->alive) {
            district *d1 = &world[p->row][p->col];
            p->row = targetRow;
            p->col = targetCol;
            district *d2 = &world[targetRow][targetCol];
            return moveT(p, d1, &world[targetRow][targetCol]);
        }else{
            return false;
        }

    }

    std::vector<int> * members(int row, int col)const{
        vector<int>* mems = new vector<int>;
        if(row<=rows && col<=cols) {
            district d = world[row][col];
            person* temp = d.head;
            while(temp!= nullptr) {
                mems->push_back(temp->id);
                temp = temp->next;
            }
        }
        return mems;
    }

    int population()const{
        return totalPopulation;
    }
    //const
    int population(int row, int col)const{
        if(row<=rows && col<=cols &&row>=0 && col>=0){
            return world[row][col].population;
        }
        return 0;
    }

    int num_rows()const {
        return rows;
    }
    int num_cols()const {
        return cols;
    }

};