
#include <iostream>
#include "Graph.h"

double dist;
int pred;
char state;
int npaths;

void reporter(std::vector<graph::vertex_label> report){
  printf("reporter:\n");
  for(int i = 0; i<report.size();i++){
    printf("dist: %f pred: %d state: %c npaths: %d", report[i].dist, report[i].pred, report[i].state, report[i].npaths);
    printf("\n");
  }
}

int main(){
  graph g;
  graph g1;

  std::vector<graph::vertex_label> report;
  std::vector<int> res;
  std::vector<string> resSTR;

  std::vector<int> topo;
  topo.push_back(0);
  topo.push_back(1);
  topo.push_back(2);
  topo.push_back(3);

  int i;
  g1._add_edge("a b");


  /*omar
  g._add_edge("a b");
  g._add_edge("a c");
  g._add_edge("b g");
  g._add_edge("c g");
  g._add_edge("g e");
   //*/
  /* //ex1A i think
  g._add_edge("a b");
  g._add_edge("a c");
  g._add_edge("a d");
  g._add_edge("b d");
  g._add_edge("c d");
  g._add_edge("d e");
  g._add_edge("d f");
  g._add_edge("d g");
  g._add_edge("e g");
  g._add_edge("f g");
   //*/


  //*/small
  g._add_edge("a b");
  g._add_edge("a c");
  g._add_edge("b d");
  g._add_edge("c d");
  //*/
   /* //topo
  if(g.valid_topo_order(topo)){
    printf("topo passed\n");
  }else{printf("topo failed\n");}
  //*/


  /*//test dag num paths
  g._add_edge("a d");
  g._add_edge("b d");
  g._add_edge("c d");
  g._add_edge("d e");
  g._add_edge("d f");
  g._add_edge("e g");
  g._add_edge("f g");
  g._add_edge("g h");
  g._add_edge("g i");
  g._add_edge("h j");
  g._add_edge("i j");
  g.dag_num_paths(report);
  //*/

  /* //ring
    g._add_edge("x y");
    g._add_edge("y z");
    g._add_edge("a b");
    g._add_edge("b c");
    g._add_edge("x a");
    g._add_edge("a x");
    g._add_edge("y b");
    g._add_edge("b y");
    g._add_edge("z c");
    g._add_edge("c z");
    */

  /*//test critical paths
  g.dag_critical_paths(report);
  for(i = 0 ; i< report.size();i++){
    printf("index %d, crit path %f, pred %d\n", i, report[i].dist, report[i].pred);
  }
   */
  //* //test extract path
  //g.dag_critical_paths(report);
  //g.bfs(0, report);
//  for(int j = 0; j<report.size();j++) {
    //g.extract_path(j, res);
    g.enum_paths(3,resSTR);
    for (i = 0; i < res.size(); i++) {
      printf("%s ", resSTR[i]);
    }
    printf("\n");
  //}
   //*/
  reporter(report);


  //g._add_edge("a c 2");
  //g._add_edge("a d");
  //g.printVectorList();
  //g._add_edge("b d ten");
  //g._add_edge("a");
  /*
  g.add_edge("a", "b");
  g.add_edge("b", "a");

  g.add_edge("b", "c");
  g.add_edge("d", "a");
  g.add_edge("b", "d");
  g.add_edge("a", "b");
  */


  printf("\n\ndisplay\n\n");
  g.display();

  return 0;
}

