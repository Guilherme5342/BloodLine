#include "Galapagos/Components/ParticleEmmiter.hpp"
#include "Galapagos/Core/Resources.hpp"
#include "Galapagos/Core/Game.hpp"
#include "Galapagos/Utils/Random.h"

ParticleEmmiter::ParticleEmmiter(GameObject& associated, std::uint32_t numberOfParticles)
	: Component(associated)
{
	SetNumberOfParticles(numberOfParticles);
}

void ParticleEmmiter::Start()
{
}

void ParticleEmmiter::Update(float deltaTime)
{
	m_timer.Update(deltaTime);
	for (Particle& particle : m_particleList)
	{
		if (!particle.active || particle.lifeRemaning <= 0)
		{
			particle.active = false;
			continue;
		}

		particle.lifeRemaning -= deltaTime;
		particle.position += particle.velocity * deltaTime;
		particle.rotation += 0.05f * deltaTime;
	}
}

void ParticleEmmiter::Render() const
{
	for (const Particle& particle : m_particleList)
	{
		if (!particle.active)
		{
			continue;
		}
		float lifePercent = particle.lifeRemaning / particle.lifeTime;
		SDL_Rect distRect = SDL_Rect{ static_cast<int>(particle.position.x),static_cast<int>(particle.position.y),
									  static_cast<int>(particle.startSize), static_cast<int>(particle.startSize) };

		SDL_SetRenderDrawBlendMode(Game::GetRenderer(), SDL_BLENDMODE_ADD);
		SDL_SetRenderDrawColor(Game::GetRenderer(), particle.startColor.r, particle.startColor.g, particle.startColor.b, particle.startColor.a * lifePercent);
		SDL_RenderFillRect(Game::GetRenderer(), &distRect);
	}

}

void ParticleEmmiter::SetNumberOfParticles(std::uint32_t numberOfParticles)
{
	m_particleList.resize(numberOfParticles);
	m_currentParticle = numberOfParticles - 1;
}

void ParticleEmmiter::Emit(const ParticleConfig& particleConfig)
{
	if (m_timer.Get() < 0.04) {
		return;
	}
	m_timer.Restart();
	Particle& particle = m_particleList[m_currentParticle];
	particle.active = true;
	particle.position = particleConfig.position;
	particle.rotation = Random::SlowFloat() * 2 * M_PI;

	particle.velocity = particleConfig.velocity;
	particle.velocity.x = particleConfig.velocityVariation.x * (Random::SlowFloat() - 0.5f);
	particle.velocity.y = particleConfig.velocityVariation.y * (Random::SlowFloat() - 0.5f);

	particle.startColor = particleConfig.startColor;
	particle.endColor = particleConfig.endColor;

	particle.lifeTime = particleConfig.lifeTime;
	particle.lifeRemaning = particleConfig.lifeTime;
	particle.startSize = particleConfig.startSize + particleConfig.sizeVariation * (Random::SlowFloat() - 0.5f);
	particle.endSize = particleConfig.endSize;

	m_currentParticle = --m_currentParticle % m_particleList.size();
}