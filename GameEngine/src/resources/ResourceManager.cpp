#include "ResourceManager.h"

#include <exceptions/BengineException.h>
#include <resources/ObjFile.h>
#include <util/filesys/FileSystem.h>
#include <util/StringFunctions.h>

//Must actually include the files for the stuff we need to work with (no more forward declaration)
#include <rendering/Material.h>
#include <rendering/OpenGLMesh.h>
#include <rendering/ShaderProgram.h>
#include <rendering/Texture.h>
#include <resources/Image.h>

using Exceptions::BengineException;
using Rendering::OpenGLMesh;
using namespace Util;

namespace Resources
{
	ResourceManager::ResourceManager() : averageLinesPerByte(0.0f) {}

	OpenGLMesh* ResourceManager::loadMesh(const string& filePath, const string& meshName)
	{
		return loadMeshFromObj(filePath, meshName);
	}

	OpenGLMesh* ResourceManager::getMesh(const string& meshName)
	{
		map<string, OpenGLMesh*>::iterator it = m_meshes.find(meshName);
		if (it != m_meshes.end())
		{
			return it->second;
		}
		else
		{
			string message("No such Mesh of name '");
			message += meshName;
			message += "' exists.";
			throw BengineException(message);
		}
		return 0;
	}

	OpenGLMesh* ResourceManager::loadMeshFromObj(const string& filePath, const string& meshName)
	{
		//Get the proper filePath
		FileSystem& filesys = FileSystem::getInstance();
		string newPath = filesys.path(filePath);

		//This will open the .obj file
		ObjFile objFile;
		objFile.open(newPath);

		//If there are no tangents... ?

		//Calculate normals if necessary

		//Get the name for the mesh.
		string finalMeshName;
		if (meshName.compare("") == 0)
		{
			//Derive the name of the new mesh from the filePath
			//e.g. ./res/meshes/testCube.obj yields a meshName of 'testCube'
			string fileName = getFileNameFromPath(filePath);
			finalMeshName = removeExtensionFromFileName(fileName);
		}
		else
		{
			//Use the meshName supplied
			finalMeshName = meshName;
		}

		OpenGLMesh* mesh = new OpenGLMesh;

		//This is the first thing we want to do; if we encounter an exception, we want to make sure
		//the ResourceManager can destroy this Mesh and avoid leaked memory
		m_meshes[finalMeshName] = mesh;

		//Populate the Mesh with data from the ObjFile

		vector<Vector3>& positions = objFile.get_v_list();
		vector<Vector2>& texCoords = objFile.get_vt_list();
		vector<Vector3>& normals = objFile.get_vn_list();
		vector<ObjVertex>& vertices = objFile.getVertices();
		vector<uint>& indices = objFile.getIndices();

		//For each unique ObjVertex
		vector<ObjVertex>::iterator uniqueVert;
		for (uniqueVert = vertices.begin(); uniqueVert != vertices.end(); uniqueVert++)
		{
			Vector3 position = positions[uniqueVert->v_index - 1];
			Vector2 texCoord;
			Vector3 normal;

			if (objFile.hasTextureCoordinates())
			{
				if (uniqueVert->vt_index != -1)
				{
					texCoord = texCoords[uniqueVert->vt_index - 1];
				}
				else
				{
					texCoord = Vector2();
				}
			}

			//TODO: change this when we are able to calculate normals
			if (objFile.hasNormals())
			{
				if (uniqueVert->vn_index != -1)
				{
					normal = normals[uniqueVert->vn_index - 1];
				}
				else
				{
					normal = Vector3();
				}
			}

			mesh->getPositions().push_back(position);
			mesh->getUvCoords().push_back(texCoord);
			mesh->getNormals().push_back(normal);
		}

		mesh->getIndices() = indices;

		averageLinesPerByte += objFile.getLinesPerByte();
		objFile.close();

		mesh->createOpenGLData();

		return mesh;
	}

	template<typename T>
	uint ResourceManager::indexOf(const vector<T>& theVector, const T& theTarget)
	{
		for (uint i = 0; i < theVector.size(); i++)
		{
			if (theVector[i] == theTarget)
			{
				return (int)i;
			}
		}
		return -1;
	}

	void ResourceManager::calcNormalsForMesh(Mesh* mesh)
	{
		//To be implemented at a future date
	}



	ShaderProgram* ResourceManager::loadShader(const string& filePath, const string& shaderName)
	{
		//If it has a file extension, get rid of it
		string finalFilePath;
		string fileName = getFileNameFromPath(filePath);
		vector<string> nameElements;
		splitString(fileName, '.', nameElements);
		if (nameElements.size() >= 2)
		{
			finalFilePath = removeExtensionFromFileName(filePath);
		}
		else
		{
			finalFilePath = filePath;
		}

		string finalShaderName;
		if (shaderName.compare("") == 0)
		{
			finalShaderName = removeExtensionFromFileName(fileName);
		}
		else
		{
			finalShaderName = shaderName;
		}

		//Get the correct filepath
		FileSystem& filesys = FileSystem::getInstance();
		finalFilePath = filesys.path(finalFilePath);

		//Load the shader
		ShaderProgram* shader = 0;

		//If the constructor of ShaderProgram throws an exception, we need to make sure
		//we delete the new ShaderProgram.
		//After that, we can pass the exception upward to the next exception handler
		try
		{
			shader = new ShaderProgram(finalFilePath);
		}
		catch (...)
		{
			delete shader;
			throw;
		}

		//Now, if we encounter any further exceptions, we want to make sure that the ResourceManager
		//can delete the new ShaderProgram. So the first thing we want to do is add this new
		//ShaderProgram to our list of ShaderPrograms.
		m_shaders[finalShaderName] = shader;

		return shader;
	}

	ShaderProgram* ResourceManager::getShader(const string& shaderName)
	{
		map<string, ShaderProgram*>::iterator it = m_shaders.find(shaderName);
		if (it != m_shaders.end())
		{
			return it->second;
		}
		else
		{
			string message("No such ShaderProgram of name '");
			message += shaderName;
			message += "' exists.";
			throw BengineException(message);
		}
		return 0;
	}



	Image* ResourceManager::loadImage(const string& filePath, const string& imageName)
	{
		Image* loadedImage = 0;
		Image* convertedImage = 0;

		string finalImageName;
		if (imageName.compare("") == 0)
		{
			//Derive the image's name from its filePath (WITHOUT removing the file extension)
			finalImageName = getFileNameFromPath(filePath);
		}
		else
		{
			//Just use the imageName supplied
			finalImageName = imageName;
		}

		//Get the file extension
		string imageType = getFileExtension(getFileNameFromPath(filePath));

		//Get the correct filePath
		FileSystem& filesys = FileSystem::getInstance();
		string newPath = filesys.path(filePath);

		//Make sure we can deallocate memory if construction throws
		try
		{
			loadedImage = new Image;

			if (!(loadedImage->load(newPath.c_str(), imageType.c_str())))
			{
				throw FileNotFoundException(newPath);
			}

			
			//Convert it to one of the formats OpenGL accepts

			QImage::Format newFormat;

			if (loadedImage->hasAlphaChannel())
			{
				//Specify an RGBA8888 format
				newFormat = QImage::Format_RGBA8888;
			}
			else
			{
				//Specify an RGB888 format
				newFormat = QImage::Format_RGB888;
			}

			convertedImage = new Image(loadedImage->convertToFormat(newFormat));

			delete loadedImage;
		}
		catch (...)
		{
			delete loadedImage;
			delete convertedImage;
			throw;
		}

		//Add the Image to our list of Images
		m_images[finalImageName] = convertedImage;

		return convertedImage;
	}

	Image* ResourceManager::getImage(const string& imageName)
	{
		map<string, Image*>::iterator it = m_images.find(imageName);
		if (it != m_images.end())
		{
			return it->second;
		}
		else
		{
			string message("No such Image of name '");
			message += imageName;
			message += "' exists.";
			throw BengineException(message);
		}
		return 0;
	}



	Texture* ResourceManager::loadTexture(const string& filePath, const string& textureName, uint textureUnit)
	{
		Texture* ret = 0;

		//Load the image
		this->loadImage(filePath);

		//Derive the image's name from its filePath (WITHOUT removing the file extension)
		string imageName = getFileNameFromPath(filePath);

		//Get the texture's name
		string finalTextureName;
		if (textureName.compare("") == 0)
		{
			finalTextureName = imageName;
		}
		else
		{
			finalTextureName = textureName;
		}

		//Create the texture
		this->createTexture(imageName, textureName, textureUnit);

		//Free the image
		this->freeImage(imageName);

		return ret;
	}

	Texture* ResourceManager::createTexture(const string& imageName, const string& textureName, uint textureUnit)
	{
		Texture* texture = 0;

		try
		{
			texture = new Texture(this->getImage(imageName), textureUnit);
		}
		catch (...)
		{
			delete texture;
			throw;
		}

		m_textures[textureName] = texture;

		return texture;
	}

	Texture* ResourceManager::getTexture(const string& textureName)
	{
		map<string, Texture*>::iterator it = m_textures.find(textureName);
		if (it != m_textures.end())
		{
			return it->second;
		}
		else
		{
			string message("No such Texture of name '");
			message += textureName;
			message += "' exists.";
			throw BengineException(message);
		}
		return 0;
	}



	Material* ResourceManager::createMaterial(const string& materialName, ShaderProgram* shader, Texture* texture)
	{
		Material* material = 0;

		try
		{
			material = new Material(shader, texture);
			m_materials[materialName] = material;
		}
		catch (...)
		{
			if (material != 0)
			{
				delete material;
			}
		}

		return material;
	}

	Material* ResourceManager::getMaterial(const string& materialName)
	{
		map<string, Material*>::iterator it = m_materials.find(materialName);
		if (it != m_materials.end())
		{
			return it->second;
		}
		else
		{
			string message("No such Material of name '");
			message += materialName;
			message += "' exists.";
			throw BengineException(message);
		}
		return 0;
	}



	void ResourceManager::freeAllResources()
	{
		this->freeAllMeshes();
		this->freeAllShaders();
		this->freeAllTextures();
		this->freeAllImages();
	}

	void ResourceManager::freeAllMeshes()
	{
		map<string, OpenGLMesh*>::iterator i;
		for (i = m_meshes.begin(); i != m_meshes.end(); i++)
		{
			delete i->second;
		}
		m_meshes.clear();
	}
	void ResourceManager::freeAllShaders()
	{
		map<string, ShaderProgram*>::iterator i;
		for (i = m_shaders.begin(); i != m_shaders.end(); i++)
		{
			delete i->second;
		}
		m_shaders.clear();
	}
	void ResourceManager::freeImage(const string& imageName)
	{
		delete m_images[imageName];
		map<string, Image*>::iterator i = m_images.find(imageName);
		m_images.erase(i);
	}
	void ResourceManager::freeAllImages()
	{
		map<string, Image*>::iterator i;
		for (i = m_images.begin(); i != m_images.end(); i++)
		{
			delete i->second;
		}
		m_images.clear();
	}
	void ResourceManager::freeAllTextures()
	{
		map<string, Texture*>::iterator i;
		for (i = m_textures.begin(); i != m_textures.end(); i++)
		{
			delete i->second;
		}
		m_textures.clear();
	}
	void ResourceManager::freeAllMaterials()
	{
		map<string, Material*>::iterator i;
		for (i = m_materials.begin(); i != m_materials.end(); i++)
		{
			delete i->second;
		}
		m_materials.clear();
	}

	float ResourceManager::getAverageLinesPerByte() const
	{
		return averageLinesPerByte / m_meshes.size();
	}

	ResourceManager::~ResourceManager() 
	{
		this->freeAllResources();
	}
}