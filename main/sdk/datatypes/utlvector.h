#pragma once

#include "utlmemory.h"

template <class T>
void destruct(T* m_memory)
{
	m_memory->~T();
}

template <class T>
T* construct(T* m_memory)
{
	return new(m_memory) T;
}

template< class T >
T* copy(T* m_memory, T const& src)
{
	return new(m_memory) T(src);
}

template <class T, class A = utl_memory<T>>
class utl_vector
{
	using allocator = A;
public:
	auto begin() const noexcept
	{
		return m_memory.Base();
	}

	auto end() const noexcept
	{
		return m_memory.Base() + m_size;
	}

	T& operator[](int i)
	{
		return m_memory[i];
	}

	const T& operator[](int i) const
	{
		return m_memory[i];
	}

	T& get(int i)
	{
		return m_memory[i];
	}

	const T& get(int i) const
	{
		return m_memory[i];
	}

	T* base()
	{
		return m_memory.Base();
	}

	int count() const
	{
		return m_size;
	}

	int& size()
	{
		return m_size;
	}

	void grow_vector(int count = 1)
	{
		if (m_size + count > m_memory.NumAllocated())
			m_memory.Grow(m_size + count - m_memory.NumAllocated());

		m_size += count;
	}

	void shift_elements_right(const int element, const int shift = 1)
	{
		const int nToMove = m_size - element - shift;

		if (nToMove > 0 && shift > 0)
			memmove(&get(element + shift), &get(element), nToMove * sizeof(T));
	}

	void shift_elements_left(const int element, const int shift = 1)
	{
		const int nToMove = m_size - element - shift;

		if (nToMove > 0 && shift > 0)
			memmove(&get(element), &get(element + shift), nToMove * sizeof(T));
	}

	int insert_before(const int element)
	{
		// can insert at the end
		grow_vector();
		shift_elements_right(element);
		Construct(&get(element));
		return element;
	}

	int insert_before(int element, const T& src)
	{
		// reallocate if can't insert something that's in the list
		// can insert at the end
		grow_vector();
		shift_elements_right(element);
		copy(&get(element), src);
		return element;
	}

	int add_to_tail()
	{
		return insert_before(m_size);
	}

	int add_to_tail(const T& src)
	{
		return insert_before(m_size, src);
	}

	int find(const T& src) const
	{
		for (int i = 0; i < count(); ++i)
		{
			if (get(i) == src)
				return i;
		}

		return -1;
	}

	void remove(const int element)
	{
		destruct(&get(element));
		shift_elements_left(element);
		--m_size;
	}

	void remove_all()
	{
		for (int i = m_size; --i >= 0;)
			destruct(&get(i));

		m_size = 0;
	}

	bool find_and_remove(const T& src)
	{
		if (const int element = find(src); element != -1)
		{
			remove(element);
			return true;
		}

		return false;
	}

protected:
	allocator m_memory;
	int m_size;
	T* m_elements;
};