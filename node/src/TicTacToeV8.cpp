#ifdef THIS_FILE
#undef THIS_FILE
#endif
#define THIS_FILE "TicTacToeV8.cpp"

#include <nan.h>
#include "CTicTacToe.h"

// The game brain
CTicTacToe tttGame;

// ********************************************************************
//   Javascript interface
// ********************************************************************

// Init the TicTacToe Engine
NAN_METHOD(Startup)
{
	// Start a new game
	tttGame.NewGame();

	// Winning sequence location
	std::vector<int> winRows;
	std::vector<int> winCols;

	// Loop variables
	MARKER_TYPE marker = X_MARKER;
	int row = -1, col = -1;


	// Set Javascript status delegate
	// assume info[0]->IsFunction()
	jsStatusDelegate.Reset(info[0].As<v8::Function>());
}

// Shutdown CGDV on Main UI thread
NAN_METHOD(Shutdown)
{
	// Start CGDV
	tttGame->Shutdown();
}

// Reset game
NAN_METHOD(NewGame)
{
	// Reset game
	tttGame.NewGame();

	// Reset local state
}

// Do player turn
NAN_METHOD(DoTurn)
{
	// Validate parameters
	if (!info[0]->IsUndefined() && !info[1]->IsUndefined())
	{
		// Extract Javascript parameters (row, column)
		int row = Nan::To<int>(info[0]).FromJust();
		int col = Nan::To<int>(info[1]).FromJust();

		// Set player marker on specified ceel
		tttGame->SetMark(row, col, X_MARKER);
	}
}

// Do AI turn
NAN_METHOD(DoAiTurn)
{
	// Do AI move
	int row = -1, col = -1;
	tttGame.GetBestMove(O_MARKER, row, col);
	tttGame.SetMark(row, col, O_MARKER);

	// Set parameters to Javascript (row, col)
	v8::Local<v8::Array> retVals = Nan::New<v8::Array>(3);
	Nan::Set(retVals, 0, Nan::New(row));
	Nan::Set(retVals, 0, Nan::New(col));

	// Return selected cell to Javascript
	info.GetReturnValue().Set(retVals);
}

// Check if game is over
NAN_METHOD(IsGameOver)
{
	// Parameters are pointers to rowVector & colVector
	// to indicate winning cells (i.e. a WinRow).

	// Check for end game, retrieving any winning row
	bool gameOver = tttGame.IsGameOver(winRows, winCols);
	if (gameOver)
	{
		// Determine type of end game
	}

	// Set parameters to Javascript (gameOver, winRows, winCols)
}

// Module initialization logic
NAN_MODULE_INIT(Initialize)
{
	// Export CGDV methods
	NAN_EXPORT(target, Startup);
	NAN_EXPORT(target, Shutdown);
	NAN_EXPORT(target, NewGame);
	NAN_EXPORT(target, DoTurn);
	NAN_EXPORT(target, DoAiTurn);
	NAN_EXPORT(target, IsGameOver);
}

// Create the add-on module and initialize it (created with NAN_MODULE_INIT macro)
NODE_MODULE(tic-tac-svc, Initialize);

