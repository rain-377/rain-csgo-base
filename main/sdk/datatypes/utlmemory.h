#pragma once

inline int utl_memory_calc_new_allocation_count(int allocation_count, int grow_size, int new_size, int bytes_item)
{
	if (grow_size)
		allocation_count = ((1 + ((new_size - 1) / grow_size)) * grow_size);
	else
	{
		if (!allocation_count)
			allocation_count = (31 + bytes_item) / bytes_item;

		while (allocation_count < new_size)
			allocation_count *= 2;
	}

	return allocation_count;
}

template <class T, class N = int>
class utl_memory
{
public:
	T& operator[](N i)
	{
		return m_memory[i];
	}

	const T& operator[](N i) const
	{
		return m_memory[i];
	}

	T* base()
	{
		return m_memory;
	}

	int num_allocated() const
	{
		return m_allocation_count;
	}

	void grow(int iNum = 1)
	{
		if (is_externally_allocated())
			return;

		int old_allocation_count = m_allocation_count;
		int allocation_requested = m_allocation_count + iNum;
		int new_allocation_count = utl_memory_calc_new_allocation_count(m_allocation_count, m_grow_size, allocation_requested, sizeof(T));

		if (static_cast<int>(static_cast<N>(new_allocation_count)) < allocation_requested)
		{
			if (static_cast<int>(static_cast<N>(new_allocation_count)) == 0 && static_cast<int>(static_cast<N>(new_allocation_count - 1)) >= allocation_requested)
				--new_allocation_count;
			else
			{
				if (static_cast<int>(static_cast<N>(allocation_requested)) != allocation_requested)
				{
					return;
				}

				while (static_cast<int>(static_cast<N>(new_allocation_count)) < allocation_requested)
					new_allocation_count = (new_allocation_count + allocation_requested) / 2;
			}
		}

		m_allocation_count = new_allocation_count;

		if (m_memory != nullptr)
		{
			auto data = new unsigned int[m_allocation_count * sizeof(T)];
			memcpy(data, m_memory, old_allocation_count * sizeof(T));
			m_memory = reinterpret_cast<T*>(data);
		}
		else
			//m_memory = reinterpret_cast<T*>(I::MemAlloc->Alloc(m_allocation_count * sizeof(T)));
			m_memory = reinterpret_cast<T*>(new std::byte[m_allocation_count * sizeof(T)]);
	}

	bool is_externally_allocated() const
	{
		return m_grow_size < 0;
	}

protected:
	T* m_memory;
	int m_allocation_count;
	int m_grow_size;
};