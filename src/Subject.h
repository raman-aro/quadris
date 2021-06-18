#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include <vector>
#include <memory>


class Observer;

class Subject {
  std::vector<std::shared_ptr<Observer>> observers;
 public:
  void attach(std::shared_ptr<Observer> o);
  void notifyObservers();
  void detach(std::shared_ptr<Observer> o);
  virtual ~Subject() {}
};

#endif

