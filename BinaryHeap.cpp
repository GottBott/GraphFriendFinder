#include "BinaryHeap.h"
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using std::stringstream;
using namespace std;

/**
 * Returns the BinaryHeapNode that is the left child of the given node.
 */
BinaryHeapNode * MinBinaryHeap::getLeftChild(BinaryHeapNode * node) const {
  // TODO: complete the implementation
	BinaryHeapNode * left;
	int index = (2*node->index) +1;
	if(index > nodes.size()-1)
		return NULL;
	left = nodes[index];
    return left;
}

/**
 * Returns the BinaryHeapNode that is the right child of the given node.
 */
BinaryHeapNode * MinBinaryHeap::getRightChild(BinaryHeapNode * node) const {
  // TODO: complete the implementation
	BinaryHeapNode * right;
		int index = (2*(node->index)) +2;
		if(index > nodes.size()-1)
				return NULL;
		right = nodes[index];
	    return right;
}

/**
 * Returns the BinaryHeapNode that is the parent of the given node.
 */
BinaryHeapNode * MinBinaryHeap::getParent(BinaryHeapNode * node) const {
  // TODO: complete the implementation
	BinaryHeapNode * parent;
	int index = node->index;
	if(node->index == 0)
		return NULL;
	if(index%2 == 0)
		index = ((index-1) /2);
	else{
		index = index /2;
	}
	parent = nodes[index];
  return parent;
}

/**
 * Adds a new BinaryHeapNode at the last position in the heap.
 */
BinaryHeapNode * MinBinaryHeap::addLast(Data * data) {
  BinaryHeapNode * node = new BinaryHeapNode(nodes.size(), data);
  nodes.push_back(node);
  return node;
}

/**
 * Deletes the BinaryHeapNode at the last position in the heap.
 */
BinaryHeapNode * MinBinaryHeap::deleteLast() {
  BinaryHeapNode * last = NULL;
  if (!nodes.empty()) {
    last = nodes.back();
    nodes.pop_back();
  }
  return last;
}

/**
 * Insert item x into the heap, maintaining heap order.
 * Duplicates are allowed.
 */
Container * MinBinaryHeap::insert(Data * x) {
  BinaryHeapNode * node = addLast(x);
  BinaryHeapNode * current = nodes.back();

  // TODO: complete the implementation


  //checks for parent
  while(getParent(current) != NULL){
  	  BinaryHeapNode * parent = getParent(current);

  	 //check to see if needs swaping
  	  if(current->data->compareTo(parent->data)== -1){
  		  int p = parent->index;
  		  int c = current->index;
  		  BinaryHeapNode * Ntemp;
  		  BinaryHeapNode * Ptemp;
  		  Ntemp = current;
  		  Ptemp =parent;
  		  nodes[p] = nodes[c];
  		  nodes[c] = Ptemp;
  		  nodes[c]->index = c;
  		  nodes[p]->index = p;
  		  node = nodes[p];
  	  }
  	  //exit loop
  	  else{
  		 return node;
  	  }

    }

  return node;
}

/**
 * Returns the data value at the minimum position in the heap
 * (the root data value).
 */
Data * MinBinaryHeap::min() const {
  if (nodes.empty()) {
    return NULL;
  }
  else {
    return nodes[0]->data;
  }
}

/**
 * Deletes the min Data from the heap and returns it. Maintains
 * heap order.
 */
Data * MinBinaryHeap::deleteMin() {
	Data* result;
  if (nodes.empty()) {
    return NULL;
  }
  //handle only 1 node
  else if(nodes.size() == 1){


	  result = deleteLast()->data;

    }
  //more then one node
  else{
	 result = nodes.front()->data;
	BinaryHeapNode * min = nodes.front();
	BinaryHeapNode * max = nodes.back();
	nodes.front() = nodes.back();
	nodes.pop_back();
	nodes.front()->index = 0;
	BinaryHeapNode * current = nodes.front();
	BinaryHeapNode * Ntemp;
	BinaryHeapNode * Ctemp;


    while(getRightChild(current) != NULL){

    		//test if anything needs to move
    		if(current->data->compareTo(getLeftChild(current)->data)== -1 && current->data->compareTo(getRightChild(current)->data)== -1){
    			return result;
    		}
    		else{
    			//swap with left
    			if(getRightChild(current)->data->compareTo(getLeftChild(current)->data)== 1 ){
  				  BinaryHeapNode * lc = getLeftChild(current);
  				  int lci = lc->index;
  				  int c = current->index;
  				  Ntemp = current;
  				  Ctemp =getLeftChild(current);
  				  nodes[lci] = nodes[c];
  				  nodes[c] = Ctemp;
  				  nodes[c]->index = c;
  				  nodes[lci]->index = lci;
    			}

    			//swap with right
    			else{
				  BinaryHeapNode * Rc = getRightChild(current);
				  int Rci = Rc->index;
				  int c = current->index;
				  Ntemp = current;
				  Ctemp =getRightChild(current);
				  nodes[Rci] = nodes[c];
				  nodes[c] = Ctemp;
				  nodes[c]->index = c;
				  nodes[Rci]->index = Rci;
    			}
    		}
    }

    	//after exiting loop could still have left child
        if(getLeftChild(current) != NULL){
        	if(getLeftChild(current)->data->compareTo(current->data)== -1){
        	  BinaryHeapNode * lc = getLeftChild(current);
			  int lci = lc->index;
			  int c = current->index;
			  Ntemp = current;
			  Ctemp =getLeftChild(current);
			  nodes[lci] = nodes[c];
			  nodes[c] = Ctemp;
			  nodes[c]->index = c;
			  nodes[lci]->index = lci;

        	}
        }



    return result;
  }

}

/**
 * Returns true if the heap is empty
 */
bool MinBinaryHeap::isEmpty() const {
  return nodes.empty();
}

/**
 * Returns true if the given Data is a member of the heap.
 * Warning: this is an O(n) operation.
 */
bool MinBinaryHeap::member(Data * x) {
  for (vector<BinaryHeapNode*>::iterator i = nodes.begin();
        i != nodes.end(); i++) {
    BinaryHeapNode * node = (*i);
    if (node->data->compareTo(x) == 0) {
      return true;
    }
  }
  return false;
}

/**
 * Updates the position of the given node in the heap.  It is
 * assumed that the position is the same or has increased in heap order.
 *
 * (this is a min heap, so it is a percolate/bubble down operation)
 */
void MinBinaryHeap::increaseKey(Container * container) {
  BinaryHeapNode * current = (BinaryHeapNode *)container;
  // TODO: complete the implementation
  BinaryHeapNode * Ntemp;
  BinaryHeapNode * Ctemp;

  while(getRightChild(current) != NULL){

	  	  // check if things need to move
  		if(current->data->compareTo(getLeftChild(current)->data)== -1 && current->data->compareTo(getRightChild(current)->data)== -1){
  			return;
  		}
  		else{
  			// swap left
  			if(getRightChild(current)->data->compareTo(getLeftChild(current)->data)== 1 ){
				  BinaryHeapNode * lc = getLeftChild(current);
				  int lci = lc->index;
				  int c = current->index;
				  Ntemp = current;
				  Ctemp =getLeftChild(current);
				  nodes[lci] = nodes[c];
				  nodes[c] = Ctemp;
				  nodes[c]->index = c;
				  nodes[lci]->index = lci;
  			}
  			//swap right
  			else{
			  BinaryHeapNode * Rc = getRightChild(current);
			  int Rci = Rc->index;
			  int c = current->index;
			  Ntemp = current;
			  Ctemp =getRightChild(current);
			  nodes[Rci] = nodes[c];
			  nodes[c] = Ctemp;
			  nodes[c]->index = c;
			  nodes[Rci]->index = Rci;
  			}
  		}
  }

  	  // after exiting loop could still have left child
      if(getLeftChild(current) != NULL){
      	if(getLeftChild(current)->data->compareTo(current->data)== -1){
      	  BinaryHeapNode * lc = getLeftChild(current);
		  int lci = lc->index;
		  int c = current->index;
		  Ntemp = current;
		  Ctemp =getLeftChild(current);
		  nodes[lci] = nodes[c];
		  nodes[c] = Ctemp;
		  nodes[c]->index = c;
		  nodes[lci]->index = lci;

      	}
      }

}

/**
 * Updates the position of the given node in the heap.  It is
 * assumed that the position is the same or has decreased in heap order.
 *
 * (this is a min heap, so it is a percolate/bubble up operation)
 */
void MinBinaryHeap::decreaseKey(Container * container) {
  BinaryHeapNode * node = (BinaryHeapNode *)container;
  // TODO: complete the implementation
  BinaryHeapNode * current = node;

// check for parents
  while(getParent(current) != NULL){

    	  BinaryHeapNode * parent = getParent(current);

    	  //if we need to make a swap
    	  if(current->data->compareTo(parent->data)== -1){
    		  BinaryHeapNode * Ntemp;
    		  BinaryHeapNode * Ptemp;
    		  int p = parent->index;
    		  int c = current->index;
    		  Ntemp = current;
    		  Ptemp =parent;
    		  nodes[p] = nodes[c];
    		  nodes[c] = Ptemp;
    		  nodes[c]->index = c;
    		  nodes[p]->index = p;
    		  node = nodes[p];
    	  }
    	  //exit loop
    	  else{
    		  return;
    	  }

      }


}
/**
 * Returns a string value representation of the heap from top to bottom
 */
string MinBinaryHeap::toString() const {
  stringstream s;

  s << "[";
  for (vector<BinaryHeapNode*>::const_iterator i = nodes.begin();
        i != nodes.end(); i++) {
    BinaryHeapNode * node = (*i);
    if (i != nodes.begin()) {
      s << ", ";
    }
    s << node->data->toString();
  }
  s << "]";

  return s.str();
}
