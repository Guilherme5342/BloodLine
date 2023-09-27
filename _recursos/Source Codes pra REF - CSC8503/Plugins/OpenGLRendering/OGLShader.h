#pragma once
#include "../../Common/ShaderBase.h"
#include "glad\glad.h"

namespace NCL {
	namespace Rendering {
		class OGLShader : public ShaderBase
		{
		public:
			friend class OGLRenderer;
			OGLShader(const string& vertex, const string& fragment, const string& geometry = "", const string& domain = "", const string& hull = "");
			~OGLShader();

			void ReloadShader() override;

			bool LoadSuccess() const {
				return programValid == GL_TRUE;
			}

			int GetProgramID() const {
				return programID;
			}

		protected:
			void	DeleteIDs();
			void	PrintCompileLog(int object) const;
			void	PrintLinkLog() const;

			GLuint	programID;
			GLuint	shaderIDs[ShaderStages::SHADER_MAX];
			int		shaderValid[ShaderStages::SHADER_MAX];
			int		programValid;
		};
	}
}