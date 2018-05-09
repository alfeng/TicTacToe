// Require TicTacToe library
//var tttGame = require('bindings')('tic-tac-toe');
var tttGame = require('./TicTacSvc');

// Marker types
const NO_MARKER = 0;
const X_MARKER = 1;
const O_MARKER = 2;

// Marker names
var markerName = [" ", "X", "O"];

// Loop variables
var gameOver = false;
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
    // Determine best move for current marker
    var bestMove = tttGame.GetBestMove(marker, row, col);
    row = bestMove[0];
    col = bestMove[1];

    // Make the move
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

    // Check if game over, extract game data
    var winData = tttGame.IsGameOver(winRows, winCols);
    if (winData.winMark >= 0)
    {
        // Copy win row data
        gameOver = true;
        winRows = winData.winRows;
        winCols = winData.winCols;
    }
}
while (!gameOver);

console.log(".............. GAME OVER ..............");

// Print winner info.
var winMark = tttGame.GetMark(winRows[0], winCols[0]);
console.log("Winner: " + markerName[winMark]);
tttGame.PrintBoard(winRows, winCols);
console.log("\n");

