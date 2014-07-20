#pragma once

namespace Foundation
{
	//智能指针模版所需要使用的类
	class IObject
	{
	public:
		virtual void AddRef() = 0;
		virtual void Release() = 0;
		virtual long GetHashCode() const = 0;
	};

	class  Object
	{
	public:
		Object();
		Object(const Object& o);
		virtual ~Object() {}
		
		void AddRef()
		{
			++_refCount;
		}

		void Release()
		{
			long result = --_refCount;
			if(result == 0)
			{
				delete this;
			}
		}

		virtual long GetHashCode() const
		{
			return _hashCode;
		}

		long GetReferenceCount() const
		{
			return _refCount; 
		}
	protected:
		long _refCount;
		long _hashCode;
		
	};

	template<class T>
	class TObjectImpl : public T, public Object
	{
	public:
		virtual void AddRef()
		{
			Object::AddRef();
		}
		virtual void Release()
		{
			Object::Release();
		}
		virtual long GetHashCode() const
		{
			return Object::GetHashCode();
		}
	};
}

#define ImplementClass(classname) \
class classname; \
	typedef Foundation::TObjectImpl<classname> classname##I;

#define ImplementIObject \
	public: \
		virtual void AddRef() \
		{ \
			Object::AddRef(); \
		} \
		virtual void Release() \
		{ \
			Object::Release(); \
		} \
		virtual long GetHashCode() const \
		{ \
			return Object::GetHashCode(); \
		}

