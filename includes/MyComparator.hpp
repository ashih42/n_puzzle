#ifndef MY_COMPARATOR_HPP
# define MY_COMPARATOR_HPP

# include "Board.hpp"

# define NUM_SEARCH_METHODS		3
# define NUM_HEURISTICS			3

enum eSearchMethod
{
	UNIFORM_COST_SEARCH,
	GREEDY_BEST_FIRST_SEARCH,
	A_STAR_SEARCH
};

enum eHeuristic
{
	CMP_HAMMING_DISTANCE,
	CMP_MANHATTAN_DISTANCE,
	CMP_MANHATTAN_DISTANCE_WITH_LINEAR_CONFLICTS
};

class MyComparator
{
public:

	MyComparator( void );
	MyComparator( eSearchMethod searchMethod, eHeuristic heuristic );
	~MyComparator( void );
	MyComparator( MyComparator const & src );
	MyComparator & operator=( MyComparator const & rhs );

	bool			operator()( const Board * a, const Board * b ) const;

private:

	eSearchMethod	_searchMethod;
	eHeuristic		_heuristic;

	int				_getHeuristicValue( const Board * b ) const;

};

#endif
