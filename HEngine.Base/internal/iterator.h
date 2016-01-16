#pragma once
#include "common.h"
#include <functional>

template <class T> using DTMatches = std::function<bool(const T&)>;

template <class T>
class ConstIterator
{
public:
	virtual ~ConstIterator() {}
	virtual const T& get() const = 0;
	virtual void next() = 0;
	virtual bool end() const = 0;

	const T& operator()() const { return get(); }
	bool operator!() const { return end(); }
	void operator++() { next(); }
	u32 countIterated() const { return m_iCountIterated;  };

	u32 countValues(const T& value)
	{
		u32 c = 0;
		for (;!!this;++this)
		{
			if (this() == value)
				++c;
		}
		return c;
	}
	u32 count(DTMatches<T> func)
	{
		u32 c = 0;
		for (;!!this;++this)
		{
			if (func(this()))
				++c;
		}
		return c;
	}
	const T* firstOrDefault(DTMatches<T> func, const T* defvalue = nullptr)
	{
		for (;!!this;++this)
		{
			auto o = &this();
			if (func(*o))
			{
				return o;
			}
		}
		return defvalue;
	}
protected:
	u32 m_iCountIterated = 0;
};

template <class T>
class Iterator : public ConstIterator<T>
{
public:
	virtual T& get() = 0;

	T& operator()() { return get(); }
};