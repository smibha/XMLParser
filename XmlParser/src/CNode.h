/*
 * CNode.h
 *
 *  Created on: Nov 25, 2013
 *      Author: smi u
 */

#ifndef CNODE_H_
#define CNODE_H_

/* enum to store the type of node in xml document */
enum node_t{ELEMENT_NODE, TEXT_NODE};

enum nodeComponents_t{TAG, ATTRIBUTE, VALUE, TEXT};

/* Parent class to different nodes in xml document, helps in storing different nodes in same data structure as all nodes will be derived from this class */
class CNode {

public:

	/* Virtual destructor - deleting a derived class object using base class pointer results in undefined behaviour if it is not virtual */
	virtual ~CNode()
	{
	};

	/* API to get node type of derived objects. It is a pure virtual function */
	virtual node_t getNodeType() const = 0;

protected:

	void removeFromFront(std::string& text, const std::string& chars = " ");
	void removeFromBack(std::string& text, const std::string& chars = " ");
	void trim(std::string& text, const std::string& chars = " ");

	bool checkValTextValidity(const std::string& text, nodeComponents_t nodeComp);
	std::string nodeComponentsToString(nodeComponents_t nodeComp);

};

#endif /* CNODE_H_ */
