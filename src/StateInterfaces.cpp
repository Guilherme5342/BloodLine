#include "StateInterfaces.hpp"

AnimState::AnimState(Sprite& sprite) : spriteAnim(sprite)
{
}

void AnimState::Play(std::string animFile, int columns, int rows) {
	
	spriteAnim.Open(animFile, columns, rows);
}
