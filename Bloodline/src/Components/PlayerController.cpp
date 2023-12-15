#include "PlayerController.hpp"
#include "Components/Spells/Spell.hpp"
#include "Components/Spells/BloodSpell.hpp"
#include "Components/Spells/BloodBarrage.hpp"
#include "Components/Atack.hpp"
#include "Galapagos/Core/Game.hpp"
#include <cmath>

PlayerController::PlayerController(GameObject &m_associated, Sprite &sprite, Rigidbody2D &body, int speed)
	: StateMachine(m_associated, sprite),
	  speed(speed), playerBody(body), spells({{"BloodSpell", new BloodSpell(m_associated, 10.0, 10.0, 10, *this)}, {"BloodBarrage", new BloodBarrage(m_associated, 10.0, 10.0, 15, *this) }})
{
	animState = nullptr;
	canDash = true;
	dashTimer = 0.0f;
	dashElapsedTime = 0.0f;
}

PlayerController::~PlayerController()
{
}

float lastDashVel;
void PlayerController::Update(float dt)
{
	if(health <= 0) {
		dead = true;
	}

	if(dead){
		animState = new DeathState(sprite);
		std::cout << "Player is dead" << std::endl;
		return;
	}

	moving = (!jumping) && (InputManager::IsKeyDown(Key::A) || InputManager::IsKeyDown(Key::D));

	moveDir = {0, 0};
	moveDir.x += InputManager::IsKeyDown(Key::A) * (-speed * dt);
	moveDir.x -= InputManager::IsKeyDown(Key::D) * (-speed * dt);

	jumping = InputManager::KeyPress(Key::Space) && canJump;
	playerBody.ApplyForce(Vec2(0, jumping * -jumpForce), IMPULSE);

	int direction = InputManager::IsKeyDown(Key::A) ? -1 : InputManager::IsKeyDown(Key::D) ? 1 : 0;
	float dashVelocity = DASH_SPEED_MULTIPLIER * direction;

	if (canDash && InputManager::KeyPress(Key::Lshift))
	{
		lastDashVel = dashVelocity;

		playerBody.ApplyVelocity(Vec2(dashVelocity, 0));
		canDash = false;
		dashElapsedTime = 0.0f;
		animState = new DashState(sprite);
	}

	if(InputManager::KeyPress(Key::Z)){
		GameObject *atackObject = new GameObject();
		atackObject->m_box.SetCenter(m_associated.m_box.GetCenter());
		float angle = 0;
		float speed = 200;
		int damage = 20;
		float maxDistance = 100;
		std::string sprite = "../assets/img/atack.png";
		bool targetsPlayer = false;
		int frameCount = 1;

		Atack *atack = new Atack(*atackObject, angle, damage, sprite, targetsPlayer, direction,frameCount);
		atackObject->AddComponent(atack);
		Game::GetCurrentState().AddObject(atackObject);
	}

	if (!canDash)
	{
		dashElapsedTime += dt;
		if (dashElapsedTime >= DASH_DURATION)
		{
			playerBody.ApplyVelocity(Vec2(-lastDashVel, 0));
			canDash = true;
			dashTimer = 0.0f;
		}
	}

	// cout << m_associated.m_box.x << endl;
	m_associated.m_box.SetCenter(m_associated.m_box.GetCenter() + moveDir);

	animState = new IdleState(sprite);
	if (moving && canJump)
	{
		animState = new MovingState(sprite);
	}

	if (InputManager::KeyPress(Key::Z))
	{
		animState = new AttackState(sprite, 10, 30, .2f);
	}

	if (InputManager::KeyPress(Key::B))
	{
		CastSpell("BloodSpell");
	}

	if (InputManager::KeyPress(Key::L))
	{
		CastSpell("BloodBarrage");
	}

	animState->Update(*this, dt);

	SetState(animState);
}

void PlayerController::CastSpell(std::string spellName)
{
	if (spells.find(spellName) != spells.end() && spells[spellName]->canCast(*this))
	{
		spells[spellName]->Activate();
		health -= spells[spellName]->GetHealthCost(); // Assuming each spell has a health cost
	}
}

void PlayerController::AddSpell(std::string spellName, Spell *spell)
{
	spells[spellName] = spell;
}

void PlayerController::NotifyCollision(GameObject &otherObj)
{
	canJump = otherObj.tag == "Ground";
}

void PlayerController::NotifyNoCollision(GameObject& otherObj) {

}

void PlayerController::Render() const
{
	animState->Render(*this);
}

int PlayerController::GetHealth()
{
	return health;
}

bool PlayerController::IsDead()
{
	return dead;
}