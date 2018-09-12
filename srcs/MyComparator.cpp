#include "MyComparator.hpp"

MyComparator::MyComparator( void )
{ }

MyComparator::MyComparator( eSearchMethod searchMethod, eHeuristic heuristic ) : _searchMethod(searchMethod), _heuristic(heuristic)
{ }

MyComparator::~MyComparator( void )
{ }

MyComparator::MyComparator( MyComparator const & src )
{
	*this = src;
}

MyComparator &	MyComparator::operator=( MyComparator const & rhs )
{
	this->_searchMethod = rhs._searchMethod;
	this->_heuristic = rhs._heuristic;
	return (*this);
}

bool			MyComparator::operator()( const Board * a, const Board * b ) const
{
	int			a_value = 0;
	int			b_value = 0;

	if (this->_searchMethod != GREEDY_BEST_FIRST_SEARCH)
	{
		a_value += a->_distanceFromStart;
		b_value += b->_distanceFromStart;
	}
	if (this->_searchMethod != UNIFORM_COST_SEARCH)
	{
		a_value += this->_getHeuristicValue(a);
		b_value += this->_getHeuristicValue(b);
	}
	return (a_value > b_value);
}

int				MyComparator::_getHeuristicValue( const Board * b ) const
{
	int			value;

	switch (this->_heuristic)
	{
		case CMP_HAMMING_DISTANCE:
			value = b->_hammingDistance;
			break;
		case CMP_MANHATTAN_DISTANCE:
			value = b->_manhattanDistance;
			break;
		case CMP_MANHATTAN_DISTANCE_WITH_LINEAR_CONFLICTS:
			value = b->_manhattanDistance + b->_linearConflicts * 2;
			break;
		default:
			value = 0;
			break;
	}
	return (value);
}
