#include "Duel.hpp"
#include "Game/Game.hpp"
#include "HitParticle.hpp"
#include "Game/Grid.hpp"
#include "ShieldParticle.hpp"

Duel::Duel(Unit* _attacker, Unit* _defender) : m_attacker(_attacker), m_defender(_defender)
{
	m_logger.Debug("Duel created");
}

Duel::~Duel()
{
	m_logger.Debug("Duel destroyed");
}

void Duel::PerformDuel()
{
	int dmg = m_attacker->GetAtk() > 1 ? RandIntInRange(1, m_attacker->GetAtk()) : 1;
	m_logger.Debug("Attacker deals " + std::to_string(dmg) + " to defender");

	if (m_defender->HasShield())
	{
		m_logger.Debug("Defender has shield");
		GameData::GetInstance()->GetParticleManager()->AddParticle(new BlockedParticle(GridData::World2Screen(m_defender->GetPos().x, m_defender->GetPos().y, 0)));
	}
	else
	{
		GameData::GetInstance()->GetParticleManager()->AddParticle(new HitParticle(GridData::World2Screen(m_defender->GetPos().x, m_defender->GetPos().y, 0), dmg, false));
	}

	m_defender->Hurt(dmg);
	m_logger.Debug("Defender hp : " + std::to_string(m_defender->GetHp()));

	PerformCounterAttack();
}

void Duel::PerformCounterAttack()
{
	if (m_defender->GetHp() <= 0)
	{
		m_logger.Debug("Defender is dead");
		return;
	}

	int dmg = m_defender->GetAtk() > 3 ? RandIntInRange(1, m_defender->GetAtk() / 2) : 1;
	m_logger.Debug("Defender deals " + std::to_string(dmg) + " to attacker in counter attack");

	if (m_attacker->HasShield())
	{
		m_logger.Debug("Attacker has shield");
		GameData::GetInstance()->GetParticleManager()->AddParticle(new BlockedParticle(GridData::World2Screen(m_attacker->GetPos().x, m_attacker->GetPos().y, 0)));
	}
	else
	{
		GameData::GetInstance()->GetParticleManager()->AddParticle(new HitParticle(GridData::World2Screen(m_attacker->GetPos().x, m_attacker->GetPos().y, 0), dmg, true));
	}

	m_attacker->Hurt(dmg);
	m_logger.Debug("Attacker hp : " + std::to_string(m_attacker->GetHp()));
}