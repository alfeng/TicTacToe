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
		tttGame.SetMark(row, col, X_MARKER);
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
	v8::Local<v8::Array> retVals = Nan::New<v8::Array>(2);
	Nan::Set(retVals, 0, Nan::New(row));
	Nan::Set(retVals, 1, Nan::New(col));

	// Return selected cell to Javascript
	info.GetReturnValue().Set(retVals);
}

// Check if game is over
NAN_METHOD(IsGameOver)
{
	// Winning marker (-1 = game not over)
	int winMark = -1;

	// Winning sequence location
	std::vector<int> winRows;
	std::vector<int> winCols;

	// Generic JS object for return data
	v8::Local<v8::Object> jsObject = Nan::New<v8::Object>();

	// Check it
	bool gameOver = tttGame.IsGameOver(winRows, winCols);
	if (gameOver)
	{
		// Determine type of end game
		winMark = 0;
		if (winRows.size() > 0)
		{
			// Determine winner
			winMark = (int) tttGame.GetMark(winRows[0], winCols[0]);

			// Create JS arrays of win row data
			v8::Local<v8::Array> jsWinRows = Nan::New<v8::Array>(NUM_ROWS);
			v8::Local<v8::Array> jsWinCols = Nan::New<v8::Array>(NUM_COLS);
			for (int i = 0;  i < (int) winRows.size();  i++)
			{
				// Set marker for this win cell
				Nan::Set(jsWinRows, i, Nan::New(winRows[i]));
				Nan::Set(jsWinCols, i, Nan::New(winCols[i]));
			}

			// Return win rows
			v8::Local<v8::String> arrayName = Nan::New("winRows").ToLocalChecked();
//			v8::Local<v8::Array> arrayValues = Nan::New(winRows).ToLocalChecked();
			Nan::Set(jsObject, arrayName, jsWinRows);

			// Return win colums
			arrayName = Nan::New("winCols").ToLocalChecked();
//			arrayValues = Nan::New(winCols).ToLocalChecked();
			Nan::Set(jsObject, arrayName, jsWinCols);
		}
	}

	// Set game over status
	v8::Local<v8::String> propName = Nan::New("winMark").ToLocalChecked();
	v8::Local<v8::Value> propValue = Nan::New(winMark);
	Nan::Set(jsObject, propName, propValue);

	// Return data to Javascript
	info.GetReturnValue().Set(jsObject);
}

// Get number of turns that have been played
NAN_METHOD(GetTurnCount)
{
	// Get count and return it to Javascript
	int count = tttGame.GetTurnCount();
	info.GetReturnValue().Set(count);
}

// Get marker at specified cell
NAN_METHOD(GetMark)
{
	// Set default
	MARKER_TYPE marker = NO_MARKER;

	// Validate parameters
	if (!info[0]->IsUndefined() && !info[1]->IsUndefined())
	{
		// Extract Javascript parameters (row, column)
		int row = Nan::To<int>(info[0]).FromJust();
		int col = Nan::To<int>(info[1]).FromJust();

		// Get it
		marker = tttGame.GetMark(row, col);
	}

	// Return marker value to Javascript
	info.GetReturnValue().Set((int) marker);
}

// Log current game board state
NAN_METHOD(PrintBoard)
{
	// Winning sequence location
	std::vector<int> winRows;
	std::vector<int> winCols;

	// Validate parameters
	if (!info[0]->IsUndefined() && !info[1]->IsUndefined())
	{
		// Extract Javascript arrays
//		v8::Local<v8::Array> jsWinRows = v8::Local<v8::Array>::Cast(info[0]);
//		v8::Local<v8::Array> jsWinCols = v8::Local<v8::Array>::Cast(info[1]);
		v8::Local<v8::Array> jsWinRows = info[0].As<v8::Array>();
		v8::Local<v8::Array> jsWinCols = info[1].As<v8::Array>();

		// Marshall arrays
		for (unsigned int i = 0;  i < jsWinRows->Length();  i++)
		{
			if (Nan::Has(jsWinRows, i).FromJust())
				winRows[i] = Nan::To<int>(Nan::Get(jsWinRows, i)).FromJust();
//				winRows[i] = Nan::Get(jsWinRows, i).ToLocalChecked()->NumberValue();

			if (Nan::Has(jsWinCols, i).FromJust())
				winCols[i] = Nan::To<int>(Nan::Get(jsWinCols, i)).FromJust();
//				winCols[i] = Nan::Get(jsWinCols, i).ToLocalChecked()->NumberValue();
		}
	}

	// Print board
	tttGame.PrintBoard(winRows, winCols);
}

// Module initialization logic
NAN_MODULE_INIT(Initialize)
{
	// Export CGDV methods
	NAN_EXPORT(target, NewGame);
	NAN_EXPORT(target, DoTurn);
	NAN_EXPORT(target, DoAiTurn);
	NAN_EXPORT(target, IsGameOver);
	NAN_EXPORT(target, GetMark);
	NAN_EXPORT(target, GetTurnCount);
	NAN_EXPORT(target, PrintBoard);
}

// Create the add-on module and initialize it (created with NAN_MODULE_INIT macro)
NODE_MODULE(tic-tac-svc, Initialize);

