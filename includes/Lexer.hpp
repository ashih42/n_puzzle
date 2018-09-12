#ifndef LEXER_HPP
# define LEXER_HPP

# include <string>
# include <vector>

class Lexer
{
public:

	Lexer( void );	
	~Lexer( void );

	void		splitLine( std::string & line, std::vector<std::string> & tokens ) const;

private:

	Lexer( Lexer const & src );
	Lexer & operator=( Lexer const & rhs );

};

#endif
