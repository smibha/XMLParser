/*
 * CText.h
 *
 *  Created on: Nov 25, 2013
 *      Author: smi u
 */

#ifndef CTEXT_H_
#define CTEXT_H_

#include <fstream>

#include "CNode.h"

/* Represents text node of xml document */
class CText : public CNode
{
	friend std::ostream& operator<<(std::ostream& out, const CText& text);

public:

	/* Constructor */
	CText(std::string text = "NoText");

	/* Get the value of text data member of the CText node object */
	const std::string getText() const;

	/* Sets the text data member of the CText node object */
	void setText (std::string text);


	bool parseInput (const std::string &input, size_t &parsePosition);


	void print (uint8_t indent, bool containElementNode);

	/* Get the node type of the CText node object */
	node_t getNodeType() const;

	bool isContainPrintableChar() const;

	void writeTextToFile(std::ostream& out, uint8_t indent, bool val) const;

private:

	/* Data member to store the content of text node */
	std::string m_text;

	/* Data member to store if text contains printable character */
	bool m_containPrintableChar;

};



#endif /* CTEXT_H_ */
