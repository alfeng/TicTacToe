// Require TicTacToe library
//var tttGame = require('bindings')('tic-tac-toe');
var tttGame = require('./ticTacNode');

// Set marker type values
const NO_MARKER = 0;
const X_MARKER = 1;
const Y_MARKER = 2;

// Loop variables
var marker = X_MARKER;
var row = -1;
var col = -1;

// Winning sequence locaiton
var winRows = [-1, -1, -1];
var winCols = [-1, -1, -1];

console.log(".............. BEGIN GAME ..............");
tttGame.NewGame();

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
    console.log("\n" + "Turn #" + tttGame.GetTurnCount());
    tttGame.PrintBoard(winRows, winCols);
    console.log("\n");
}
while (!tttGame.IsGameOver(winRows, winCols));



console.log(".............. END GAME ..............");




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

