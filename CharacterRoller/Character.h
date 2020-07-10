#pragma once

#include <string>
#include "Enums.h"
#include <map>
#include <cstdint>
#include <memory>
#include <string>
#include <random>

class Character {
	
private:

	uint64_t characterLevel;
	std::string characterName;
	std::map<Skill, uint64_t> skills; // Points in an individual skill
	std::map<Skill, uint64_t> traits; // Trait Points associated with Skills
	std::map<Skill, std::string> rolls; // What the die roll was for the traits

public:

	Character(uint64_t level, std::string name, std::shared_ptr<std::mt19937> rng);

};
