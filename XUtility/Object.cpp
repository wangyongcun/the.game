#include "stdafx.h"
#include "Object.h"

using namespace Foundation;


static long g_createdCount = 0;

Object::Object()
: _refCount(0)
{
	_hashCode = InterlockedIncrement(&g_createdCount);
}


Object::Object(const Object& o)
: _refCount(0)
{
	_hashCode = InterlockedIncrement(&g_createdCount);
}