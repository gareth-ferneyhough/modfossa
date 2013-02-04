#ifndef _MODELDESCRIPTION_H
#define _MODELDESCRIPTION_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class Connection;

class ModelDescription {
 public:
  ModelDescription();
  ~ModelDescription();
  void AddConnection(string startState, string endState, string rateName);
  const vector<Connection*>& GetConnections() const;

 private:
  vector<Connection*> connections;
};

#endif
