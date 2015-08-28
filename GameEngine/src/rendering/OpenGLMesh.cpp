#include "OpenGLMesh.h"

#include <rendering/OpenGL.h>

namespace Rendering
{
	OpenGLMesh::OpenGLMesh() : m_vaoID(-1), m_iboID(-1)
	{
		for (uint i = 0; i < (uint)Mesh::NUM_VERTEX_ATTRIBUTES; i++)
		{
			m_vboIDs[i] = -1;
		}
	}

	void OpenGLMesh::createOpenGLData()
	{
		//Generate gl buffers
		glCheckCall(glGenVertexArrays(1, &m_vaoID));
		glCheckCall(glGenBuffers(Mesh::NUM_VERTEX_ATTRIBUTES, &m_vboIDs[0]));
		glCheckCall(glGenBuffers(1, &m_iboID));

		//Bind Vertex Array
		glCheckCall(glBindVertexArray(m_vaoID));

		//Bind Vertex Attribute Indices
		//glBindAttribLocation(programID, Mesh::POSITION_ATTRIBUTE, "position");
		//glBindAttribLocation(programID, Mesh::UV_COORD_ATTRIBUTE, "uvCoord");
		//glBindAttribLocation(programID, Mesh::NORMAL_ATTRIBUTE, "normal");

		//Copy position data into POSITION buffer
		glCheckCall(glBindBuffer(GL_ARRAY_BUFFER, m_vboIDs[Mesh::POSITION_ATTRIBUTE]));
		glCheckCall(glBufferData(
			GL_ARRAY_BUFFER,
			this->getPositions().size() * sizeof(this->getPositions()[0]),
			&(this->getPositions()[0]),
			GL_STATIC_DRAW));
		//Enable position attribute
		glCheckCall(glEnableVertexAttribArray(Mesh::POSITION_ATTRIBUTE));
		glCheckCall(glVertexAttribPointer(
			Mesh::POSITION_ATTRIBUTE,
			3, GL_FLOAT,
			GL_FALSE,
			0, 0));

		//Copy uvCoord data into UV_COORD buffer
		glCheckCall(glBindBuffer(GL_ARRAY_BUFFER, m_vboIDs[Mesh::UV_COORD_ATTRIBUTE]));
		glCheckCall(glBufferData(
			GL_ARRAY_BUFFER,
			this->getUvCoords().size() * sizeof(this->getUvCoords()[0]),
			&(this->getUvCoords()[0]),
			GL_STATIC_DRAW));
		//Enable uvCoord attribute
		glCheckCall(glEnableVertexAttribArray(Mesh::UV_COORD_ATTRIBUTE));
		glCheckCall(glVertexAttribPointer(
			Mesh::UV_COORD_ATTRIBUTE,
			2, GL_FLOAT,
			GL_FALSE,
			0, 0));

		//Copy normal data into NORMAL buffer
		glCheckCall(glBindBuffer(GL_ARRAY_BUFFER, m_vboIDs[Mesh::NORMAL_ATTRIBUTE]));
		glCheckCall(glBufferData(
			GL_ARRAY_BUFFER,
			this->getNormals().size() * sizeof(this->getNormals()[0]),
			&(this->getNormals()[0]),
			GL_STATIC_DRAW));
		//Enable normal attribute
		glCheckCall(glEnableVertexAttribArray(Mesh::NORMAL_ATTRIBUTE));
		glCheckCall(glVertexAttribPointer(
			Mesh::NORMAL_ATTRIBUTE,
			3, GL_FLOAT,
			GL_FALSE,
			0, 0));

		//Copy index data to Element Array
		glCheckCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboID));
		glCheckCall(glBufferData(
			GL_ELEMENT_ARRAY_BUFFER,
			this->getIndices().size() * sizeof(this->getIndices()[0]),
			&(this->getIndices()[0]),
			GL_STATIC_DRAW));

		//Unbind Vertex Array
		glCheckCall(glBindVertexArray(0));
	}

	OpenGLMesh::~OpenGLMesh() 
	{
		//Delete vao, vbos, and ibo
		glDeleteVertexArrays(1, &m_vaoID);
		glDeleteBuffers(Mesh::NUM_VERTEX_ATTRIBUTES, &m_vboIDs[0]);
		glDeleteBuffers(1, &m_iboID);
	}
}