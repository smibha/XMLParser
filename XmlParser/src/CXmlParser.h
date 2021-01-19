/*
 * CXmlParser.h
 *
 *  Created on: Nov 25, 2013
 *      Author: smi u
 */

#ifndef CXMLPARSER_H_
#define CXMLPARSER_H_

#include "CElement.h"

class CXmlParser
{

public:

	CXmlParser();

	~CXmlParser();

	bool parseXml(const char *filename);

	void outputParsedXml(const char *filename) const;

private:

	CElement m_element;

};

#endif /* CXMLPARSER_H_ */
