#include "Array.h"

template<class T> Array<T>::Array(): size(0), data(nullptr) {}

template<class T> Array<T>::Array(int _size) {
	size = _size;
	data = new T [size];
}

template<class T> Array<T>::Array(const Array<T>& a) {
	size = a.getSize();
	data = new T [size];

	for(int i=0;i<size;i++) {
		data[i] = a[i];
	}
}

template<class T> Array<T>::~Array() {
	delete [] data;
}

template<class T> void Array<T>::operator =(const Array<T>& a) {
	delete [] data;

	size = a.size();
	data = new T [size];

	for(int i=0;i<size;i++) {
		data[i] = a[i];
	}
}

template<class T> int Array<T>::getSize() const {
	return size;
}

template<class T> T& Array<T>::operator [](const int& idx) const {
	return data[idx];
}