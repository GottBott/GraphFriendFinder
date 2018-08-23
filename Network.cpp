

#include "Network.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <algorithm>
#include <vector>
#include <limits>

#include "CSV.h"

using std::cout;
using std::cerr;
using std::ifstream;
using std::ofstream;
using std::endl;
using std::vector;

bool Network::readFromFile(const char * fileName) {
  ifstream inFile(fileName);
  if (!inFile) {
    cerr << "File could not be opened" << endl;
    return false;
  }
  if (inFile.fail()) {
    cerr << "File not found" <<endl;
    return false;
  }
  
  vector<string> row;
  string line;

  
  int type = 0;

  while(getline(inFile, line, '\r') && inFile.good() ) {
    csvline_populate(row, line, ',');

    if (row[0].at(0) == '#') {
      type++;
      //cout << "now on type " << type << endl;
    }
    else if (type == 2 || type == 3) {
      // Friend 
      int id1;
      int id2;
	  int cc;
	  double weight;

      id1 = atoi(row[0].c_str());
      id2 = atoi(row[1].c_str());
	  weight = atof(row[2].c_str());
	  cc = atoi(row[3].c_str());
      
      //cout << id1 << ',' << id2 << ',' << weight << ',' << cc << endl;
      
      // we need to find the User object that was created earlier
      User* v1;
      User* v2;
      // find them by iterating through our Network
      for (vector<User*>::iterator iter = vertices.begin();
           iter != vertices.end(); iter++) {
        User* vTest = *iter;
        if (vTest->id == id1) {
          v1 = vTest;
        }
        else if (vTest->id == id2) {
          v2 = vTest;
        }
      }

      //double distance = v1->getDistance(v2);
      v1->links.push_back(new Friend(v1,v2,weight,cc));
      v2->links.push_back(new Friend(v2,v1,weight,cc));

    }
    else if (type == 1) {
      // User
	  string firstname = row[0];
	  string lastname = row[1];
      int id = atoi(row[2].c_str());
	  string gender = row[3];
	  string joindate = row[4];
	  double lat = atof(row[5].c_str());
	  double lon = atof(row[6].c_str());
	  string city = row[7];
	  string state = row[8];
	  string country = row[9];
	  int numcheckins = atoi(row[10].c_str());

      City* c = new City(city, state, country, lat, lon);
      User* v = new User(id, firstname, lastname, gender, joindate, numcheckins, c);

      vertices.push_back(v);
    }
  }

  for (vector<User*>::iterator iter = vertices.begin();
         iter != vertices.end(); iter++) {
      User* vTest = *iter;
      if (vTest->id > maxId) {
        maxId = vTest->id;
      }
  }

  return true;
}

