#ifndef STACK_
#define STACK_
#ifndef NULL
#define NULL 0
#endif

#include "Collection.h"

class Stack {
  public:
    virtual ~Stack() {}
    
    /**
     * Returns the top element of the stack without removing it
     */
    virtual Data * peek() const = 0;
    
    /**
     * Removes (and returns) the top element of the stack
     */
    virtual Data * pop() = 0;
    
    /**
     * Pushes the given Data * onto the top of the stack
     */
    virtual void push(Data *) = 0;
};

#endif /*STACK_*/
