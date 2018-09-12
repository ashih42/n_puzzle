#ifndef BOARD_HPP
# define BOARD_HPP

# include "Piece.hpp"

/*  --------------> x, i
** |
** |
** |
** V
** y, j
*/

class AMove;

class Board
{
public:

	Board( void );
	Board( int size );
	Board( int size, int * values );
	~Board( void );
	Board( Board const & src );
	Board & operator=( Board const & rhs );

	int				getSize( void ) const;
	Piece &			getPiece( int i ) const;
	Piece &			getPiece( int x, int y ) const;
	bool			isSolved( void ) const;

	std::string		toString( void ) const;
	void			debug( void ) const;

private:

	friend class	MoveLeft;
	friend class	MoveRight;
	friend class	MoveDown;
	friend class	MoveUp;
	friend class	Solver;
	friend class	MyComparator;
	friend struct	BoardHasher;
	friend struct	BoardComparator;

	int				_size;
	int				_total;
	Piece *			_pieces;

	int				_emptyPosX;
	int				_emptyPosY;

	int				_distanceFromStart;
	int				_hammingDistance;
	int				_manhattanDistance;
	int				_linearConflicts;

	Board *			_prevBoard;
	AMove *			_prevMove;

	void			_initFromIntArray( int * values );
	bool			_swapEmptyWith( int x, int y );

	void			_countLinearConflicts( void );
	bool			_hasLinearConflict( int a_src, int a_dst, int b_src, int b_dst ) const;

};

#endif
