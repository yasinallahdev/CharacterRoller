#include "Utilities.h"
#include "Die.h"
#include "Enums.h"
#include <iostream>
#include <sstream>


// Die Size is defined by the following table:
// 0 : D2
// 1 : D4
// 3 : D6
// 5 : D8
// 8 : D10
// 10 : D12
// 15 : D20
// 16 : 1D20 + 1D4
// 18 : 1D20 + 1D6
uint16_t determineDieSize(uint64_t points) {
	switch (points) {
	case 0: return 2;
	case 1: // Fall Through
	case 2: return 4;
	case 3: // Fall Through
	case 4: return 6;
	case 5: // Fall Through
	case 6: // Fall Through
	case 7: return 8;
	case 8: // Fall Through
	case 9:return 10;
	case 10: // Fall Through
	case 11: // Fall Through
	case 12: // Fall Through
	case 13: // Fall Through
	case 14:return 12;
	case 15:return 20;
	default:return 20;
	}
}

std::pair<uint64_t, std::string> rollTraitPoints(uint64_t skillPoints, std::shared_ptr<std::mt19937> rng) {
	if (skillPoints <= 15) {
		uint64_t dieSize = determineDieSize(skillPoints);
		Die theDie(dieSize, rng);
		std::stringstream stringBuilder;
		stringBuilder << "1d" << dieSize;
		return std::make_pair<uint64_t>(theDie.roll(), stringBuilder.str());
	} else {
		std::stringstream stringBuilder;
		uint64_t DTwenties = skillPoints / 15;
		uint64_t smallerDieSize = determineDieSize(skillPoints % 15);
		Die otherDie(smallerDieSize, rng);
		uint64_t result = 0;
		for (uint64_t count = 0; count < DTwenties; count++) {
			Die thisDie(20, rng);
			result += thisDie.roll();
		}
		result += otherDie.roll();
		stringBuilder << DTwenties << "d20";
		if ((skillPoints % 15) != 0) {
			stringBuilder << " + 1d" << smallerDieSize;
		}
		return std::make_pair(result, stringBuilder.str());
	}
}

Skill getSkillEnumFromNumber(int16_t value) {
	switch (value) {
	case 0:return Skill::Combat;
	case 1:return Skill::Mental;
	case 2:return Skill::Resistance;
	case 3:return Skill::Special;
	case 4:return Skill::Utility;
	default:return Skill::Utility; // If the passed value is somehow not between 0 and 4, default to upgrading Utility to prevent an error case
	}
}

std::string getSkillTextFromNumber(int16_t value) {
	switch (value) {
	case 0:return "Combat";
	case 1:return "Mental";
	case 2:return "Resistance";
	case 3:return "Special";
	case 4:return "Utility";
	default:return "Utility";
	}
}

std::string getSkillTextFromEnum(Skill theSkill) {
	switch (theSkill) {
	case Skill::Combat:return "Combat";
	case Skill::Mental:return "Mental";
	case Skill::Resistance:return "Resistance";
	case Skill::Special:return "Special";
	case Skill::Utility:return "Utility";
	default:return "Utility";
	}
}
