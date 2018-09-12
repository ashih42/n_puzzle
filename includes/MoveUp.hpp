#ifndef MOVE_UP_HPP
# define MOVE_UP_HPP

# include "AMove.hpp"

class MoveUp : public AMove
{
public:

	MoveUp( void );
	~MoveUp( void );

	bool		execute( Board & board ) const;
	void		undo ( Board & board ) const;
	AMove *		clone( void ) const;

private:

	MoveUp( MoveUp const & src );
	MoveUp & operator=( MoveUp const & rhs );

};

#endif
