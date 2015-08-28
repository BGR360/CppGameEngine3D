#include "ObjFile.h"

#include <cctype> //isspace()
#include <iostream>
#include <map>
#include <sstream>

#include <exceptions/FileException.h>
#include <exceptions/FileNotFoundException.h>
#include <exceptions/InvalidOperationException.h>
#include <util/Types.h>
#include <util/StringFunctions.h>

using std::cout;
using std::endl;
using std::getline;
using std::ios;
using std::isspace;
using std::map;
using std::noskipws;
using std::skipws;

using Exceptions::BengineException;
using Exceptions::FileException;
using Exceptions::FileNotFoundException;
using Exceptions::InvalidOperationException;
using Util::splitString;
using Util::stringToFloat;
using Util::stringToInt;

namespace Resources
{
	const int REPORT_LINE_AT = 1000;
	const uint ObjVertex::MAX_NUM_HASH_BUCKETS = 15485863;
	const int ObjVertex::INITIAL_BIT_SHIFT = 5;

	ObjFile::ObjFile()
		: m_filePath(""),
		m_lineNumber(-1),
		m_bIsOpen(false),
		m_bHasVt(false),
		m_bHasVn(false),
		m_v_list(),
		m_vt_list(),
		m_vn_list(),
		m_objVertices(),
		m_indices()
	{}

	ObjFile::ObjFile(string filePath)
		: m_filePath(filePath),
		m_lineNumber(-1),
		m_bIsOpen(false),
		m_bHasVt(false),
		m_bHasVn(false),
		m_v_list(),
		m_vt_list(),
		m_vn_list(),
		m_objVertices(),
		m_indices()
	{}

	//This just calls open(string)
	void ObjFile::open()
	{
		//Make sure we have a filePath to open
		if (m_filePath.compare("") == 0)
		{
			throw InvalidOperationException("open", "ObjFile", "It has no file path.");
		}

		this->open(m_filePath);
	}

	//This is what does the actual opening of the file
	void ObjFile::open(const string& filePath)
	{
		//Make sure file is not already open
		if (m_bIsOpen)
		{
			throw InvalidOperationException("open", "ObjFile", "It is already open.");
		}

		m_filePath = filePath;

		ifstream fileStream;
		fileStream.open(filePath.c_str());

		//Check for FileNotFound
		if (fileStream.fail())
		{
			throw FileNotFoundException(filePath);
		}

		//Check for other generic failure
		if (!fileStream.good())
		{
			throw FileException(filePath);
		}

		//Get length of file:
		fileStream.seekg(0, fileStream.end);
		m_fileSize = fileStream.tellg();
		fileStream.seekg(0, fileStream.beg);

		//Load the .obj file!!
		this->loadObj1(fileStream);

		fileStream.close();
		m_bIsOpen = true;
	}

	void ObjFile::close()
	{
		if (!m_bIsOpen)
		{
			throw InvalidOperationException("close", "ObjFile", "It is not open.");
		}

		m_v_list.clear();
		m_vt_list.clear();
		m_vn_list.clear();
		m_objVertices.clear();
		m_indices.clear();

		m_bIsOpen = false;
	}

	//And this is where the REAL magic happens
	void ObjFile::loadObj(istream& stream)
	{
		while (stream.good())
		{
			//Read each line of the file
			string line = "";
			while (getline(stream, line))
			{
				m_lineNumber++;

				if (m_lineNumber % REPORT_LINE_AT == 0 && m_lineNumber != 0)
				{
					cout << m_lineNumber << " lines processed." << endl;
				}

				//If we got an empty line, get the next non-empty one
				//Or if it's a comment line, keep fetching
				while (line.compare("") == 0 || line.at(0) == '#')
				{
					getline(stream, line);
					m_lineNumber++;
				}

				//Split the line using space as a delimiter
				vector<string> lineElements;
				splitString(line, ' ', lineElements);

				//Now lineElements should have some strings in it
				if (lineElements.size() == 0)
					throw FileException(m_filePath);

				//Now figure out what to do with this line
				string firstElement = lineElements[0];

				if (firstElement.compare("v") == 0)
				{
					//vertex coordinate
					//lineElements = {"v", "1.0", "1.0", "1.0"}

					if (lineElements.size() < 4)
						throw BengineException("Could not create vertex position from .obj file. Not enough data in the line.");

					float x = stringToFloat(lineElements[1]);
					float y = stringToFloat(lineElements[2]);
					float z = stringToFloat(lineElements[3]);

					m_v_list.push_back(Vector3(x, y, z));
				}
				else if (firstElement.compare("vt") == 0)
				{
					//texture coordinate
					//lineElements = {"vt", "1.0", "1.0"}

					if (lineElements.size() < 3)
						throw BengineException("Could not create texture coordinate from .obj file. Not enough data in the line.");

					float x = stringToFloat(lineElements[1]);
					float y = stringToFloat(lineElements[2]);

					m_vt_list.push_back(Vector2(x, y));
				}
				else if (firstElement.compare("vn") == 0)
				{
					//vertex normal
					//lineElements = {"vn", "1.0", "1.0", "1.0"}

					if (lineElements.size() < 4)
						throw BengineException("Could not create vertex normal from .obj file. Not enough data in the line.");

					float x = stringToFloat(lineElements[1]);
					float y = stringToFloat(lineElements[2]);
					float z = stringToFloat(lineElements[3]);

					m_vn_list.push_back(Vector3(x, y, z));
				}
				else if (firstElement.compare("f") == 0)
				{
					//face definition
					//lineElements = {"f", "1/2/3", "4/5/6", "7/8/9"}

					if (lineElements.size() < 4)
						throw BengineException("Could not create face from .obj file. There are less than 3 index groups specified in the line.");

					if (lineElements.size() == 5)
					{
						//It's a quad face. Split it into two triangle faces
						m_objVertices.push_back(this->createObjVertex(lineElements[1]));
						m_objVertices.push_back(this->createObjVertex(lineElements[2]));
						m_objVertices.push_back(this->createObjVertex(lineElements[3]));
						m_objVertices.push_back(this->createObjVertex(lineElements[1]));
						m_objVertices.push_back(this->createObjVertex(lineElements[3]));
						m_objVertices.push_back(this->createObjVertex(lineElements[4]));
					}
					else
					{
						//It's a triangle face. Make an ObjFace out of it
						m_objVertices.push_back(this->createObjVertex(lineElements[1]));
						m_objVertices.push_back(this->createObjVertex(lineElements[2]));
						m_objVertices.push_back(this->createObjVertex(lineElements[3]));
					}
				}
			}
		}
	}

	//The strings expected for this function are a v/vt/vn pair (e.g. "1/2/3")
	ObjFace ObjFile::createObjFace(const string& vert1, const string& vert2, const string& vert3)
	{
		vector<string> vertex1, vertex2, vertex3;
		splitString(vert1, '/', vertex1);
		splitString(vert2, '/', vertex2);
		splitString(vert3, '/', vertex3);

		ObjFace objFace;

		objFace.vertices[0] = this->createObjVertex(vert1);
		objFace.vertices[1] = this->createObjVertex(vert2);
		objFace.vertices[2] = this->createObjVertex(vert3);

		return objFace;
	}

	//The vert string will look like this: "1/2/3"
	ObjVertex ObjFile::createObjVertex(const string& vert)
	{
		ObjVertex objVert;

		vector<string> vertexElements;
		splitString(vert, '/', vertexElements);

		uint numElements = vertexElements.size();

		if (numElements > 0 && vertexElements[0].length() > 0)
		{
			objVert.v_index = (uint)stringToInt(vertexElements[0]);
		}
		else
		{
			throw BengineException("Could not create ObjVertex from .obj file. There is no data from which to create one.");
		}

		if (numElements > 1 && vertexElements[1].length() > 0)
		{
			//If we haven't already discovered that we have vt's, discover so
			if (!m_bHasVt)
			{
				m_bHasVt = true;
			}
			objVert.vt_index = (uint)stringToInt(vertexElements[1]);
		}
		else
		{
			//No vt for this vertex
			objVert.vt_index = -1;
		}

		if (numElements > 2 && vertexElements[2].length() > 0)
		{
			//If we haven't already discovered that we have vn's, discover so
			if (!m_bHasVn)
			{
				m_bHasVn = true;
			}
			objVert.vn_index = (uint)stringToInt(vertexElements[2]);
		}
		else
		{
			//No vn for this vertex
			objVert.vn_index = -1;
		}

		return objVert;
	}

	//A new loading algorithm
	void ObjFile::loadObj1(istream& stream)
	{
		m_lineNumber = 0;

		map<uint, uint> hashToIndex;

		char c;
		while (stream.good())
		{
			if (++m_lineNumber % REPORT_LINE_AT == 0)
			{
				cout << ".";
			}

			//Check the first character of the line
			stream >> c;

			if (c == '#')
			{
				//Comment line. Discard the whole line
				getline(stream, string());
			}
			else if (c == 'v')
			{
				char next = stream.peek();
				if (next == ' ')
				{
					//Vertex definition ("v")
					Vector3 position;
					readVector3(position, stream);
					m_v_list.push_back(position);
				}
				else
				{
					stream >> c;
					if (c == 't')
					{
						//Texture Coordinate definition ("vt")
						//Make sure we read a space after "vt"
						if (stream.peek() != ' ')
						{
							//**BAD FILE**: No space after "vt"
						}
						else
						{
							Vector2 texCoord;
							readVector2(texCoord, stream);
							m_vt_list.push_back(texCoord);
						}

						if (!m_bHasVt) m_bHasVt = true;
					}
					else if (c == 'n')
					{
						//Vertex Normal definition ("vn")				
						//Make sure we read a space after "vn"
						if (stream.peek() != ' ')
						{
							//**BAD FILE**: No space after "vn"
						}
						else
						{
							Vector3 normal;
							readVector3(normal, stream);
							m_vn_list.push_back(normal);
						}

						if (!m_bHasVn) m_bHasVn = true;
					}
				}
			}
			else if (c == 'f')
			{
				//Make sure we read a space after "f"
				if (stream.peek() != ' ')
				{
					//**BAD FILE**: No space after "f"
				}

				string line;
				getline(stream, line);
				stringstream ss(line);

				vector<uint> vertsInThisFace;
				while (ss)
				{
					if (ss.eof())
						break;

					ObjVertex vert;
					readObjVertex(vert, ss);
					
					uint hash = vert.hash();
					map<uint, uint>::iterator found = hashToIndex.find(hash);
					if (found == hashToIndex.end())
					{
						//Vert does not already exist
						uint index = m_objVertices.size();
						hashToIndex[hash] = index;
						m_objVertices.push_back(vert);
						vertsInThisFace.push_back(index);
					}
					else
					{
						//Vert already exists
						uint index = found->second;
						vertsInThisFace.push_back(index);
					}
				}

				if (vertsInThisFace.size() < 3)
				{
					//**BAD FILE**: Not enough information to create a face
				}
				else
				{
					//Construct triangles out of the vertices in this face
					for (uint i = 2; i < vertsInThisFace.size(); i++)
					{
						m_indices.push_back(vertsInThisFace[0]);
						m_indices.push_back(vertsInThisFace[i - 1]);
						m_indices.push_back(vertsInThisFace[i]);
					}
				}
			}
			else
			{
				//Unknown symbol. Discard the whole line
				getline(stream, string());
			}
		}

		cout << endl << "Done (";
		if ((m_fileSize / 1024) < 1)
		{
			cout << m_fileSize << " bytes, ";
		}
		else
		{
			cout << m_fileSize / 1024 << " kbytes, ";
		}
		cout << m_lineNumber << " lines processed)." << endl;
	}

	void ObjFile::readVector2(Vector2& vec, istream& stream)
	{
		for (uint i = 0; i < 2; i++)
		{
			//Read the float
			float component;
			stream >> component;
			vec[i] = component;

			while (!isspace(stream.peek()))
			{
				stream.ignore(1);
			}
		}
	}

	void ObjFile::readVector3(Vector3& vec, istream& stream)
	{
		for (uint i = 0; i < 3; i++)
		{
			//Read the float
			float component;
			stream >> component;
			vec[i] = component;

			while (!isspace(stream.peek()))
			{
				stream.ignore(1);
			}
		}
		char next = stream.peek();
	}

	void ObjFile::readFace(istream& stream)
	{
		ObjVertex vert;
		readObjVertex(vert, stream);
	}

	void ObjFile::readObjVertex(ObjVertex& vert, istream& stream)
	{
		char c;
		readIntBeforeSlash(vert.v_index, stream);
		c = stream.peek();
		if (c != '/')
		{
			if (c == ' ')
			{
				//Vertex ended early; no vt or vn specified
				vert.vt_index = -1;
				vert.vn_index = -1;
			}
			else
			{
				//**BAD FILE**: unrecognized character
			}
		}
		else
		{
			stream >> c;
			readIntBeforeSlash(vert.vt_index, stream);
			c = stream.peek();
			if (c != '/')
			{
				if (c == ' ')
				{
					//Vertex ended early; no vn specified
					vert.vn_index = -1;
				}
				else
				{
					//**BAD FILE**: unrecognized character
				}
			}
			else
			{
				stream >> c;
				readIntBeforeSlash(vert.vn_index, stream);
				c = stream.peek();
				if (c != ' ')
				{
					//**BAD FILE**: unrecognized character after vertex tuple
				}
			}
		}
	}

	void ObjFile::readIntBeforeSlash(uint& theInt, istream& stream)
	{
		stringstream ss(stringstream::in | stringstream::out);
		char c;
		char next;
		while (stream && ss)
		{
			next = stream.peek();
			if (next != '/')
			{
				stream >> c;
				ss << c;
				next = stream.peek();
			} else break;
			if (isspace(next)) break;
			if (next == EOF)
			{
				if (stream.eof())
				{
					break;
				}
			}
		}

		//If we read something, return the value, else return -1;
		string str = ss.str();
		size_t size = str.length();
		if (size != 0)
		{
			ss >> theInt;
		}
		else
		{
			theInt = -1;
		}
	}

	ObjFile::~ObjFile()
	{
		if (m_bIsOpen)
		{
			this->close();
		}
	}
}