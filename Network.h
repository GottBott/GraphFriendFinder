#ifndef NETWORK_H_
#define NETWORK_H_

#ifndef NULL
#define NULL 0
#endif

#include "BinaryHeap.h"
#include <vector>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>

using std::cout;
using std::vector;
using std::endl;
using std::string;

// Reserve the name for each Class to allow recursive definition
class User;
class City;
class Friend;

class Network {
  public:
    vector<User*> vertices;
    int maxId;
    
    Network(){}
    ~Network(){}
    
    int size() {
      return vertices.size();
    }
    
    bool readFromFile(const char * fileName);
};


class City {
  public:

    string name;
    string region;
	string country;
	double lat;
	double lon;

	/* ??
    Location* local;
    vector<Location*> ports;
    vector<FoodSource*> foodSources; // this country is the To for each of these
    vector<FoodSource*> foodTargets; // this country is the From for each of these
	*/

  City(string name, string region, string country, double lat, double lon) :
    name(name), region(region), country(country), lat(lat), lon(lon) {}

  ~City() {}

  void print() {
    cout << name << ": lat=" << lat << " lon=" << lon << endl;
  }
};


class User : public Data {
  public:
  int id;
  string firstname;
  string lastname;
  string gender;
  string joindate;
  int numcheckins;
  City *city;

  // stored here for Dijkstra's algorithm to use so that User can extend Data
  // this allows us to directly insert User instances into the heap
  double dist;
  User *prior;
  Container *heapNode;

  vector<Friend*> links;
  User(int uId, string first, string last, string gender, string jdate, int numcheckins, City *pCity) :
    id(uId), firstname(first), lastname(last), gender(gender), joindate(jdate), numcheckins(numcheckins),
        city(pCity), dist(0), prior(NULL) {
  }

  // for if you want to get a geographic distance between two users
  double getDistance(User *p) {
    // approximate distance
    // http://www.meridianworlddata.com/Distance-Calculation.asp
    double difflon = p->city->lon - city->lat;

    if (abs(difflon) > 180.0) {
      // it really should wrap around the world instead
      // sign doesn't matter because of sqrt
      difflon = 360.0 - abs(difflon);
    }

    double x = 69.1 * (difflon);
    double y = 53.0 * (p->city->lat - city->lat);
    return sqrt(x * x + y * y);
  }

  /**
   * Returns 0 if equal to other, -1 if < other, 1 if > other
   */
  int compareTo(Data * other) const {
    if (dist < ((User*) other)->dist) {
      return -1;
    }
    else if (dist > ((User*) other)->dist) {
      return 1;
    }
    else {
      return 0;
    }
  }

  /**
   * Returns a string representation of the data and dist
   */
  string toString() const {
    stringstream s;
    s << firstname << " " << lastname << "=" << dist;
    return s.str();
  }
};

class Friend {
  public:
    User *source;
    User *target;
    double weight;
	int commoncheckins;
    string text;

    Friend(User *pSource, User *pTarget, double pWeight, int pCommoncheckins)
        : source(pSource), target(pTarget), weight(pWeight), commoncheckins(pCommoncheckins) { }

    double getGeographicalDistance() {
      return source->getDistance(target);
    }

    double getDistance() {
	  return weight;
    }
};


#endif
