#pragma once


#include "Component.hpp"
#include "GameObject.hpp"

#include "Sprite.hpp"
#include "Rigidbody2D.hpp"
#include "HealthHandler.hpp"

#include "GlobalDefinitions.hpp"
#include "Timer.hpp";

class EnemyBase : public Component {

protected:
	Action enemyAction;

	std::weak_ptr<GameObject> player;

	HealthHandler health;
	Rigidbody2D rb;

	Timer waitingTimer;
	Sprite sprite;

	Vector2 speed;

	int damage;

	Collider hitBox;

public:
	/// <summary>
	/// Esta é a classe base abstrata do Inimigo
	/// </summary>
	/// <param name="associated"> GameObject associado ao inimigo</param>
	/// <param name="player"> Referencia pro Player principal</param>
	/// <param name="enemySprite"> Sprite para o Inimigo </param>
	/// <param name="health">Vida do Inimigo</param>
	/// <param name="damage"> Dano do Inimigo </param>
	/// <param name="enemyPhys"> Comportamento da Física do Inimigo</param>
	EnemyBase(GameObject& associated, std::weak_ptr<GameObject> player,
		Sprite& sprite,int health, int damage, Action initialAction = IDLE, EnemyTypePhysics enemyPhys = GROUND);

	virtual ~EnemyBase();

	// Herdado por meio de Component
	virtual void Update(float dt);

	virtual void Render();

	inline virtual bool Is(std::string type) {
		return type == "EnemyBase";
	}

	virtual void Idle(float dt) {}
	virtual void Move(float dt) = 0;
	virtual void Attack(float dt) = 0;
	virtual void SpecialAttack(float dt) = 0;


	inline void SetActionState(Action action) {
		this->enemyAction = action;
	}
};

