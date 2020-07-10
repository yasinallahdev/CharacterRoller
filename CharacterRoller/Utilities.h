#pragma once

#include <cstdint>
#include <random>
#include <memory>

enum class Skill : int16_t;

std::pair<uint64_t, std::string> rollTraitPoints(uint64_t skillPoints, std::shared_ptr<std::mt19937> rng);

Skill getSkillEnumFromNumber(int16_t value);

std::string getSkillTextFromNumber(int16_t value);

std::string getSkillTextFromEnum(Skill theSkill);
