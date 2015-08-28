#include "SceneLoader.h"

#include <iostream>

#include <qt/QtCore/qdebug.h>

#include <exceptions/FileException.h>
#include <exceptions/FileNotFoundException.h>
#include <exceptions/InvalidOperationException.h>
#include <rendering/MeshRenderer.h>
#include <util/filesys/FileSystem.h>
#include <util/StringFunctions.h>

using std::cout;
using std::endl;

using Exceptions::FileException;
using Exceptions::FileNotFoundException;
using Exceptions::InvalidOperationException;
using Rendering::MeshRenderer;
using Util::FileSystem;
using Util::qStringToStdString;

namespace Util
{
	void SceneLoader::loadFromXml()
	{
		m_scene = this->generateScene();

		try
		{
			if (m_filePath.compare("") == 0)
			{
				throw InvalidOperationException("loadFromXml", "SceneLoader", "No filePath has been specified.");
			}

			string finalFilePath = FileSystem::getInstance().path(m_filePath);
			QFile xmlFile(finalFilePath.c_str());

			if (!xmlFile.exists())
			{
				throw FileNotFoundException(finalFilePath);
			}

			if (!xmlFile.open(QFile::ReadOnly | QFile::Text))
			{
				throw FileNotFoundException(finalFilePath);
			}
			xml.setDevice(&xmlFile);

			//Compile the list of scenes
			if (xml.readNextStartElement())
			{
				update();
				if (xml.name() == "scene" && xml.attributes().value("version") == "1.0")
				{
					if (xml.readNextStartElement() && xml.name() == "resources")
					{
						this->loadResourcesFromXml();
					}
					else
					{
						xml.raiseError(QObject::tr("The file does not specify a resources category."));
					}

					if (xml.readNextStartElement() && xml.name() == "camera")
					{
						this->loadCameraFromXml();
					}
					else
					{
						xml.raiseError(QObject::tr("The file does not specify a camera."));
					}

					if (xml.readNextStartElement() && xml.name() == "gameObject" && xml.attributes().value("name") == "Root")
					{
						this->createObjectTreeFromXml();
					}
					else
					{
						xml.raiseError(QObject::tr("The file does not specify a root gameObject."));
					}
				}
				else
				{
					xml.raiseError(QObject::tr("The file is not a scene file version 1.0."));
				}
				if (xml.hasError())
				{
					qDebug() << xml.errorString();
					throw FileException(finalFilePath);
				}
			}
		}
		catch (...)
		{
			delete m_scene;
			m_scene = 0;
			throw;
		}
	}

	void SceneLoader::loadFromXml(const string& filePath)
	{
		m_filePath = filePath;
		this->loadFromXml();
	}

	Scene* SceneLoader::getScene()
	{
		return m_scene;
	}

	Scene* SceneLoader::generateScene()
	{
		cout << "Using a Scene!" << endl;
		return new Scene;
	}

	GameObject* SceneLoader::generateGameObject()
	{
		return new GameObject;
	}

	void SceneLoader::loadComponent(GameObject* gameObject, const string& componentType)
	{
		ResourceManager* res = m_scene->getResourceManager();

		update();
		if (componentType.compare("MeshRenderer") == 0)
		{
			MeshRenderer* mr = 0;
			OpenGLMesh* mesh = 0;
			Material* material = 0;

			string meshName;
			string materialName;

			xml.readNextStartElement();
			update();
			if (xml.name() == "mesh")
			{
				qStringToStdString(xml.readElementText(), meshName);
			}
			else
			{
				xml.raiseError("No mesh specified for MeshRenderer.");
			}

			xml.readNextStartElement();
			update();
			if (xml.name() == "material")
			{
				qStringToStdString(xml.readElementText(), materialName);
			}
			else
			{
				xml.raiseError("No material specified for MeshRenderer.");
			}

			mesh = res->getMesh(meshName);
			material = res->getMaterial(materialName);

			mr = new MeshRenderer(mesh, material);
			gameObject->addComponent(mr);
		}
	}

	void SceneLoader::loadResourcesFromXml()
	{
		cout << "Loading Resources..." << endl;

		ResourceManager* res = m_scene->getResourceManager();

		if (xml.isStartElement() && xml.name() == "resources")
		{
			this->loadShaders(res);
			this->loadMeshes(res);
			this->loadImages(res);
			this->loadTextures(res);
			this->loadMaterials(res);
		}

		xml.skipCurrentElement();

		Q_ASSERT(xml.isEndElement());
		Q_ASSERT(xml.name() == "resources");
	}

	void SceneLoader::loadShaders(ResourceManager* res)
	{
		if (xml.readNextStartElement() && xml.name() == "shaders")
		{
			while (!(xml.name() == "shaders" && xml.isEndElement()))
			{
				xml.readNext();
				if (xml.isStartElement())
				{
					if (xml.name() == "shader")
					{
						string path;
						string name;
						qStringToStdString(xml.attributes().value("src"), path);
						qStringToStdString(xml.attributes().value("name"), name);

						cout << "Loading Shader '" << name << "'..." << endl;

						res->loadShader(path, name);
					}
					else
					{
						xml.raiseError(QObject::tr("Unrecognized tag '%1'").arg(xml.name().toString()));
					}
				}
			}
		}
		else
		{
			xml.raiseError(QObject::tr("The file does not specify a shaders category."));
		}
	}

	void SceneLoader::loadMeshes(ResourceManager* res)
	{
		if (xml.readNextStartElement() && xml.name() == "meshes")
		{
			while (!(xml.name() == "meshes" && xml.isEndElement()))
			{
				xml.readNext();
				if (xml.isStartElement())
				{
					if (xml.name() == "mesh")
					{
						string path;
						string name;
						qStringToStdString(xml.attributes().value("src"), path);
						qStringToStdString(xml.attributes().value("name"), name);

						cout << "Loading Mesh '" << name << "'";

						res->loadMesh(path, name);
					}
					else
					{
						xml.raiseError(QObject::tr("Unrecognized tag '%1'").arg(xml.name().toString()));
					}
				}
			}

			cout << "Average lines per byte: " << res->getAverageLinesPerByte() << endl;
		}
		else
		{
			xml.raiseError(QObject::tr("The file does not specify a meshes category."));
		}
	}

	void SceneLoader::loadImages(ResourceManager* res)
	{
		if (xml.readNextStartElement() && xml.name() == "images")
		{
			while (!(xml.name() == "images" && xml.isEndElement()))
			{
				xml.readNext();
				if (xml.isStartElement())
				{
					if (xml.name() == "image")
					{
						string path;
						string name;
						qStringToStdString(xml.attributes().value("src"), path);
						qStringToStdString(xml.attributes().value("name"), name);

						cout << "Loading Image '" << name << "'..." << endl;

						res->loadImage(path, name);
					}
					else
					{
						xml.raiseError(QObject::tr("Unrecognized tag '%1'").arg(xml.name().toString()));
					}
				}
			}
		}
		else
		{
			xml.raiseError(QObject::tr("The file does not specify an images category."));
		}
	}

	void SceneLoader::loadTextures(ResourceManager* res)
	{
		if (xml.readNextStartElement() && xml.name() == "textures")
		{
			while (!(xml.name() == "textures" && xml.isEndElement()))
			{
				xml.readNext();
				if (xml.isStartElement())
				{
					if (xml.name() == "texture")
					{
						string image;
						string name;
						qStringToStdString(xml.attributes().value("image"), image);
						qStringToStdString(xml.attributes().value("name"), name);

						cout << "Creating Texture '" << name << "'..." << endl;

						res->createTexture(image, name);
					}
					else
					{
						xml.raiseError(QObject::tr("Unrecognized tag '%1'").arg(xml.name().toString()));
					}
				}
			}
		}
		else
		{
			xml.raiseError(QObject::tr("The file does not specify an images category."));
		}
	}

	void SceneLoader::loadMaterials(ResourceManager* res)
	{
		if (xml.readNextStartElement() && xml.name() == "materials")
		{
			while (!(xml.name() == "materials" && xml.isEndElement()))
			{
				xml.readNext();
				if (xml.isStartElement())
				{
					if (xml.name() == "material")
					{
						string materialName;
						string shaderName;
						string textureName;
						qStringToStdString(xml.attributes().value("name"), materialName);
						qStringToStdString(xml.attributes().value("shader"), shaderName);
						qStringToStdString(xml.attributes().value("texture"), textureName);

						cout << "Creating Material '" << materialName << "'..." << endl;

						res->createMaterial(
							materialName, 
							res->getShader(shaderName), 
							res->getTexture(textureName));
					}
					else
					{
						xml.raiseError(QObject::tr("Unrecognized tag '%1'").arg(xml.name().toString()));
					}
				}
			}
		}
		else
		{
			xml.raiseError(QObject::tr("The file does not specify a materials category."));
		}
	}

	void SceneLoader::loadCameraFromXml()
	{
		Camera* cam = m_scene->getDefaultCamera();

		if (xml.isStartElement() && xml.name() == "camera")
		{
			while (xml.readNextStartElement())
			{
				update();
				if (xml.name() == "position")
				{
					cam->setPosition(this->loadVector3FromXml());
					update();
				}
				else if (xml.name() == "forward")
				{
					cam->setViewDirection(this->loadVector3FromXml());
				}
				else if (xml.name() == "up")
				{
					update();
					cam->setUp(this->loadVector3FromXml());
					update();
				}
				else if (xml.name() == "fov")
				{
					update();
					cam->setFov(xml.readElementText().toFloat());
					update();
				}
				else if (xml.name() == "aspectRatio")
				{
					update();
					cam->setAspectRatio(xml.readElementText().toFloat());
					update();
				}
				else if (xml.name() == "near")
				{
					update();
					cam->setNear(xml.readElementText().toFloat());
					update();
				}
				else if (xml.name() == "far")
				{
					update();
					cam->setFar(xml.readElementText().toFloat());
					update();
				}
				else
				{
					xml.skipCurrentElement();
				}
			}
		}
	}

	void SceneLoader::createObjectTreeFromXml()
	{
		if (xml.isStartElement() && xml.name() == "gameObject" && xml.attributes().value("name") == "Root")
		{
			cout << "Creating GameObject tree..." << endl;

			//Load the root object
			this->loadGameObjectFromXml(0);
		}
	}

	GameObject* SceneLoader::loadGameObjectFromXml(GameObject* parent)
	{
		GameObject* ret = 0;

		if (xml.isStartElement() && xml.name() == "gameObject")
		{
			if (parent == 0)
			{
				ret = m_scene->getRoot();
			}
			else
			{
				ret = this->generateGameObject();
			}

			try
			{
				this->loadGameObjectAttributes(ret);

				while (! (xml.name() == "gameObject" && xml.isEndElement()))
				{
					xml.readNext();
					update();
					if (xml.isStartElement())
					{
						if (xml.name() == "transform")
						{
							this->loadTransformForObject(ret);
						}
						else if (xml.name() == "components")
						{
							this->loadComponentsForObject(ret);
							update();
							Q_ASSERT(xml.isEndElement());
							Q_ASSERT(xml.name() == "components");
						}
						else if (xml.name() == "children")
						{
							update();
							while (!(xml.name() == "children" && xml.isEndElement()))
							{
								xml.readNext();
								update();
								if (xml.isStartElement())
								{
									if (xml.name() == "gameObject")
									{
										ret->addChild(this->loadGameObjectFromXml(ret));
										update();
										Q_ASSERT(xml.isEndElement());
										Q_ASSERT(xml.name() == "gameObject");
									}
									else
									{
										xml.raiseError(QObject::tr("Unrecognized tag '%1'").arg(xml.name().toString()));
									}
								}
							}

							Q_ASSERT(xml.isEndElement());
							Q_ASSERT(xml.name() == "children");
						}
						else
						{
							xml.raiseError(QObject::tr("Unrecognized tag '%1'").arg(xml.name().toString()));
						}
					}
				}

				Q_ASSERT(xml.isEndElement());
				Q_ASSERT(xml.name() == "gameObject");
				
				return ret;
			}
			catch (...)
			{
				if (ret != 0 && parent != 0)
				{
					delete ret;
				}
				ret = 0;
				throw;
			}
		}

		return ret;
	}

	void SceneLoader::loadGameObjectAttributes(GameObject* gameObject)
	{
		if (xml.attributes().hasAttribute("id"))
		{
			gameObject->setID(xml.attributes().value("id").toInt());
		}
		else
		{
			gameObject->setID(-1);
		}
	}

	void SceneLoader::loadTransformForObject(GameObject* gameObject)
	{
		Transform* trans = gameObject->getTransform();

		if (xml.isStartElement() && xml.name() == "transform")
		{
			xml.readNextStartElement();
			update();
			if (xml.name() == "position")
			{
				trans->setPosition(this->loadVector3FromXml());

				update();
				xml.readNextStartElement();
				update();
				if (xml.name() == "rotation")
				{
					trans->setRotation(this->loadVector3FromXml());

					xml.readNextStartElement();
					if (xml.name() == "scale")
					{
						trans->setScale(this->loadVector3FromXml());
					}
					else
					{
						xml.raiseError("Could not load scale data for GameObject's Transform.");
					}
				}
				else
				{
					xml.raiseError("Could not load rotation data for GameObject's Transform.");
				}
			}
			else
			{
				xml.raiseError("Could not load position data for GameObject's Transform.");
			}
			xml.skipCurrentElement();
		}
	}

	void SceneLoader::loadComponentsForObject(GameObject* gameObject)
	{
		update();
		while (xml.readNextStartElement())
		{
			update();
			if (xml.name() == "component")
			{
				string componentType;
				qStringToStdString(xml.attributes().value("type"), componentType);
				this->loadComponent(gameObject, componentType);

				while (!(xml.name() == "component" && xml.isEndElement()))
				{
					xml.readNext();
				}

				update();
				Q_ASSERT(xml.isEndElement());
				Q_ASSERT(xml.name() == "component");
			}
			else
			{
				xml.raiseError(QObject::tr("Unrecognized tag '%1'").arg(xml.name().toString()));
			}
		}
	}

	Vector3 SceneLoader::loadVector3FromXml()
	{
		Vector3 ret;

		QString qtext;

		xml.readNextStartElement();
		update();
		if (xml.name() == "x")
		{
			qtext = xml.readElementText();
			qStringToStdString(qtext, text);
			ret.x = qtext.toFloat();

			update();
			xml.readNextStartElement();
			update();
			if (xml.name() == "y")
			{
				qtext = xml.readElementText();
				qStringToStdString(qtext, text);
				ret.y = qtext.toFloat();

				update();
				xml.readNextStartElement();
				update();
				if (xml.name() == "z")
				{
					qtext = xml.readElementText();
					qStringToStdString(qtext, text);
					ret.z = qtext.toFloat();
				}
				else
				{
					xml.raiseError("Could not read z-component of 3-component Vector.");
				}
			}
			else
			{
				xml.raiseError("Could not read y-component of 3-component Vector.");
			}
		}
		else
		{
			xml.raiseError("Could not read x-component of 3-component Vector.");
		}

		update();
		xml.skipCurrentElement();
		update();

		return ret;
	}

	void SceneLoader::update()
	{
		isStart = xml.isStartElement();
		isEnd = xml.isEndElement();
		qStringToStdString(xml.name(), name);
	}
}