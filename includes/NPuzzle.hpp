#ifndef NPUZZLE_HPP
# define NPUZZLE_HPP

# include "Board.hpp"
# include "MutantStack.hpp"
# include "AMove.hpp"
# include "MyComparator.hpp"

class Visualizer;

class NPuzzle
{
public:

	NPuzzle( char flag, const std::string & arg );
	~NPuzzle( void );

private:

	friend class			Visualizer;
	friend class			Solver;

	MutantStack<AMove *>	_moveStack;
	Board					_board;
	Board					_originalBoard;

	eSearchMethod			_searchMethod;
	eHeuristic				_heuristic;

	NPuzzle( void );
	NPuzzle( NPuzzle const & src );
	NPuzzle & operator=( NPuzzle const & rhs );

	void					_initFromSize( const std::string & size );
	void					_initFromFile( const std::string & filename );

	void					_processMove( AMove * move );
	void					_undoLastMove( void );
	void					_reset( void );
	void					_printMoves( void );

	void					_switchSearchMethod( void );
	void					_switchHeuristic( void );
	void					_displaySearchMethod( void ) const;
	void					_solve( Visualizer & visualizer );

};

#endif
