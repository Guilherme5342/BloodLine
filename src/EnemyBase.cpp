#include "EnemyBase.hpp"


EnemyBase::EnemyBase(GameObject& associated, std::weak_ptr<GameObject> player, Sprite& sprite
	, int health, int damage,Action initialAction, EnemyTypePhysics enemyPhys)
	: Component(associated),
	player(player),
	sprite(sprite),
	health(associated,health),
	rb(associated),
	damage(damage),
	hitBox(associated)
{
	enemyAction = initialAction;

	Vector2 spriteScale = Vector2(sprite.GetWidth(), sprite.GetHeight());

	hitBox.SetScale(Vector2(sprite.GetWidth(), sprite.GetHeight()));
	associated.box.SetSize(spriteScale);

	associated.AddComponent(&sprite);
	associated.AddComponent(&this->health);
	associated.AddComponent(&rb);
	associated.AddComponent(&hitBox);
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Update(float dt)
{
	switch (enemyAction)
	{
		case IDLE:
			Idle(dt);
			break;
		case MOVE:
			Move(dt);
			break;
		case ATTACK:
			Attack(dt);
			break;
		case MAGIC_SPELL:
			SpecialAttack(dt);
			break;
	}
}

void EnemyBase::Render()
{
}
