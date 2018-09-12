#include "Parser.hpp"
#include "ParserException.hpp"
#include "format.h"
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include <fstream>

Parser::Parser( void ) : _size(-1), _values(NULL), _lineNumber(0), _valueLinesRemaining(-1), _valueIndex(0)
{ }

Parser::~Parser( void )
{
	delete[] this->_values;
}

int			Parser::parseSize( const std::string & size )
{
	try
	{
		this->_size = std::stoi(size);
		if (!(MIN_SIZE <= this->_size && this->_size <= MAX_SIZE) ||
			size.find('.') != std::string::npos || size.find(',') != std::string::npos)
			throw ParserException("No");
	}
	catch (std::exception & e)
	{
		throw ParserException("Invalid size" CYAN "\n  (must be an integer in [" +
			std::to_string(MIN_SIZE) + ", " + std::to_string(MAX_SIZE) + "]" NORMAL);
	}
	return (this->_size);
}

void		Parser::parseFile ( const std::string & filename )
{
	this->_checkFileExists(filename);
	this->_checkIsDirectory(filename);
	this->_checkHasReadPermission(filename);

	std::ifstream		inputFileStream(filename);
	std::string			line;

	while (std::getline(inputFileStream, line))
		this->_processLine(line);

	if (this->_size == -1)
		throw ParserException("Missing size" CYAN "\n  (must be an integer in [" +
			std::to_string(MIN_SIZE) + ", " + std::to_string(MAX_SIZE) + "]" NORMAL);
	
	if (this->_valueLinesRemaining != 0)
		throw ParserException("Missing some values in [0, " + std::to_string(this->_size * this->_size - 1) + "]");

	this->_validateAllValues();
}

int			Parser::getSize( void ) const
{
	return (this->_size);
}

int *		Parser::getValues( void ) const
{
	return (this->_values);
}

void		Parser::_checkFileExists( const std::string & filename ) const
{
	struct stat s;
	if (stat(filename.c_str(), &s) != 0)
		throw ParserException("No such file or directory");
}

void		Parser::_checkIsDirectory( const std::string & filename ) const
{
	struct stat s;
	stat(filename.c_str(), &s);
	if (s.st_mode & S_IFDIR)
		throw ParserException("Is a directory");
}

void		Parser::_checkHasReadPermission( const std::string & filename ) const
{
	if (access(filename.c_str(), R_OK) != 0)
		throw ParserException("Permission denied");
}

void		Parser::_validateAllValues( void ) const
{
	int		total = this->_size * this->_size;
	bool *	isFilled = new bool[total];

	for (int i = 0; i < total; i++)
		isFilled[i] = false;

	for (int i = 0; i < total; i++)
		isFilled[this->_values[i]] = true;

	for (int i = 0; i < total; i++)
	{
		if (isFilled[i] == false)
		{
			delete[] isFilled;
			throw ParserException("Missing some values in [0, " + std::to_string(this->_size * this->_size - 1) + "]");
		}
	}

	delete[] isFilled;
}

void		Parser::_processLine( std::string & line )
{
	this->_lineNumber++;
	this->_tokens.clear();
	this->_lexer.splitLine(line, this->_tokens);

	if (this->_tokens.size() == 0)
		;
	else if (this->_size == -1)
		this->_parseSizeLine();
	else if (this->_valueLinesRemaining != 0)
		this->_parseValueLine();
}

void		Parser::_parseSizeLine( void )
{
	if (this->_tokens.size() != 1)
		throw ParserException("Invalid size at " MAGENTA "line " + std::to_string(this->_lineNumber) +
			CYAN "\n  (must be an integer in [" +
			std::to_string(MIN_SIZE) + ", " + std::to_string(MAX_SIZE) + "]" NORMAL);

	try
	{
		this->_size = std::stoi(this->_tokens[0]);
		if (!(MIN_SIZE <= this->_size && this->_size <= MAX_SIZE) ||
			this->_tokens[0].find('.') != std::string::npos || this->_tokens[0].find(',') != std::string::npos)
			throw ParserException("No");
	}
	catch (std::exception & e)
	{
		throw ParserException("Invalid size at " MAGENTA "line " + std::to_string(this->_lineNumber) +
			CYAN "\n  (must be an integer in [" +
			std::to_string(MIN_SIZE) + ", " + std::to_string(MAX_SIZE) + "]" NORMAL);
	}

	this->_values = new int[this->_size * this->_size];
	this->_valueLinesRemaining = this->_size;
}

void		Parser::_parseValueLine( void )
{
	if (this->_tokens.size() != static_cast<unsigned long>(this->_size))
		throw ParserException("Invalid number of terms at " MAGENTA "line " + std::to_string(this->_lineNumber) +
			CYAN "\n  (must be " + std::to_string(this->_size) + " integers in [0, " + std::to_string(this->_size * this->_size - 1) + "])" NORMAL);

	try
	{
		for (std::vector<std::string>::iterator it = this->_tokens.begin(); it != this->_tokens.end(); it++)
		{
			int v = std::stoi(*it);
			if (!(0 <= v && v < this->_size * this->_size) ||
				(*it).find('.') != std::string::npos || (*it).find(',') != std::string::npos)
				throw ParserException("No");
			this->_values[this->_valueIndex++] = v;
		}
	}
	catch (std::exception & e)
	{
		throw ParserException("Invalid value at " MAGENTA "line " + std::to_string(this->_lineNumber) +
			CYAN "\n  (must be " + std::to_string(this->_size) + " integers in [0, " + std::to_string(this->_size * this->_size - 1) + "])" NORMAL);
	}

	this->_valueLinesRemaining--;
}
