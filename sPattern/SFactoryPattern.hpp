/**
*
*	SFactoryPattern
*	@brief 工厂模式
*	@author ZEROX
*	@link -
*	@version v1.0
*	@date 2017-12-22
*	@update 2017-12-22
*/
#ifndef _SFACTORYPATTERN_H_
#define _SFACTORYPATTERN_H_

class SSimpleFactory;		//简单工厂
class SFactoryMethod;		//工厂方法
template<class T>class SAbstractFactory;		//抽象工厂

class SAbstractProduct;				//产品

///////////////////////////////
/// 简单工厂
/////////////////////////////
class SSimpleFactory
{
protected:
	SSimpleFactory();
	virtual ~SSimpleFactory();
public:
	//产生产品
	virtual SAbstractProduct *Create(int nType) = 0;
};



///////////////////////////////
/// 工厂方法
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
/// 抽象工厂类
/////////////////////////////
template<class T>
class SAbstractFactory
{
protected:
	SAbstractFactory();
	virtual ~SAbstractFactory();
public:
	//产生产品
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
/// 抽象产品类
/////////////////////////////
class SAbstractProduct
{
protected:
	SAbstractProduct();
	virtual ~SAbstractProduct();
};

#endif