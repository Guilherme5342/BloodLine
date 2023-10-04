#pragma once

#include <type_traits>
#include <cmath>
#include <algorithm>

#ifdef _WIN32
#include "SDL_image.h"
#else
#include <SDL2/SDL_image.h>
#endif

#include "Vector3.h"

struct Rect
{

public:
	float x, y, w, h; // Posi��o X e Y e Largura + Altura

	// SDL_Rect debugRect{ x,y,w,h };

	inline Rect()
	{
		x = y = w = h = 0;
	}

	inline Rect(float x, float y, float width, float height)
	{
		this->x = x, this->y = y, this->w = width, this->h = height;
	}

	// template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::val, T>::type>
	inline Rect(Vector2 pos, float width, float height)
	{
		this->x = pos.x, this->y = pos.y, this->w = width, this->h = height;
	}

	inline Rect(Vector2 pos, Vector2 size)
	{
		this->x = pos.x, this->y = pos.y;
		this->w = size.x, this->h = size.y;
	}

	inline Vector2 GetCenter()
	{
		return Vector2(x + w / 2, y + h / 2);
	}

	inline void SetCenter(float x, float y)
	{
		this->x = x - (w / 2);
		this->y = y - (h / 2);
	}

	template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::val, T>::type>
	inline void SetCenter(T const x, T const y)
	{
		this->x = x - (w / 2);
		this->y = y - (h / 2);
	}

	inline void SetCenter(Vector2 const &pos)
	{
		SetCenter(pos.x, pos.y);
	}

	inline void SetSize(float w, float h)
	{
		this->w = w;
		this->h = h;
	}
	inline void SetSize(Vector2 size)
	{
		SetSize(size.x, size.y);
	}

	inline bool Contains(Rect otherRect)
	{
		return this->x<otherRect.x &&this->y<otherRect.y &&this->x + w> otherRect.x &&this->y + h> otherRect.y;
	}

	Rect operator+(const Vector2 &vec2)
	{
		return Rect(GetCenter() + vec2, GetCenter() + vec2);
	}

	Rect &operator+=(const Vector2 &vec)
	{
		this->x += vec.x;
		this->y += vec.y;
		return *this;
	}

	bool operator==(Rect otherRect)
	{
		if (this->x == otherRect.x && this->y == otherRect.y && this->w == otherRect.w && this->h == otherRect.h)
		{
			return true;
		}
		return false;
	}

	Rect GetIntersection(Rect &otherRect);

	void FillRect();
};