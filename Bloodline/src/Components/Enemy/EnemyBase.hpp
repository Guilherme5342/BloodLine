#pragma once

#include "Galapagos/Core/Component.hpp"
#include "Galapagos/Core/GameObject.hpp"

#include "Galapagos/Components/Sprite.hpp"
#include "Galapagos/Components/Rigidbody2D.hpp"
#include "Galapagos/Components/Collider.hpp"

#include "Components/HealthHandler.hpp"

#include "GameDefines/GlobalDefinitions.hpp"
#include "Galapagos/Utils/Timer.hpp"

class EnemyBase : public Component
{
public:
	/// <summary>
	/// Esta � a classe base abstrata do Inimigo
	/// </summary>
	/// <param name="associated"> GameObject associado ao inimigo</param>
	/// <param name="player"> Referencia pro Player principal</param>
	/// <param name="enemySprite"> Sprite para o Inimigo </param>
	/// <param name="health">Vida do Inimigo</param>
	/// <param name="damage"> Dano do Inimigo </param>
	/// <param name="enemyPhys"> Comportamento da F�sica do Inimigo</param>
	EnemyBase(GameObject &associated, std::weak_ptr<GameObject> player,
			  Sprite &sprite, int health, int damage, Action initialAction = Action::IDLE, EnemyTypePhysics enemyPhys = EnemyTypePhysics::GROUND);

	virtual ~EnemyBase();

	virtual void Start() {}
	// Herdado por meio de Component
	virtual void Update(float dt);

	virtual void Render();

	inline virtual bool Is(std::string type) { return type == "EnemyBase"; }

	virtual void NotifyCollision(GameObject &other);

	virtual void Idle(float dt) {}
	virtual void Move(float dt) = 0;
	virtual void Attack(float dt) = 0;
	virtual void SpecialAttack(float dt) = 0;

	inline void SetActionState(Action action) { this->m_enemyAction = action; }

	inline Collider GetHitBox() const { return this->m_hitBox; }

protected:
	Action m_enemyAction;

	std::weak_ptr<GameObject> m_player;

	HealthHandler m_health;
	Rigidbody2D m_rb;

	Timer m_waitingTimer;
	Sprite &m_sprite;

	Vec2 m_speed = {1, 1};

	int m_damage;
	bool m_isOnFloor = false;

	Collider m_hitBox;
};
