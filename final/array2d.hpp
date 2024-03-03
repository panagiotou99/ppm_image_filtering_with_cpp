#include "array2d.h"
namespace math {
	template<typename T>
	const unsigned int Array2D<T>::getWidth() const {
		return this->width;
	}
	template<typename T>
	const unsigned int Array2D<T>::getHeight() const {
		return this->height;
	}
	template<typename T>
	T* Array2D<T>::getRawDataPtr() {
		return this->buffer.data();
	}
	template<typename T>
	void Array2D<T>::setData(const T* const& data_ptr) {
		if (getWidth() == 0 || getHeight() == 0 || getRawDataPtr()== 0)
			return;
		for (unsigned int i = 0; i < getWidth() * getHeight(); i++)
			this->buffer[i] = data_ptr[i];
	}
	template<typename T>
	T& Array2D<T>::operator()(unsigned int x, unsigned int y){
		return this->buffer[x*(width) + y];
	}
	template<typename T>
	Array2D<T>::Array2D(unsigned int width, unsigned int height, const T * data_ptr) :
	width(width),
	height(height),
	buffer(data_ptr,data_ptr+width*height)
	{}

	template<typename T> 
	Array2D<T>::Array2D(const Array2D& src) {
		this->width = src.getWidth();
		this->height = src.getHeight();
		this->buffer = src.buffer;
	}

	template<typename T>
	Array2D<T>::~Array2D() {
		std::vector<T>().swap(buffer);

	}
	template<typename T>
	Array2D<T>& Array2D<T>::operator=(const Array2D& right) {
		this->width = right.getWidth();
		this->height = right.getHeight();
		this->buffer = right.buffer;
		return *this;
	}
}