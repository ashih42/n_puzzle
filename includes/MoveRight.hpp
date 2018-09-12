#ifndef MOVE_RIGHT_HPP
# define MOVE_RIGHT_HPP

# include "AMove.hpp"

class MoveRight : public AMove
{
public:

	MoveRight( void );
	~MoveRight( void );

	bool		execute( Board & board ) const;
	void		undo ( Board & board ) const;
	AMove *		clone( void ) const;

private:

	MoveRight( MoveRight const & src );
	MoveRight & operator=( MoveRight const & rhs );

};

#endif
