#pragma once

#include <xmemory>

#include "Component.hpp"
#include "GameObject.hpp"

#include "Sprite.hpp"
#include "Rigidbody2D.hpp"
#include "HealthHandler.hpp"

#include "GlobalDefinitions.hpp"

class EnemyBase : public Component {

protected:
	Action enemyAction;

	HealthHandler health;
	Rigidbody2D rb;

	Sprite sprite;

	int damage;

public:
	/// <summary>
	/// Esta é a classe base abstrata do Inimigo
	/// </summary>
	/// <param name="associated"> GameObject associado ao inimigo</param>
	/// <param name="enemySprite"> Sprite para o Inimigo </param>
	/// <param name="health">Vida do Inimigo</param>
	/// <param name="damage"> Dano do Inimigo </param>
	/// <param name="enemyPhys"> Comportamento da Física do Inimigo</param>
	EnemyBase(GameObject& associated,Sprite& enemySprite,int health, int damage, EnemyTypePhysics enemyPhys);
	EnemyBase(GameObject& associated,std::string filePath,int health, int damage, EnemyTypePhysics enemyPhys);

	// Herdado por meio de Component
	virtual void Update(float dt);

	virtual void Render();

	inline virtual bool Is(std::string type) {
		return type == "EnemyBase";
	}

	virtual void Move() = 0;
	virtual void Attack() = 0;
	virtual void SpecialAttack() = 0;

};

