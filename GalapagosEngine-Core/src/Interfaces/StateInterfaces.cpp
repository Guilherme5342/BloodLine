#include "Galapagos/Interfaces/StateInterfaces.hpp"

AnimState::AnimState(Sprite& sprite) : spriteAnim(sprite)
{
}

void AnimState::Play(std::string animFile, std::uint32_t columns, std::uint32_t rows, float frameTime) {
	
	spriteAnim.Open(animFile, columns, rows,frameTime);
}
