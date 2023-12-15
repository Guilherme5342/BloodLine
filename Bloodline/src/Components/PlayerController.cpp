#include "PlayerController.hpp"
#include "Components/Spells/Spell.hpp"
#include "Components/Spells/BloodSpell.hpp"
#include "Components/Spells/BloodBarrage.hpp"
#include "Components/Atack.hpp"
#include "Galapagos/Core/Game.hpp"
#include <cmath>

PlayerController::PlayerController(GameObject &associated, Sprite &sprite, Rigidbody2D &body, int speed)
	: StateMachine(associated, sprite),
	  speed(speed), playerBody(body), spells({{"BloodSpell", new BloodSpell(associated, 10.0, 10.0, 10, *this)}, {"BloodBarrage", new BloodBarrage(associated, 10.0, 10.0, 15, *this) }})
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
		cout << "Player is dead" << endl;
		return;
	}

	moving = (!jumping) && (InputSystem::Instance().IsKeyDown(SDLK_a) || InputSystem::Instance().IsKeyDown(SDLK_d));

	moveDir = {0, 0};
	moveDir.x += InputSystem::Instance().IsKeyDown(SDLK_a) * (-speed * dt);
	moveDir.x -= InputSystem::Instance().IsKeyDown(SDLK_d) * (-speed * dt);

	jumping = InputSystem::Instance().KeyPress(SDLK_SPACE) && canJump;
	playerBody.ApplyForce(Vector2(0, jumping * -jumpForce), IMPULSE);

	int direction = InputSystem::Instance().IsKeyDown(SDLK_a) ? -1 : InputSystem::Instance().IsKeyDown(SDLK_d) ? 1
																												   : 0;
	float dashVelocity = DASH_SPEED_MULTIPLIER * direction;

	if (canDash && InputSystem::Instance().KeyPress(SDLK_LSHIFT))
	{
		lastDashVel = dashVelocity;

		playerBody.ApplyVelocity(Vector2(dashVelocity, 0));
		canDash = false;
		dashElapsedTime = 0.0f;
		animState = new DashState(sprite);
	}

	if(InputSystem::Instance().KeyPress(SDLK_z)){
		GameObject *atackObject = new GameObject();
		atackObject->box.SetCenter(associated.box.GetCenter());
		float angle = 0;
		float speed = 200;
		int damage = 20;
		float maxDistance = 100;
		string sprite = "../assets/img/atack.png";
		bool targetsPlayer = false;
		int frameCount = 1;

		Atack *atack = new Atack(*atackObject, angle, damage, sprite, targetsPlayer, direction,frameCount);
		atackObject->AddComponent(atack);
		Game::Instance().GetState().AddObject(atackObject);
	}

	if (!canDash)
	{
		dashElapsedTime += dt;
		if (dashElapsedTime >= DASH_DURATION)
		{
			playerBody.ApplyVelocity(Vector2(-lastDashVel, 0));
			canDash = true;
			dashTimer = 0.0f;
		}
	}

	// cout << associated.box.x << endl;
	associated.box += moveDir;

	animState = new IdleState(sprite);
	if (moving && canJump)
	{
		animState = new MovingState(sprite);
	}

	if (InputSystem::Instance().KeyPress(SDLK_z))
	{
		animState = new AttackState(sprite, 10, 30, .2f);
	}

	if (InputSystem::Instance().KeyPress(SDLK_b))
	{
		CastSpell("BloodSpell");
	}

	if (InputSystem::Instance().KeyPress(SDLK_l))
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

void PlayerController::Render()
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