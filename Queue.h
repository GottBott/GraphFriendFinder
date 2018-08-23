#ifndef QUEUE_
#define QUEUE_
#ifndef NULL
#define NULL 0
#endif

#include "Collection.h"

class Queue {
  public:
    virtual ~Queue() {}
    
    /**
     * Returns the top element of the queue without removing it
     */
    virtual Data * peek() const = 0;
    
    /**
     * Removes (and returns) the top element of the queue 
     */
    virtual Data * dequeue() = 0;
    
    /**
     * Pushes the given Data * onto the top of the queue
     */
    virtual void enqueue(Data *) = 0;
};

#endif /*QUEUE_*/
