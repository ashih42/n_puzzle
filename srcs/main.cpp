#include "NPuzzle.hpp"
#include "ParserException.hpp"
#include "VisualizerInitializationException.hpp"
#include "format.h"

int		print_usage( int ret )
{
	std::cout << "usage: npuzzle -s SIZE | -f FILE\n" << std::endl;

	std::cout << BOLD BLUE "[CONTROLS]"	NORMAL << std::endl;
	std::cout << BLUE "ARROW KEYS\t"	NORMAL "Slide a tile toward empty position" << std::endl;
	std::cout << BLUE "BACKSPACE\t"		NORMAL "Undo last move" << std::endl;
	std::cout << BLUE "R\t\t"			NORMAL "Reset puzzle" << std::endl;
	std::cout << BLUE "TAB\t\t"			NORMAL "Toggle among number tiles/background pictures" << std::endl;
	std::cout << BLUE "H\t\t"			NORMAL "Toggle hint on/off" << std::endl;
	std::cout << BLUE "P\t\t"			NORMAL "Print log of moves made" << std::endl;
	std::cout << BLUE "S\t\t"			NORMAL "Reset and solve puzzle" << std::endl;
	std::cout << BLUE "M\t\t"			NORMAL "Switch search method" << std::endl;
	std::cout << BLUE "K\t\t"			NORMAL "Switch heuristic" << std::endl;
	std::cout << BLUE "D\t\t"			NORMAL "Print diagnostics about current board" << std::endl;

	return (ret);
}

int		main( int argc, char *argv[] )
{
	srand(time(NULL));

	if (argc != 3)
		return (print_usage(EXIT_FAILURE));
	if (!(strcmp(argv[1], "-s") == 0 || strcmp(argv[1], "-f") == 0))
		return (print_usage(EXIT_FAILURE));

	try
	{
		NPuzzle puzzle(argv[1][1], std::string(argv[2]));
	}
	catch (ParserException & e)
	{
		std::cout << RED BOLD << "ParserException : " << NORMAL << e.what() << std::endl;
	}
	catch (VisualizerInitializationException & e)
	{
		std::cout << RED BOLD << "VisualizerInitializationException : " << NORMAL << e.what() << std::endl;
	}

	return (EXIT_SUCCESS);
}
