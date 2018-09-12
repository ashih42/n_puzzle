#ifndef MOVE_LEFT_HPP
# define MOVE_LEFT_HPP

# include "AMove.hpp"

class MoveLeft : public AMove
{
public:

	MoveLeft( void );
	~MoveLeft( void );

	bool		execute( Board & board ) const;
	void		undo ( Board & board ) const;
	AMove *		clone( void ) const;

private:

	MoveLeft( MoveLeft const & src );
	MoveLeft & operator=( MoveLeft const & rhs );

};

#endif
