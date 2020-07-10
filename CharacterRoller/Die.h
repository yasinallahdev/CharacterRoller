#pragma once

#include <random>
#include <memory>
#include <cstdint>

class Die {

private:

	uint64_t dieSize;
	std::shared_ptr<std::mt19937> mersenneTwisterEngine;

public:

	Die(uint64_t size, std::shared_ptr<std::mt19937> rngEngine);

	uint64_t roll();

};
