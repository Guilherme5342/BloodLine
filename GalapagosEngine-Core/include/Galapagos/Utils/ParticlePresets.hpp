#pragma once
#include "Galapagos/Components/ParticleEmmiter.hpp"

namespace ParticlePreset {
    const ParticleConfig Fire = {
		.position = {0, 0},
		.velocity = {0, -100},
		.velocityVariation = {60, 20},
		.startColor = {245, 228, 122, 255},
		.endColor = {255, 91, 10, 255},
		.startSize = 8,
		.endSize = 0,
		.sizeVariation = 2,
		.lifeTime = 2,
		.rate = 80
	};
	const ParticleConfig Rain = {
		.position = {0, 0},
		.velocity = {20, 80},
		.velocityVariation = {10, 20},
		.startColor = {180, 255, 255, 255},
		.endColor = {49, 228, 247, 255},
		.startSize = 4,
		.endSize = 1,
		.sizeVariation = 2,
		.lifeTime = 10,
		.rate = 50
	};
};