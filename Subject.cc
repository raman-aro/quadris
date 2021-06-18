
#include "Subject.h"
#include "Observer.h"
void Subject::attach(std::shared_ptr<Observer> o) {
    observers.emplace_back(o);
}
void Subject::notifyObservers() {

}
void Subject::detach(std::shared_ptr<Observer> o) {
    int i= 0;
    for (auto n: observers) {
        if (o == n) {
            observers.erase(observers.begin()+i);
        }
        ++i;
    }
}

