#ifndef _CONNECTION_H
#define _CONNECTION_H

#include <string>
using std::string;

class Connection {
 public:
  Connection();
  Connection(string start, string end, string rate);
  ~Connection();
  
  string GetStart() const;
  void SetStart(string);
  string GetEnd() const;
  void SetEnd(string);
  string GetRate() const;
  void SetRate();

 private:
  string start;
  string end;
  string rate;
};

#endif
