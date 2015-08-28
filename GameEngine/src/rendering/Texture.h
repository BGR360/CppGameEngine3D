#ifndef BENGINE_TEXTURE_H
#define BENGINE_TEXTURE_H

#include <Engine.h>

#include <util/Types.h>

namespace Resources
{
	class Image;
}

using Resources::Image;

namespace Rendering
{
	class Texture
	{
	public:
		enum TextureType
		{
			TEXTURE_2D,
			NUM_TEXTURE_TYPES
		};
		enum FilteringType
		{
			FILTER_NEAREST,
			FILTER_LINEAR,

			NUM_FILTERING_TYPES
		};
		enum WrappingType
		{
			WRAP_REPEAT,
			WRAP_MIRRORED_REPEAT,
			WRAP_CLAMP_TO_EDGE,
			WRAP_CLAMP_TO_BORDER,

			NUM_WRAPPING_TYPES
		};

	private:
		Image* m_image;
		uint m_textureID;
		uint m_textureUnit;

	public:
		Texture(Image* image, uint textureUnit = 0);
		virtual ~Texture();

		void bind();

		void setTextureUnit(uint textureUnit);
		uint getTextureUnit() const;
		uint getTextureID() const;

		void setMinFiltering(FilteringType filteringType);
		void setMaxFiltering(FilteringType filteringType);
		void setWrappingHorizontal(WrappingType wrappingType);
		void setWrappingVertical(WrappingType wrappingType);

	private:
		void initialize();

		Texture(const Texture& source) {}	//override copy ctor
		Texture& operator=(const Texture& source) {}	//override assignment operator
	};
}

#endif //BENGINE_TEXTURE_H