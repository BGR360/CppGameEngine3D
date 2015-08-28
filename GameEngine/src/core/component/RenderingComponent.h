#ifndef BENGINE_RENDERING_COMPONENT_H
#define BENGINE_RENDERING_COMPONENT_H

#include <Engine.h>

#include <core/GameObject.h>

namespace Core
{
	namespace Component
	{
		class ENGINE_DLL_EXPORT_IMPORT RenderingComponent : public GameComponent
		{
		public:
			virtual void render() = 0;
		};
	}
}

#endif //BENGINE_RENDERING_COMPONENT_H