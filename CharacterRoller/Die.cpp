#include "Die.h"

Die::Die(uint64_t size, std::shared_ptr<std::mt19937> rngEngine) {
	this->dieSize = size;
	this->mersenneTwisterEngine = rngEngine;
}

uint64_t Die::roll() {
	
	if (this->dieSize == 0) {
		return 0;
	}

	std::uniform_int_distribution<uint64_t> distribution(0, this->dieSize);

	return distribution(*mersenneTwisterEngine);

}
