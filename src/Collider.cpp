#include "Collider.hpp"
#include "GameObject.hpp"
#include "Game.hpp"

Collider::Collider(GameObject &associated, Vector2 scale, Vector2 offset,
	bool trigger, bool setManually) : Component(associated)
{
	this->scale = scale;
	this->offset = offset;
	this->isTrigger = trigger;
	this->setManually = setManually;

	debug = true;
}

Collider::~Collider()
{
}

void Collider::Start()
{
	if (setManually)
		return;

	box.SetSize(associated.box.w,associated.box.h);
}

void Collider::FixedUpdate(float fixedDt)
{
	box.SetCenter(associated.box.GetCenter() + offset.GetRotated(associated.angleDeg * FRAC_PI));

}

void Collider::Update(float dt)
{

}

// Copie o conte�do dessa fun��o para dentro da sua e adapte o nome das fun��es para as suas.
// Fun��es usadas:
// Rect::GetCenter()				- Retorna um Vector2 no centro do Rect
// Vector2::operator-( const Vector2& )	- Subtrai dois Vector2
// Vector2::Rotate( float rad )		- Rotaciona um Vector2 pelo �ngulo em radianos passado
void Collider::Render()
{
	if (InputSystem::KeyPress(SDLK_TAB)) {
		debug = !debug;
	}

	if (!debug)
		return;

#pragma region Render Collider Bounds

	Vector2 center(box.GetCenter());
	SDL_Point points[5];

	Vector3 point = (Vector2(box.x, box.y) - center).GetRotated(associated.angleDeg / (FRAC_PI)) + center - Camera::GetCurrentCamPos();
	points[0] = { (int)point.x, (int)point.y };
	points[4] = { (int)point.x, (int)point.y };

	point = (Vector2(box.x + box.w, box.y) - center).GetRotated(associated.angleDeg / (FRAC_PI)) + center - Camera::GetCurrentCamPos();
	points[1] = { (int)point.x, (int)point.y };

	point = (Vector2(box.x + box.w, box.y + box.h) - center).GetRotated(associated.angleDeg / (FRAC_PI)) + center - Camera::GetCurrentCamPos();
	points[2] = { (int)point.x, (int)point.y };

	point = (Vector2(box.x, box.y + box.h) - center).GetRotated(associated.angleDeg / (FRAC_PI)) + center - Camera::GetCurrentCamPos();
	points[3] = { (int)point.x, (int)point.y };

	SDL_SetRenderDrawColor(Game::GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::GetRenderer(), points, 5);

#pragma endregion
}
