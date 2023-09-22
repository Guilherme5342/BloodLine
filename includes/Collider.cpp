#include "Collider.h"
#include "GameObject.h"

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
// Rect::GetCenter()				- Retorna um Vec2 no centro do Rect
// Vec2::operator-( const Vec2& )	- Subtrai dois Vec2
// Vec2::Rotate( float rad )		- Rotaciona um Vec2 pelo ângulo em radianos passado
void Collider::Render()
{

#ifdef DEBUG
	Vec2 center(box.GetCenter());
	SDL_Point points[5];

	Vec2 point = (Vec2(box.x, box.y) - center).Rotate(associated.angleDeg / (180 / PI))
		+ center - Camera::pos;
	points[0] = { (int)point.x, (int)point.y };
	points[4] = { (int)point.x, (int)point.y };

	point = (Vec2(box.x + box.w, box.y) - center).Rotate(associated.angleDeg / (180 / PI))
		+ center - Camera::pos;
	points[1] = { (int)point.x, (int)point.y };

	point = (Vec2(box.x + box.w, box.y + box.h) - center).Rotate(associated.angleDeg / (180 / PI))
		+ center - Camera::pos;
	points[2] = { (int)point.x, (int)point.y };

	point = (Vec2(box.x, box.y + box.h) - center).Rotate(associated.angleDeg / (180 / PI))
		+ center - Camera::pos;
	points[3] = { (int)point.x, (int)point.y };

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
#endif // DEBUG


}
