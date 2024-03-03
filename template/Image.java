#include "ppm.h"
#include <string>
#include <iostream>

namespace image
{
	class ImageIO
	{
	protected:
		int height, width;
		float* float_image;
		ImageIO() {
			this->height = 0;
			this->width = 0;
			this->float_image = nullptr;
		}
	public:
		virtual bool load(const std::string& filename, const std::string& format) {
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
				static bool compare_strings(const std::string& a, const std::string& b){
					unsigned int sz = a.size();
					if (b.size() != sz)
						return false;
					for (unsigned int i = 0; i < sz; ++i)
						if (tolower(a[i]) != tolower(b[i]))
							return false;
					return true;
				}
			};
			temp = compare_struct::compare_strings(extension,format);
			if (temp) {
				int pw = 0;
				int ph = 0;
				const char* cstr = filename.c_str();
				float* image = image::ReadPPM(cstr, &pw, &ph);
				this->float_image = image;
				this->width = pw;
				this->height = ph;
				return true;
			}
			else 
				return false;
		}

		virtual bool save(const std::string& filename, const std::string& format) {
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
				bool writing = image::WritePPM(float_image, width, height, new_name);
				return true;
			}
			else
				return false;
		}
	};
}