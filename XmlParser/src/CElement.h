/*
 * CElement.h
 *
 *  Created on: Nov 25, 2013
 *      Author: smi u
 */

#ifndef CELEMENT_H_
#define CELEMENT_H_

#include <string>
#include <vector>
#include <fstream>

#include "CNode.h"

#define NESTED_ELEMENT_SIZE 50

class CElement : public CNode
{

	friend std::ostream& operator<<(std::ostream& out, const CElement& element);

public:

	CElement(std::string tag = "NoTag", bool isTagSet = false, std::string att = "NoAttribute", std::string val = "NoValue");

	~CElement();

	bool parseInput(const std::string& input, size_t& parsePosition);

	void print(uint8_t indent = 0) const;

	node_t getNodeType() const;

	bool isRootElement() const;

	void setRootElement(bool rootElement);

	bool isContainElementNode() const;

	void setContainElementNode(bool containElementNode);

	bool isContainTextNode() const;

	void setContainTextNode(bool containTextNode);

	int getContentNodes() const;

	void setContentNodes(int contentNodes);

	const std::string& getAttribute() const;

	const std::string& getTag() const;

	const std::string& getValue() const;

	CNode* const* getContent() const;
//	CNode* const*& getContent() const;
//	const CNode**& getContent() const;
//	const CNode** getContent() const;

	/* 2nd way to write to output file */
	void writeElementToFile(std::ostream& out, uint8_t indent = 0) const;


private:

	/*TODO Replace with STL*/
	CNode* m_content[NESTED_ELEMENT_SIZE];

	int m_contentNodes;

	std::string m_tag;

	std::string m_attribute;

	std::string m_value;

	bool m_tagSet;

	bool m_rootElement;

	bool m_containTextNode;

	bool m_containElementNode;

	uint8_t m_indent;

	bool addToContent(CNode* child);

	bool deleteContent();

	bool parseStartOrEndTag(const std::string& input, size_t& parsePosition, bool& isStartTag, std::string& tag, std::string& attribute, std::string& value);

	bool extractTagAttVal(std::string& input, std::string& tag, std::string& attribute, std::string& value);

	bool extractTag(std::string& input, std::string& tag);

	/*TODO - extract tag and rest separately to support multiple attribute and vale pairs */
	bool extractAttVal(std::string& input, std::string& attribute, std::string& value);

	bool checkTagAttValidity(const std::string& tag, nodeComponents_t comp);

};

#endif /* CELEMENT_H_ */
