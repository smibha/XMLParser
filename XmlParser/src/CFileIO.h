/*
 * CFileIO.h
 *
 *  Created on: Nov 25, 2013
 *      Author: smi u
 */

#ifndef CFILEIO_H_
#define CFILEIO_H_

#include <fstream>

#include "CElement.h"
#include "CText.h"

enum t_openMode{IN, OUT, UNDEFINED};

class CFileIO
{

public:

	CFileIO();

	CFileIO(const char *filename, t_openMode mode);

	~CFileIO();

	bool openFile(const char *filename, t_openMode mode);

	bool closeFile();

	bool readFile(std::string& reafFromFile);

	bool writeFile(const CElement* ele, uint8_t indent = 0);

	bool writeFileText(const CText* txt, uint8_t indent, bool val);

	static void setProlog(bool prolog);

private:

	std::fstream m_fileStream;

	t_openMode m_openMode;

	static bool s_prolog;

};

#endif /* CFILEIO_H_ */
