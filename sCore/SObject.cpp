#include "SObject.h"

SString SObject::ToString()
{
	return SString::Format(_T("%d"),this);
}