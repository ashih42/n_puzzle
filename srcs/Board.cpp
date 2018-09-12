#include "Board.hpp"
#include "AMove.hpp"
#include "format.h"
#include <iostream>

Board::Board ( void ) : _size(0), _total(0), _pieces(NULL), _prevBoard(NULL), _prevMove(NULL)
{ }

Board::Board( int size ) : _size(size), _total(size * size), _prevBoard(NULL), _prevMove(NULL)
{
	int *	randValues = new int[this->_total];

	for (int i = 0; i < this->_total; i++)
		randValues[i] = i;

	for (int i = 0; i < this->_total; i++)
	{
		int j = std::rand() % this->_total;
		int temp = randValues[i];
		randValues[i] = randValues[j];
		randValues[j] = temp;
	}

	this->_initFromIntArray(randValues);
	delete[] randValues;
}

Board::Board( int size, int * values ) : _size(size), _total(size * size), _prevBoard(NULL), _prevMove(NULL)
{
	this->_initFromIntArray(values);
}

void		Board::_initFromIntArray( int * values )
{
	this->_distanceFromStart = 0;
	this->_hammingDistance = 0;
	this->_manhattanDistance = 0;

	this->_pieces = new Piece[this->_total];
	for (int i = 0; i < this->_total; i++)
	{
		int x = i % this->_size;
		int y = i / this->_size;
		this->_pieces[i] = Piece(values[i], this->_size);
		this->_pieces[i].checkPosition(x, y);
		this->_hammingDistance += this->_pieces[i].getHammingDistance();
		this->_manhattanDistance += this->_pieces[i].getManhattanDistance();

		if (values[i] == 0)
		{
			this->_emptyPosX = x;
			this->_emptyPosY = y;
		}
	}
	this->_countLinearConflicts();
}

Board::~Board( void )
{
	if (this->_size != 0)
		delete[] this->_pieces;
	delete this->_prevMove;
}

Board::Board( Board const & src ) : _size(0), _total(0), _pieces(NULL), _prevBoard(NULL), _prevMove(NULL)
{
	*this = src;
}

Board &		Board::operator=( Board const & rhs )
{
	// delete old stuff
	if (this->_size != 0)
		delete[] this->_pieces;
	delete this->_prevMove;

	// copy new stuff
	this->_size = rhs._size;
	this->_total = rhs._total;

	this->_pieces = new Piece[this->_total];
	for (int i = 0; i < this->_total; i++)
		this->_pieces[i] = rhs._pieces[i];

	this->_emptyPosX = rhs._emptyPosX;
	this->_emptyPosY = rhs._emptyPosY;

	this->_distanceFromStart = rhs._distanceFromStart;
	this->_hammingDistance = rhs._hammingDistance;
	this->_manhattanDistance = rhs._manhattanDistance;
	this->_linearConflicts = rhs._linearConflicts;

	this->_prevBoard = rhs._prevBoard;
	this->_prevMove = rhs._prevMove;

	return (*this);
}

int			Board::getSize( void ) const
{
	return (this->_size);
}

Piece &		Board::getPiece( int i ) const
{
	return (this->_pieces[i]);
}

Piece &		Board::getPiece( int x, int y ) const
{
	return (this->_pieces[y * this->_size + x]);
}

bool		Board::isSolved( void ) const
{
	return (this->_hammingDistance == 0);
}

std::string	Board::toString( void ) const
{
	std::string		fullStr = "";
	for (int i = 0; i < this->_total; i++)
	{
		std::string str = this->_pieces[i].toString();
		while(str.length() < 3)
			str = " " + str;
		fullStr += str + " ";
		if ((i + 1) % this->_size == 0)
			fullStr += "\n";
	}
	return (fullStr);
}

void		Board::debug( void ) const
{
	std::cout << BOLD "CURRENT BOARD:" NORMAL << std::endl;
	std::cout << this->toString();
	std::cout << GREEN "Distance From Start :\t" NORMAL << this->_distanceFromStart << std::endl;
	std::cout << GREEN "Hamming Distance :\t" NORMAL << this->_hammingDistance << std::endl;
	std::cout << GREEN "Manhattan Distance :\t" NORMAL << this->_manhattanDistance << std::endl;
	std::cout << GREEN "Linear Conflicts :\t" NORMAL << this->_linearConflicts << std::endl;
	std::cout << std::endl;
}

bool		Board::_swapEmptyWith( int x, int y )
{
	if (!(0 <= x && x < this->_size && 0 <= y && y < this->_size))
		return (false);

	this->_hammingDistance -= this->getPiece(x, y).getHammingDistance();
	this->_manhattanDistance -= this->getPiece(x, y).getManhattanDistance();

	Piece temp(this->getPiece(this->_emptyPosX, this->_emptyPosY));
	this->getPiece(this->_emptyPosX, this->_emptyPosY) = this->getPiece(x, y);
	this->getPiece(x, y) = temp;

	this->getPiece(this->_emptyPosX, this->_emptyPosY).checkPosition(this->_emptyPosX, this->_emptyPosY);

	this->_hammingDistance += this->getPiece(this->_emptyPosX, this->_emptyPosY).getHammingDistance();
	this->_manhattanDistance += this->getPiece(this->_emptyPosX, this->_emptyPosY).getManhattanDistance();

	this->_emptyPosX = x;
	this->_emptyPosY = y;

	this->_countLinearConflicts();

	return (true);
}

void		Board::_countLinearConflicts( void )
{
	this->_linearConflicts = 0;

	for (int z = 0; z < this->_total; z++)
	{
		int x = z % this->_size;
		int y = z / this->_size;

		Piece & piece = this->getPiece(x, y);
		
		if (piece.getValue() == 0)
			continue;
		
		// check if right neighbors are in the same row
		if (piece.getCorrectPosY() == y)
		{
			for (int i = x + 1; i < this->_size; i++)
			{
				Piece & next = this->getPiece(i, y);
				if (next.getValue() == 0) continue;
				if (next.getCorrectPosY() == y && this->_hasLinearConflict(x, piece.getCorrectPosX(), i, next.getCorrectPosX()))
					this->_linearConflicts++;
			}
		}

		// check if down neighbors are in the same column
		if (piece.getCorrectPosX() == x)
		{
			for (int j = y + 1; j < this->_size; j++)
			{
				Piece & next = this->getPiece(x, j);
				if (next.getValue() == 0) continue;
				if (next.getCorrectPosX() == x && this->_hasLinearConflict(y, piece.getCorrectPosY(), j, next.getCorrectPosY()))
					this->_linearConflicts++;
			}
		}
	}
}

bool		Board::_hasLinearConflict( int a_src, int a_dst, int b_src, int b_dst ) const
{
	int			a = a_src;
	int			b = b_src;

	int			d_a = (a_dst - a_src) > 0 ? 1 : -1;
	int			d_b = (b_dst - b_src) > 0 ? 1 : -1;

	bool		relation = (a < b);

	while (!(a == a_dst && b == b_dst))
	{
		if (a != a_dst)
			a += d_a;

		if (b != b_dst)
			b += d_b;

		if ((a < b) != relation)
			return (true);
	}
	return (false);
}
