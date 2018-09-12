#ifndef PIECE_HPP
# define PIECE_HPP

# include <string>

class Piece
{
public:

	Piece( void );
	Piece( int value, int size );
	~Piece( void );
	Piece( Piece const & src );
	Piece & operator=( Piece const & rhs );

	int					getValue( void ) const;
	const std::string &	toString( void ) const;

	bool				isAtCorrectPos( void ) const;

	int					getCorrectPosX( void ) const;
	int					getCorrectPosY( void ) const;

	int					getHammingDistance( void ) const;
	int					getManhattanDistance( void ) const;

	void				checkPosition( int x, int y );

private:

	int					_value;
	std::string			_str;

	int					_correctPosX;
	int					_correctPosY;

	int					_hammingDistance;
	int					_manhattanDistance;

};

#endif
