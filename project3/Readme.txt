


Name:

-----------------------------------------------

Please confirm that you compiled your solution with test cases exercising ALL
functions using g++ -std=c++11.  Confirm this statement by typing YES below.
(If you did not do this, compilation errors may result in an overall grade of
zero!)






Describe what augmentations to the bst data structures you made to complete the 
project -- i.e., what types / data members did you change and why?







-----------------------------------------------
Which functions did you need to modify as a result of the augmentations from the previous
question?  









-----------------------------------------------
For each function from the previous question, how did you ensure that the (assymptotic) runtime 
remained the same?








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
i do num_leq for both elements in my range and do a subtraction of the two results. since num_leq is O(h) and i am always
running it 2 times it is still O(h)
-----------------------------------------------
Implementation of size-balanced criteria according to 
the given guidelines (including bst_sb_work):

    Level of completion: ___________


Write a few sentences describing how you tested your solutions.  Are there
any tests that in retrospect you wish you'd done?











