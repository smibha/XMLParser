/*
 *  main.cpp
 *
 *  Created on: Nov 25, 2013
 *      Author: smi u
 */

#include <iostream>

#include "CXmlParser.h"

int main (void)
{
	std::cout << "==========================================================================" << std::endl;
	std::cout << "                                 XML Parser                               " << std::endl;
	std::cout << "==========================================================================" << std::endl << std::endl;

	CXmlParser xmlParser;
	std::string filename = "xml_input.txt";
	if(xmlParser.parseXml(filename.c_str()))
		xmlParser.outputParsedXml("xml_output.txt");
	return 0;
}
