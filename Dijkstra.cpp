#include "Network.h"
#include "Dijkstra.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <vector>
#include <limits>

using namespace std;
using std::cout;
using std::cerr;
using std::ifstream;
using std::endl;
using std::vector;
using std::numeric_limits;

/**
 * Finds all of the shortest paths from source to each other User in the
 * Network. Stores the dist, prior vertex in path as properties on the User class.
 * The User class also has a property to store a pointer to a Container
 * (the heap node) that represents that User.
 */
void dijkstra_getShortestPaths(Network *net, User *source, bool printOutput) {
  // create heap
  MinBinaryHeap heap;

  double inf = numeric_limits<double>::infinity();


  //added every node to the heap and set the source node distance to 0
  for (vector<User*>::iterator iter = net->vertices.begin();iter != net->vertices.end(); iter++) {
       User* v = *iter;
       v->dist = inf;
       v->heapNode = heap.insert(v);
  }

  source->dist=0;
  heap.decreaseKey(source->heapNode);

  //while the heap is not empty delete the min
    	   while(heap.isEmpty() != true){
    		  User* u = (User*)heap.deleteMin();


 //loop over all of the mins friends
    		  for(int i = 0; i<u->links.size();i++){
    			  User* frnd = u->links[i]->target;
 //update the distance if necessary
    			 if(frnd->dist > u->links[i]->weight + u->dist){
    				 frnd->dist = u->links[i]->weight + u->dist;
    				 frnd->prior = u;
    				heap.decreaseKey(frnd->heapNode);

    			  }
    		  }

    	   }

 }



LinkedList bfs(Network *net, User *source, bool printOutput) {
  // create queue and a output list
  LinkedList queue;
  LinkedList visited;

  //enqueueing the source
 queue.enqueue(source);

 //Repeat until the queue is empty
 while(queue.size()>0){

	 // dequeue the first element in the queue
	 User* u = (User*)queue.dequeue();
	 if(printOutput ==true){
		 cout<<endl;
		 cout<<u->firstname<<" was dequeued and added to bfs results "<<endl;
	 }
	 // add it to the visited list
	 visited.enqueue(u);

	 if(printOutput ==true)
		 cout<<"visited list size = "<<visited.size()<<" queue size = "<<queue.size()<<endl;

	 // visit all of the recently dequeued's friends to the back of the queue;
	 for(int j = 0; j<u->links.size();j++){
		User* s = u->links[j]->target;
		bool add =true;
		//dont add if already in result
		for(int k=0; k<visited.size();k++){
			User* t = (User*)visited.get(k);
			int x = t->id;
			if(s->id == x){
				add = false;

			}
		}
		//Don't add if already in queue
		for(int k=0; k<queue.size();k++){
			User* t = (User*)queue.get(k);
			int x = t->id;
			if(s->id == x){
				add = false;

			}
		}
		//add to queue if conditions are met
		if(add == true){
			queue.enqueue(s);
			if(printOutput ==true)
				cout<<"added to queue "<<u->firstname<<"'S friend "<< s->firstname<<endl;
		}
//		else{
//			if(printOutput ==true)
//				cout<<"did not add to queue "<< s->firstname<<endl;
//		}


	}

 }
 return visited;

  
  // TODO: complete the implementation
}
