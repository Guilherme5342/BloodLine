#pragma once
#include <string>

namespace NCL {
	class TextureWriter
	{
	public:
		static void WritePNG(const std::string& filename, char* data, int width, int height, int channels);
	};
}

