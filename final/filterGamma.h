#ifndef _FILTER_GAMMA
#define _FILTER_GAMMA
#include "image.h"
#include "filter.h"
#include "vec3.h"
#define Color math::Vec3<float>
#include <math.h>
namespace image
{
	class FilterGamma : public Filter
	{
	public:
		float gamma;
		FilterGamma(float g) {
			this->gamma = g;
		}
		FilterGamma(const FilterGamma& src) {
			this->gamma = src.gamma;
		}
		Image operator << (const Image& image) {
			Color pixel;
			image::Image temp_image = image::Image(image);
			std::vector<Color> temp_vect;
			int buffer_size = image.buffer.size();
			if (gamma < 0.5f || gamma>2.0f) {
				std::cout << "Gamma should be between 0.5 and 2.0. Image returned is the same";
				return temp_image;
			}
			for (int i = 0; i < buffer_size; i++) {
				pixel = image.buffer[i];
				pixel.x = pow(pixel.x, gamma);
				pixel.y = pow(pixel.y, gamma);
				pixel.z = pow(pixel.z, gamma);
				temp_image.buffer[i] = pixel;
			}
			return temp_image;
		}
	};
}
#endif 