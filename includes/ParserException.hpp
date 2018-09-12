#ifndef PARSER_EXCEPTION_HPP
# define PARSER_EXCEPTION_HPP

# include <string>

class ParserException : public std::exception
{
public:

	ParserException( std::string errorMessage );
	~ParserException( void ) _NOEXCEPT;

	ParserException( ParserException const & src );
	ParserException & operator=( ParserException const & rhs );

	const char *	what( void ) const throw();

private:

	std::string		_errorMessage;

	ParserException( void );

};

#endif
