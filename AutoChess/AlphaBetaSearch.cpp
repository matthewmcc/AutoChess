#include "stdafx.h"
#include "AlphaBetaSearch.h"


template <typename State>
AlphaBetaSearch<State>::AlphaBetaSearch(int maxScore, int maxSearchTime)
{
	MaxScore = maxScore;
	MaxSearchTime = maxSearchTime;
};

template <typename State>
State AlphaBetaSearch<State>::nextMove(State currState, int searchDepth)
{
	State bestMove;
	double alpha = -HUGE_VAL;
	double result;

	std::vector<State> moves = nextMoves(currState);

	for (int i = 0; i < moves.size(); i++) {
		result = minscore(moves[i], depth - 1, alpha, HUGE_VAL);

		if (result > alpha) {
			alpha = result;
			bestMove = moves[i].move();
		}

		if (alpha >= MaxScore)
			break;
	}

	return bestMove;
};

template <typename State>
double AlphaBetaSearch<State>::maxscore(State currState, int depth, double alpha, double beta)
{
	int result;
	//////////if (terminalTest(currState))
	/////////	return 

	if (depth <= 0)
		return heuristic(currState);

	std::vector<State> moves = nextMoves(currState);

	for (int i = 0; i < moves.size(); i++) {
		result = minscore(moves[i], depth - 1, alpha, beta);
		alpha = max(alpha, result);

		if (alpha >= beta)
			return beta;
	}

	return alpha;
};

template<typename State>
double AlphaBetaSearch<State>::minscore(State currState, int depth, double alpha, double beta) {
	int result;
	//////////if (terminalTest(currState))
	/////////	return 

	if (depth <= 0)
		return heuristic(currState);

	std::vector<State> moves = currState.nextMoves();

	for (int i = 0; i < moves.size(); i++) {
		result = maxscore(moves[i], depth - 1, alpha, beta);
		beta = min(beta, result);

		if (alpha >= beta)
			return alpha;
	}

	return beta;
};

template <typename State>
int AlphaBetaSearch<State>::heuristic(State)
{
	return 0;
};

template <typename State>
bool AlphaBetaSearch<State>::terminalTest(State)
{
	return false;
};

template<typename State>
std::vector<State> AlphaBetaSearch<State>::nextMoves(State)
{
	return std::vector<State>();
};



/*
def next-move(state, depth):
bestMove = nil
alpha = -INF
for next-state in state.nexts():
result = minscore(next-state, depth-1, alpha, INF)
if result > alpha:
alpha = result
bestMove = next-state.move()
if alpha >= MAX-POSSIBLE-SCORE:
break
return bestMove

def maxscore(state, depth, alpha, beta):
if isTerminal(state):
return goal-value(state)
if depth <= 0:
return heuristic-value(state)
for next-state in state.nexts():
score = minscore(next, depth-1, alpha, beta)
alpha = max(alpha, score)
if alpha >= beta:
return beta
return alpha

def minscore(state, depth, alpha, beta):
if isTerminal(state):
return goal-value(state)
if depth <= 0:
return heuristic-value(state)
for next-state in state.nexts():
score = maxscore(next, depth-1, alpha, beta)
beta = min(beta, score)
if alpha >= beta:
return alpha
return beta
*/

