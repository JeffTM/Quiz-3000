#pragma once
#include <exception>

//Number the vectors capacity is multiplied by on expansion. Should be an integer > 1
#define CAPACITY_MULT 2

namespace Jeff
{
	template<class T>
	class Vector
	{
	public:
		//Default constructor. Creates an empty vector with a capacity of 2
		Vector();
		//Creates an empty vector with a capacity of initCapacity. Throws an exception if initCapacity < 1 that should not be caught.
		Vector(int initCapacity);
		//Copy constructor. Uses a deep copy
		Vector(const Vector<T> & other);
		//Destructor
		~Vector();
		//Assignment operator. Uses a deep copy
		Vector<T> & operator=(const Vector<T> & other);

		//Returns the size of the vector
		int size() const;
		//Returns the capacity of the vector
		int capacity() const;
		//Ensures the vector has the capacity for an least n elements
		void reserve(int n);
		//Shrinks the vectors capacity to its size
		void shrinkToFit();

		//Gets the element at index. Does not perform bounds checking
		T & operator[](int index);
		const T & operator[] (int index) const;
		//Gets the element at index. Throws an exception if the index is out of bounds
		T & at(int index);
		const T & at(int index) const;

		//Adds a copy of elem to the end of the vector
		void add(const T & elem);
		//Adds a copy of elem into the vector before index
		void add(int index, const T & elem);
		//Removes the element at the end of the vector. Throws an exception if the vectors size is 0
		void remove();
		//Removes the element at index. An exception is thrown if index >= size
		void remove(int index);
		//Removes all elements in the vector
		void clear();

	private:
		//Dynamic array for the elements. It's capacity should always be > 0
		T * _elements;
		//Actual size of the dynamic array
		int _capacity;
		//Size of the vector
		int _size;

		//Master reallocation method. All elements reallocation should be done through this method. newCapacity must be >= _size.
		void reallocate(int newCapacity);
		//Multiplies this vectors capacity by CAPACITY_MULT using reallocate(CAPACITY_MULT * capacity)
		void expand();
	};

	template <class T>
	Vector<T>::Vector()
		:_elements(new T[2]), _capacity(2), _size(0)
	{}

	template <class T>
	Vector<T>::Vector(int initCapacity)
		: _elements(new T[initCapacity]), _capacity(initCapacity), _size(0)
	{
		if (initCapacity < 1)
			throw std::invalid_argument("intiCapacity must be >= 1");
	}

	template<class T>
	Vector<T>::Vector(const Vector<T> & other)
	{
		_elements = new T[other._capacity];
		for (int i = 0; i < other._capacity; i++)
			_elements[i] = other._elements[i];
		_capacity = other._capacity;
		_size = other._size;
	}

	template<class T>
	Vector<T>::~Vector()
	{
		delete[] _elements;
	}

	template<class T>
	Vector<T> & Vector<T>::operator=(const Vector<T> & other)
	{
		if (this != &other)
		{
			delete[] _elements;
			_elements = new T[other._capacity];
			for (int i = 0; i < other._capacity; i++)
				_elements[i] = other._elements[i];
			_capacity = other._capacity;
			_size = other._size;
		}
		return *this;
	}

	template<class T>
	int Vector<T>::size() const
	{
		return _size;
	}

	template<class T>
	int Vector<T>::capacity() const
	{
		return _capacity;
	}

	template<class T>
	void Vector<T>::reserve(int n)
	{
		if (n > _capacity)
			reallocate(n);
	}

	template<class T>
	void Vector<T>::shrinkToFit()
	{
		if (_size > 1)
			reallocate(_size);
		else
			reallocate(1);
	}

	template<class T>
	T & Vector<T>::operator[](int index)
	{
		return _elements[index];
	}

	template<class T>
	const T & Vector<T>::operator[](int index) const
	{
		return _elements[index];
	}

	template<class T>
	T & Vector<T>::at(int index)
	{
		if (index < 0 || index >= _size)
			throw std::out_of_range("index out of range");

		return _elements[index];
	}

	template<class T>
	const T & Vector<T>::at(int index) const
	{
		if (index < 0 || index >= _size)
			throw std::out_of_range("index out of range");

		return _elements[index];
	}

	template<class T>
	void Vector<T>::add(const T & elem)
	{
		if (_capacity == _size)
			expand();

		_elements[_size] = elem;
		_size++;
	}

	template<class T>
	void Vector<T>::add(int index, const T & elem)
	{
		if (index > _size)
			throw std::invalid_argument("index must be <= size");

		if (_capacity == _size)
			expand();

		for (int i = _size; i > index; i--)
			_elements[i] = _elements[i - 1];
		_elements[index] = elem;
		_size++;
	}

	template<class T>
	void Vector<T>::remove()
	{
		if (_size > 0)
			_size--;
		else
			throw std::out_of_range("No element to remove");
	}

	template<class T>
	void Vector<T>::remove(int index)
	{
		if (index >= _size)
			throw std::invalid_argument("index must be < size");

		//If the index to be removed is not at the end of the array copy down the elements above
		for (int i = index + 1; i < _size; i++)
			_elements[i - 1] = element[i];

		_size--;
	}

	template<class T>
	void Vector<T>::clear()
	{
		_size = 0;
	}

	//private -----------------------------------------------------------------------

	template<class T>
	void Vector<T>::reallocate(int newCapacity)
	{
		T * temp = new T[newCapacity];

		for (int i = 0; i < _size; i++)
			temp[i] = _elements[i];

		delete[] _elements;
		_elements = temp;
		_capacity = newCapacity;
	}

	template<class T>
	void Vector<T>::expand()
	{
		reallocate(CAPACITY_MULT * _capacity);
	}
}
