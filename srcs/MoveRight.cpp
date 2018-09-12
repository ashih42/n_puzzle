#include "MoveRight.hpp"

MoveRight::MoveRight( void ) : AMove("R")
{ }

MoveRight::~MoveRight( void ) { }

bool	MoveRight::execute( Board & board ) const
{
	bool	success = board._swapEmptyWith(board._emptyPosX - 1, board._emptyPosY);

	if (success)
		board._distanceFromStart++;
	return (success);
}

void	MoveRight::undo( Board & board ) const
{
	board._swapEmptyWith(board._emptyPosX + 1, board._emptyPosY);
	board._distanceFromStart--;
}

AMove *	MoveRight::clone( void ) const
{
	return (new MoveRight());
}
