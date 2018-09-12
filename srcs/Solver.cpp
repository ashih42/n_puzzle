#include "Solver.hpp"
#include "MoveLeft.hpp"
#include "MoveRight.hpp"
#include "MoveDown.hpp"
#include "MoveUp.hpp"
#include "Visualizer.hpp"
#include "format.h"
#include <iostream>
#include <iomanip>

Solver::Solver( Visualizer & visualizer, Board & board, eSearchMethod searchMethod, eHeuristic heuristic ) : _visualizer(visualizer)
{
	this->_frontier = std::priority_queue<Board *, std::vector<Board *>, MyComparator>(MyComparator(searchMethod, heuristic));
	this->_frontier.push(new Board(board));
}

Solver::~Solver( void )
{
	while (!this->_frontier.empty())
	{
		delete this->_frontier.top();
		this->_frontier.pop();
	}

	for (std::unordered_set<Board *, BoardHasher, BoardEqualsComparator>::iterator it = this->_visited.begin();
		it != this->_visited.end(); it++)
		delete *it;
}

void		Solver::solve( void )
{
	bool	solvable = this->_canSolve(*this->_frontier.top());

	if (solvable)
		std::cout << BLUE BOLD "Solver: " NORMAL << "I GOT DIS" << std::endl;
	else
	{
		std::cout << BLUE BOLD "Solver: " NORMAL << "NO WAI MANG\n" << std::endl;
		return;
	}

	std::chrono::time_point<std::chrono::high_resolution_clock> startTime = std::chrono::high_resolution_clock::now();

	Board * solvedBoard = this->_findSolvedBoard();
	if (!solvedBoard) return;

	std::chrono::time_point<std::chrono::high_resolution_clock> finishTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsedTime = finishTime - startTime;
	size_t minutes = static_cast<size_t>(elapsedTime.count() / 60);
	double seconds = fmod(elapsedTime.count(), 60.0);
	std::cout << BLUE BOLD "Solver: " NORMAL << "I SOLVED IT I'M A GENIUS" << std::endl;
	std::cout << "Elapsed time: " << minutes << " min " << std::fixed << std::setprecision(3) << seconds << " sec\n" << std::endl;
	std::cout << BLUE "Time:" NORMAL "\tVisited states:\t\t" << this->_visited.size() << std::endl;
	std::cout << BLUE "Space:" NORMAL "\tGenerated states:\t" << (this->_visited.size() + this->_frontier.size()) << std::endl;
	
	this->_displayMoves(solvedBoard);
}

void		Solver::_displayMoves( Board * board ) const
{
	if (board == NULL) return;

	MutantStack<AMove *> tempStack;
	while (board->_prevMove)
	{
		tempStack.push(board->_prevMove->clone());
		board = board->_prevBoard;
	}
	std::cout << BLUE "Moves:\t\t\t\t" NORMAL << tempStack.size() << std::endl;

	while (!tempStack.empty())
	{
		AMove * move = tempStack.top();
		tempStack.pop();
		this->_visualizer._puzzle._processMove(move);
		this->_visualizer._render();
	}
}

Board *		Solver::_findSolvedBoard( void )
{
	while (!this->_frontier.empty())
	{
		Board * currentBoard = this->_frontier.top();
		this->_frontier.pop();

		if (currentBoard->isSolved())
		{
			this->_visited.insert(currentBoard);
			return (currentBoard);
		}

		if (this->_visited.find(currentBoard) != this->_visited.end())
			delete currentBoard;
		else
		{
			this->_generateNextBoard(currentBoard, new MoveLeft);
			this->_generateNextBoard(currentBoard, new MoveRight);
			this->_generateNextBoard(currentBoard, new MoveDown);
			this->_generateNextBoard(currentBoard, new MoveUp);
			this->_visited.insert(currentBoard);	
		}
	}
	return (NULL);
}

void		Solver::_generateNextBoard( Board * currentBoard, AMove * move )
{
	if (move->execute(*currentBoard))
	{
		Board * nextBoard = new Board(*currentBoard);
		move->undo(*currentBoard);
		nextBoard->_prevBoard = currentBoard;
		nextBoard->_prevMove = move;

		if (this->_visited.find(nextBoard) != this->_visited.end())
			delete nextBoard;
		else
			this->_frontier.push(nextBoard);
	}
	else
		delete move;
}

/*
** First, count number of inversions.
** 
** If size is odd, and number of inversions is even, then it is solvable.
** If size is even, and blank is on even row counting from bottom, and inversions is odd, then it is solvable.
** If size is even, and blank is on odd row counting from bottom, and inversions is even, then it is solvable.
** Otherwise, it is NOT solvable.
*/
bool		Solver::_canSolve( Board & board ) const
{
	int		inversionCount = this->_countInversions(board);

	if (board._size % 2 == 1)
		return (inversionCount % 2 == 0);
	if ((board._size - board._emptyPosY) % 2 == 0)
		return (inversionCount % 2 == 1);
	else
		return (inversionCount % 2 == 0);
}

/*
** Inversion : when some a appears before b, and a > b.
** Do not count empty space.
*/
int				Solver::_countInversions( Board & board ) const
{
	int			count = 0;

	for (int i = 0; i < board._total; i++)
	{
		Piece a = board.getPiece(i);
		for (int j = i + 1; j < board._total; j++)
		{
			Piece b = board.getPiece(j);
			if (a.getValue() != 0 && b.getValue() != 0 && a.getValue() > b.getValue())
				count++;
		}
	}
	return (count);
}
