// ****************************************************************************
//  CTicTacToe class -- contains logic for game AI
// ****************************************************************************

#include "CTicTacToe.h"

// Marker names for printing
std::string const CTicTacToe::markerName[] = { " ", "X", "O" };
std::string const CTicTacToe::winnerName[] = { " ", "+", "*" };

// Base scores for each cell
int const CTicTacToe::baseScore[NUM_ROWS][NUM_COLS] = { { 2, 1, 2 },
														{ 1, 3, 1 },
														{ 2, 1, 2 } };

// Constructor
CTicTacToe::CTicTacToe()
{
	initEvalData();
}

// Destructor
CTicTacToe::~CTicTacToe()
{
}

// Initialize evaluation data for later use
void CTicTacToe::initEvalData(void)
{
	// Row data collection variables
	std::vector<MARKER_TYPE*> markers;
	std::vector<int*> scores;
	std::vector<int> rows;
	std::vector<int> cols;

	// Define data for rows
	for (int i = 0;  i < NUM_ROWS;  i++)
	{
		// Define next row
		rows.clear(); markers.clear();
		cols.clear(); scores.clear();
		for (int j = 0;  j < NUM_COLS;  j++)
		{
			markers.push_back(&playBoard[i][j]);
			scores.push_back(&scoreBoard[i][j]);
			rows.push_back(i); cols.push_back(j);
		}

		// Save row definition
		evalMarkers.push_back(markers);
		evalScores.push_back(scores);
		evalRows.push_back(rows);
		evalCols.push_back(cols);
	}

	// Define data for columns
	for (int j = 0;  j < NUM_COLS;  j++)
	{
		// Define next column
		rows.clear(); markers.clear();
		cols.clear(); scores.clear();
		for (int i = 0;  i < NUM_ROWS;  i++)
		{
			markers.push_back(&playBoard[i][j]);
			scores.push_back(&scoreBoard[i][j]);
			rows.push_back(i); cols.push_back(j);
		}

		// Save column definition
		evalMarkers.push_back(markers);
		evalScores.push_back(scores);
		evalRows.push_back(rows);
		evalCols.push_back(cols);
	}

	// Define data for first diagonal
	rows.clear(); markers.clear();
	cols.clear(); scores.clear();
	for (int i = 0;  i < NUM_ROWS;  i++)
	{
		markers.push_back(&playBoard[i][i]);
		scores.push_back(&scoreBoard[i][i]);
		rows.push_back(i); cols.push_back(i);
	}

	// Save row definition
	evalMarkers.push_back(markers);
	evalScores.push_back(scores);
	evalRows.push_back(rows);
	evalCols.push_back(cols);

	// Define data for second diagonal
	rows.clear(); markers.clear();
	cols.clear(); scores.clear();
	for (int j = 0;  j < NUM_COLS;  j++)
	{
		int i = NUM_COLS - 1 - j;
		markers.push_back(&playBoard[i][j]);
		scores.push_back(&scoreBoard[i][j]);
		rows.push_back(i); cols.push_back(j);
	}

	// Save row definition
	evalMarkers.push_back(markers);
	evalScores.push_back(scores);
	evalRows.push_back(rows);
	evalCols.push_back(cols);
}

// Reset scores
void CTicTacToe::resetScores(void)
{
	// Reset all scores to prepare for evaluation
	for (int i = 0;  i < NUM_ROWS;  i++)
	{
		for (int j = 0;  j < NUM_COLS;  j++)
			scoreBoard[i][j] = baseScore[i][j];
	}
}

// Reset board to default state
void CTicTacToe::NewGame(void)
{
	// Clear game history
	turnLog.Clear();

	// Clear markers
	for (int i = 0;  i < NUM_ROWS;  i++)
	{
		for (int j = 0;  j < NUM_COLS;  j++)
			playBoard[i][j] = NO_MARKER;
	}

	// Reset scores
	resetScores();
}

// Get marker at specified cell
MARKER_TYPE CTicTacToe::GetMark(int row, int col)
{
	MARKER_TYPE rc = NO_MARKER;
	if ((row >= 0) && (row < NUM_ROWS) && (col >= 0) && (col < NUM_COLS))
		rc = playBoard[row][col];

	return rc;
}

// Set specified cell to specified marker (returns FALSE if cell was already marked)
bool CTicTacToe::SetMark(int row, int col, MARKER_TYPE marker)
{
	// Sanity checks
	bool rc = false;
	if ((row >= 0) && (row < NUM_ROWS) && (col >= 0) && (col < NUM_COLS))
	{
		// Rules check
		if ((playBoard[row][col] == NO_MARKER) && (marker != NO_MARKER))
		{
			playBoard[row][col] = marker;
			turnLog.Add(row, col, marker);
			rc = true;
		}
	}

	return rc;
}

// Get number of turns that have been played
int CTicTacToe::GetTurnCount(void)
{
	// Just use the log's count
	return turnLog.GetTurnCount();
}

// Undo turn
void CTicTacToe::UndoTurn(void)
{
	// Get most recent turn data
	int row, col;
	MARKER_TYPE marker;
	if (turnLog.GetLastTurn(row, col, marker))
	{
		// Undo it
		playBoard[row][col] = NO_MARKER;
		turnLog.Undo();
	}
}

// Utility for getting index of item in a vector
int CTicTacToe::itemIndex(std::vector<int> vec, int val)
{
	int rc = -1;
	if (vec.size() > 0)
	{
		std::vector<int>::iterator itr = std::find(vec.begin(), vec.end(), val);
		if (itr != vec.end())
			rc = (int) std::distance(vec.begin(), itr);
	}

	return rc;
}

// Print current board state
void CTicTacToe::PrintBoard(std::vector<int> &winRows, std::vector<int> &winCols)
{
	// Print one row at a time
	std::string cellStr;
	for (int i = 0;  i < NUM_ROWS;  i++)
	{
		for (int j = 0;  j < NUM_COLS;  j++)
		{
			// Check if printing a win or a regular cell value
			int idxRow = itemIndex(winRows, i);
			int idxCol = itemIndex(winCols, j);
			if ((idxRow >= 0) && (idxCol >= 0) && (idxRow == i) && (idxCol == j))
				cellStr = winnerName[playBoard[i][j]];
			else
				cellStr = markerName[playBoard[i][j]];

			// Print cell
			std::cout << cellStr;

			// Print column separator
			if (j < NUM_COLS - 1)
				std::cout << COL_SEPARATOR;
		}

		// Print row separator
		if (i < NUM_ROWS - 1)
			std::cout << std::endl << ROW_SEPARATOR << std::endl;
	}
}

// Choose best move for specified marker
void CTicTacToe::GetBestMove(MARKER_TYPE marker, int &row, int &col)
{
	// Evaluate board
	evaluateBoard(marker);

	// If more than one cell with same value, choose randomly between them
//	std::mt19937 rng;
//	rng.seed(std::random_device()());
//	std::uniform_int_distribution<std::mt19937::result_type> cellDistributor(0, scoreCount - 1);
//	int cell = cellDistributor(rng);

	// Choose best move
	int score = -1;
	for (int i = 0;  i < NUM_ROWS;  i++)
	{
		for (int j = 0;  j < NUM_COLS;  j++)
		{
			// Find the highest score
			if ((playBoard[i][j] == NO_MARKER) && (scoreBoard[i][j] > score))
			{
				score = scoreBoard[i][j];
				row = i; col = j;
			}
		}
	}
}

// Check if row has any free cells
bool CTicTacToe::hasFreeCell(std::vector<MARKER_TYPE*> const &markers)
{
	// Check row for any NO_MARKER cells
	bool rc = false;
	for (size_t i = 0;  i < markers.size();  i++)
	{
		if (*markers[i] == NO_MARKER)
		{
			rc = true;
			break;
		}
	}

	return rc;
}

// Check if specified row is a winner
MARKER_TYPE CTicTacToe::isWinningRow(std::vector<MARKER_TYPE*> const &markers)
{
	// Sanity check first
	MARKER_TYPE rc = NO_MARKER;
	if (markers.size() > 0)
	{
		// Count matches
		size_t mCount = 1;
		for (size_t i = 1;  i < markers.size();  i++)
		{
			if (*markers[i] == *markers[0])
				mCount++;
		}

		// Check for all matching
		if ((mCount == markers.size()) && (*markers[0] != NO_MARKER))
			rc = *markers[0];
	}

	return rc;
}

// Check for game over (returns winning row if applicable)
bool CTicTacToe::IsGameOver(std::vector<int> &rows, std::vector<int> &cols)
{
	// Assume not
	bool rc = false;
	bool freeCellFound = false;
	rows.clear();  cols.clear();

	// Evaluate all rows
	for (size_t i = 0;  i < evalMarkers.size();  i++)
	{
		// Determine if any free cells exist
		if (!freeCellFound)
			freeCellFound = hasFreeCell(evalMarkers[i]);

		// Determine if row is a winning pattern
		MARKER_TYPE winMarker = isWinningRow(evalMarkers[i]);
		if (winMarker != NO_MARKER)
		{
			// Identify winning row so it can be highlighted
			rows = evalRows[i];
			cols = evalCols[i];
			rc = true;
			break;
		}
	}

	// If no winner found, check for free cells
	if (!rc && !freeCellFound)
		rc = true;

	return rc;
}

// Evaluate board for specified marker type
void CTicTacToe::evaluateBoard(MARKER_TYPE marker)
{
	// Evaluation data
	std::vector<MARKER_TYPE*> markers;
	std::vector<int*> scores;

	// Reset scores
	resetScores();

	// Evaluate all rows
	for (size_t i = 0;  i < evalMarkers.size();  i++)
		evaluateRow(marker, evalMarkers[i], evalScores[i]);
}

// Evaluate row for specified marker type
void CTicTacToe::evaluateRow(MARKER_TYPE playerMarker, std::vector<MARKER_TYPE*> const &markers, std::vector<int*> &scores)
{
	// Count markers
	int xCount = 0, oCount = 0, nilCount = 0;
	for (auto marker : markers)
	{
		if (*marker == X_MARKER)
			xCount++;
		else if (*marker == O_MARKER)
			oCount++;
		else
			nilCount++;
	}

	// Set player & opponent marker counts
	int pCount = 0, oppCount = 0;
	if (playerMarker == X_MARKER)
	{
		pCount = xCount;
		oppCount = oCount;
	}
	else if (playerMarker == O_MARKER)
	{
		pCount = oCount;
		oppCount = xCount;
	}

	// Set index to first unmarked cell
	int idxUnmarked = -1;
	for (size_t i = 0;  i < markers.size();  i++)
	{
		if (*markers[i] == NO_MARKER)
		{
			// Set index for win & block evaluations
			idxUnmarked = (int) i;
			break;
		}
	}

	// Evaluate placement conditions
	if (pCount == NUM_ROWS - 1)
	{
		// Favor cell that will yield a win
		if (idxUnmarked >= 0)
			*scores[idxUnmarked] += SCORE_TO_WIN;
	}
	else if (oppCount == NUM_ROWS - 1)
	{
		// Favor cell that will block opponent from winning
		if (idxUnmarked >= 0)
			*scores[idxUnmarked] += SCORE_TO_BLOCK;
	}
	else if (((pCount + 1) == (NUM_ROWS - 1)) && (oppCount == 0))
	{
		// Favor creating a run in an unblocked row
		for (size_t i = 0;  i < markers.size();  i++)
		{
			if (*markers[i] == NO_MARKER)
				*scores[i] += SCORE_TO_GROUP;
		}
	}
}
