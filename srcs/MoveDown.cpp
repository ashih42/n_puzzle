#include "MoveDown.hpp"

MoveDown::MoveDown( void ) : AMove("D")
{ }

MoveDown::~MoveDown( void ) { }

bool	MoveDown::execute( Board & board ) const
{
	bool	success = board._swapEmptyWith(board._emptyPosX, board._emptyPosY - 1);

	if (success)
		board._distanceFromStart++;
	return (success);
}

void	MoveDown::undo( Board & board ) const
{
	board._swapEmptyWith(board._emptyPosX, board._emptyPosY + 1);
	board._distanceFromStart--;
}

AMove *	MoveDown::clone( void ) const
{
	return (new MoveDown());
}
