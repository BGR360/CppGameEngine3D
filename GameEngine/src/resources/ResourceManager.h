#ifndef BENGINE_RESOURCE_MANAGER_H
#define BENGINE_RESOURCE_MANAGER_H

#include <Engine.h>

#include <map>
#include <string>
#include <vector>

#include <util/Types.h>

using std::map;
using std::string;
using std::vector;

//Forward Declaration of all the types that the ResourceManager can load
//Because we only need to store pointers in the header

namespace Rendering
{
	class Material;
	class Mesh;
	class OpenGLMesh;
	class ShaderProgram;
	class Texture;
}

using Rendering::Material;
using Rendering::Mesh;
using Rendering::OpenGLMesh;
using Rendering::ShaderProgram;
using Rendering::Texture;

namespace Resources
{
	class Image;

	class ENGINE_DLL_EXPORT_IMPORT ResourceManager
	{
		map<string, OpenGLMesh*> m_meshes;
		map<string, ShaderProgram*> m_shaders;
		map<string, Image*> m_images;
		map<string, Texture*> m_textures;
		map<string, Material*> m_materials;

		float averageLinesPerByte;

	public:
		ResourceManager();
		virtual ~ResourceManager();

		OpenGLMesh* loadMesh(const string& filePath, const string& meshName = "");
		OpenGLMesh* getMesh(const string& meshName);

		ShaderProgram* loadShader(const string& filePath, const string& shaderName = "");
		ShaderProgram* getShader(const string& shaderName);

		Image* loadImage(const string& filePath, const string& imageName = "");
		Image* getImage(const string& imageName);

		Texture* loadTexture(const string& filePath, const string& textureName = "", uint textureUnit = 0);
		Texture* createTexture(const string& imageName, const string& textureName = "", uint textureUnit = 0);
		Texture* getTexture(const string& textureName);

		Material* createMaterial(const string& materialName, ShaderProgram* shader, Texture* texture);
		Material* getMaterial(const string& materialName);

		float getAverageLinesPerByte() const;

		void freeAllResources();

	private:
		OpenGLMesh* loadMeshFromObj(const string& filePath, const string& meshName = "");
		
		template<typename T> uint indexOf(const vector<T>& theVector, const T& theTarget);
		void calcNormalsForMesh(Mesh* mesh); //TODO: Implement normal calculation

		void freeAllMeshes();
		void freeAllShaders();
		void freeImage(const string& imageName);
		void freeAllImages();
		void freeAllTextures();
		void freeAllMaterials();
	};
}

#endif //BENGINE_RESOURCE_MANAGER_H