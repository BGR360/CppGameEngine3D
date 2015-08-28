#ifndef BENGINE_IMAGE_H
#define BENGINE_IMAGE_H

#include <string>

#include <qt/QtGui/qimage.h>

#include <exceptions/FileNotFoundException.h>

using std::string;

using Exceptions::FileNotFoundException;

namespace Resources
{
	class Image : public QImage
	{
	public:
		Image() {}
		Image(const QImage& qimage) : QImage(qimage) {}
		virtual ~Image() {}

	private:
		Image(const Image& source) {}	//override copy constructor
		Image& operator=(const Image& source) {} //override assignment operator
	};
}

#endif //BENGINE_IMAGE_H