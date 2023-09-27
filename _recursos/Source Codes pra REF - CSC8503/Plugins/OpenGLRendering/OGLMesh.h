#pragma once
#include "../../Common/MeshGeometry.h"
#include "glad\glad.h"

#include <string>

namespace NCL {
	namespace Rendering {
		class OGLMesh : public NCL::MeshGeometry
		{
		public:
			enum MeshBuffer {
				VERTEX_BUFFER,
				COLOUR_BUFFER,
				TEXTURE_BUFFER,
				NORMAL_BUFFER,
				TANGENT_BUFFER,
				INDEX_BUFFER,
				SKELINDEX_BUFFER,
				SKELWEIGHT_BUFFER,
				MAX_BUFFER
			};

			friend class OGLRenderer;
			OGLMesh();
			OGLMesh(const std::string&filename);
			~OGLMesh();

			void RecalculateNormals();

			void UploadToGPU() override;

		protected:
			GLuint	GetVAO()			const { return vao;			}
			int		GetSubMeshCount()	const { return subCount;	}

			void BindVertexAttribute(int attribSlot, int bufferID, int bindingID, int elementCount, int elementSize, int elementOffset);

			//void BufferData();

			int		subCount;

			GLuint vao;
			GLuint oglType;
			GLuint buffers[MAX_BUFFER];
		};
	}
}