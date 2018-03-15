#ifndef __CTURNLOG_H__
#define __CTURNLOG_H__

#include <vector>

// Marker type for each board cell
typedef enum {
	NO_MARKER = 0, X_MARKER, O_MARKER
} MARKER_TYPE;

// Turn log class
class CTurnLog
{
public:
	// Default constructor
	CTurnLog();

	// Destructor
	virtual ~CTurnLog();

	// Clear log
	void Clear(void);

	// Undo most recent turn
	void Undo(void);

	// Add next turn to the log
	void Add(int row, int col, MARKER_TYPE marker);

	// Get number of turns currently stored in log
	int GetTurnCount(void);

	// Get last turn data (returns FALSE if unavailable)
	bool GetLastTurn(int &row, int &col, MARKER_TYPE &marker);

	// Get specified one-based turn data (returns FALSE if unavailable)
	bool GetTurn(int turn, int &row, int &col, MARKER_TYPE &marker);

protected:
	// Turn sequence (for playback and undo)
	std::vector<int> turnRow;
	std::vector<int> turnCol;
	std::vector<MARKER_TYPE> turnMarker;
};

#endif // __CTURNLOG_H__
