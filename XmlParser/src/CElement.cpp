/*
 * CElement.cpp
 *
 *  Created on: Nov 25, 2013
 *      Author: smi u
 */

#include<iostream>
#include <ctype.h>

#include "CElement.h"
#include "CText.h"

CElement::CElement(std::string tag, bool isTagSet, std::string att, std::string val) :
m_contentNodes(0),
m_tag(tag),
m_attribute(att),
m_value(val),
m_tagSet(isTagSet),
m_rootElement(false),
m_containTextNode(false),
m_containElementNode(false),
m_indent(0)
{

}

CElement::~CElement()
{
}

bool CElement::addToContent (CNode *child)
{
	if (m_contentNodes < NESTED_ELEMENT_SIZE)
	{
		m_content[m_contentNodes] = child;
		m_contentNodes++;
		return true;
	}
	else
	{
		std::cout << "ERROR : No memory to store the node element of xml document." << std::endl;
		return false;
	}
}

bool CElement::deleteContent()
{
	if(m_contentNodes == 0)
	{
		std::cout << "ERROR : No entry of node in memory to delete." << std::endl;
		return false;
	}
	m_contentNodes--;
	return true;
}

bool CElement::isRootElement() const
{
	return m_rootElement;
}

void CElement::setRootElement(bool rootElement)
{
	m_rootElement = rootElement;
}

bool CElement::isContainElementNode() const
{
	return m_containElementNode;
}

void CElement::setContainElementNode(bool containElementNode)
{
	m_containElementNode = containElementNode;
}

bool CElement::isContainTextNode() const
{
	return m_containTextNode;
}

void CElement::setContainTextNode(bool containTextNode)
{
	m_containTextNode = containTextNode;
}

bool CElement::parseStartOrEndTag(const std::string &input, size_t &parsePosition, bool &isStartTag, std::string &tag, std::string& attribute, std::string& value)
{
 	if (input[parsePosition] == '<' && input[parsePosition + 1] != '/')
 	{
 		unsigned end = input.find('>', parsePosition + 1);
 		std::string text = input.substr((parsePosition + 1), end - (parsePosition + 1));

 		if(extractTagAttVal(text, tag, attribute, value))
 		{
 	 		parsePosition = end+1;
 	 		isStartTag = true;
 	 		return true;
 		}
 		else
 		{
 			std::cout << "ERROR : Start tag of an element does not follow standard naming convention." << std::endl;
 			return false;
 		}
 	}
 	else if (input[parsePosition] == '<' && input[parsePosition + 1] == '/')
 	{
 		unsigned end = input.find('>', parsePosition + 2);
 		tag = input.substr((parsePosition + 2), end - (parsePosition + 2));
 		trim(tag, " ");
 		parsePosition = end+1;
 		isStartTag = false;
 		return true;
 	}
 	else
 	{
 		std::cout << "ERROR : Improper tag format." << std::endl;
 		return false;
 	}
}

bool CElement::extractTagAttVal(std::string& input, std::string& tag, std::string& attribute, std::string& value)
{
	if(!input.empty())
	{
		std::string::size_type spacePos = input.find_first_of(" \t\r\v\f\n");
		if(spacePos == std::string::npos)
		{
			tag = input;
			if(!checkTagAttValidity(tag, nodeComponents_t::TAG))
				return false;
			return true;
		}
		else
		{
			tag = input.substr(0, spacePos);
			if(!checkTagAttValidity(tag, nodeComponents_t::TAG))
				return false;
			std::string::size_type attStartPos = input.find_first_not_of(" \t\r\v\f\n", spacePos+1);
			if(attStartPos != std::string::npos)
			{
				std::string::size_type attEndPos = input.find("=", attStartPos+1);
				if(attEndPos != std::string::npos)
				{
					attribute = input.substr(attStartPos, attEndPos-attStartPos);
					attribute.erase(attribute.find_last_not_of(" \t\r\v\f\n")+1);
					if(!checkTagAttValidity(attribute, nodeComponents_t::ATTRIBUTE))
						return false;

					std::string::size_type valStartPos = input.find_first_not_of(" \t\r\v\f\n", attEndPos+1);
					if(input.at(valStartPos) == '\"')
					{
						std::string::size_type valEndPos = input.find("\"", valStartPos+1);
						if(valEndPos != std::string::npos)
						{
							value = input.substr(valStartPos+1, valEndPos-(valStartPos+1));
							if(!checkValTextValidity(value, nodeComponents_t::VALUE))
								return false;
						}
						else
						{
							std::cout << "ERROR : Value should end with \"." << std::endl;
						}
					}
					else
					{
						std::cout << "ERROR : Attribute should be followed by value in \"\"." << std::endl;
						return false;
					}
				}
				else
				{
					std::cout << "ERROR : Attribute should be followed by = ." << std::endl;
					return false;
				}

				return true;
			}
			return true;
		}
	}
	else
	{
		std::cout << "ERROR : Element name cannot be null." << std::endl;
		return false;
	}
}

const std::string& CElement::getAttribute() const
{
	return m_attribute;
}

const std::string& CElement::getTag() const
{
	return m_tag;
}

const std::string& CElement::getValue() const
{
	return m_value;
}

CNode* const* CElement::getContent() const
{
	return m_content;
}

int CElement::getContentNodes() const
{
	return m_contentNodes;
}

void CElement::setContentNodes(int contentNodes)
{
	m_contentNodes = contentNodes;
}

node_t CElement::getNodeType() const
{
	return node_t::ELEMENT_NODE;
}

bool CElement::checkTagAttValidity(const std::string& tag, nodeComponents_t comp)
{
	/* Check if tag name starts with either letter or underscore */
	if(!((64 < tag.at(0) && tag.at(0) < 91) || (96 < tag.at(0) && tag.at(0) < 123) || (tag.at(0) == 95)))
	{
		std::cout << "ERROR : Illegal " << nodeComponentsToString(comp) << " beginning." << std::endl;
		return false;
	}

	/* Check if tag name starts with letters xml */
	if(tag.at(0) == 88 || tag.at(0) == 120)
	{
		if(tag.at(1) == 77 || tag.at(1) == 109)
		{
			if(tag.at(2) == 76 || tag.at(2) == 108)
			{
				std::cout<<"ERROR : " << nodeComponentsToString(comp) << " cannot start with letters xml." << std::endl;
				return false;
			}
		}
	}

	/* Check if characters in tag name are legal */
	for (unsigned int i = 1; i < tag.length(); i++)
	{
		if (!((64 < tag.at(i) && tag.at(i) < 91) || (96 < tag.at(i) && tag.at(i) < 123) || (tag.at(i) == 95) || (47 < tag.at(i) && tag.at(i) < 58) || (44 < tag.at(i) && tag.at(i) < 47)))
		{
			std::cout<<"ERROR : Illegal " << nodeComponentsToString(comp) << " character." << std::endl;
			return false;
		}
	}
	return true;
}

bool CElement::parseInput(const std::string &input, size_t &parsePosition)
{
	/*TODO Tell where the problem is*/
	bool isStartTag = false;
	std::string tag = "NoTag";
	std::string attribute = "NoAttribute";
	std::string value = "NoValue";

	while(m_contentNodes < NESTED_ELEMENT_SIZE)
	{
		if(parsePosition == input.find('<', parsePosition))
		{
			if(parseStartOrEndTag(input, parsePosition, isStartTag, tag, attribute, value))
			{
				if(!this->m_tagSet && isStartTag)
				{
					this->m_tag = tag;
					this->m_tagSet = true;
					this->m_attribute = attribute;
					this->m_value = value;
				}
				else if(!isStartTag)
				{
					if(this->m_tag == tag)
						return true;
					else
					{
						m_contentNodes--;
						std::cout << "ERROR : Start tag != End tag." << std::endl;
						return false;
					}
				}
				else
				{
					CElement* ele = new CElement(tag, true, attribute, value);
					this->setContainElementNode(true);
					if(!this->addToContent(ele))
						return false;
					if(!ele->parseInput(input, parsePosition))
					{
						/* Delete added entry from m_content */
						this->deleteContent();
						return false;
					}
				}
			}
			else
				return false;
		}
		else
		{
			CText* txt = new CText;
			this->setContainTextNode(true);
			if(!addToContent(txt))
				return false;
			if(!txt->parseInput(input, parsePosition))
			{
				m_contentNodes--;
				return false;
			}

		}
	}
	std::cout << "ERROR : No memory to store more element nodes." << std::endl;
	return false;
}

void CElement::print(uint8_t indent) const
{
	int temp = indent;
	while(temp)
	{
		std::cout << "-";
		temp--;
	}

	std::cout << "<" << m_tag;
	if(m_attribute.compare("NoAttribute") && m_value.compare("NoValue"))
	{
		std::cout << " " << m_attribute << " = \"" << m_value << "\"" ;
	}
	std::cout << ">";

	for(int i = 0; i < m_contentNodes; i++)
	{
		switch(m_content[i]->getNodeType())
		{
		case 0:
		{
			CElement* ele = dynamic_cast<CElement*>(m_content[i]);
			indent += 3;
			std::cout << std::endl;
			ele->print(indent);
			indent -= 3;
			break;
		}
		case 1:
		{
			CText* txt = dynamic_cast<CText*>(m_content[i]);
			indent += 3;
			txt->print(indent, this->isContainElementNode());
			indent -= 3;
			break;
		}
		default:
		{
			std::cout<<"ERROR : Not valid node."<< std::endl;
			break;
		}
		}
	}
	if(m_containElementNode && m_containTextNode)
	{
		std::cout << std::endl;
		while(indent)
		{
			std::cout << "-";
			indent--;
		}
	}
	std::cout << "</" << m_tag << ">";
}

void CElement::writeElementToFile(std::ostream& out, uint8_t indent) const
{
	int temp = indent;
	while(temp)
	{
		out << "-";
		temp--;
	}

	out << "<" << m_tag;
	if(m_attribute.compare("NoAttribute") && m_value.compare("NoValue"))
	{
		out << " " << m_attribute << " = \"" << m_value << "\"" ;
	}
	out << ">";

	for(int i = 0; i < m_contentNodes; i++)
	{
		switch(m_content[i]->getNodeType())
		{
		case 0:
		{
			CElement* ele = dynamic_cast<CElement*>(m_content[i]);
			indent += 3;
			out << std::endl;
			ele->writeElementToFile(out, indent);
			indent -= 3;
			break;
		}
		case 1:
		{
			CText* txt = dynamic_cast<CText*>(m_content[i]);
			indent += 3;
			txt->writeTextToFile(out, indent, this->isContainElementNode());
			indent -= 3;
			break;
		}
		default:
		{
			std::cout<<"ERROR : Not valid node."<< std::endl;
			break;
		}
		}
	}
	if(m_containElementNode && m_containTextNode)
	{
		out << std::endl;
		while(indent)
		{
			out << "-";
			indent--;
		}
	}
	out << "</" << m_tag << ">";
}

std::ostream& operator<<(std::ostream& out, const CElement& element)
{
/*	uint8_t temp = element.m_indent;
	while(temp)
	{
		out << "-";
		temp--;
	}

	out << "<" << element.getTag();
	if(element.getAttribute().compare("NoAttribute") && element.getValue().compare("NoValue"))
	{
		out << " " << element.getAttribute() << " = \"" << element.getValue() << "\"";
	}
	out << ">";

	for(int i = 0; i < element.getContentNodes(); i++)
	{
		switch(m_content[i]->getNodeType())
		{
		case 0:
		{
			CElement* ele = dynamic_cast<CElement*>(m_content[i]);
			indent += 3;
			out << std::endl;
			out << ele;
			indent -= 3;
			break;
		}
		case 1:
		{
			CText* txt = dynamic_cast<CText*>(m_content[i]);
			indent += 3;
			txt->writeTextToFile(out, indent, this->isContainElementNode());
			indent -= 3;
			break;
		}
		default:
		{
			std::cout<<"ERROR : Not valid node."<< std::endl;
			break;
		}
		}
	}
	if(element.isContainElementNode() && element.isContainTextNode())
	{
		out << std::endl;
		while(element.m_indent)
		{
			out << "-";
			element.m_indent--;
		}
	}
	out << "</" << element.getTag() << ">";*/

	return out;
}
