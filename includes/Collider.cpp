#include "Collider.h"
#include "GameObject.h"
#include "Game.h"


Collider::Collider(GameObject& associated, Vector2 scale, Vector2 offset) : Component(associated) {
	this->scale = scale;
	this->offset = offset;


}

Collider::~Collider() {

}


void Collider::Update(float dt)
{
	box = associated.box;

	box.SetSize(scale);
	
	box.SetCenter(associated.box.GetCenter() + offset.GetRotated(associated.angleDeg));

	Render();
}

// Copie o conteúdo dessa função para dentro da sua e adapte o nome das funções para as suas.
// Funções usadas:
// Rect::GetCenter()				- Retorna um Vector2 no centro do Rect
// Vector2::operator-( const Vector2& )	- Subtrai dois Vector2
// Vector2::Rotate( float rad )		- Rotaciona um Vector2 pelo ângulo em radianos passado
void Collider::Render()
{


	Vector2 center(box.GetCenter());
	SDL_Point points[5];
	
	Vector3 point = (Vector2(box.x, box.y) - center).GetRotated(associated.angleDeg / (FRAC_PI))
		+ center - Camera::GetCurrentCamPos();
	points[0] = { (int)point.x, (int)point.y };
	points[4] = { (int)point.x, (int)point.y };

	point = (Vector2(box.x + box.w, box.y) - center).GetRotated(associated.angleDeg / (FRAC_PI))
		+ center - Camera::GetCurrentCamPos();
	points[1] = { (int)point.x, (int)point.y };

	point = (Vector2(box.x + box.w, box.y + box.h) - center).GetRotated(associated.angleDeg / (FRAC_PI))
		+ center - Camera::GetCurrentCamPos();
	points[2] = { (int)point.x, (int)point.y };

	point = (Vector2(box.x, box.y + box.h) - center).GetRotated(associated.angleDeg / (FRAC_PI))
		+ center - Camera::GetCurrentCamPos();
	points[3] = { (int)point.x, (int)point.y };

	SDL_SetRenderDrawColor(Game::Instance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::Instance().GetRenderer(), points, 5);
 // DEBUG


}
