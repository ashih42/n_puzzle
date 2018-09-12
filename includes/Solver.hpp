#ifndef SOLVER_HPP
# define SOLVER_HPP

# include <queue>
# include <unordered_set>
# include "chrono"
# include "MutantStack.hpp"
# include "Board.hpp"
# include "MyComparator.hpp"

class Visualizer;

class Solver
{
public:

	Solver( Visualizer & visualizer, Board & board, eSearchMethod searchMethod, eHeuristic heuristic );
	~Solver( void );

	void						solve( void );

private:

	struct BoardHasher
	{
		size_t	operator()( Board * b ) const
		{
			return std::hash<std::string>()(b->toString());
		}
	};

	struct BoardEqualsComparator
	{
		bool	operator()( Board * a, Board * b ) const
		{
			for (int i = 0; i < a->_total; i++)
			{
				if (a->_pieces[i].getValue() != b->_pieces[i].getValue())
					return (false);
			}
			return (true);
		}
	};

	Visualizer &				_visualizer;

	std::priority_queue<Board *, std::vector<Board *>, MyComparator>	_frontier;
	std::unordered_set<Board *, BoardHasher, BoardEqualsComparator>		_visited;

	Solver( Solver const & src );
	Solver & operator=( Solver const & rhs );

	bool						_canSolve( Board & board ) const;
	int							_countInversions( Board & board ) const;
	Board *						_findSolvedBoard( void );
	void						_generateNextBoard( Board * currentBoard, AMove * move );

	void						_displayMoves( Board * b ) const;

};

#endif
