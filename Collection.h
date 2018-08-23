#ifndef COLLECTION_H_
#define COLLECTION_H_
#ifndef NULL
#define NULL 0
#endif

#include <string>
using std::string;

#include "Data.h"

class Collection {
  public:
    virtual ~Collection() {}

    /**
     * Returns the count of the number of elements in the Collection
     */
    virtual int size() const = 0;
    
    /**
     * Adds the given Data value to the Collection. Placement index of
     * the newly inserted element is assumed to be at the end.
     */
    virtual void insert_tail(Data *) = 0;

    /**
     * Gets a Data value from the Collection based on an index. The meaning
     * of indexes is implementation dependent, but generally index 0 is the
     * "beginning" of the Collection and index=size()-1 is the "end" of the
     * Collection.
     */
    virtual Data * get(int index) = 0;

    /**
     * Removes a given value from the Collection based on pointer equality
     * (data to be removed must be == to parameter).  Returns true if
     * the Data was removed from the Collection.
     */
    virtual bool remove(Data *) = 0;

    /**
     * Tests if the given Data is already a member of this Collection.
     * Uses the compareTo method of the Data class.  Data is a member of the
     * Collection if compareTo(x) == 0 for any x currently in Collection.
     */
    virtual bool member(Data *) = 0;

    /**
     * Returns a string representation of the data
     */
    virtual string toString() const = 0;
};


#endif /*COLLECTION_H_*/
