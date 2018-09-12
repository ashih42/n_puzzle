#include "MoveLeft.hpp"

MoveLeft::MoveLeft( void ) : AMove("L")
{ }

MoveLeft::~MoveLeft( void ) { }

bool	MoveLeft::execute( Board & board ) const
{
	bool	success = board._swapEmptyWith(board._emptyPosX + 1, board._emptyPosY);

	if (success)
		board._distanceFromStart++;
	return (success);
}

void	MoveLeft::undo( Board & board ) const
{
	board._swapEmptyWith(board._emptyPosX - 1, board._emptyPosY);
	board._distanceFromStart--;
}

AMove *	MoveLeft::clone( void ) const
{
	return (new MoveLeft());
}
