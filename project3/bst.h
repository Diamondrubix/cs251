#ifndef _BST_H
#define _BST_H

#include <iostream>
#include <vector>

template <typename T>
class bst {

  private: 
    struct bst_node {
      T      val;
      bst_node *left;
      bst_node *right;
        int height;
        int leftChildren;
        int rightChildren;

      bst_node ( const T & _val = T{}, bst_node * l = nullptr, bst_node *r = nullptr, int h = -1, int c = 0)
        : val { _val },  left { l }, right {r} ,height{h}, leftChildren{c}, rightChildren{c}
      { }
    };



  public:
    // constructor:  initializes an empty tree
    bst(){
      root = nullptr;
    }

  private:
    // helper function which recursively deallocates nodes
    //   in a tree.
    static void delete_nodes(bst_node *r){
      if(r==nullptr) return;
      delete_nodes(r->left);
      delete_nodes(r->right);
      delete r;
    }

  public:
    // destructor
    ~bst() {
      delete_nodes(root);
    }

  private:
    static int min(int l, int r){
        if(l<r){
            return l;
        }else{
            return r;
        }
    }

    static int max(int l, int r){
        if(l>r){
            return l;
        }else{
            return r;
        }
    }
    //swap n1 with n2
    static void swap(bst_node* n1, bst_node* n2){
        T tempVal = n1->val;
        n1->val=n2->val;
        n2->val = tempVal;
        /*
        bst_node *left = n1->left;
        bst_node *right = n1->right;
        int height = n1->height;
        int leftChildren = n1->leftChildren;
        int rightChildren = n1->rightChildren;
         */

    }
    //helper function that makes an in order array
    static void C_balance(bst_node* n, std::vector<bst_node*> *o){
        if(n== nullptr){
            return;
        }
        C_balance(n->left, o);
        o->push_back(n);
        C_balance(n->right, o);

    }

    static bst_node* _balance(bst_node* n,std::vector<bst_node*> *o, unsigned long int middle ){
        if(middle<0){
            return n;
        }
        //n->right = _balance()
    }

    static bst_node* balance( bst_node* n){
        std::vector<bst_node*> inOrder;
        //inOrder = new std::vector<T>();
        C_balance(n, &inOrder);
        //remake tree
        unsigned long int middle = inOrder.size()/2;
        bst_node* r = _balance(inOrder[middle],&inOrder,middle);


        return n;
    }



/**
 * function:  insert()
 * desc:      recursive helper function inserting x into
 *            binary search tree rooted  at r.
 *
 * returns:   pointer to root of tree after insertion.
 *
 * notes:     if x is already in tree, no modifications are made.
 */
    static bst_node * _insert(bst_node *r, T & x, bool &success, int height){
      if(r == nullptr){
        success = true;
        return new bst_node(x, nullptr, nullptr, height);
      }

      if(r->val == x){
        success = false;
        return r;
      }
      if(x < r->val){ //left
          if(max(r->leftChildren+1,r->rightChildren)>((2*min(r->leftChildren+1,r->rightChildren))+1)){
              bst_node* n = new bst_node(x, nullptr, nullptr, height);
              if(r->right== nullptr){
                  if(r->left->val>x){
                      swap(r, r->left);
                      r->right = r->left;
                      r->rightChildren = r->leftChildren;
                      n->height=r->height+1;
                      r->left = n;
                      return r;
                  }
                  n->left = r->left;
                  r->left = nullptr;
                  n->right = r;
                  //variable updates
                  n->height = r->height;
                  r->height++;
                  n->leftChildren = r->leftChildren;
                  r->leftChildren = 0;
                  n->rightChildren++;
                  return n;
              }else{
                  //rotation
                  if(r->left->right==nullptr) {
                      swap(r, r->left);
                  }else{
                      swap(r, r->left->right);
                  }
                  bst_node * temp = r->right;
                  bst_node* temp2 = r->left->right;
                  r->right = r->left;
                  r->left = r->left->left;
                  r->left->height--;
                  //r->right->left = r->right->right; //del
                  temp->height++;
                  r->right->right = temp;
                  //r->left = r->left->left;
                  r->right->left = temp2;
                  r->leftChildren= 1;
                  r->rightChildren = r->right->rightChildren+r->right->leftChildren+1;
                  return _insert(r,x,success,height);

              }
          }else {
              r->leftChildren++;
              r->left = _insert(r->left, x, success, height + 1);
          }

        return r;
      }

      else {
          //if(r->left !=nullptr) {
          if(max(r->leftChildren,r->rightChildren+1)>((2*min(r->leftChildren,r->rightChildren+1))+1)) {
              bst_node *n = new bst_node(x, nullptr, nullptr, height);
              if (r->left == nullptr) {
                  if(r->right->val<x){
                      swap(r, r->right);
                      r->left = r->right;
                      r->leftChildren = r->rightChildren;
                      n->height=r->height+1;
                      r->right = n;
                      return r;
                  }
                  n->right = r->right;
                  r->right = nullptr;
                  n->left = r;
                  //variable updates
                  n->height = r->height;
                  r->height++;
                  n->rightChildren = r->rightChildren;
                  r->rightChildren = 0;
                  n->leftChildren++;
                  return n;
              }else{
                  //rotation
                  swap(r, r->right);
                  bst_node * temp = r->right;
                  bst_node* temp2 = r->right->left;
                  r->left = r->right;
                  r->right = r->right->right;
                  r->right->height--;
                  //r->right->left = r->right->right; //del
                  temp->height++;
                  r->left->left = temp;
                  //r->left = r->left->left;
                  r->left->right = temp2;
                  r->rightChildren= 1;
                  r->leftChildren = r->left->leftChildren+r->left->rightChildren+1;
                  return _insert(r,x,success,height);

              }
          }else{
              r->rightChildren++;
              r->right = _insert(r->right, x, success, height + 1);
          }
        return r;
      }
    }


  public:
  /**
   * function:  insert
   * desc:      inserts x into BST given by t.  Note that
   *            a BST stores a SET -- no duplicates.  Thus,
   *            if x is already in t when call made, no 
   *            modifications to tree result.
   *
   * note:      helper function does most of the work.
   *
   */
   bool insert(T & x){
      bool success;
      root = _insert(root, x, success, 0);
      return success;
   }

/**
 * function:  contains()
 * desc:      returns true or false depending on whether x is an
 *            element of BST (calling object)
 *
 */
    bool contains(const T & x){
      bst_node *p = root;

      while(p != nullptr){

        if(p->val == x)
          return true;
        if(x < p->val){
          p = p->left;
        }
        else
          p = p->right;
      }
      return false;  
    }

  private:
    // returns pointer to node containing
    //   smallest value in tree rooted at r
    static bst_node * _min_node(bst_node *r ){
      if(r==nullptr)
        return nullptr; // should never happen!
      while(r->left != nullptr)
        r = r->left;
      return r;
    }

    // returns pointer to node containing
    //   smallest value in tree rooted at r
    static bst_node * _max_node(bst_node *r ){
      if(r==nullptr)
        return nullptr; // should never happen!
      while(r->right != nullptr)
        r = r->right;
      return r;
    }

    // recursive helper function for node removal
    //   returns root of resulting tree after removal.
    static bst_node * _remove(bst_node *r, T & x, bool &success){
      bst_node *tmp;
      bool sanity;

      if(r==nullptr){
        success = false;
        return nullptr;
      }
      if(r->val == x){
        success = true;

        if(r->left == nullptr){
          tmp = r->right;
          delete r;
            //tmp->rightChildren--;
          return tmp;
        }
        if(r->right == nullptr){
          tmp = r->left;
          delete r;
            //tmp->leftChildren--;
          return tmp;
        }
        // if we get here, r has two children
        r->val = _min_node(r->right)->val;
          r->rightChildren--;
        r->right = _remove(r->right, r->val, sanity);
        if(!sanity)
          std::cerr << "ERROR:  remove() failed to delete promoted value?\n";
        return r;
      }
      if(x < r->val){ //left

          if(max(r->leftChildren-1,r->rightChildren)<=((2*min(r->leftChildren-1,r->rightChildren))+1)){
              r->left = _remove(r->left, x, success);
              r->leftChildren--;
          }else {
              r->left = _remove(r->left, x, success);
              r->leftChildren--;


          }
      }
      else { //right
          if(max(r->leftChildren,r->rightChildren-1)<=((2*min(r->leftChildren,r->rightChildren-1))+1)) {
              r->right = _remove(r->right, x, success);
              r->rightChildren--;
          }else{
              r->right = _remove(r->right, x, success);
              r->rightChildren--;
              bst_node* temp = r;
              if(r->left->right== nullptr){
                  r = r->left;
                  r->right = temp;
              }else{
                  r = r->left->right;
                  r->leftChildren = temp->leftChildren-1;
                  r->height = temp->height;
                  temp->leftChildren = 0;
                  temp->left->right =nullptr;
                  r->left = temp->left;
                  r->right = temp;
                  temp->height++;
                  //r->rightChildren+=r->right->leftChildren+r->right->rightChildren+1;
                  r->right->left = nullptr; //why do i do this?
                  r->rightChildren++;
                  r->left->rightChildren = 0;
              }

          }
      }
      return r;

    }
  public:

    bool remove(T & x){
      bool success;
      root = _remove(root, x, success);
      return success;
    }


  private:
    // recursive helper function to compute size of
    //   tree rooted at r
    static int _size(bst_node *r){
      if(r==nullptr) return 0;
      return _size(r->left) + _size(r->right) + 1;
    }

  public: 
    int size() {
      return _size(root);
    }

  private:

    static int _height(bst_node *r){
      int l_h, r_h;

      if(r==nullptr) return -1;
      l_h = _height(r->left);
      r_h = _height(r->right);
      return 1 + (l_h > r_h ? l_h : r_h);
    }

  public:

    int height() {
      return _height(root);
    }

    bool min(T & answer) {
      if(root == nullptr){
        return false;
      }
      answer = _min_node(root)->val;
      return true;
    }

    T max() {
      return _max_node(root)->val;
    }

    /******************************************
     *
     * "stubs" for assigned TODO functions below 
     *
     *****************************************/
    //helper function to to_vector
    void _to_vector(bst_node* n, std::vector<T> *o){
        if(n== nullptr){
            return;
        }
        _to_vector(n->left, o);
        o->push_back(n->val);
        _to_vector(n->right, o);


    }

    // TODONE
    std::vector<T> * to_vector() {
        std::vector<T> *inOrder;
        inOrder = new std::vector<T>();
        _to_vector(root, inOrder);
      return inOrder;
    }
    //helper function for get_ith
    void _get_ith(bst_node*n, int i, T &x){
        if(i == n->leftChildren+1){
            x = n->val;
        }else if(i>n->leftChildren+1){
            _get_ith(n->right,i-(n->leftChildren+1),x);
        }else{
            _get_ith(n->left,i,x);
        }
    }
    /* TODONE
     * Function:  get_ith
     * Description:  determines the ith smallest element in t and
     *    "passes it back" to the caller via the reference parameter x.  
     *    i ranges from 1..n where n is the number of elements in the 
     *    tree.
     *
     *    If i is outside this range, false is returned.
     *    Otherwise, true is returned (indicating "success").
     *
     * Runtime:  O(h) where h is the tree height
     */
    bool get_ith(int i, T &x) {
        if(i<=0 || i>1+(root->leftChildren+root->rightChildren)){
            return false;
        }
        _get_ith(root, i, x);
        return true;
    }


    bool get_ith_SLOW(int i, T &x) {
      int n = size();
      int sofar=0;

      if(i < 1 || i > n) 
        return false;

      _get_ith_SLOW(root, i, x, sofar);
      return true;
    }

    int _num_geq(bst_node* n,const T & x, int count){
        if(n->val==x){
            return n->rightChildren+1+count;
        }else{
            if(n->val<x) {
                if(n->right== nullptr){
                    return count;
                }
                return _num_geq(n->right, x, count);
            }else{
                if(n->left== nullptr){
                    return count+1;
                }
                return _num_geq(n->left, x, count+=(n->rightChildren+1));
            }
        }
    }
    /* TODONE
     * Function:  num_geq
     * Description:  returns the number of elements in tree which are 
     *       greater than or equal to x.
     *
     * Runtime:  O(h) where h is the tree height
     */
    int num_geq(const T & x) {
      return _num_geq(root,x,0);  // placeholder
    }

    /*
     * function:     num_geq_SLOW
     * description:  same functionality as num_geq but sloooow (linear time)
     *
     */
    int num_geq_SLOW(const T & x) {
      return _num_geq_SLOW(root, x);
    }

    int _num_leq(bst_node* n,const T & x, int count){
        if(n->val==x){
            return n->leftChildren+1+count;
        }else{
            if(n->val<x) {
                if(n->right== nullptr){
                    return count+1;
                }
                return _num_leq(n->right, x, count+=n->leftChildren+1);
            }else{
                if(n->left== nullptr){
                    return count;
                }
                return _num_leq(n->left, x, count);
            }
        }
    }
    /* TODONE
     * Function:  num_leq
     * Description:  returns the number of elements in tree which are less
     *      than or equal to x.
     *
     * Runtime:  O(h) where h is the tree height
     *
     **/
    int num_leq(const T &x) {
      return _num_leq(root, x, 0);
    }

    /*
     * function:     num_leq_SLOW
     * description:  same functionality as num_leq but sloooow (linear time)
     *
     */
    int num_leq_SLOW(const T & x) {
      return _num_leq_SLOW(root, x);
    }

    /* TODONE
     * Function:  num_range
     * Description:  returns the number of elements in tree which are
     *       between min and max (inclusive).
     *
     * Runtime:  O(h) where h is the tree height
     *
     **/
    int num_range(const T & min, const T & max) {
        return num_geq(min)-(num_geq(max)-1);
    }

    /*
     * function:     num_range_SLOW
     * description:  same functionality as num_range but sloooow (linear time)
     *
     */
    int num_range_SLOW(const T & min, const T & max) {
      return _num_range_SLOW(root, min, max);
    }

  private:


    static void _get_ith_SLOW(bst_node *t, int i, T &x, int &sofar) {
      if(t==nullptr) 
        return;
      _get_ith_SLOW(t->left, i, x, sofar);

      if(sofar==i) 
        return;
      sofar++;
      if(sofar==i) {
        x = t->val;
        return;
      }
      _get_ith_SLOW(t->right, i, x, sofar);
    }

    static int _num_geq_SLOW(bst_node * t, const T & x) {
      int total;

      if(t==nullptr) return 0;
      total =_num_geq_SLOW(t->left, x) + _num_geq_SLOW(t->right, x);

      if(t->val >= x)
        total++;
      return total;
    }

    static int _num_leq_SLOW(bst_node *t, const T &x) {
      int total;

      if(t==nullptr) return 0;
      total =_num_leq_SLOW(t->left, x) + _num_leq_SLOW(t->right, x);

      if(t->val <= x)
        total++;
      return total;
    }

    static int _num_range_SLOW(bst_node *t, const T &min, const T &max) {
      int total;

      if(t==nullptr) return 0;
      total =_num_range_SLOW(t->left, min, max) + 
                _num_range_SLOW(t->right, min, max);

      if(t->val >= min && t->val <= max)
        total++;
      return total;
    }





  private:
    static void indent(int m){
      int i;
      for(i=0; i<m; i++)
        std::cout << "-";
    }

    static void _inorder(bst_node *r){
      if(r==nullptr) return;
      _inorder(r->left);
      std::cout << "[ " << r->val << " ]\n";
      _inorder(r->right);
    }

    static void _preorder(bst_node *r, int margin){
      if(r==nullptr) {
        indent(margin);
        std::cout << " nullptr \n";
      } 
      else {
        indent(margin);
        std::cout << "[ " << r->val << " ]\n";
        _preorder(r->left, margin+3);
        _preorder(r->right, margin+3);
      }
    }

    /* 
     * TODO:
     * Complete the (recursive) helper function for the post-order traversal.
     * Remember: the indentation needs to be proportional to the height of the node!
     */
    static void _postorder(bst_node *r, int margin){

      std::cout << "\n   WARNING:  POSTORDER UNIMPLEMENTED...\n";
    }

  public:
    void inorder() {
      std::cout << "\n======== BEGIN INORDER ============\n";
      _inorder(root);
      std::cout << "\n========  END INORDER  ============\n";
    }


    void preorder() {

      std::cout << "\n======== BEGIN PREORDER ============\n";
      _preorder(root, 0);
      std::cout << "\n========  END PREORDER  ============\n";

    }

    // indentation is proportional to depth of node being printed
    //   depth is #hops from root.
    void postorder() {

      std::cout << "\n======== BEGIN POSTORDER ============\n";
      _postorder(root, 0);
      std::cout << "\n========  END POSTORDER  ============\n";

    }

  private:
    /* 
     * Recursive  helper function _from_vec, used by
     * bst_from_sorted_arr(...). The function must return a sub-tree that is
     * perfectly balanced, given a sorted array of elements a.
     */
    static bst_node * _from_vec(const std::vector<T> &a, int low, int hi){
      int m;
      bst_node *root;

      if(hi < low) return nullptr;
      m = (low+hi)/2;
      root = new bst_node(a[m]);
      root->left  = _from_vec(a, low, m-1);
      root->right = _from_vec(a, m+1, hi);
      return root;

    }

  public:
    static bst * from_sorted_vec(const std::vector<T> &a, int n){

      bst * t = new bst();
      t->root = _from_vec(a, 0, n-1);
      return t;
    }

    // TODO:  num_leaves
    //   Hint:  feel free to write a helper function!!
    int num_leaves() {

      std::cout << "\n     WARNING:  bst::num_leaves UNIMPLEMENTED...\n";
      return 0;
    }

    // TODO:  num_at_level
    // description:  returns the number of nodes at specified level
    //   in tree.
    // note:  the root is at level 0.
    // Hint:  recursive helper function?
    int num_at_level(int level) {

      std::cout << "\n     WARNING:  bst::num_leaves UNIMPLEMENTED...\n";
      return 0;
    }


  private:
    bst_node *root;


}; // end class bst

#endif
