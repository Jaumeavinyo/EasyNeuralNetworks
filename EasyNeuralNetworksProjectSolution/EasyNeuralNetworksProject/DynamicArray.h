#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <cassert>

#define DYNAMIC_ARRAY_CHUNK_SIZE 5
#define DYNAMIC_ARRAY_INITIAL_CAPACITY DYNAMIC_ARRAY_CHUNK_SIZE

template<class T>
class DynamicArray
{
private:

	T* p_Array = nullptr;
	unsigned int p_Capacity = DYNAMIC_ARRAY_INITIAL_CAPACITY;
	unsigned int p_Size = 0;

public:

	DynamicArray()
	{
		p_Capacity = DYNAMIC_ARRAY_INITIAL_CAPACITY;
		p_Array = new T[p_Capacity]();
		p_Size = 0;
	}

	DynamicArray(unsigned int size)
	{
		const int intPart = size / DYNAMIC_ARRAY_CHUNK_SIZE;
		const int resPart = static_cast<int>(static_cast<bool>(size % DYNAMIC_ARRAY_CHUNK_SIZE));
		p_Capacity = (intPart + resPart) * DYNAMIC_ARRAY_CHUNK_SIZE;
		p_Array = new T[p_Capacity]();
		p_Size = size;
	}

	~DynamicArray()
	{
		delete[] p_Array;
	}

	bool empty() const
	{
		return p_Size == 0;
	}

	unsigned int size() const
	{
		return p_Size;
	}

	unsigned int capacity() const
	{
		return p_Capacity;
	}

	T& operator[](unsigned int index)
	{
		assert(index < p_Size && "operator[] - index out of bounds");
		return p_Array[index];
	}

	const T& operator[](unsigned int index) const
	{
		assert(index < p_Size && "operator[] - index out of bounds");
		return p_Array[index];
	}

	void pushBack(const T& value)
	{
		if (p_Size >= p_Capacity)
		{
			increaseCapacity();
		}
		p_Array[p_Size] = value;
		p_Size++;
	}

	void pushFront(const T& value)
	{
		if (p_Size >= p_Capacity)
		{
			increaseCapacity();
		}
		shiftRightwardsFromIndex(0);
		p_Array[0] = value;
		p_Size++;
	}

	void insert(unsigned int index, const T& value)
	{
		assert(index <= p_Size && "insert() - index out of bounds");
		if (p_Size >= p_Capacity)
		{
			increaseCapacity();
		}
		shiftRightwardsFromIndex(index);
		p_Array[index] = value;
		p_Size++;
	}

	void erase(unsigned int index)
	{
		assert(index < p_Size && "erase() - index out of bounds");
		shiftLeftwardsFromIndex(index);
		p_Size--;
	}

	void clear()
	{
		p_Size = 0;
	}

	void shrinkToFit()
	{
		p_Capacity = p_Size;
		T* fitted_array = new T[p_Capacity];
		for (unsigned int i = 0; i < p_Size; ++i) {
			fitted_array[i] = p_Array[i];
		}
		delete p_Array;
		p_Array = fitted_array;
	}


private:


	void increaseCapacity()
	{
		p_Capacity += DYNAMIC_ARRAY_CHUNK_SIZE;
		T* newArray = new T[p_Capacity]();
		for (int i = 0; i < p_Size; ++i) {
			newArray[i] = p_Array[i];
		}
		delete p_Array;
		p_Array = newArray;
	}

	void shiftRightwardsFromIndex(unsigned int index)
	{
		for (unsigned int i = p_Size; i > index; --i)
		{
			p_Array[i] = p_Array[i - 1];
		}
	}

	void shiftLeftwardsFromIndex(unsigned int index)
	{
		for (unsigned int i = index; i < p_Size - 1; ++i)
		{
			p_Array[i] = p_Array[i + 1];
		}
	}

	
};


#endif