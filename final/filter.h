//Filter is an abstact class.
#ifndef _FILTER
#define _FILTER
#include "image.h"
namespace image
{
	class Filter
	{
	protected:
		Filter() {}
	public:
		virtual Image operator << (const Image& image) = 0;
	};
}
#endif