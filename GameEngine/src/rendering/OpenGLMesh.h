#ifndef BENGINE_OPENGL_MESH_H
#define BENGINE_OPENGL_MESH_H

#include <Engine.h>

#include <rendering/Mesh.h>
#include <util/Types.h>

namespace Rendering
{
	class OpenGLMesh : public Mesh
	{
		//The OpenGLMesh is responsible for converting its data into OpenGL buffer objects
		uint m_vaoID;									//Vertex Array Object
		uint m_vboIDs[Mesh::NUM_VERTEX_ATTRIBUTES];		//Vertex Buffer Object (One per vertex attribute)
		uint m_iboID;									//Index Buffer Object

	public:
		OpenGLMesh();
		virtual ~OpenGLMesh();

		inline uint getVAO() const				{ return m_vaoID; }
		inline uint getVBO(uint index) const	{ return m_vboIDs[index]; }
		inline const uint* getVBOs() const		{ return m_vboIDs; }
		inline uint getIBO() const				{ return m_iboID; }

		void createOpenGLData();
	};
}

#endif //BENGINE_OPENGL_MESH_H