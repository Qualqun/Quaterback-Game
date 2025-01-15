#ifndef DUEL_HPP
#define DUEL_HPP

#include "Common.hpp"
#include "Unit.hpp"

class Duel
{
private:
	Unit* m_attacker;
	Unit* m_defender;

	Logger m_logger = Logger(std::cout, "Duel");

protected:
	void PerformCounterAttack();

public:
	Duel(Unit* _attacker, Unit* _defender);
	~Duel();

	// Perform a duel between two units
	void PerformDuel();
};

#endif