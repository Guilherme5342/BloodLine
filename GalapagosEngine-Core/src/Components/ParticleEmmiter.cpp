#include "Galapagos/Components/ParticleEmmiter.hpp"

#include <cmath>

#include "Galapagos/Core/Resources.hpp"
#include "Galapagos/Core/Game.hpp"
#include "Galapagos/Utils/Random.h"
#include "Galapagos/Math/Functions.hpp"


ParticleEmmiter::ParticleEmmiter(GameObject& associated, std::uint32_t numberOfParticles, Type type, std::string textureFile)
	: Component(associated)
{
	SetNumberOfParticles(numberOfParticles);
	m_type = type;
	if (type == Type::Texture && textureFile != "") {
		m_texture = Resources::GetImage(textureFile);
		SDL_QueryTexture(m_texture, nullptr, nullptr, &m_textureClipRect.w, &m_textureClipRect.h);
	}
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
		SDL_Color renderColor = Math::lerp(particle.endColor, particle.startColor, lifePercent);
		float renderSize = std::lerp(particle.endSize, particle.startSize, lifePercent);

		SDL_Rect distRect = SDL_Rect{ static_cast<int>(particle.position.x),static_cast<int>(particle.position.y),
									  static_cast<int>(particle.startSize), static_cast<int>(particle.startSize) };
		switch (m_type)
		{
		case ParticleEmmiter::Type::Rect:
			SDL_SetRenderDrawBlendMode(Game::GetRenderer(), SDL_BLENDMODE_BLEND);
			SDL_SetRenderDrawColor(Game::GetRenderer(), renderColor.r, renderColor.g, renderColor.b, renderColor.a * lifePercent);
			SDL_RenderFillRect(Game::GetRenderer(), &distRect);
			break;
		case ParticleEmmiter::Type::Texture:
			SDL_RenderCopyEx(Game::GetRenderer(), m_texture, &m_textureClipRect, &distRect, particle.rotation, nullptr, SDL_FLIP_NONE);
			break;
		case ParticleEmmiter::Type::Circle:
			break;
		default:
			break;
		}

	}

}

void ParticleEmmiter::SetNumberOfParticles(std::uint32_t numberOfParticles)
{
	m_particleList.resize(numberOfParticles);
	m_currentParticle = numberOfParticles - 1;
}

void ParticleEmmiter::Emit(const ParticleConfig& particleConfig)
{
	if (particleConfig.rate < 0 || m_timer.Get() < (1 / particleConfig.rate)) {
		return;
	}
	m_timer.Restart();
	Particle& particle = m_particleList[m_currentParticle];
	particle.active = true;
	particle.position = particleConfig.position;
	particle.rotation = Random::SlowFloat() * 360;

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