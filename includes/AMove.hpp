#ifndef AMOVE_HPP
# define AMOVE_HPP

# include <iostream>
# include "Board.hpp"

class AMove
{
public:

	AMove( void );
	AMove( const std::string & str );
	virtual ~AMove( void );

	virtual bool		execute( Board & board ) const = 0;
	virtual void		undo( Board & board ) const = 0;
	virtual AMove *		clone( void ) const = 0;

	const std::string &	toString( void ) const;

private:

	std::string			_str;

	AMove( AMove const & src );
	AMove & operator=( AMove const & rhs );

};

#endif
