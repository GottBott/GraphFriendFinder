# first name a variable objects for all object files
# FOR strauss
#CXX = CC

objectsqueue = LinkedList.o

objectstestqueue = QueueTests.o

objectsheap = BinaryHeap.o

objectstestheap = BinaryHeapTest.o

objectsdijkstra = CSV.o Network.o Dijkstra.o

objectstestdijkstra = DijkstraTest.o

# name a variable sources for all source files

sourcesqueue = LinkedList.cpp

sourcestestqueue = QueueTests.cpp

sourcesheap = BinaryHeap.cpp

sourcestestheap = BinaryHeapTest.cpp

sourcesdijkstra = CSV.cpp Network.cpp Dijkstra.cpp

sourcestestdijkstra = DijkstraTest.cpp

# now make default target all exe files
all: testqueue testheap testdijkstra

# list the dependencies for object files - those header files which help build objects
LinkedList.cpp: Collection.h Stack.h Queue.h
QueueTests.o: QueueTests.cpp LinkedList.cpp
BinaryHeap.o: BinaryHeap.h 
BinaryHeapTest.o: BinaryHeap.h 
Dijkstra.o: CSV.h Dijkstra.h Network.h BinaryHeap.h 

# how to build all object files from all dependent source files

$(objectsqueue): $(sourcesqueue)
	$(CXX) -c $(sourcesqueue) $(INCLUDES)

$(objectstestqueue): $(sourcestestqueue)
	$(CXX) -c $(sourcestestqueue) $(INCLUDES)

$(objectsheap): $(sourcesheap)
	$(CXX) -c $(sourcesheap) $(INCLUDES)

$(objectstestheap): $(sourcestestheap)
	$(CXX) -c $(sourcestestheap) $(INCLUDES)

$(objectsdijkstra): $(sourcesdijkstra)
	$(CXX) -c $(sourcesdijkstra) $(INCLUDES)
	
$(objectstestdijkstra): $(sourcestestdijkstra)
	$(CXX) -c $(sourcestestdijkstra) $(INCLUDES)

clean:
	rm -f *.o
	rm -f *.exe

testqueue:  $(objectsqueue) $(objectstestqueue)
	$(CXX) -o QueueTests.exe $(objectsqueue) $(objectstestqueue)

testheap: $(objectsheap) $(objectstestheap) 
	$(CXX) -o BinaryHeapTest.exe $(objectsheap) $(objectstestheap)

testdijkstra: $(objectsheap) $(objectsdijkstra) $(objectstestdijkstra) 
	$(CXX) -o DijkstraTest.exe $(objectsheap) $(objectsdijkstra) $(objectstestdijkstra)
