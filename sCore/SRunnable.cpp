#include "SRunnable.h"
using namespace std;
SRunnableImpl::SRunnableImpl(function<void(void)> callback) :
	m_callback(callback)
{

}

void SRunnableImpl::Run()
{
	m_callback();
	
}
