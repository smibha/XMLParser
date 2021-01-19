/*
 * CText.cpp
 *
 *  Created on: Nov 25, 2013
 *      Author: smi u
 */

#include <iostream>
#include <ctype.h>
#include <iomanip>

#include "CText.h"

CText::CText(std::string text) : m_text("NoText"), m_containPrintableChar(false)
{
}

const std::string CText::getText() const
{
	return this->m_text;
}

void CText::setText(std::string text)
{
	trim(text, " \t\r\v\f\n");
	if(!text.empty())
	{
		this->m_containPrintableChar = true;
		m_text = text;
	}

}

bool CText::parseInput(const std::string &input, size_t &parsePosition)
{
	size_t end = input.find("<", parsePosition);
	if(end == std::string::npos)
		return false;
	std::string text = input.substr(parsePosition, end-parsePosition);
	/*TODO tell where the problem is */
	if(!checkValTextValidity(text, nodeComponents_t::TEXT))
		return false;
	this->setText(text);
	parsePosition = end;
	return true;
}

void CText::print(uint8_t indent, bool containElementNode)
{
	if(this->m_containPrintableChar)
	{
		if(containElementNode)
		{
			std::cout << std::endl;
			uint8_t temp = indent;
			while(temp)
			{
				std::cout << "-";
				temp--;
			}
		}
		std::cout << m_text;
	}
}

node_t CText::getNodeType() const
{
	return node_t::TEXT_NODE;
}

std::ostream& operator<<(std::ostream& out, const CText& text)
{
	if(text.m_containPrintableChar)
	{
//		if(containElementNode)
//		{
//			out << std::endl;
//			uint8_t temp = indent;
//			while(temp)
//			{
//				out << "-";
//				temp--;
//			}
//		}
		out << text.m_text;
	}
	return out;
}

bool CText::isContainPrintableChar() const
{
	return m_containPrintableChar;
}

void CText::writeTextToFile(std::ostream& out, uint8_t indent, bool val) const
{
	if(this->m_containPrintableChar)
	{
		if(val)
		{
			out << std::endl;
			uint8_t temp = indent;
			while(temp)
			{
				out << "-";
				temp--;
			}
		}
		out << m_text;
	}
}
