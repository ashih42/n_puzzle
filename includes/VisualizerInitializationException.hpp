#ifndef VISUALIZER_INITIALIZATION_EXCEPTION_HPP
# define VISUALIZER_INITIALIZATION_EXCEPTION_HPP

# include <string>

class VisualizerInitializationException : public std::exception
{
public:

	VisualizerInitializationException( std::string errorMessage );
	~VisualizerInitializationException( void ) _NOEXCEPT;

	VisualizerInitializationException( VisualizerInitializationException const & src );
	VisualizerInitializationException & operator=( VisualizerInitializationException const & rhs );

	const char *	what( void ) const throw();

private:

	std::string		_errorMessage;

	VisualizerInitializationException( void );

};

#endif
