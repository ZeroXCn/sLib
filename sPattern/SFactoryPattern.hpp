/**
*
*	SFactoryPattern
*	@brief ����ģʽ
*	@author ZEROX
*	@link -
*	@version v1.0
*	@date 2017-12-22
*	@update 2017-12-22
*/
#ifndef _SFACTORYPATTERN_H_
#define _SFACTORYPATTERN_H_

class SSimpleFactory;		//�򵥹���
class SFactoryMethod;		//��������
template<class T>class SAbstractFactory;		//���󹤳�

class SAbstractProduct;				//��Ʒ

///////////////////////////////
/// �򵥹���
/////////////////////////////
class SSimpleFactory
{
protected:
	SSimpleFactory();
	virtual ~SSimpleFactory();
public:
	//������Ʒ
	virtual SAbstractProduct *Create(int nType) = 0;
};



///////////////////////////////
/// ��������
/////////////////////////////
class SFactoryMethod
{
protected:
	SFactoryMethod();
	virtual ~SFactoryMethod();
public:
	virtual SSimpleFactory *Create(int nType) = 0;
};


///////////////////////////////
/// ���󹤳���
/////////////////////////////
template<class T>
class SAbstractFactory
{
protected:
	SAbstractFactory();
	virtual ~SAbstractFactory();
public:
	//������Ʒ
	virtual T *Create();
};
template<class T>
SProduct *SAbstractFactory<T>::Create()
{
	T *product = new T();
	return product;
}

//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////

///////////////////////////////
/// �����Ʒ��
/////////////////////////////
class SAbstractProduct
{
protected:
	SAbstractProduct();
	virtual ~SAbstractProduct();
};

#endif