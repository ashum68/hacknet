#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>

class Observer; // forward declaration

class Subject {
  std::vector<Observer*> observers;
 public:
  void attach( Observer* o ); // bool or void?
  void detach( Observer* o );
  void notifyObservers();
  virtual char getState( int r, int c ) const = 0;
  virtual ~Subject() = default;
};

#endif
