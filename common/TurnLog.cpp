// ****************************************************************************
//  CTurnLog class -- store and track game turns
// ****************************************************************************

#include <vector>

#include "TurnLog.h"

// Constructor
CTurnLog::CTurnLog()
{
}

// Destructor
CTurnLog::~CTurnLog()
{
}

// Get number of turns currently stored in log
int CTurnLog::GetTurnCount(void)
{
	// Just use vector size
	return (int) turnRow.size();
}

// Clear log
void CTurnLog::Clear(void)
{
	// Clear all data
	turnRow.clear();
	turnCol.clear();
	turnMarker.clear();
}

// Undo most recent turn
void CTurnLog::Undo(void)
{
	// Ensure there's something to remove
	if (!turnRow.empty())
	{
		// Remove most recent turn
		turnRow.pop_back();
		turnCol.pop_back();
		turnMarker.pop_back();
	}
}

// Add next turn to the log
void CTurnLog::Add(int row, int col, MARKER_TYPE marker)
{
	// Add specified turn
	turnRow.push_back(row);
	turnCol.push_back(col);
	turnMarker.push_back(marker);
}

// Get last turn data (returns FALSE if unavailable)
bool CTurnLog::GetLastTurn(int &row, int &col, MARKER_TYPE &marker)
{
	// Ensure there's something to get
	bool rc = false;
	if (!turnRow.empty())
	{
		// Get most recent turn
		row = turnRow.back();
		col = turnCol.back();
		marker = turnMarker.back();
		rc = true;
	}

	return rc;
}

// Get specified turn data (returns FALSE if unavailable)
bool CTurnLog::GetTurn(int turn, int &row, int &col, MARKER_TYPE &marker)
{
	// Turns are one-based from a user perspective
	bool rc = false;
	turn -= 1;

	// Ensure there's something to get
	if ((turn >= 0) && (turn < (int) turnRow.size()))
	{
		// Get specified turn
		row = turnRow[turn];
		col = turnCol[turn];
		marker = turnMarker[turn];
		rc = true;
	}

	return rc;
}
