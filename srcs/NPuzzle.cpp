#include "NPuzzle.hpp"
#include "ParserException.hpp"
#include "Visualizer.hpp"
#include "Parser.hpp"
#include "Solver.hpp"
#include "format.h"
#include <iostream>

NPuzzle::NPuzzle( char flag, const std::string & arg )
{
	if (flag == 's')
		this->_initFromSize(arg);
	else if (flag == 'f')
		this->_initFromFile(arg);
	else
		throw ParserException("IMPOSSIBRU!!!!!");

	this->_board = this->_originalBoard;

	this->_searchMethod = A_STAR_SEARCH;
	this->_heuristic = CMP_MANHATTAN_DISTANCE_WITH_LINEAR_CONFLICTS;
	this->_displaySearchMethod();

	Visualizer visualizer(*this);	
	visualizer.loop();
}

NPuzzle::~NPuzzle( void )
{
	for (MutantStack<AMove *>::iterator it = this->_moveStack.begin();
		it != this->_moveStack.end(); it++)
		delete *it;
}

void		NPuzzle::_initFromSize( const std::string & size )
{
	Parser	parser;

	this->_originalBoard = Board(parser.parseSize(size));
}

void		NPuzzle::_initFromFile( const std::string & filename )
{
	Parser	parser;

	parser.parseFile(filename);
	this->_originalBoard = Board(parser.getSize(), parser.getValues());
}

void		NPuzzle::_processMove( AMove * move )
{
	if (move->execute(this->_board))
	{
		this->_moveStack.push(move);
		if (this->_board.isSolved())
			std::cout << "😂 CONGLATURATIONS!! U R WINRAR!! 😂\n" << std::endl;
	}
	else
		delete move;
}

void		NPuzzle::_undoLastMove( void )
{
	if (this->_moveStack.empty()) return;

	AMove * lastMove = this->_moveStack.top();
	lastMove->undo(this->_board);
	this->_moveStack.pop();
	delete lastMove;
}

void		NPuzzle::_reset( void )
{
	this->_board = this->_originalBoard;
	while (!this->_moveStack.empty())
	{
		delete this->_moveStack.top();
		this->_moveStack.pop();
	}
	std::cout << MAGENTA "Puzzle has been reset\n" NORMAL << std::endl;
}

void		NPuzzle::_printMoves( void )
{
	int		count = 0;

	std::cout << BOLD BLUE "MOVES: " NORMAL << std::to_string(this->_moveStack.size()) << std::endl;
	for (MutantStack<AMove *>::iterator it = this->_moveStack.begin();
		it != this->_moveStack.end(); it++)
	{
		std::cout << (*it)->toString() << " ";
		count++;
		if (count % 4 == 0)
			std::cout << "\t";
		if (count % 16 == 0)
			std::cout << "\n";
	}
	if (count % 16 != 0)
		std::cout << "\n";	
	std::cout << std::endl;
}

void		NPuzzle::_switchSearchMethod( void )
{
	this->_searchMethod = static_cast<eSearchMethod>((this->_searchMethod + 1) % NUM_SEARCH_METHODS);
	this->_displaySearchMethod();
}

void		NPuzzle::_switchHeuristic( void )
{
	this->_heuristic = static_cast<eHeuristic>((this->_heuristic + 1) % NUM_HEURISTICS);
	this->_displaySearchMethod();
}

void		NPuzzle::_displaySearchMethod( void ) const
{
	std::cout << BOLD GREEN "Search Method:\t\t" NORMAL BOLD;
	switch(this->_searchMethod)
	{
		case UNIFORM_COST_SEARCH:
			std::cout << "Uniform Cost Search ( g(x) only )";
			break;
		case GREEDY_BEST_FIRST_SEARCH:
			std::cout << "Greedy Best First Search ( h(x) only )";
			break;
		case A_STAR_SEARCH:
			std::cout << "A-Star Search ( g(x) + h(x) )";
			break;
		default:
			std::cout << "u w0t m8";
			break;
	}
	std::cout << NORMAL << std::endl;

	if (this->_searchMethod != GREEDY_BEST_FIRST_SEARCH)
		std::cout << BOLD GREEN "  Cost Function g(x):\t" NORMAL << "Number of Moves from Start" << std::endl;

	if (this->_searchMethod != UNIFORM_COST_SEARCH)
	{
		std::cout << BOLD GREEN "  Heuristic h(x):\t" NORMAL;
		switch(this->_heuristic)
		{
			case CMP_HAMMING_DISTANCE:
				std::cout << "Hamming Distance";
				break;
			case CMP_MANHATTAN_DISTANCE:
				std::cout << "Manhattan Distance";
				break;
			case CMP_MANHATTAN_DISTANCE_WITH_LINEAR_CONFLICTS:
				std::cout << "Manhattan Distance with Linear Conflicts";
				break;
			default:
				std::cout << "u w0t m8";
				break;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void		NPuzzle::_solve( Visualizer & visualizer )
{
	Solver	solver(visualizer, this->_board, this->_searchMethod, this->_heuristic);

	solver.solve();
}
