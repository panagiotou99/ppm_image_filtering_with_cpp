#ifndef _IMAGE
#define _IMAGE

#include "vec3.h"
#include "imageio.h"
#include "array2d.h"
#include <iostream>
#include "ppm.h"
#define Color math::Vec3<float>
#include <string>
namespace image
{
	class Image : public ImageIO, public math::Array2D<Color>
	{
	public:
		int ww; //width
		int hh; //height
		Array2D::buffer;
		Image() {
			this->ww = 0;
			this->hh = 0;
		}
		~Image() {
			std::vector<Color>().swap(buffer);

		}
		bool load(const std::string& filename, const std::string& format) {
			std::string extension = "";
			// find the last occurrence of '.'
			size_t pos = filename.find_last_of(".");
			// make sure the poisition is valid
			if (pos != std::string::npos)
				extension = filename.substr(pos + 1);
			else {
				std::cout << "Could not find . in the filename\n";
				return false;
			}
			//case insensitive comparison between the two strings
			bool temp;
			struct compare_struct {
				static bool compare_strings(const std::string& a, const std::string& b) {
					unsigned int sz = a.size();
					if (b.size() != sz)
						return false;
					for (unsigned int i = 0; i < sz; ++i)
						if (tolower(a[i]) != tolower(b[i]))
							return false;
					return true;
				}
			};
			temp = compare_struct::compare_strings(extension, format);
			if (temp) {
				int pw = 0;
				int ph = 0;
				const char* cstr = filename.c_str();
				float* image = image::ReadPPM(cstr, &pw, &ph);
				if (image == 0) {
					return false;
				}
				this->ww = pw;
				this->hh = ph;
				for (int i = 0; i < 3 * pw * ph; i=i +3) {
					Color temp = Color(image[i], image[i + 1], image[i + 2]);
					this->buffer.push_back(temp);
				}
				delete[] image;
				return true;
			}
			else
				return false;
		}

		bool save(const std::string& filename, const std::string& format) {
			//We'll follow the same procedure as the load(...) method for starters 
			std::string extension = "";
			// find the last occurrence of '.'
			size_t pos = filename.find_last_of(".");
			// make sure the poisition is valid
			if (pos != std::string::npos)
				extension = filename.substr(pos + 1);
			else {
				std::cout << "Could not find . in the filename\n";
				return false;
			}
			//case insensitive comparison between the two strings
			bool temp;
			struct compare_struct {
				static bool compare_strings(const std::string& a, const std::string& b) {
					unsigned int sz = a.size();
					if (b.size() != sz)
						return false;
					for (unsigned int i = 0; i < sz; ++i)
						if (tolower(a[i]) != tolower(b[i]))
							return false;
					return true;
				}
			};
			temp = compare_struct::compare_strings(extension, format);
			if (temp) {
				const char* new_name = filename.c_str();
				int stoixeio = 0;
				int temp_size = 3*buffer.size();
				temp_size = temp_size * 3;
				float* float_image = new float[temp_size];
				for (decltype(buffer.size()) i = 0; i< buffer.size(); i++) {
					Color pixel = buffer[i];
					float_image[stoixeio] = pixel.x;
					stoixeio++;
					float_image[stoixeio] = pixel.y;
					stoixeio++;
					float_image[stoixeio] = pixel.z;
					stoixeio++;
				}
				bool writing = image::WritePPM(float_image,this->ww,this->hh, new_name);
				delete[] float_image;
				return true;
			}
			else
				return false;
		}
	};
} //namespace image

#endif