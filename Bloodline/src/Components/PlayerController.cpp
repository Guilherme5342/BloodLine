#include "PlayerController.hpp"
#include "Components/Spells/Spell.hpp"
#include "Components/Spells/BloodSpell.hpp"
#include "Components/Spells/BloodBarrage.hpp"
#include "Components/Atack.hpp"
#include "Galapagos/Core/Game.hpp"
#include <cmath>

PlayerController::PlayerController(GameObject &m_associated, Sprite &sprite, Rigidbody2D &body, int speed)
	: StateMachine(m_associated, sprite),
	  m_speed(speed), m_playerBody(body), m_spells({{"BloodSpell", new BloodSpell(m_associated, 10.0, 10.0, 10, *this)}, {"BloodBarrage", new BloodBarrage(m_associated, 10.0, 10.0, 15, *this)}})
{
	m_animState = nullptr;
	m_canDash = true;
	m_dashTimer = 0.0f;
	m_dashElapsedTime = 0.0f;
}

PlayerController::~PlayerController()
{
}

float lastDashVel;
void PlayerController::Update(float dt)
{
	if (m_health <= 0)
	{
		m_dead = true;
	}

	if (m_dead)
	{
		m_animState = new DeathState(sprite);
		std::cout << "Player is dead" << std::endl;
		return;
	}

	m_moving = (!m_jumping) && (InputManager::IsKeyDown(Key::A) || InputManager::IsKeyDown(Key::D));

	m_moveDir = {0, 0};
	m_moveDir.x += InputManager::IsKeyDown(Key::A) * (-m_speed * dt);
	m_moveDir.x -= InputManager::IsKeyDown(Key::D) * (-m_speed * dt);

	m_jumping = InputManager::KeyPress(Key::Space) && m_canJump;
	m_playerBody.ApplyForce(Vec2(0, m_jumping * -m_jumpForce), ForceType::IMPULSE);

	int direction = InputManager::IsKeyDown(Key::A) ? -1 : InputManager::IsKeyDown(Key::D) ? 1
																						   : 0;
	float dashVelocity = DASH_SPEED_MULTIPLIER * direction;

	if (m_canDash && InputManager::KeyPress(Key::Lshift))
	{
		lastDashVel = dashVelocity;

		m_playerBody.ApplyVelocity(Vec2(dashVelocity, 0));
		m_canDash = false;
		m_dashElapsedTime = 0.0f;
		m_animState = new DashState(sprite);
	}

	if (InputManager::KeyPress(Key::Z))
	{
		GameObject *atackObject = new GameObject();
		atackObject->m_box.SetCenter(m_associated.m_box.GetCenter());
		float angle = 0;
		float speed = 200;
		int damage = 20;
		float maxDistance = 100;
		std::string sprite = "../assets/img/atack.png";
		bool targetsPlayer = false;
		int frameCount = 1;

		Atack *atack = new Atack(*atackObject, angle, damage, sprite, targetsPlayer, direction, frameCount);
		atackObject->AddComponent(atack);
		Game::GetCurrentState().AddObject(atackObject);
	}

	if (!m_canDash)
	{
		m_dashElapsedTime += dt;
		if (m_dashElapsedTime >= DASH_DURATION)
		{
			m_playerBody.ApplyVelocity(Vec2(-lastDashVel, 0));
			m_canDash = true;
			m_dashTimer = 0.0f;
		}
	}

	// cout << m_associated.m_box.x << endl;
	m_associated.m_box.SetCenter(m_associated.m_box.GetCenter() + m_moveDir);

	m_animState = new IdleState(sprite);
	if (m_moving && m_canJump)
	{
		m_animState = new MovingState(sprite);
	}

	if (InputManager::KeyPress(Key::Z))
	{
		m_animState = new AttackState(sprite, 10, 30, .2f);
	}

	if (InputManager::KeyPress(Key::B))
	{
		CastSpell("BloodSpell");
	}

	if (InputManager::KeyPress(Key::L))
	{
		CastSpell("BloodBarrage");
	}

	m_animState->Update(*this, dt);

	SetState(m_animState);
}

void PlayerController::CastSpell(std::string spellName)
{
	if (m_spells.find(spellName) != m_spells.end() && m_spells[spellName]->canCast(*this))
	{
		m_spells[spellName]->Activate();
		m_health -= m_spells[spellName]->GetHealthCost(); // Assuming each spell has a health cost
	}
}

void PlayerController::AddSpell(std::string spellName, Spell *spell)
{
	m_spells[spellName] = spell;
}

void PlayerController::NotifyCollision(GameObject &otherObj)
{
	m_canJump = otherObj.tag == "Ground";
}

void PlayerController::NotifyNoCollision(GameObject &otherObj)
{
}

void PlayerController::Render() const
{
	m_animState->Render(*this);
}

int PlayerController::GetHealth()
{
	return m_health;
}

bool PlayerController::IsDead()
{
	return m_dead;
}