#include "Character.h"
#include <string>
#include <iostream>
#include <fstream>
#include "Die.h"
#include "Utilities.h"

// Roll damage dice out of eachand gain that many Traits Points to divide between each Skill

// Traits must be tied to a skill, but can only stack with Traits from seperate skills.
// For example
// if Grunt has a Trait "Violence, Combat" he can't also pop "Bludgeoner, Combat"  but he might be able to pop "Kung Fu, Special"
// Traits add a Flat Bonus to any of these skills
// 0 : D2
// 1 : D4
// 3 : D6
// 5 : D8
// 8 : D10
// 10 : D12
// 15 : D20
// 16 : 1D20 + 1D4
// 18 : 1D20 + 1D6

Character::Character(uint64_t level, std::string name, std::shared_ptr<std::mt19937> rng) {

	this->characterLevel = level;
	this->characterName = name;
	std::uniform_int_distribution<int16_t> distribution(0, 4);

	std::ofstream outputFile("Character.txt", std::ofstream::out | std::ofstream::app
	);

	outputFile << "Character Name: " << name << '\n';
	outputFile << "Character Level: " << level << '\n';

	this->skills[Skill::Combat] = 0;
	this->skills[Skill::Mental] = 0;
	this->skills[Skill::Resistance] = 0;
	this->skills[Skill::Special] = 0;
	this->skills[Skill::Utility] = 0;


	for (uint64_t toDistribute = level; toDistribute > 0; --toDistribute) {
		Skill theSkill = getSkillEnumFromNumber(distribution(*rng));
		this->skills[theSkill] += 1;
	}

	std::pair<uint64_t, std::string> combatRoll = rollTraitPoints(this->skills[Skill::Combat], rng);
	std::pair<uint64_t, std::string> mentalRoll = rollTraitPoints(this->skills[Skill::Mental], rng);
	std::pair<uint64_t, std::string> resistanceRoll = rollTraitPoints(this->skills[Skill::Resistance], rng);
	std::pair<uint64_t, std::string> specialRoll = rollTraitPoints(this->skills[Skill::Special], rng);
	std::pair<uint64_t, std::string> utilityRoll = rollTraitPoints(this->skills[Skill::Utility], rng);

	this->traits[Skill::Combat] = combatRoll.first;
	this->traits[Skill::Mental] = mentalRoll.first;
	this->traits[Skill::Resistance] = resistanceRoll.first;
	this->traits[Skill::Special] = specialRoll.first;
	this->traits[Skill::Utility] = utilityRoll.first;

	this->rolls[Skill::Combat] = combatRoll.second;
	this->rolls[Skill::Mental] = mentalRoll.second;
	this->rolls[Skill::Resistance] = resistanceRoll.second;
	this->rolls[Skill::Special] = specialRoll.second;
	this->rolls[Skill::Utility] = utilityRoll.second;

	for (auto it = this->skills.begin(); it != skills.end(); ++it) {
		std::cout << getSkillTextFromEnum(it->first) << ": " << it->second << std::endl;
		std::cout << this->traits[it->first] << " TP" << " (" << this->rolls[it->first] << ')' << std::endl;
		outputFile << getSkillTextFromEnum(it->first) << ": " << it->second << '\n';
		outputFile << this->traits[it->first] << " TP" << " (" << this->rolls[it->first] << ")\n";
	}

	outputFile << std::endl;

	outputFile.close();

}
