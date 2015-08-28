#ifndef BENGINE_OBJ_FILE_H
#define BENGINE_OBJ_FILE_H

#include <Engine.h>

#include <fstream>
#include <string>
#include <vector>

#include <math/Vector2.h>
#include <math/Vector3.h>
#include <util/Types.h>

using std::istream;
using std::ifstream;
using std::string;
using std::vector;

using Math::Vector2;
using Math::Vector3;


//ObjFile is an Engine-Internal class. It will not be exposed to the dll-interface

namespace Resources
{
	//If there is no vt and/or no vn, they will be given values of -1
	struct ObjVertex
	{
		uint v_index;
		uint vt_index;
		uint vn_index;

		static const uint MAX_NUM_HASH_BUCKETS;
		static const int INITIAL_BIT_SHIFT;

		inline uint hash();
	};

	struct ObjFace
	{
		ObjVertex vertices[3];
	};

	inline bool operator==(const ObjVertex& left, const ObjVertex& right)
	{
		return left.v_index == right.v_index 
			&& left.vn_index == right.vn_index 
			&& left.vt_index == right.vt_index;
	}
	inline bool operator==(const ObjFace& left, const ObjFace& right)
	{
		return left.vertices[0] == right.vertices[0]
			&& left.vertices[1] == right.vertices[1]
			&& left.vertices[2] == right.vertices[2];
	}

	class ENGINE_DLL_TESTING_ONLY ObjFile
	{
		string m_filePath;
		uint m_lineNumber;
		uint m_fileSize;
		bool m_bIsOpen;
		bool m_bHasVt;
		bool m_bHasVn;

		vector<Vector3> m_v_list;
		vector<Vector2> m_vt_list;
		vector<Vector3> m_vn_list;

		vector<ObjVertex> m_objVertices;	//A list of UNIQUE ObjVertexes
		vector<uint> m_indices;

	public:
		ObjFile();
		ObjFile(string filePath);
		virtual ~ObjFile();

		void open();
		void open(const string& filePath);
		void close();

		inline bool isOpen() const;
		inline bool hasTextureCoordinates() const;
		inline bool hasNormals() const;

		inline uint getNumLines() const;
		inline uint getFileSize() const;
		inline float getLinesPerByte() const;

		inline vector<Vector3>& get_v_list();
		inline vector<Vector2>& get_vt_list();
		inline vector<Vector3>& get_vn_list();

		inline vector<ObjVertex>& getVertices();
		inline vector<uint>& getIndices();

	private:
		void loadObj(istream& stream);
		void readVector2(Vector2& vec, istream& stream);
		void readVector3(Vector3& vec, istream& stream);
		void readFace(istream& stream);
		void readObjVertex(ObjVertex& vert, istream& stream);
		void readIntBeforeSlash(uint& theInt, istream& stream);
		ObjFace createObjFace(const string& vert1, const string& vert2, const string& vert3);
		ObjVertex createObjVertex(const string& vert);

		void loadObj1(istream& stream);
	};

	#include "ObjFile.inl"
}

#endif //BENGINE_OBJ_FILE_H