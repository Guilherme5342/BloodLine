#include "StateInterfaces.hpp"

AnimState::AnimState(Sprite& sprite) : spriteAnim(sprite)
{
}

void AnimState::Play(std::string animFile) {
	
	spriteAnim.Open(animFile);
	if (spriteAnim.IsOpen()) {
		spriteAnim.SetFrame(0);
		cout << "Tocando animacao " << animFile << endl;
	}
}
