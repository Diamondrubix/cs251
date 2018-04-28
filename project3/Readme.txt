


Name:

-----------------------------------------------

Please confirm that you compiled your solution with test cases exercising ALL
functions using g++ -std=c++11.  Confirm this statement by typing YES below.
(If you did not do this, compilation errors may result in an overall grade of
zero!)
yes





Describe what augmentations to the bst data structures you made to complete the 
project -- i.e., what types / data members did you change and why?

I added left and right child nodes. I needed a way to keep track of how many nodes were in the child sub tree of each
side of any given node. this was nessesary to know at what point any given sub tree was inbalanced.

This also helped with the




-----------------------------------------------
Which functions did you need to modify as a result of the augmentations from the previous
question?  

i had to modify the insert and delete function to update the leftchildren and rightchildren fields.







-----------------------------------------------
For each function from the previous question, how did you ensure that the (assymptotic) runtime 
remained the same?


I did a simple math operation. that runs constant time so i didn't need to worry about changing the runtime.





-----------------------------------------------
For each of the assigned functions, tell us how far you got using the choices 0-5 and
answer the given questions.  


0:  didn't get started
1:  started, but far from working
2:  have implementation but only works for simple cases
3:  finished and I think it works most of the time but not sure the runtime req is met. 
4:  finished and I think it works most of the time and I'm sure my design leads to 
       the correct runtime (even if I still have a few bugs).
5:  finished and confident on correctness and runtime requirements

finished and confident on correctness and runtime requirements

to_vector level of completion:  5


-----------------------------------------------
get_ith level of completion:  5

    How did you ensure O(h) runtime?

    ANSWER:
each node stores how many nodes are in its left and right subtrees. the number of nodes in the left subtree
are the number of elements smaller than the current node. if i am looking for the 5th smallest node i need to make sure
that there are 4 nodes in my left subtree. i basically just see if my left subtree node count is greater than or less
than i and move left or right accordingly. I only move down the tree so i cannot do more comparision than the height.


-----------------------------------------------
num_geq level of completion:  5

    How did you ensure O(h) runtime?

    ANSWER:
similar logic as get_ith. each node stores how many children are in its right subtree. that number correspondes with
how many nodes are greater than it. so once i find the node i am looking for i just check that number and that is my
answer

-----------------------------------------------
num_leq level of completion:  5

    How did you ensure O(h) runtime?

    ANSWER:
basically the same as num_geq but this time i am checking the left subtree.
-----------------------------------------------
num_range level of completion: 5

    How did you ensure O(h) runtime?

    ANSWER:
i do num_geq for both elements in my range and do a subtraction of the two results. since num_geq is O(h) and i am always
running it 2 times it is still O(h)
-----------------------------------------------
Implementation of size-balanced criteria according to 
the given guidelines (including bst_sb_work):

    Level of completion: 5
(i called the bst_sb_work balance)

so i took the working insert function and i created an if statement before adding a new node to any sub tree that
checks to see if adding this node will imbalance it. if it will, i add it, then call my balance function after.
I do not call the balance function otherwise

the balance function takes the inbalanced subtree, puts the pointers to the nodes in a vector in order, and then
creates a new balanced subtree by finding median, making that the root, and having each left and right sub array do the
same.





Write a few sentences describing how you tested your solutions.  Are there
any tests that in retrospect you wish you'd done?


Testing this program was a pain. I tried my best to do all cases I could think of.

Basically, I used a deck of cards with the numbers in my input string performed my algorithm by hand.
then i used the debuger to see if the right and left nodes of each number were the same and the tree i built by hand.

I tried a few combinations where I have to rebalance twice in one build, or delete a few important parts and so on.

I also tested edge cases like just inserting a bunch of sequenctial numbers. everything behaved as expected so i am
confident everything works.









