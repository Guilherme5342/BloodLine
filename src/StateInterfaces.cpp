#include "StateInterfaces.hpp"

AnimState::AnimState(Sprite& sprite,std::string animFile) : spriteAnim(sprite)
{
	spriteAnim.Open(animFile);
}

void AnimState::Play(std::string animFile) {

	spriteAnim.Open(animFile);
	if (spriteAnim.IsOpen()) {
		spriteAnim.SetFrame(0);
	}
}
