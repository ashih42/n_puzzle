#include "MoveUp.hpp"

MoveUp::MoveUp( void ) : AMove("U")
{ }

MoveUp::~MoveUp( void ) { }

bool	MoveUp::execute( Board & board ) const
{
	bool	success = board._swapEmptyWith(board._emptyPosX, board._emptyPosY + 1);

	if (success)
		board._distanceFromStart++;
	return (success);
}

void	MoveUp::undo( Board & board ) const
{
	board._swapEmptyWith(board._emptyPosX, board._emptyPosY - 1);
	board._distanceFromStart--;
}

AMove *	MoveUp::clone( void ) const
{
	return (new MoveUp());
}
