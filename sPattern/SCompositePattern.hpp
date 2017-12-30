#ifndef _SCOMPOSITEPATTERN_H_
#define _SCOMPOSITEPATTERN_H_
#include <vector>

class SAbstractNode;		//³éÏó½áµã

class SAbstractNode
{
public:
	virtual void AddNode(SAbstractNode *pNode);

	virtual void RemoveNode(SAbstractNode *pNode);
private:
	std::vector<SAbstractNode *>		m_NodeList;	
};

#endif