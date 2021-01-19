/*
 * CNode.cpp
 *
 *  Created on: Nov 25, 2013
 *      Author: smi u
 */
#include <string>
#include <iostream>

#include "CNode.h"

void CNode::removeFromFront(std::string &text, const std::string &chars)
{
	text.erase(0, text.find_first_not_of(chars));
}

void CNode::removeFromBack(std::string &text, const std::string &chars)
{
	text.erase(text.find_last_not_of(chars)+1);
}

void CNode::trim(std::string &text, const std::string &chars)
{
	removeFromBack(text, chars);
	removeFromFront(text, chars);
}

bool CNode::checkValTextValidity(const std::string &text, nodeComponents_t nodeComp)
{
	size_t index = text.find_first_of(">\"");
	if(index == std::string::npos)
		return true;
	std::cout << "ERROR : " << nodeComponentsToString(nodeComp) << " contains illegal character."<< std::endl;
	return false;
}

std::string CNode::nodeComponentsToString(nodeComponents_t nodeComp)
{
	switch(nodeComp)
	{
	case nodeComponents_t::TAG:
		return "tag";
	case nodeComponents_t::ATTRIBUTE:
		return "attribute";
	case nodeComponents_t::VALUE:
		return "value";
	case nodeComponents_t::TEXT:
		return "text";
	default:
		return "WRONG_NODE_COMPONENT";
	}
}
