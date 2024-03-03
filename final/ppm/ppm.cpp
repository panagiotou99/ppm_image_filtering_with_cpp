#include <fstream>
#include <iostream>
#include <cstring>

using namespace std;

namespace image
{
	//Reads a PPM image file and returns a pointer to a newly allocated float array containing the image data
	float* ReadPPM(const char* filename, int* w, int* h) {
		ifstream file;
		char* keno = new char[1];
		file.open(filename, ios::binary);
		if (file.is_open()) {
			string format;
			file >> format;
			if (format != "P6") {
				cout << "File's format not supported.\n";
				cin.get();
				return 0;
			}
			int width, height;
			file >> width;
			file >> height;
			*w = width;
			*h = height;
			string bytes;
			file >> bytes;
			if (bytes != "255") {
				cout << "Byte number is not valid.\n" << endl;
				cin.get();
				return 0;
			}
			int size = (*w) * (*h) * 3;
			file.read(keno, 1);
			float* buff = new float[size];
			unsigned char* temp = new unsigned char[size];
			file.read((char*)temp, size);
			int i = 0;
			while (i < size) {
				buff[i] = (float)temp[i] / 255;
				i++;
			}
			file.close();
			delete[] temp;
			delete[] keno;
			return buff;
		}
		else {
			cout << "Error, can't open the file.\n";
			cin.get();
			return 0;
		}
	}

	//Writes an image buffer as a PPM file.
	bool WritePPM(const float* data, int w, int h, const char* filename) {
		ofstream file;
		file.open(filename, ios::out | ios::binary);
		file << "P6\n" << w << "\n" << h << "\n255\n";
		for (int i = 0; i < 3 * w * h; i++) {
			unsigned char c = (unsigned char)(255.0f * data[i]);
			file.write((char*)& c, sizeof(c));
		}
		file.close();
		return 0;
	}

} //namespace image