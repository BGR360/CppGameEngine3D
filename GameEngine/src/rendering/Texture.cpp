#include "Texture.h"

#include <sstream>

#include <rendering/OpenGL.h>
#include <resources/Image.h>

using std::stringstream;

namespace Rendering
{
	Texture::Texture(Image* image, uint textureUnit)
		: m_image(image), m_textureUnit(textureUnit)
	{
		this->initialize();
	}

	void Texture::initialize()
	{
		//Generate Texture
		glCheckCall(glGenTextures(1, &m_textureID));

		this->bind();

		//Specify Wrapping
		this->setWrappingHorizontal(WRAP_REPEAT);
		this->setWrappingVertical(WRAP_REPEAT);

		//Specify Filtering
		this->setMinFiltering(FILTER_LINEAR);
		this->setMaxFiltering(FILTER_LINEAR);

		//Load Image Data to OpenGL
		QImage::Format imageFormat = m_image->format();

		GLenum glInternalFormat = -1;
		GLenum glImageFormat = -1;
		GLenum glDataFormat = -1;
		
		switch (imageFormat)
		{
		case QImage::Format_RGB888:
			//GL_RGB, GL_UNSIGNED_BYTE
			glInternalFormat = glImageFormat = GL_RGB;
			glDataFormat = GL_UNSIGNED_BYTE;
			break;

		case QImage::Format_RGBA8888:
			//GL_RGB, GL_UNSIGNED_BYTE
			glInternalFormat = glImageFormat = GL_RGBA;
			glDataFormat = GL_UNSIGNED_BYTE;
			break;

		default:
			stringstream message("The image has not been loaded with a usable internal format. Format is: ");
			message << imageFormat << '.';
			throw OpenGLException(message.str());
			break;
		}

		//Do this so that QImage::bits() does not perform a deep copy
		const Image* constImage = m_image;

		glCheckCall(
			glTexImage2D(
			GL_TEXTURE_2D, 0, glInternalFormat,
			m_image->width(), m_image->height(), 0, glImageFormat,
			glDataFormat, static_cast<const void*>(constImage->bits()))
		);
	}

	void Texture::bind()
	{
		glCheckCall(glActiveTexture(GL_TEXTURE0 + m_textureUnit));
		glCheckCall(glBindTexture(GL_TEXTURE_2D, m_textureID));
	}

	void Texture::setTextureUnit(uint textureUnit)
	{
		m_textureUnit = textureUnit;
	}

	uint Texture::getTextureUnit() const
	{
		return m_textureUnit;
	}

	uint Texture::getTextureID() const
	{
		return m_textureID;
	}

	void Texture::setMinFiltering(FilteringType filteringType)
	{
		switch (filteringType)
		{
		case FILTER_LINEAR:
			glCheckCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
			break;
		case FILTER_NEAREST:
			glCheckCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
			break;
		default:
			glCheckCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
			break;
		}
	}

	void Texture::setMaxFiltering(FilteringType filteringType)
	{
		switch (filteringType)
		{
		case FILTER_LINEAR:
			glCheckCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
			break;
		case FILTER_NEAREST:
			glCheckCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
			break;
		default:
			glCheckCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
			break;
		}
	}

	void Texture::setWrappingHorizontal(WrappingType wrappingType)
	{
		switch (wrappingType)
		{
		case WRAP_REPEAT:
			glCheckCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
			break;
		case WRAP_MIRRORED_REPEAT:
			glCheckCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT));
			break;
		case WRAP_CLAMP_TO_EDGE:
			glCheckCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
			break;
		case WRAP_CLAMP_TO_BORDER:
			glCheckCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER));
			break;
		default:
			glCheckCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
			break;
		}
	}

	void Texture::setWrappingVertical(WrappingType wrappingType)
	{
		switch (wrappingType)
		{
		case WRAP_REPEAT:
			glCheckCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
			break;
		case WRAP_MIRRORED_REPEAT:
			glCheckCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT));
			break;
		case WRAP_CLAMP_TO_EDGE:
			glCheckCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
			break;
		case WRAP_CLAMP_TO_BORDER:
			glCheckCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER));
			break;
		default:
			glCheckCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
			break;
		}
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_textureID);
	}
}