#include "VisualizerInitializationException.hpp"

VisualizerInitializationException::
	VisualizerInitializationException( std::string errorMessage ) : _errorMessage(errorMessage)
{ }

VisualizerInitializationException::
	~VisualizerInitializationException( void ) _NOEXCEPT
{ }

VisualizerInitializationException::
	VisualizerInitializationException( VisualizerInitializationException const & src )
{
	*this = src;
}

VisualizerInitializationException & VisualizerInitializationException::operator=
	( VisualizerInitializationException const & rhs )
{
	this->_errorMessage = rhs._errorMessage;
	return (*this);
}

const char *		VisualizerInitializationException::what( void ) const throw()
{
	return (this->_errorMessage.c_str());
}
