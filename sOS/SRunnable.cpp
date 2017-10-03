#include "SRunnable.h"
using namespace std;

SRunnableImpl::SRunnableImpl()
{
	m_fCallback = [=](){};
}
SRunnableImpl::SRunnableImpl(function<void(void)> callback) :
	m_fCallback(callback)
{

}

SRunnableImpl::~SRunnableImpl()
{

}
void SRunnableImpl::Run(std::function<void(void)> fCallback)
{
	m_fCallback = fCallback;
}

void SRunnableImpl::Run()
{
	m_fCallback();
	
}
