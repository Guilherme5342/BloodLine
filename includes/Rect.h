#pragma once

#include <type_traits>
#include <cmath>
#include "Vector3.h"

class Rect {

public:
	float x, y, w, h; // Posição X e Y e Largura + Altura
	inline Rect() {
		x = y = w = h = 0;
	}

	inline Rect(float x, float y, float width, float height) {
		this->x = x, this->y = y, this->w = width, this->h = height;
	}

	template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::val, T>::type>
	inline Rect(T x, T y, T width, T height) {
		this->x = x, this->y = y, this->w = width, this->h = height;
	}

	template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::val, T>::type>
	inline Rect(Vector2 pos, T width, T height) {
		this->x = pos.x, this->y = pos.y, this->w = width, this->h = height;
	}

	inline Rect(Vector2 pos, Vector2 size) {
		this->x = pos.x, this->y = pos.y;
		this->w = size.x, this->h = size.y;
	}

	inline Vector2 GetCenter() {
		return Vector2(x + w / 2, y + h / 2);
	}

	inline void SetCenter(float x, float y) {
		this->x = x - (w / 2);
		this->y = y - (h / 2);
	}

	template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::val, T>::type>
	inline void SetCenter(T x, T y) {
		this->x = x - (w / 2);
		this->y = y - (h / 2);
	}

	inline void SetCenter(Vector2 pos) {
		SetCenter(pos.x, pos.y);
	}

	inline void SetSize(Vector2 size) {
		this->w = size.x;
		this->h = size.y;
	}

	inline bool Contains(Rect otherRect) {
		return this->x < otherRect.x && this->y < otherRect.y && this->x + w > otherRect.x && this->y + h > otherRect.y;
	}

	Rect operator+(Vector2 vec2) {
		return Rect(GetCenter() + vec2, GetCenter() + vec2);
	}

	bool operator==(Rect otherRect) {
		if (this->x == otherRect.x && this->y == otherRect.y && this->w == otherRect.w && this->h == otherRect.h) {
			return true;
		}
		return false;
	}
};