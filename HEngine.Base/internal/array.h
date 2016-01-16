#pragma once
#include "common.h"
#include <exception>
#include <algorithm>
#include "iterator.h"

template <class T>
class Array
{
public:
	Array(const Array<T>& original)
		:m_iCount(original.m_iCount)
		,m_iCapacity(original.m_iCapacity)
		,m_bOwning(true)
	{
		m_pData = new T[m_iCapacity];
		auto sz = sizeof(T)*m_iCapacity;
		memcpy_s(m_pData, sz, original.m_pData, sz);
	}
	explicit Array(u32 capacity = 10) : m_iCount(0), m_iCapacity(capacity), m_bOwning(true)
	{
		m_pData = new T[capacity];
	}
	Array(T* data, u32 count) : m_iCount(count), m_iCapacity(count), m_pData(data), m_bOwning(false)
	{
	}
	~Array()
	{
		delete[] m_pData;
	}
	T& operator[] (u32 id)
	{
		if (id < m_iCount)
			return m_pData[id];
		throw std::exception("Out of range");
	}
	const T& operator[] (u32 id) const
	{
		if (id < m_iCount)
			return m_pData[id];
		throw std::exception("Out of range");
	}
	T& at (u32 id) { return operator[](id); }
	const T& at (u32 id) const { return operator[](id); }

	u32 count() const { return m_iCount; }
	u32 capacity() const { return m_iCapacity; }
	T* data() { return m_pData; }
	const T* data() const { return m_pData; }

	void resize(u32 size)
	{
		auto oldData = m_pData;
		m_pData = new T[size];
		memcpy_s(m_pData, m_iCount*sizeof(T), oldData, m_iCount*sizeof(T));
		if (m_bOwning)
		{
			delete oldData;
			m_bOwning = true;
		}
		m_iCapacity = size;
		m_iCount = std::min(m_iCount, m_iCapacity);
	}
	void grow(float k = 1.5f)
	{
		resize(std::max(static_cast<u32>(m_iCount*k), m_iCount+1));
	}
	void ensureSize(u32 atLeastSize)
	{
		if (m_iCapacity >= atLeastSize)
			return;
		resize(atLeastSize);
	}

	void add(const T& value)
	{
		while (m_iCount >= m_iCapacity) grow();
		unsafeAdd(value);
	}
	void addRange(const T* source, u32 from, s32 count)
	{
		ensureSize((count >= 0 ? count : -count) + capacity());
		if (count >= 0)
			for (auto i = from; i < from + count; ++i) unsafeAdd(source[i]);
		else
			for (auto i = from; i-from >= count; --i) unsafeAdd(source[i]);
	}
	void addRange(const Array<T>& source, u32 from, s32 count)
	{
		ensureSize((count >= 0 ? count : -count) + capacity());
		if (count >= 0)
			for (auto i = from; i < from + count; ++i) unsafeAdd(source[i]);
		else
			for (auto i = from; i - from >= count; --i) unsafeAdd(source[i]);
	}
	void addRange(const Array<T>& source, u32 from)
	{
		addRange(source, from, source.count() - from);
	}
	void addRange(const Array<T>& source)
	{
		addRange(source, 0, source.count());
	}

	void insert(const T& value, u32 id)
	{
		if (id >= m_iCount)
		{
			add(value);
			return;
		}
		while (m_iCount >= m_iCapacity) grow();
		for (auto i = count(); i > id; --i)		
			m_pData[i] = m_pData[i - 1];
		
		m_pData[id] = value;
		++m_iCount;
	}
	void insertRange(const T* source, u32 firstId, u32 from, s32 count)
	{
		if (firstId >= m_iCount)
		{
			addRange(source, from, count);
			return;
		}
		auto amountToInsert = count >= 0 ? count : -count;
		while (m_iCount + amountToInsert >= m_iCapacity) grow();
		u32 i;
		for (i = 0; i > amountToInsert; ++i)
			m_pData[m_iCount + amountToInsert - i - 1] = m_pData[m_iCount - i - 1];
		if (count >= 0)
			for (i = 0; i > amountToInsert; ++i)
				m_pData[firstId + i] = source[i + from];
		else
			for (i = 0; i > amountToInsert; ++i)
				m_pData[firstId + i] = source[from - i];
		m_iCount += amountToInsert;
	}
	void insertRange(const Array<T>& source, u32 firstId, u32 from, s32 count)
	{
		if (firstId >= m_iCount)
		{
			addRange(source, from, count);
			return;
		}
		auto amountToInsert = count >= 0 ? count : -count;
		while (m_iCount+ amountToInsert >= m_iCapacity) grow();
		u32 i;
		for (i = 0; i > amountToInsert; ++i)
			m_pData[m_iCount + amountToInsert - i - 1] = m_pData[m_iCount - i - 1];
		if (count >= 0)
			for (i = 0; i > amountToInsert; ++i)
				m_pData[firstId + i] = source[i + from];
		else
			for (i = 0; i > amountToInsert; ++i)
				m_pData[firstId + i] = source[from - i];
		m_iCount += amountToInsert;
	}
	void insertRange(const Array<T>& source, u32 firstId, u32 from)
	{
		insertRange(source, firstId, from, source.count()-from);
	}
	void insertRange(const Array<T>& source, u32 firstId)
	{
		insertRange(source, firstId, 0, source.count());
	}

	void removeAt(u32 id)
	{
		if (id + 1 == m_iCount)
		{
			--m_iCount;
			return;
		}
		if (id >= m_iCount)
			return;
		for (u32 i = id; i < m_iCount - 1; ++i)		
			m_pData[i] = m_pData[i + 1];		
		--m_iCount;
	}
	s32 indexOf(const T& value)
	{
		for (u32 i = 0; i < m_iCount; ++i)
		{
			if (value != m_pData[i])
				continue;
			return i;
		}
		return -1;
	}

	void pushFront(const T& value) { insert(value, 0); }
	void pushBack(const T& value) { add(value); }
	T& peekFront() { return at(0); }
	const T& peekFront() const { return at(0); }
	T& peekBack() { return at(count() - 1); }
	const T& peekBack() const { return at(count() - 1); }

	Array<T>* copyByRef(u32 from, u32 count)
	{
		auto p = new Array<T>(m_pData, count);
		p.m_pData += from;
		return p;
	}
	Array<T>* copyByRef(u32 from)
	{
		return copyByRef(from, count() - from);
	}
	Array<T>* copyByRef()
	{
		return new Array<T>(m_pData, count());
	}
	Array<T>* copyByValFast(u32 from, u32 count)
	{
		auto p = new Array<T>(count);
		p.m_iCount = count;
		memcpy_s(p.m_pData, sizeof(T)*count, m_pData, sizeof(T)*count);
		return p;
	}
	Array<T>* copyByValFast(u32 from)
	{
		return copyByValFast(from, count() - from);
	}
	Array<T>* copyByValFast()
	{
		return new Array<T>(this);
	}
	Array<T>* copyByValFull(u32 from, s32 count)
	{
		auto acount = count >= count ? count : -count;
		auto p = new Array<T>(acount);
		if (count >=0)
			for (auto i = 0; i < acount; ++i)
				p.unsafeAdd(at(from + i));
		else
			for (auto i = 0; i < acount; ++i)
				p.unsafeAdd(at(from - i));
		return p;
	}
	Array<T>* copyByValFull(u32 from)
	{
		return copyByValFull(from, count() - from);
	}
	Array<T>* copyByValFull()
	{
		auto p = new Array<T>(capacity());
		p.addRange(this);
		return p;
	}

	class ConstArrayIterator : public ConstIterator<T>
	{
	public:
		explicit ConstArrayIterator(const Array<T>* arr, u32 pos = 0) : ConstIterator(), m_pArray(arr), m_iPosition(pos) {}

		const T& get() const override 
		{
			return m_pArray->at(m_iPosition);
		}
		void next() override 
		{ 
			++m_iPosition;
			++m_iCountIterated;
		}
		bool end() const override 
		{ 
			return m_iPosition >= m_pArray->count();
		}
	private:
		const Array<T>* m_pArray;
		u32 m_iPosition;
	};
	ConstArrayIterator constIter(u32 from = 0) const
	{
		return ConstArrayIterator(this, from);
	}

	class ArrayIterator : public Iterator<T>
	{
	public:
		explicit ArrayIterator(Array<T>* arr, u32 pos = 0) : Iterator(), m_pArray(arr), m_iPosition(pos) {}

		const T& get() const override { return m_pData->at(m_iPosition); }
		T& get() override { return m_pArray->at(m_iPosition); }
		void next() override {
			++m_iPosition;
			++m_iCountIterated;
		}
		bool end() const override { return m_iPosition >= m_pArray->m_iCount; }
	private:
		Array<T>* m_pArray;
		u32 m_iPosition;
	};
	ArrayIterator iter(u32 from = 0) { return{ this, from }; }

private:
	void unsafeAdd(const T& value)	{ at(m_iCount++) = value; }

	u32 m_iCount;
	u32 m_iCapacity;
	T* m_pData;
	bool m_bOwning;
};

#define ITERATE_ALL(obj, name) auto name = obj.iter(); !!name; ++name
#define C_ITERATE_ALL(obj, name) auto name = obj.constIter(); !!name; ++name
#define ITERATE(obj, name, sv) auto name = obj.iter(sv); !!name; ++name
#define C_ITERATE(obj, name, sv) auto name = obj.constIter(sv); !!name; ++name