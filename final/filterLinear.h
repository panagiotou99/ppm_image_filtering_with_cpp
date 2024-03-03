#ifndef _FILTER_LINEAR
#define _FILTER_LINEAR
#include "image.h"
#include "filter.h"
#include "vec3.h"
#define Color math::Vec3<float>
namespace image {
	class FilterLinear : public image::Filter
	{
	public:
		Color a, c;
		FilterLinear(Color a, Color c) {
			this->a = a;
			this->c = c;
		}
		FilterLinear(const FilterLinear& src) {
			this->a = src.a;
			this->c = src.c;
		}
		Image operator << (const image::Image& image){
			Color pixel;
			image::Image temp_image = image::Image(image);
			std::vector<Color> temp_vect;
			int buffer_size = image.buffer.size();
			for (int i = 0; i < buffer_size; i++) {
				pixel = image.buffer[i];
				pixel = pixel * a;
				pixel = pixel + c;
				if (pixel.x < 0)
					pixel.x = 0.0f;
				if (pixel.y < 0)
					pixel.y = 0.0f;
				if (pixel.z < 0)
					pixel.z = 0.0f;
				if (pixel.x > 1)
					pixel.x = 1.0f;
				if (pixel.y > 1)
					pixel.y = 1.0f;
				if (pixel.z > 1)
					pixel.z = 1.0f;
				temp_image.buffer[i] = pixel;
			}
			return temp_image;
		}
	};
}
#endif 