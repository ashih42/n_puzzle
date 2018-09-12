#include "Piece.hpp"
#include <iostream>

Piece::Piece( void ) : _value(-1) { }

Piece::Piece( int value, int size ) : _value(value)
{
	this->_str = (this->_value == 0) ? " " : std::to_string(this->_value);
	if (this->_value != 0)
	{
		this->_correctPosX = (this->_value - 1) % size;
		this->_correctPosY = (this->_value - 1) / size;
	}
}

Piece::~Piece( void ) { }

Piece::Piece( Piece const & src )
{
	*this = src;
}

Piece &				Piece::operator=( Piece const & rhs )
{
	this->_value = rhs._value;
	this->_str = rhs._str;
	this->_correctPosX = rhs._correctPosX;
	this->_correctPosY = rhs._correctPosY;
	this->_hammingDistance = rhs._hammingDistance;
	this->_manhattanDistance = rhs._manhattanDistance;
	return (*this);
}

int					Piece::getValue( void ) const
{
	return (this->_value);
}

const std::string &	Piece::toString( void ) const
{
	return (this->_str);
}

bool				Piece::isAtCorrectPos( void ) const
{
	return (this->_hammingDistance == 0);
}

int					Piece::getCorrectPosX( void ) const
{
	return (this->_correctPosX);
}

int					Piece::getCorrectPosY( void ) const
{
	return (this->_correctPosY);
}

int					Piece::getHammingDistance( void ) const
{
	return (this->_hammingDistance);
}

int					Piece::getManhattanDistance( void ) const
{
	return (this->_manhattanDistance);
}

void				Piece::checkPosition( int x, int y )
{
	if (this->_value == 0)
	{
		this->_manhattanDistance = 0;
		this->_hammingDistance = 0;
	}
	else
	{
		int diffX = std::abs(this->_correctPosX - x);
		int diffY = std::abs(this->_correctPosY - y);

		this->_manhattanDistance = diffX + diffY;
		this->_hammingDistance = (this->_manhattanDistance == 0) ? 0 : 1;
	}
}
