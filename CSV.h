#ifndef CSV_H_
#define CSV_H_


#include <string>
#include <vector>

using std::vector;
using std::string;

void csvline_populate(vector<string> &record, const string& line, char delimiter);

#endif
