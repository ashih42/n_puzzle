#ifndef PARSER_HPP
# define PARSER_HPP

# define MIN_SIZE		3
# define MAX_SIZE		20

# include "Lexer.hpp"

class Parser
{
public:

	Parser( void );
	~Parser( void );

	int							parseSize( const std::string & size );
	void						parseFile( const std::string & filename );

	int							getSize( void ) const;
	int *						getValues( void ) const;

private:

	int							_size;
	int *						_values;

	int							_lineNumber;
	int							_valueLinesRemaining;
	int							_valueIndex;
	
	Lexer						_lexer;
	std::vector<std::string>	_tokens;

	Parser( Parser const & src );
	Parser & operator=( Parser const & rhs );

	void						_checkFileExists( const std::string & filename ) const;
	void						_checkIsDirectory( const std::string & filename ) const;
	void						_checkHasReadPermission( const std::string & filename ) const;
	void						_validateAllValues( void ) const;

	void						_processLine( std::string & line );
	void						_parseSizeLine( void );
	void						_parseValueLine( void );
};

#endif
