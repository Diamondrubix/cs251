
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>    // std::reverse

using std::string;
using std::vector;
using std::unordered_map;
using std::unordered_set;

#define UNDISCOVERED 'u'
#define DISCOVERED   'd'
#define ACTIVE       'a'
#define FINISHED     'f'

/*
 * function:  pvec
 * description:  utility function that prints the elements of
 *   a vector: one per line.
 * 
 * Note that this is a templated function; only works if the type
 *   T is acceptable with:
 *
 *     cout << var_of_type_T
 */
template <typename T>
void pvec(const std::vector<T> & vec) {

  for(const T &x : vec) {
    std::cout << x << "\n";;
  }
}


/*
 * class:  graph
 *
 * desc:   class for representing directed graphs.  Uses the
 *   adjacency list representation.
 */
class graph {

  private:

    // note:  this struct does not store both
    //   vertices in the edge -- just one.  This
    //   is because of the overall structure of
    //   the adjacency list organization:  an
    //   edge struct is stored in a vector associated
    //   with the other vertex.
    struct edge {
      int vertex_id;
      double weight;
      edge ( int vtx_id=0, double _weight=1.0) 
        : vertex_id { vtx_id}, weight { _weight} 
      { }
    };

    struct vertex {
      int id;
      vector<edge> outgoing;
      vector<edge> incoming;
      string name;

      vertex ( int _id=0, string _name="") 
        : id { _id }, name { _name } 
      { }
    };

    unordered_map<string, int> _name2id;
    unordered_set<string> edges;
    vector<vertex> vertices;

  public:
    //deleteme
    void printVectorList(){
        for(int i = 0; i <vertices.size();i++){
            printf("id %d, name %s\noutgoing:\n", vertices[i].id,vertices[i].name.c_str());
            for(int j = 0; j<vertices[i].outgoing.size();j++){
                printf("\t id:%d\n",vertices[i].outgoing[j].vertex_id);
            }
            printf("incoming:\n");
            for(int j = 0; j<vertices[i].incoming.size();j++){
                printf("\t id:%d",vertices[i].incoming[j].vertex_id);
            }
            printf("\n\n");
        }
    }

    // this struct is used for capturing the results of an operation.
    // typically a "report" will be a vector of vertex_labels indexed
    // by vertex-id.
    struct  vertex_label {
      double dist;
      int pred;
      char state;
      int npaths;
      
      vertex_label( double _dist=0.0, int _pred=-1, char _state='?',
          int _npaths=0) 
        : dist { _dist }, pred { _pred }, state { _state}, npaths { 0 }
      { }

    };


    graph() {}

    ~graph() {}

  private:

    int add_vertex(const string &name) {
      int id = vertices.size();
        vertices.push_back(vertex(id, name));
        _name2id[name] = id;
        return id;
    }

    /*
     * function:  edge_string
     *
     * returns concatenation of src and dest vertex strings with
     * a single space between
     *
     * Purpose:  gives a unique string representing the edge
     * -- data member edges stores sets of such strings to
     * quickly detect if an edge has already been created.
     *
     */
    static
    string edge_string(const string &src, const string &dest) {
      return src + " " + dest;
    }


    /*
     * function: p_edge
     * desc:  simple function for printing an edge
     */
    void p_edge(edge &e) {
      std::cout << "(" << id2name(e.vertex_id) 
        << ", " << e.weight << ") ";
    }

  public:

    /*
     * func:  id2name
     * desc:  returns vertex name (a string) associated with given 
     *         vertex id.
     *
     *         If id not valid for given graph, the string "$NONE$"
     *         is returned.
     */
    string  id2name(int id) {
      if(id<0 || id>=vertices.size())
        return "$NONE$";
      return vertices[id].name;
    }

    /*
     * func: name2id
     * desc: returns integer vertex id of given vertex name.
     *       If there is no such vertex in the graph, -1 is returned.
     */
    int name2id(const string &vtx_name) {
      if(_name2id.count(vtx_name)==0)
        return -1;
      return _name2id[vtx_name];
    }

    /*
     * func: name_vec2string
     * desc: utility function - if you have a bunch of
     *   vertex names (as strings) stored in a vector, this
     *   function puts the names in a single string with
     *   nodes separated by single spaces.
     *
     *   Might be handy for things like getting an easy to
     *   print representation of a path for example.
     */
    string name_vec2string(const vector<string> &vec) {
      string s = "";
      int i;

      if(vec.size()==0)
        return s;

      s = s + vec[0];
      for(i = 1; i<vec.size(); i++) {
        s = s + " " + vec[i];
      }
      return s;
    }

    /*
     * func: id_vec2string
     * desc: utility function - if you have a bunch of
     *   vertex ids (ints) stored in a vector, this
     *   function connverts them to names and builds a in a 
     *   single string with nodes-names separated by single spaces.
     *
     *   Might be handy for things like getting an easy to
     *   print representation of a path for example.
     */
    string id_vec2string(const vector<int> &vec) {
      string s = "";
      int i;

      if(vec.size()==0)
        return s;

      s = s + id2name(vec[0]);
      for(i = 1; i<vec.size(); i++) {
        s = s + " " + id2name(vec[i]);
      }
      return s;
    }




    /*
     * func: add_edge
     * desc: adds edge (src,dest) with given weight to graph if
     *   possible.
     *
     *       If edge (src,dest) is already in graph, the graph is
     *       unchanged and false is returned.
     *
     *       Otherwise the edge is added and true is returned.
     *
     *       Note:  if src and/or dest are not currently vertices
     *         in the graph, they will be added.
     */
    bool add_edge(const string &src, const string &dest, 
        double weight=1.0) {

      int s_id, d_id;

      string estring = edge_string(src, dest);

      if(edges.count(estring)==1) {
        std::cerr << "warning: duplicate edge '"
          << estring << "'\n";
        return false;
      }

      edges.insert(estring);

      // get id for source vertex
      if(_name2id.count(src)==0) 
        s_id = add_vertex(src);
      else
        s_id = _name2id[src];

      // get id for destination vertex
      if(_name2id.count(dest)==0) 
        d_id = add_vertex(dest);
      else
        d_id = _name2id[dest];

      vertices[s_id].outgoing.push_back(edge(d_id, weight));
      vertices[d_id].incoming.push_back(edge(s_id, weight));

      return true;
    }


    /*
     * func: add_edge(string &)
     * desc: takes an edge specification as a single string, 
     *   parses the string into src vertex, dest vertex and
     *   weight (optional).
     *
     *   If parsing is successful, add_edge(string, string, double) above
     *   is called to do the "real work".
     *
     * returns true on success; false on failure (parse error or
     *   call to add_edge failed).
     *
     * expected format:
     *
     *   the given string must have either two or three tokens (exactly).
     *
     *   If it has three tokens, the third token must be parseable as
     *   a double.
     */
    bool add_edge(const string &str) {
      std::stringstream ss(str);
      string src, dest, junk, weight_str;
      double weight;

      if(!(ss >> src))
        return false;
      if(!(ss >> dest))
        return false;
      if(!(ss >> weight_str)){
        // only two tokens: use default weight
        weight = 1.0;
      }
      else {
        if(!(std::stringstream(weight_str) >> weight)){
          // couldn't parse weight
          return false;
        }

        if(ss >> junk){
          // extra token?  format error
          return false;
        }
      }

      add_edge(src, dest, weight);

      return true;
    }

    void _add_edge(const string &str) {

      if(!add_edge(str))
        std::cout << "add_edge failed; str='" <<
          str << "'\n";
    }

    void display(){
      int u;

      for(u=0; u<vertices.size(); u++) {
        std::cout << vertices[u].name << " : ";

        for(edge &e : vertices[u].outgoing) 
          p_edge(e);
        std::cout << "\n";
      }
    }

    /*
     * func: ids2names
     * desc: utility function which takes a vector of vertex IDs
     *   and populates another vector of strings with the corresponding
     *   vertex names.
     */
    void ids2names(std::vector<int> &  ids, std::vector<string> & names) {
      names.clear();

      for(int &u : ids) {
        names.push_back(id2name(u));
      }
    }

    /* 
     * func: read_file
     * desc:
     */
    bool read_file(const string &fname) {
      std::ifstream file;
      string line;

      file.open(fname, std::ios::in);
      if(!file.is_open())
        return false;
      
      while(getline(file, line)) {
        // skip blank lines
        if(line.length() > 0) {
          if(!add_edge(line)) {
            std::cerr << "warning: skipped input line '" 
              << line << "' (ill-formatted)\n";
          }
        }
      }
      file.close();
      return true;
    }


    int num_nodes() {
      return vertices.size();
    }
    int num_edges() {
      return edges.size();
    }

  private:
    void init_report(std::vector<vertex_label> & report) {
      int u;

      report.clear();
      for(u=0; u<vertices.size(); u++) {
        report.push_back(vertex_label(-1, -1, UNDISCOVERED));
      }
    }


  public:

    /*
     * TODONE 10 points
     *
     * modify bfs so that vertex labels reflect the NUMBER OF 
     *   SHORTEST PATHS TO THE VERTEX LABELED:
     *
     *     report[u].npaths is assigned the number of shortest 
     *        paths from src to u.
     *
     *   OBSERVATIONS:
     *
     *     report[src].npaths will be 1.
     *
     *     if a vertex u is not reachable from src, then 
     *     report[u].npaths will be assigned 0. 
     *
     * RUNTIME:  bfs must still be O(V+E).
     *
     */
    bool bfs(int src, std::vector<vertex_label> &report) {
      int u, v;
      std::queue<int> q;

      if(src < 0 || src >= num_nodes())
        return false;

      init_report(report);

      report[src].dist = 0;

      // since src is the root of the bfs tree, it has no 
      //   predecessor.
      // By convention, we set the predecessor to itself.
      report[src].pred = src;
      report[src].state = DISCOVERED;
      report[src].npaths = 1;

      q.push(src);

      while(!q.empty()) {
        // dequeue front node frombfs queue
        u = q.front();
        q.pop();

        // examine outgoing edges of u
        for(edge &e : vertices[u].outgoing) {
          v = e.vertex_id;
          if(report[v].state == UNDISCOVERED) {
            report[v].dist = report[u].dist + 1;
            report[v].pred = u;
            report[v].state = DISCOVERED;
            report[v].npaths = report[u].npaths;
            // enqueue newly discovered vertex
            q.push(v);
          }else{

              if(report[u].dist+1==report[v].dist) {
                  report[v].npaths+=report[u].npaths;
              }

              /*
              if(report[u].dist<report[v].dist){
                  if(report[u].dist+1==report[v].dist){
                      report[v].npaths++;
                  }else {
                      report[v].dist = report[u].dist + 1;
                      report[v].npaths = 1;
                  }
              }
              */
          }
        }
      }
      return true;
    }

    bool bfs(const string src, std::vector<vertex_label> &report) {
        int u;

        if((u=name2id(src)) == -1)
            return false;
        bfs(u, report);
        return true;
    }

  private:
    void _dfs(int u, vector<vertex_label> & rpt, bool &cycle) {
      int v;

      rpt[u].state = ACTIVE;
      for(edge &e : vertices[u].outgoing) {
        v = e.vertex_id;
        if(rpt[v].state == UNDISCOVERED) {
          rpt[v].pred = u;
          rpt[v].dist = rpt[u].dist + 1;
          _dfs(v, rpt, cycle);
        }
        if(rpt[v].state == ACTIVE) 
          cycle = true;
      }
      rpt[u].state = FINISHED;
    }

  public:
    bool dfs(int u, vector<vertex_label> & rpt, bool &cycle) {

      if(u < 0 || u >= num_nodes()) 
        return false;

      cycle = false;

      init_report(rpt);
      rpt[u].pred = u;
      rpt[u].dist = 0;
      _dfs(u, rpt, cycle);
      return true;
    }

    bool dfs(const string &src, vector<vertex_label> & rpt, bool &cycle) {
      int u;

      if((u=name2id(src)) == -1)
          return false;
      dfs(u, rpt, cycle);
      return true;
    }

    bool has_cycle() {
      int u;
      bool cycle=false;
      vector<vertex_label> rpt;

      init_report(rpt);
      for(u=0; u<num_nodes(); u++) {
        if(rpt[u].state == UNDISCOVERED) {
          _dfs(u, rpt, cycle);
          if(cycle)
            return true;
        }
      }
      return false;
    }

    bool topo_sort(std::vector<int> &order) {
      std::queue<int> q;
      std::vector<int> indegrees;
      int u, v;
      int indeg;

      order.clear();
      if(has_cycle())
        return false;

      for(u=0; u<num_nodes(); u++) {
        indeg = vertices[u].incoming.size();

        indegrees.push_back(indeg);
        if(indeg==0)
          q.push(u);
      }

      while(!q.empty()){
        u = q.front();
        q.pop();
        order.push_back(u);
        for(edge &e : vertices[u].outgoing) {
          v = e.vertex_id;
          indegrees[v]--;
          if(indegrees[v]==0) 
            q.push(v);
        }
      }
      return true;
    }



    void disp_report(const vector<vertex_label> & rpt, 
        bool print_paths=false) {
      int u;
      vector<int> path;

        for(u=0; u<num_nodes(); u++) {
          std::cout << id2name(u) << " : dist=" <<  rpt[u].dist
            << " ; pred=" <<  id2name(rpt[u].pred) << 
            " ; state='" << rpt[u].state << "'; npaths=" << 
            rpt[u].npaths << "\n";
          if(print_paths) {
            extract_path(rpt, u, path);
            std::cout << "     PATH: <" + id_vec2string(path) + ">\n";
          }
        }
    }

    /******************************************************
     *
     * Vocabulary:  
     *
     *   In a DAG G:
     *   
     *       inputs:  subset of vertices with INDEGREE ZERO
     *
     *       outputs: subset of vertices with OUTDEGREE ZERO
     *
     *       input-path: a path in G STARTING AT AN INPUT VERTEX
     *          (and ending at any vertex).
     *
     *       output-path:  a path in G starting at any vertex and
     *          ENDING AT AN OUTPUT VERTEX.
     *
     *       input-output-path (or io-path):  a path STARTING AT
     *          AN INPUT VERTEX _AND_ ENDING AT AN OUTPUT VERTEX.
     *
     */

    /* TODONE 20 points
     * function:  extract_path
     * desc:  extracts the path (if any) encoded by vertex labels
     *        ending at vertex dest (as an int ID).  Resulting path
     *        is stored in the int vector path (sequence of vertex
     *        IDs ENDING WITH dest -- i.e., in "forward order").
     *
     *     parameters:
     *       rpt:  vector of vertex labels associated with given
     *             graph (calling object).  Presumption:  labels
     *             have been previously populated by another function
     *             like bfs, dfs, or critical_paths.
     *
     *       dest: vertex ID of the target/destination vertex.
     *
     *       path: int vector in which the constructed path is stored.
     *
     * returns:  true on success; false otherwise.
     *           failure:  there is no encoded path ending at vertex
     *              dest (see discussion below);
     *              OR, the rpt vector is not of the correct dimension.
     *
     * Notes:  predecessor conventions:
     *
     *      SOURCE VERTICES:
     *
     *         if vertex u is a "source" vertex such as:
     *
     *             the source vertex of BFS or DFS or
     *             an input vertex in a DAG (perhaps analyzed by 
     *                dag_critical_paths).
     *
     *         then the predecessor of u is u itself:
     *
     *              rpt[u].pred==u
     *
     *      UNREACHABLE VERTICES:
     *
     *          if rpt[u].pred == -1, this indicates that THERE IS 
     *          NO PATH ENDING AT VERTEX u.
     *
     *          In this situation, the path vector is made empty and
     *          false is returned.
     *
     *  RUNTIME:  O(|p|) where |p| is the number of edges on 
     *    the path extracted.
     *
     */
    bool Rextract_path(const vector<vertex_label> &rpt, int dest, vector<int> &path){
        //path.clear();
        if(rpt.size() != num_nodes())
            return false;

        //your code here
        path.push_back(dest);
        if(rpt[dest].pred == dest){
            return true;
        }
        int newdest = path.size();
        return Rextract_path(rpt, rpt[dest].pred, path);
    }
    bool extract_path(const vector<vertex_label> &rpt, int dest, vector<int> &path) {
      path.clear();

      bool ret = Rextract_path(rpt, dest, path);
      //reverse
      std::reverse(path.begin(),path.end());
      return ret;

    }

    /*
     *  TODONE 30 points
     *
     *  func: dag_critical_paths
     *  desc: for each vertex u, the length of the critical (LONGEST)
     *        input-path ENDING AT u.
     *
     *        The "length" of a path is the SUM OF THE WEIGHTS OF THE
     *        EDGES ON THE PATH.
     *
     *        On completion, the results are stored in the vector rpt.
     *        For each vertex u (as an intID),
     *
     *          rpt[u].dist  stores the length of the longest (critical)
     *            input-path ending at vertex u.
     *
     *          rpt[u].pred  stores the predecessor vertex of u on a 
     *            critical/longest input path ending at u.  If there
     *            are multiple such paths (having equal maximum length)
     *            there may be multiple correct predecessors.
     *
     *  returns:  true on success (as long as graph is a DAG).
     *            false if graph is not a DAG.
     *
     *  runtime:  O(V+E)
     */

    //move to private
    double get_dag_critical_paths(vector<vertex_label> & rpt, int index, int* visited){
        //if its been found already
        if(visited[index]){
            return rpt[index].dist;
        }
        //if it has no incoming edges
        if(vertices[index].incoming.size() == 0){
            rpt[index].dist = 0;
            rpt[index].pred = index; //double check that this is right
            visited[index] = 1;
            return 0;
        }
        //if it needs to be calculated
        double longest = 0;
        int pred = -1;
        for(int i =0 ; i<vertices[index].incoming.size();i++){
            double temp = 0;
            temp = vertices[index].incoming[i].weight+get_dag_critical_paths(rpt, vertices[index].incoming[i].vertex_id, visited);
            if(temp > longest){longest = temp; pred = vertices[index].incoming[i].vertex_id;}

        }
        rpt[index].dist = longest;
        rpt[index].pred = pred;
        visited[index] = 1;
        return longest;

    }

    bool dag_critical_paths(vector<vertex_label> & rpt) {

      if(has_cycle())
        return false;
      int i;

      rpt.resize(vertices.size());

      int visited[vertices.size()];
      for(i =0 ; i<vertices.size();i++){
          visited[i] = 0;
      }

      for(i = 0; i< vertices.size();i++){
          if(!visited[i]) {
              get_dag_critical_paths(rpt, i, visited);
          }
      }
      // your code here...
      return true;
    }

    /*
     *  TODONE 30 points
     *  function:  dag_num_paths
     *  desc:  if given graph (calling object) is a DAG, the vector
     *         rpt is populated such that:
     *
     *           rpt[u].npaths = number of io-paths passing through
     *                            vertex u.
     *
     *           Recall: an IO path starts at an input vertex and
     *             ends at an output vertex.
     *
     *           This value is defined for all vertices u in the
     *             graph (inputs, outputs and "intermediate" nodes).
     *
     *  NOTES:  rpt[u].pred, and rpt[u].dist have no partiular 
     *          meaning after this operation.
     *
     *  EXAMPLE:

                         a  b  c
                         \  |  /
                          \ | /
                            d
                           / \
                          e   f
                           \ /
                            g
                           / \
                          h   i
                           \ /
                            j

            There are 3 input nodes (a,b,c) and one output node (j)
            in this graph.

            There are 12 distinct io-paths passing through vertex d in 
            this dag (note:  edges are pointed downward)

            Can you enumerate them?

     *
     *  returns true if graph is a DAG; false otherwise.        
     *
     *  RUNTIME:  O(V+E)  -- Note: in general, the number of paths
     *                       in a graph may be exponential in the
     *                       number of vertices.
     *
     *                       This means that you cannot explicitly
     *                       enumerate all of the paths and count them!
     *                       (The enum_paths function below which DOES
     *                       enumerate a set of paths MAY take exponential
     *                       time).
     *
     * General Hint:  an io-path passing through a vertex u is 
     *   composed of an input-path ending at u, followed by an
     *   output path starting at u.  
     *
     *   Now, if you could figure out the number of input-paths
     *   ending at u and the number of output paths starting at u, 
     *   could you determine the number of io-paths passing through
     *   u?
     *
     */
    //make private
    int get1_dag_num_paths(vector<vertex_label> & rpt, int index, int* visited){
        //if it's a root node
        if(vertices[index].incoming.size()==0){
            rpt[index].npaths = 1;
            visited[index] = 1;
            return 1;
        }

        for(int i=0;i<vertices[index].incoming.size();i++){
            if(visited[vertices[index].incoming[i].vertex_id] == 0){
                rpt[index].npaths +=get1_dag_num_paths(rpt, vertices[index].incoming[i].vertex_id, visited);
            }else{
                rpt[index].npaths+=rpt[vertices[index].incoming[i].vertex_id].npaths;
            }
        }
        visited[index] = 1;
        return rpt[index].npaths;

    }
    //make private
    int get2_dag_num_paths(vector<vertex_label> & rpt, int index, int* visited){
        //if it's a root node
        if(vertices[index].outgoing.size()==0){
            //rpt[index].npaths = 1;
            visited[index] = 2;
            rpt[index].pred = 1;
            return 1;
        }
        int totalPath = 0;

        for(int i=0;i<vertices[index].outgoing.size();i++){
            if(visited[vertices[index].outgoing[i].vertex_id] == 1){
                totalPath +=get2_dag_num_paths(rpt, vertices[index].outgoing[i].vertex_id, visited);
            }else{
                int test = vertices[index].outgoing[i].vertex_id;
                int another = rpt[vertices[index].outgoing[i].vertex_id].pred;
                totalPath+=rpt[vertices[index].outgoing[i].vertex_id].pred;
            }
        }
        visited[index] =2;

        rpt[index].pred = totalPath;
        rpt[index].npaths = totalPath*rpt[index].npaths;
        return rpt[index].pred;
    }


    bool dag_num_paths(vector<vertex_label> & rpt) {

        if(has_cycle()){return false;}

        int i;
        int visited[vertices.size()];
        rpt.resize(vertices.size());
        for(i =0 ; i<vertices.size();i++){
            visited[i] = 0;
            rpt[i].npaths = 0;

        }

        for(i = 0; i <vertices.size();i++){
            if(visited[i] == 0){
                get1_dag_num_paths(rpt,i,visited);
            }

        }

        for(i=0; i<vertices.size();i++){
            if(visited[i] == 1){
                get2_dag_num_paths(rpt, i, visited);
            }
        }

        return true;
    }


    /*
     * TODONE 20 points
     * function:  valid_topo_order
     * desc:  determines if vertex sequence in the given vector
     *        (parameter order) is a valid topological ordering of
     *        the given graph (calling object).
     *
     *        returns true if it is; false otherwise.
     *
     * details:  returns false if graph is not a DAG.
     *
     *           Note that vertices are given as their integer IDs.
     *
     * RUNTIME:  O(V+E)
     */
    bool valid_topo_order(const vector<int> & order) { //check that this is fast enough
      if(has_cycle())
        return false;

      int arr[vertices.size()]; //do i need to init? (check)
        for(int dex = 0; dex< vertices.size();dex++){
            arr[dex] = 0;
        }


      for(int dex = 0; dex<order.size();dex++) {


          if (vertices[order[dex]].incoming.size() == 0) {
              arr[vertices[order[dex]].id] = 1;
          }else {
              for (int i = 0; i < vertices[order[dex]].incoming.size(); i++) {
                  if(!arr[vertices[order[dex]].incoming[i].vertex_id]){//do i need an != 1? probably not (check)
                      return false; //at this point i know the order is invalid.
                  }
              }
              arr[order[dex]] = 1;
          }

      }

      return true;

    }

    /*
     * TODONE 30 points
     *
     * function:  enum_paths
     * desc:  enumerates all input-paths ending at target vertes in
     *        a DAG.
     * details:  Given a DAG and vertex target in the graph, the
     *   vector paths is populated with ALL input paths ending at
     *   vertex target.
     *
     * [NOTE:  target vertex is passed as its integer ID; however,
     *   vertices in paths constructed are represented by their 
     *   name -- as a string]
     *
     * A path is represented as a string containing the names of
     * each vertex (NOT intger vertex IDs) on the path in sequence; 
     * vertex names are separated by a single space.
     *
     * returns:  true on success; 
     *           false on failure (graph is not a DAG or target vertex ID
     *           is out of range).
     *
     * RUNTIME:  this one may be unavoidably exponential!
     *
     * EXAMPLES:
     *
     *   Chicago
     *   NewYork
     *   LosAngeles
     *
     * and there are edges:
     *
     *   LosAngeles Chicago
     *   Chicago NewYork
     *
     * The path LosAngeles to Chicago to NewYork is represented by the
     * string:
     *
     *   "LosAngeles Chicago NewYork"
     *
     * Another example:  the input file ex1A is a DAG.  Using vertex g
     * as the target (integer ID: 6), will result in the paths vector
     * containing the following strings:
     *

           "a d g"
           "a b d g"
           "a c d g"
           "a d e g"
           "a b d e g"
           "a c d e g"
           "a d f g"
           "a b d f g"
           "a c d f g"
     *
     * NOTE:  the concatenation operator '+' on strings might
     *   make some of your work pretty easy to code!
     *
     * COMMENT:  this function can be implemented with about
     *   20 lines of code.
     */
    //make private
    vector<string> Renum_paths(int target){
        vector<string> p;
        string s = "";
        if(vertices[target].incoming.size() == 0){
            s=vertices[target].name;
            //s+=" ";
            p.push_back(s);
            return p;
        }else{
            for(int i = 0; i <vertices[target].incoming.size();i++){
                vector<string> n = Renum_paths(vertices[target].incoming[i].vertex_id);
                for(int j = 0; j<n.size();j++){
                    s = n[j]+" "+vertices[target].name;
                    p.push_back(s);
                }
            }
            return p;
        }
    }


    bool enum_paths(int target, vector<string> &paths) {
      paths.clear();
      if(has_cycle() || target < 0 || target >= num_nodes())
        return false;


      vector<string> test = Renum_paths(target);
      for(int i =0 ; i<test.size();i++){
          std::cout <<test[i];
          printf("\n");
          //printf("%s\n",test[i]); //why doens't this work?
      }
      //paths = Renum_paths(target);

      // your code here!
      return true;
    }



    /*
     * (DONE)
     * func: enum_paths(string, vector<string> &)
     * desc: same as enum_paths(int, vector<string> &) above except
     *       target vertex is taken as its name (as a string).
     *
     *       Simply translates target vertex name to its integer id
     *       and calls enum_paths(int, vector<string> &) above.
     */
    bool enum_paths(const string &target,  vector<string> &paths) {
      int tgt;
      if((tgt=name2id(target)) == -1)
          return false;

      return enum_paths(tgt, paths);
    }




};

