#ifndef DIJKSTRA_H_
#define DIJKSTRA_H_

#include "Network.h"
#include "BinaryHeap.h"
#include "LinkedList.cpp"


void dijkstra_getShortestPaths(Network *network, User *source, bool printOutput = false);

LinkedList bfs(Network *network, User *source, bool printOutput = false);

#endif /*DIJKSTRA_H_*/
