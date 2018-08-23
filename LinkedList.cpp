#ifndef LINKED_LIST_
#define LINKED_LIST_

#include <iostream>
#include <cmath>
#include <string>
#include <sstream>

using std::string;
using std::stringstream;

#include "Queue.h"
#include "Collection.h"
#include "Stack.h"

using std::cout;
using std::endl;

#ifndef NULL
#define NULL 0
#endif

struct LinkNode {
  Data * data;
  LinkNode * next;
  LinkNode(Data * data = NULL, LinkNode * next = NULL) : data(data), next(next) {}
};

class LinkedList : Collection, public Stack, public Queue {
  LinkNode * head;
  LinkNode* tail;

  public:
    LinkedList() {
      this->head = NULL;
      this->tail = head;
    }

    ~LinkedList() {
      // must clean up the internally allocated nodes here
      LinkNode * current = head;
      while (current != NULL) {
        LinkNode * next = current->next;
        delete current;
        current = next;
      }
    }

    /**
     * Returns the count of the number of elements in the Collection
     */
    int size() const {
      LinkNode* current = head;
      int count = 0;
      while (current != NULL) {
        count++;
        current = current->next;
      }
      return count;
    }

    /**
     * Inserts the given Data value in the Collection
     * by calling insert_tail().
     */
    void insert(Data * newData) {
      insert_tail(newData);
    }

    /**
     * Inserts the given Data value in the Collection. Placement index of
     * the newly inserted element is assumed to be at the beginning.
     */
    void insert_head(Data * newData) {
      LinkNode * newNode = new LinkNode(newData);
      newNode->next = head;
      head = newNode;
    }

    /**
     * Inserts the given Data value to the Collection. Placement index of
     * the newly inserted element is assumed to be at the end.
     */
    void insert_tail(Data * newData) {
      if (head == NULL) {
        head = new LinkNode(newData);
        tail = head;
      }
      else {
        LinkNode * current = head;
        while (current->next != NULL) {
          current = current->next;
        }

        current->next = new LinkNode(newData);
        tail = current->next;
      }
    }

    /**
     * Removes a given value from the Collection based on pointer equality
     * (data to be removed must be == to parameter).  Returns true if
     * the Data was removed from the Collection.
     */
     bool remove(Data * d) {
       LinkNode * current = head;
       LinkNode * previous = NULL;
       LinkNode * before = NULL;
       while (current != NULL && current->data != d) {
    	 before = previous;
         previous = current;
         current = current->next;
       }
       if (current != NULL) {
         // found it
         if (previous == NULL) {
           // found it at the head of the list
           head = current->next;
         }
         if (current->next == NULL) {
			// found it at the end of the list
			tail = before;
		  }
         else {
           previous->next = current->next;
         }
         delete current;

         return true;
       }
       else {
         // got to end of list but did not find it
         return false;
       }

     }

     /**
      * Tests if the given Data is already a member of this Collection.
      * Uses the compareTo method of the Data class.  Data is a member of the
      * Collection if compareTo(x) == 0 for any x currently in Collection.
      */
     bool member(Data * d) {
       LinkNode * current = head;
       while (current != NULL && current->data->compareTo(d) != 0) {
         current = current->next;
       }
       return current != NULL;
     }

     /**
      * Gets the Data value at the specified index.  If index >= size() then
      * NULL is returned.
      */
     Data * get(int index) {
       LinkNode* current = head;
       if (index >= size()) {
         return NULL;
       }
       int count = 0;
       while (current != NULL && count < index) {
         count++;
         current = current->next;
       }
       return current->data;
     }

     /**
      * Inserts the given Data * to the Collection. Placement index of
      * the newly inserted element is in value order, assuming this LinkedList
      * is already sorted from lowest to highest value.
      *
      * [3, 7]->insertSorted(1) --> [1, 3, 7]
      * [1, 3, 7]->insertSorted(5) --> [1, 3, 5, 7]
      */
     void insertSorted(Data * d) {
       LinkNode * current = head;
       LinkNode * previous = NULL;
       while (current != NULL && current->data->compareTo(d) <= 0) {
         previous = current;
         current = current->next;
       }
       // insert it between previous and current
       if (previous == NULL) {
         // it is going at the beginning
         head = new LinkNode(d, head);
       }
       else if (current == NULL) {
         // it is going at the end and previous is not null
         previous->next = new LinkNode(d);
         tail = previous->next;
       }
       else {
         // in the middle somewhere
         previous->next = new LinkNode(d, previous->next);
       }
     }

     /**
      * Inserts all of the Data * in the given LinkedList to the Collection.
      * The given LinkedList and this LinkedList are both assumed to be sorted
      * from lowest to highest value. Placement index of all newly inserted
      * elements is in value order. The LinkedList passed to this function must
      * not be modified.
      *
      * [3, 7]->insertSorted([1]) --> [1, 3, 7]
      * [1, 3, 7]->insertSorted([5, 6, 9]) --> [1, 3, 5, 6, 7, 9]
      */
     void insertSorted(LinkedList * otherList) {
       // one way would be to loop through otherList and insert all of them
       LinkNode * otherCurrent = otherList->head;
       while (otherCurrent != NULL) {
         insertSorted(otherCurrent->data);
         otherCurrent = otherCurrent->next;
       }
     }

     /**
      * Returns the top element of the stack without removing it
      */
     Data * peek() const {
       if (head == NULL) {
         return NULL;
       }
       else {
         return head->data;
       }
     }

     /**
      * Removes (and returns) the top element of the stack
      */
     Data * pop() {
       Data * value = peek();
       remove(value);
       return value;
     }

     /**
      * Pushes the given Data onto the top of the stack
      */
     void push(Data * d) {
       insert(d);
     }

     /**
     * Remove and return the first element of the queue
     */
     Data * dequeue(){
    	 LinkNode * temp = head;
    	 head = head->next;
    	 remove(temp->data);
    	 return temp->data;

     }
     /**
     * Add the given Data* to the back of the queue
     */
     void enqueue(Data * d){
    	 LinkNode * newnode = new LinkNode(d);
    	 if(head == NULL){
    		 head = newnode;
    		 tail = head;
    	 }
    	 else{
			 tail->next = newnode;
			 tail = tail->next;
    	 }
     }

     /**
      * Returns a string representation of the data
      */
     string toString() const {
       stringstream s;

       // left shift operator for streams takes the value and appends it to the stream
       // in this line of code, the value of x is placed into a stringstream
       // followed by a comma and then the value of y
       s << "[";
       LinkNode* current = head;
       if (current != NULL) {
         s << current->data->toString();
         current = current->next;
         while (current != NULL) {
           s << ", " << current->data->toString();
           current = current->next;
         }
       }
       s << "]";
       // now we return the string that was created in the stringstream
       return s.str();
     }
};
#endif /* LINKED_LIST_ */
