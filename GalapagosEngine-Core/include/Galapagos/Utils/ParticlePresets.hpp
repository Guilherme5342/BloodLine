#pragma once
#include "Galapagos/Components/ParticleEmmiter.hpp"

namespace ParticlePreset {
    const ParticleConfig Fire = {
		.position = {0, 0},
		.velocity = {0, 100},
		.velocityVariation = {40, 50},
		.startColor = {255, 0, 0, 255},
		.endColor = {0, 0, 255, 255},
		.startSize = 20,
		.endSize = 2,
		.sizeVariation = 5,
		.lifeTime = 10,
		.rate = 50
	};
};