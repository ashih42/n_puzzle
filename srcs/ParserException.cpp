#include "ParserException.hpp"

ParserException::
	ParserException( std::string errorMessage ) : _errorMessage(errorMessage)
{ }

ParserException::
	~ParserException( void ) _NOEXCEPT
{ }

ParserException::
	ParserException( ParserException const & src )
{
	*this = src;
}

ParserException & ParserException::operator=
	( ParserException const & rhs )
{
	this->_errorMessage = rhs._errorMessage;
	return (*this);
}

const char *		ParserException::what( void ) const throw()
{
	return (this->_errorMessage.c_str());
}
