/*
 * CFileIO.cpp
 *
 *  Created on: Nov 25, 2013
 *      Author: smi u
 */

#include <iostream>

#include "CFileIO.h"
#include "CNode.h"

bool CFileIO::s_prolog = false;

CFileIO::CFileIO()
{
	m_openMode = t_openMode::UNDEFINED;
	m_fileStream.clear();
}

CFileIO::CFileIO(const char *filename, t_openMode mode)
{
	openFile(filename, mode);
}

CFileIO::~CFileIO()
{
	closeFile();
}

bool CFileIO::openFile(const char *filename, t_openMode mode)
{
	switch(mode)
	{
	case IN:
		m_fileStream.open(filename, std::ios::in);
		m_fileStream.seekg(0);
		break;
	case OUT:
		m_fileStream.open(filename, std::ios::out | std::ios::trunc);
		m_fileStream.seekp(0);
		break;
	default:
		std::cout << "ERROR : File mode is not supported." << std::endl;
	}
	m_openMode = mode;
	if(m_fileStream.is_open())
	{
		return true;
	}
	std::cout << "ERROR : Opening file failed." << std::endl;
	return false;
}

bool CFileIO::closeFile()
{
	if(m_fileStream.is_open()) m_fileStream.close();
	return true;
}

bool CFileIO::readFile(std::string& readFromFile)
{
	if(m_fileStream.is_open())
	{
		std::string temp;
		while(!m_fileStream.eof())
		{
			getline(m_fileStream, temp);
			readFromFile += temp;
		}
		return true;
	}
	else
	{
		std::cout << "ERROR : File is not open. Reading from the file failed." << std::endl;
		return false;
	}
}

bool CFileIO::writeFile(const CElement* ele, uint8_t indent)
{
	if(m_fileStream.is_open())
	{
		if(!s_prolog)
		{
			m_fileStream << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl;
			s_prolog = true;
		}
		int temp = indent;
		while(temp)
		{
			m_fileStream << "-";
			temp--;
		}

		m_fileStream << "<" << ele->getTag();
		if(ele->getAttribute().compare("NoAttribute") && ele->getValue().compare("NoValue"))
		{
			m_fileStream << " " << ele->getAttribute() << " = \"" << ele->getValue() << "\"" ;
		}
		m_fileStream << ">";

		for(int i = 0; i < ele->getContentNodes(); i++)
		{
			switch( (*(ele->getContent()+i))->getNodeType())
			{
			case 0:
			{
				CElement* element = dynamic_cast<CElement*>((*(ele->getContent()+i)));
				indent += 3;
				m_fileStream << std::endl;
				writeFile(element, indent);
				indent -= 3;
				break;
			}
			case 1:
			{
				CText* txt = dynamic_cast<CText*>((*(ele->getContent()+i)));
				indent += 3;
				writeFileText(txt, indent, ele->isContainElementNode());
				indent -= 3;
				break;
			}
			default:
			{
				m_fileStream <<"ERROR : Not valid node."<< std::endl;
				break;
			}
			}
		}
		if(ele->isContainTextNode() && ele->isContainElementNode())
		{
			m_fileStream << std::endl;
			while(indent)
			{
				m_fileStream << "-";
				indent--;
			}
		}
		m_fileStream << "</" << ele->getTag() << ">";
		return true;
	}
	else
	{
		std::cout << "ERROR : File is not open. Writing to the file failed." << std::endl;
		return false;
	}
}

bool CFileIO::writeFileText(const CText* txt, uint8_t indent, bool val)
{
	if(m_fileStream.is_open())
	{
		if(txt->isContainPrintableChar())
		{
			if(val)
			{
				m_fileStream << std::endl;
				uint8_t temp = indent;
				while(temp)
				{
					m_fileStream << "-";
					temp--;
				}
			}
			std::string text = txt->getText();
			m_fileStream << text;
		}
		return true;
	}
	else
	{
		std::cout << "ERROR : File is not open. Writing to the file failed." << std::endl;
		return false;
	}
	return true;
}

void CFileIO::setProlog(bool prolog)
{
	s_prolog = prolog;
}
