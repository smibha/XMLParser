/*
 * CXmlParser.cpp
 *
 *  Created on: Nov 25, 2013
 *      Author: smi u
 */

#include <iostream>

#include "CXmlParser.h"
#include "CElement.h"
#include "CFileIO.h"

#define TYPE_ONE
//#define TYPE_TWO
//#define TYPE_THREE

CXmlParser::CXmlParser()
{
}

CXmlParser::~CXmlParser()
{
}

bool CXmlParser::parseXml(const char *filename)
{
	CFileIO file;
	file.openFile(filename, t_openMode::IN);

	std::string readFromFile;
	if(file.readFile(readFromFile))
	{
		size_t pos = readFromFile.find('<');
		if(pos != 0)
		{
			std::cout << "ERROR : Content is not allowed in the prolog." << std::endl;
			return false;
		}
		m_element.setRootElement(true);
		if(!m_element.parseInput(readFromFile, pos))
		{
			std::cout << "ERROR : XML document provided is not in proper format. Therefore parsing failed." << std::endl;
			return false;
		}
		return true;
	}
	else
		return false;
}

void CXmlParser::outputParsedXml(const char *filename) const
{
	if(m_element.getContentNodes() != 0)
	{
		std::cout << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl;
		m_element.print();
	}

#ifdef TYPE_ONE
	/* TYPE 1: Implement by writing file function which takes const element obj as parameter in separate file handling class */
	CFileIO file;
	file.openFile(filename, t_openMode::OUT);
	file.writeFile(&m_element);
	file.setProlog(false);
#endif

#ifdef TYPE_TWO
	/* TYPE 2: Implement by writing file function as member function of class CElement */
	std::fstream out;
	out.open(filename, std::ios::out | std::ios::trunc);
	out.seekp(0);
	m_element.writeElementToFile(out);
	out.close();
#endif

#ifdef TYPE_THREE
	/*TODO TYPE 3: Implement using overloading operators */
	std::fstream out;
	out.open(filename, std::ios::out | std::ios::trunc);
	out.seekp(0);
	out << m_element;
	out.close();
#endif

}
