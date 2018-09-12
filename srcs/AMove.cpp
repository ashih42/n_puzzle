#include "AMove.hpp"

AMove::AMove( void ) : _str("")
{ }

AMove::AMove( const std::string & str ) : _str(str)
{ }

AMove::~AMove( void )
{ }

const std::string &		AMove::toString( void ) const
{
	return (this->_str);
}
