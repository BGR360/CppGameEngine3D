#ifndef BENGINE_MESH_H
#define BENGINE_MESH_H

#include <Engine.h>

#include <vector>

#include <math/Vector2.h>
#include <math/Vector3.h>
#include <util/Types.h>

using std::vector;
using Math::Vector2;
using Math::Vector3;

namespace Rendering
{
	class Mesh
	{
	public:
		enum VertexAttribute
		{
			POSITION_ATTRIBUTE,
			UV_COORD_ATTRIBUTE,
			NORMAL_ATTRIBUTE,

			NUM_VERTEX_ATTRIBUTES
		};

	private:
		vector<Vector3> m_positions;
		vector<Vector3> m_normals;
		vector<Vector2> m_uvCoords;
		vector<uint> m_indices;

	public:
		Mesh() : m_positions(), m_normals(), m_uvCoords(), m_indices() {}
		virtual ~Mesh() {}

		inline vector<Vector3>& getPositions() { return m_positions; }
		inline vector<Vector3>& getNormals() { return m_normals; }
		inline vector<Vector2>& getUvCoords() { return m_uvCoords; }
		inline vector<uint>& getIndices() { return m_indices; }

		inline void freeData()
		{
			m_positions.clear();
			m_normals.clear();
			m_uvCoords.clear();
			m_indices.clear();
		}
	};
}

#endif //BENGINE_MESH_H