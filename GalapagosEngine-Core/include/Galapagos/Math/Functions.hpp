#pragma once
#include <SDL2/SDL.h>
#include "Galapagos/Math/Vec2.hpp"

namespace Math {
	inline SDL_Color lerp(const SDL_Color& first, const SDL_Color& second, float rate)
	{
		SDL_Color newColor;
		newColor.r = std::lerp(first.r, second.r, rate);
		newColor.g = std::lerp(first.g, second.g, rate);
		newColor.b = std::lerp(first.b, second.b, rate);
		newColor.a = std::lerp(first.a, second.a, rate);
		return newColor;
	}
	inline Vec2 lerp(const Vec2& first, const Vec2& second, float rate)
	{
		Vec2 newVec;
		newVec.x = std::lerp(first.x, second.x, rate);
		newVec.y = std::lerp(first.y, second.y, rate);
		return newVec;
	}
}