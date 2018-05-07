// Require TicTacToe library
//var tttGame = require('bindings')('tic-tac-toe');
var tttGame = require('./ticTacNode');

// Startup
tttGame.Startup();

// Loop variables
var marker = X_MARKER;
var row = -1;
var col = -1;

// Winning sequence locaiton
var winRows = [0, 0, 0];
var winCols = [0, 0, 0];


console.log(".............. BEGIN GAME ..............");


console.log(".............. END GAME ..............");


// Main Loop
var mainLoop = setInterval(updateCgdv, 500);
function updateCgdv()
{
	// Update CGDV on main UI thread
	cgdv.Update();
}



// Program entry point
int main()
{
	// Play until game over
	do
	{
		// Make best move for current marker
		tttGame.GetBestMove(marker, row, col);
		tttGame.SetMark(row, col, marker);

		// Change sides
		if (marker == X_MARKER)
			marker = O_MARKER;
		else
			marker = X_MARKER;

		// Print board
		std::cout << std::endl << "Turn #" << tttGame.GetTurnCount() << std::endl;
		tttGame.PrintBoard(winRows, winCols);
		std::cout << std::endl;
	}
	while (!tttGame.IsGameOver(winRows, winCols));

	// Game over
	std::cout << ".............. GAME OVER .............." << std::endl;

	// Indicate winner
	if (winRows.size() > 0)
	{
		// Print winner info.
		MARKER_TYPE winMark = tttGame.GetMark(winRows[0], winCols[0]);
		std::cout << "Winner: " << tttGame.markerName[winMark] << std::endl;
		tttGame.PrintBoard(winRows, winCols);
		std::cout << std::endl;
	}

