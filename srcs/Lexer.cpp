#include "Lexer.hpp"
#include <sstream>

Lexer::Lexer( void ) { }

Lexer::~Lexer( void ) { }

void	Lexer::splitLine( std::string & line, std::vector<std::string> & tokens ) const
{
	std::string::size_type	semicolonPos = line.find("#");

	if (semicolonPos != std::string::npos)
		line = line.substr(0, semicolonPos);

	std::istringstream		iss(line);

	for (std::string s; iss >> s; )
		tokens.push_back(s);
}
