#include "LinkedList.cpp"
#include <iostream>
#include <string>
#include <sstream>
using std::cout;
using std::endl;
using std::string;
using std::stringstream;

void testLinkedListBasic() {
  // create a LinkedList for our testList
    LinkedList * testList = new LinkedList();

    // TEST insert
    for (int i = 0; i < 10; i++) {
      testList->insert_tail(new IntegerData(i));
    }

    for (int i = 0; i < 10; i++) {
      IntegerData * data = (IntegerData *)testList->get(i);
      if (data == NULL || data->value != i) {
        cout << "Error: data at index " << i << " is not == " << i << endl;
      }
    }
    cout << testList->toString() << endl;
    // -- end insert test

    // TEST remove and member
    IntegerData * data5 = (IntegerData *)testList->get(5);
    if (data5 != NULL) {
      testList->remove(data5);
      cout << testList->toString() << endl;

      cout << "member 5: " << testList->member(data5) << endl;
      testList->insert(data5);

      cout << testList->toString() << endl;
      cout << "member 5: " << testList->member(data5) << endl;
    }
    // -- end remove and member test

    // clean up memory
    for (int i = 0; i < testList->size(); i++) {
      delete testList->get(i);
    }
    // now delete the data structure
    delete testList;
}

void testLinkedListAddSorted() {
  // you must write a full test here that includes at least the examples
  // in the two insertSorted function comments
  // make sure that you de-allocate all memory that is allocated during
  // your tests

  LinkedList * one = new LinkedList();
  one->insert(new IntegerData(7));
  one->insert(new IntegerData(3));
  cout << one->toString() << endl;

  one->insertSorted(new IntegerData(1));
  cout << one->toString() << endl;
  one->insertSorted(new IntegerData(5));
  cout << one->toString() << endl;

//  [3, 7]->insertSorted(1) --> [1, 3, 7]
//       * [1, 3, 7]->insertSorted(5) --> [1, 3, 5, 7]

  delete one->get(0);
  one->remove(one->get(0));
  delete one->get(1);
  one->remove(one->get(1));
  cout << one->toString() << endl;

  LinkedList * two = new LinkedList();
  two->insert(new IntegerData(1));
//  [3, 7]->insertSorted([1]) --> [1, 3, 7]
  one->insertSorted(two);
  cout << one->toString() << endl;
  cout << two->toString() << endl;

//        * [1, 3, 7]->insertSorted([5, 6, 9]) --> [1, 3, 5, 6, 7, 9]
  two->remove(two->get(0)); // do not delete, it is in one now
  two->insert(new IntegerData(9));
  two->insert(new IntegerData(6));
  two->insert(new IntegerData(5));
  cout << two->toString() << endl;

  one->insertSorted(two);
  cout << one->toString() << endl;
  cout << two->toString() << endl;

  // clean up memory
  for (int i = 0; i < one->size(); i++) {
    delete one->get(i);
  }
  // now delete the data structure
  delete one;
  delete two;

}

void testStack() {
  // you must write a full test here for the 3 functions of the Stack
  // make sure that you de-allocate all memory that is allocated during
  // your tests
  Stack * s = new LinkedList(); // allocates a LinkedList instance to serve as the Stack

  s->push(new IntegerData(5));
  s->push(new IntegerData(6));
  s->push(new IntegerData(7));

  cout << s->peek()->toString() << endl;
  Data * d = s->pop();
  cout << d->toString() << endl;
  delete d;

  while ((d = s->pop()) != NULL) {
    delete d;
  }

  delete s;
}

void testQueue() {
  // TODO
  // you must write a full test here for the 3 functions of the Queue
  // make sure that you de-allocate all memory that is allocated during
  // your tests
}

int main(int argc, const char * argv[]) {
  cout << "Testing LinkedList basic functions..." << endl;
  testLinkedListBasic();
  cout << "Testing LinkedList Queue functions..." << endl;
  testQueue();
}
