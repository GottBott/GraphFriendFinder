
#include "Network.h"
#include "Dijkstra.h"
#include <iostream>
using namespace std;

int main(int argc, const char **argv) {
  const char * dataFile = "dataset.csv";
  if (argc > 1) {
    dataFile = argv[1];
  }
  Network network;
  network.readFromFile(dataFile);

  double big = 1000000000;
  int x =0;
  double averageDistanceAll = 0;
  double size = network.vertices.size();

  // run dijkstra's algorithm for every vertex in the network
  for (vector<User*>::iterator iter = network.vertices.begin();
           iter != network.vertices.end(); iter++) {
    User* location = *iter;

    // call dijkstra's algorithm with this source, set last arg to true for debug output
    dijkstra_getShortestPaths(&network, location, false);

    double totalDistance = 0;

    // check to make sure that there exists a distance to every node that is less than
    // some really big number
    for (vector<User*>::iterator iter2 = network.vertices.begin();
               iter2 != network.vertices.end(); iter2++) {
      User* v = *iter2;
      if (v->dist < big)
        totalDistance += v->dist;
      //cout << "dist at" << v->id << " is " << v->dist << endl;

      if (!(v->dist < big && (v == location || v->dist > 0))) {
    	  x++;
    	  cerr << "User does not have distance after dijkstra's algorithm: " << v->firstname << " " << v->lastname << " (from source " << location->firstname << " " << location->lastname << ")" << endl;
      }
    }

    averageDistanceAll += (totalDistance/size);
  }

  averageDistanceAll /= size;
  cout << "Average distance is " << averageDistanceAll << endl;
  cout<<"number of error flags "<<x<<endl;


  //TODO:  test breadth-first search

  /** I tested my breath first search by making the print output variable set to true
   * an providing a detailed output of what my function was doing. as you can see it creates
   * a queue and adds the source. it then dequeues the first item adding it to a list of results
   * then enqueues all of the recently dequeued's friends. it does not add to the queue anyone
   * who is in the result list or already in the queue. you can choose what ever source you wish
   * and follow the printed output.
   */

Network * n = &network;
User* source = network.vertices[2];
//bfs(n,source,true);

}







