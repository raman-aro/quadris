#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include <vector>
#include <memory>

class Block;


class Observer {
public:
	virtual void notify(std::vector<int> oldCoordinates,
						std::vector<int> newCoordinates,
						std::shared_ptr<Block> b) = 0;
	virtual ~Observer() = default;
};
#endif
