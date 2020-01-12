#ifndef ARRAY_H
#define ARRAY_H

template<class T> class Array {
	T* data;
	int size;

	public:
		Array();
		Array(int);
		Array(const Array<T>&);
		~Array();

		void operator =(const Array<T>&);

		int getSize() const;

		T& operator [](const int&) const;
};

#endif