#pragma once
#include <string>

namespace NCL {
	namespace Assets {
		const std::string SHADERDIR("../../Assets/Shaders/");
		const std::string MESHDIR("../../Assets/Meshes/");
		const std::string TEXTUREDIR("../../Assets/Textures/");
		const std::string SOUNDSDIR("../../Assets/Sounds/");
		const std::string FONTSSDIR("../../Assets/Fonts/");
		const std::string DATADIR("../../Assets/Data/");
		extern bool ReadTextFile(const std::string &filepath, std::string& result);
		//static inline bool ReadBinaryFile(const std::string &filepath, std::string& result);
	}
}