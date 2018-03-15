#ifndef __CTICTACTOE_H__
#define __CTICTACTOE_H__

#include <string>
#include <iomanip>
#include <iostream>
#include <algorithm>
// #include <random>

#include "TurnLog.h"

// Board dimensions
#define NUM_ROWS 3
#define NUM_COLS 3

#define COL_SEPARATOR "|"
#define ROW_SEPARATOR "-|-|-"

// Tic Tac Toe class
class CTicTacToe
{
public:
	// Default constructor
	CTicTacToe();

	// Destructor
	virtual ~CTicTacToe();

	// Start a new game
	void NewGame(void);

	// Get current marker at specified cell
	MARKER_TYPE GetMark(int row, int col);

	// Set specified cell to specified marker (returns FALSE if cell was already marked)
	bool SetMark(int row, int col, MARKER_TYPE marker);

	// Choose best move for specified marker
	void GetBestMove(MARKER_TYPE marker, int &row, int &col);

	// Check for game over (returns winning row if applicable)
	bool IsGameOver(std::vector<int> &rows, std::vector<int> &cols);

	// Get number of turns that have been played
	int GetTurnCount(void);

	// Undo turn
	void UndoTurn(void);

	// Print the current board state
	void PrintBoard(std::vector<int> &winRows, std::vector<int> &winCols);

	// Marker names for printing
	static std::string const markerName[];
	static std::string const winnerName[];

protected:
	// Evaluate board for specified marker type
	void evaluateBoard(MARKER_TYPE marker);

	// Evaluate row for specified marker type
	void evaluateRow(MARKER_TYPE playerMarker, std::vector<MARKER_TYPE*> const &markers, std::vector<int*> &scores);

	// Check if specified row is a winner
	MARKER_TYPE isWinningRow(std::vector<MARKER_TYPE*> const &markers);

	// Check if row has any free cells
	bool hasFreeCell(std::vector<MARKER_TYPE*> const &markers);

	// Initialize evaluation data
	void initEvalData(void);

	// Reset scores
	void resetScores(void);

	// Utility for getting index of item in a vector
	int itemIndex(std::vector<int> vec, int val);

	// Base scores for each cell
	static int const baseScore[NUM_ROWS][NUM_COLS];

	// Calculated scores for each cell
	int scoreBoard[NUM_ROWS][NUM_COLS];

	// The play board (3x3 grid of cells)
	MARKER_TYPE playBoard[NUM_ROWS][NUM_COLS];

	// Evaluation data (look for patterns in these "rows")
	std::vector<std::vector<MARKER_TYPE*>> evalMarkers;
	std::vector<std::vector<int*>> evalScores;
	std::vector<std::vector<int>> evalRows;
	std::vector<std::vector<int>> evalCols;

	// Score modifiers for each cell type
	const int SCORE_TO_GROUP = 3;
	const int SCORE_TO_BLOCK = 7;
	const int SCORE_TO_WIN = 20;

	// Player & AI marker types
//	MARKER_TYPE aiMarker = X_MARKER;
//	MARKER_TYPE playerMarker = O_MARKER;

	// Turn log
	CTurnLog turnLog;
};

#endif // __CTICTACTOE_H__
