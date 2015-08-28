#ifndef BENGINE_WINDOW_H
#define BENGINE_WINDOW_H

#include <Engine.h>

#include <string>

using std::string;

namespace Rendering
{
	class ENGINE_DLL_EXPORT_IMPORT Window
	{
		int m_width;
		int m_height;
		float m_aspectRatio;

		string m_name;

	public:
		Window();
		Window(string name, int width = 800, int height = 600);
		virtual ~Window();

		virtual void open() = 0;
		virtual void close() = 0;

		void setName(string name);
		void setWidth(int width);
		void setHeight(int height);

		string getName() const;
		int getWidth() const;
		int getHeight() const;

	protected:
	private:
	};
}

#endif //BENGINE_WINDOW_H