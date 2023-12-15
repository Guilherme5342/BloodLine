#pragma once
#include <cstdint>

#include "Galapagos/Core/Component.hpp"
#include "Galapagos/Components/Rigidbody2D.hpp"

class Player : public Component
{
public:
	Player(GameObject& associated);

	void NotifyCollision(GameObject& otherObj) override;
	void Update(float deltaTime) override;
	void Render() const override;

	inline bool Is(std::string type) const override { return type == "Player"; }

private:

	void HandleInput(float deltaTime);

	bool m_grounded = false;
	bool m_dashing = false;
	
	Rigidbody2D* m_playerBody;

	std::int32_t m_hp;
};

