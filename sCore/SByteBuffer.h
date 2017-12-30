/**
*
*	SByteArray��
*	byte���ݵĴ���
*	@author ZeroX
*	@version v1.0 22/07/2017()
*
*/
#include "SObject.h"
#ifndef _SBYTEBUFFER_H_
#define _SBYTEBUFFER_H_
#include <vector>


//TODO:������
typedef std::vector<byte> SByteArray;
class SByteBuffer :
	public SObject,
	private SByteArray
{
public:
	template<class InputIterator>SByteBuffer(InputIterator begin, InputIterator end) :SByteArray(begin, end){};
	SByteBuffer();
	SByteBuffer(SByteBuffer &src);

public:
	//��������
	SByteBuffer &put(byte dat);
	SByteBuffer &put(int index, byte dat);
	SByteBuffer &put(byte *dat,int length=-1);
	SByteBuffer &put(byte *dat,int offset,int length);
	SByteBuffer &put(SByteBuffer &src);

	//���ص�ǰλ��
	byte get();
	byte get(int index);
	SByteBuffer get(int offset, int length);

	//ȡ�ó���
	size_t length();

	//ȡ��ռ���ڴ��С(��λ-Byte)
	size_t size();

	//���
	void clear();
	//ȡ������
	byte *toArray();
	SString toString();
public:
	//ȡ��
	byte &operator [](int index);
};

#endif