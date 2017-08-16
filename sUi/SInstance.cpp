#include "SInstance.h"

SInstance::SInstance()
{
	m_hInstance = NULL;
}
SInstance::SInstance(HINSTANCE hInstance)
{
	m_hInstance = hInstance;
}
SInstance::~SInstance()
{

}

HINSTANCE SInstance::GetHandle()
{
	return m_hInstance;
}
void SInstance::SetHandle(HINSTANCE hInstance)
{
	m_hInstance = hInstance;
}