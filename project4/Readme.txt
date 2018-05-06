


Name: Adam Arato

Answer each of the questions below to the best of your
ability.  If you didn't complete the part of the assignment
relevant to a particular question, just say so.


-----------------------------------------------

Briefly describe how you modified the basic heap organization (as
presented in class and in section 5.9 of Aho/Ullman) to support
the specifications for this assignment -- in particular how was
the idea of an ID incorporated.  

the struct pq stored an array or all that data elements (pq_part) pq_part stored the priority and data info, along with its position in the array
pq also stored an array of pointers that pointed to the elemenets in the other array. this array however was sorted by id. its id corresponded to its location in the array.

the other elements in the struct were book keeping like size capacity, what kind of heap it was.


-----------------------------------------------
How did your modifications above affect your implementation of
pq_insert (vs. the standard implementation of insert)?

I just put the element in the last unocupied element in the array list. this was easy because pq stored the number of elemments so i could just incrememnt that
and put the new element in the back.

then i used my percUp function to move it up the heap to the correct place.





-----------------------------------------------
How did your modifications above affect your implementation of
pq_delete_top (vs. the standard implementation of delete_max)?

i first made delete by id. once that was done, i was able to just get whatever was at element 1, and because each pq_part stores its id, i was able to just call delete id useing the id I just found.





-----------------------------------------------
Explain how your implementation of pq_change_priority worked,
why it is correct and why it achieves the runtime requirement.

i had a second array in my struct that stored a pointer to each element. the array possition corresponded to the id I was looking for so i was able to edit the element i wanted in const time.
After that I called a function called balance that checked the element above it. if it was greater/less than the current element (whether it should be greater than or less then depends on the heap type)
if the above element was correct, balance would use my percDown function to perculate down and find the correct place. if the above element was incorrect I would call my perk up function and it would
also take care of things. 







-----------------------------------------------
How did your implementation enable O(1) runtime for pq_get_priority?

i had an array that had everything sorted by id with a pointer to the correct element. useing this i was able to get the information of any element in the heap by its id in constant time.







