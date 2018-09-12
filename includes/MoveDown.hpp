#ifndef MOVE_DOWN_HPP
# define MOVE_DOWN_HPP

# include "AMove.hpp"

class MoveDown : public AMove
{
public:

	MoveDown( void );
	~MoveDown( void );

	bool		execute( Board & board ) const;
	void		undo ( Board & board ) const;
	AMove *		clone( void ) const;

private:

	MoveDown( MoveDown const & src );
	MoveDown & operator=( MoveDown const & rhs );

};

#endif
