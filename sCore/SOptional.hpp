/**
*
*	SOptional类
*	实现未初始化概念
*	@author qicosmos
*	@link http://www.cnblogs.com/qicosmos/p/3577449.html
*	@version v1.0 
*
*/
#include "SObject.h"

#ifndef _SOPTIONAL_H_
#define _SOPTIONAL_H_

#include <type_traits>

template<typename T>
class SOptional:public SObject
{
	using data_t = typename std::aligned_storage<sizeof(T), std::alignment_of<T>::value>::type;
public:
	SOptional() : m_hasInit(false) {}
	SOptional(const T& v)
	{
		Create(v);
	}

	SOptional(T&& v) : m_hasInit(false)
	{
		Create(std::move(v));
	}

	~SOptional()
	{
		Destroy();
	}

	SOptional(const SOptional& other) : m_hasInit(false)
	{
		if (other.IsInit())
			Assign(other);
	}

	SOptional(SOptional&& other) : m_hasInit(false)
	{
		if (other.IsInit())
		{
			Assign(std::move(other));
			other.Destroy();
		}
	}

	SOptional& operator=(SOptional &&other)
	{
		Assign(std::move(other));
		return *this;
	}

	SOptional& operator=(const SOptional &other)
	{
		Assign(other);
		return *this;
	}

	template<class... Args>
	void emplace(Args&&... args)
	{
		Destroy();
		Create(std::forward<Args>(args)...);
	}

	bool IsInit() const { return m_hasInit; }

	explicit operator bool() const {
		return IsInit();

	}

	T& operator*()
	{
		return *((T*)(&m_data));
	}

	T const& operator*() const
	{
		if (IsInit())
		{
			return *((T*)(&m_data));
		}

		throw std::exception("");
	}

	bool operator == (const SOptional<T>& rhs) const
	{
		return (!bool(*this)) != (!rhs) ? false : (!bool(*this) ? true : (*(*this)) == (*rhs));
	}

	bool operator < (const SOptional<T>& rhs) const
	{
		return !rhs ? false : (!bool(*this) ? true : (*(*this) < (*rhs)));
	}

	bool operator != (const SOptional<T>& rhs)
	{
		return !(*this == (rhs));
	}
private:
	template<class... Args>
	void Create(Args&&... args)
	{
		new (&m_data) T(std::forward<Args>

			(args)...);
		m_hasInit = true;
	}

	void Destroy()
	{
		if (m_hasInit)
		{
			m_hasInit = false;
			((T*)(&m_data))->~T();
		}
	}

	void Assign(const SOptional& other)
	{
		if (other.IsInit())
		{
			Copy(other.m_data);
			m_hasInit = true;
		}
		else
		{
			Destroy();
		}
	}

	void Assign(SOptional&& other)
	{
		if (other.IsInit())
		{
			Move(std::move(other.m_data));
			m_hasInit = true;
			other.Destroy();
		}
		else
		{
			Destroy();
		}
	}

	void Move(data_t&& val)
	{
		Destroy();
		new (&m_data) T(std::move(*((T*)

			(&val))));
	}

	void Copy(const data_t& val)
	{
		Destroy();
		new (&m_data) T(*((T*)(&val)));
	}

private:
	bool m_hasInit;
	data_t m_data;
};

#endif