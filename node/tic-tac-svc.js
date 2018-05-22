
// ****** THIS SHOULD BE CALLED ticTackToe because we need
// ****** the SERVICE to be a REST service that imports this one


// Require TicTacToe library
//var tttGame = require('bindings')('TicTacSvc');
var tttGame = require('./TicTacSvc');

// Marker types
export const NO_MARKER = 0;
export const X_MARKER = 1;
export const O_MARKER = 2;

// ********* MODULE EXPORTS ***********

// Start new game
exports.NewGame = function NewGame()
{
    // Call native method
    tttGame.NewGame();
}

// Get specified marker
exports.GetMark = function GetMark(row, column)
{
    // Call native method
    var marker = tttGame.GetMark(row, column);

    // Return marker type at that cell
    return marker;
}

// Set specified marker
exports.SetMark = function SetMark(row, column, marker)
{
    // Call native method
    tttGame.SetMark(row, column, marker);
}

// Get current turn count
exports.GetTurnCount = function GetTurnCount()
{
    // Call native method
    return tttGame.GetTurnCount();
}

// Get best possible move for specified marker
exports.GetBestMove = function GetBestMove(marker, row, column)
{
    // Call native method
    var bestRowCol = tttGame.GetBestMove(marker, row, column);

    // Return array containing best row & column
    return bestRowCol;
}

// Check if game over
exports.IsGameOver = function IsGameOver(row, column)
{
    // Returns custom object containing three fields
    //   winRows - Array of win row coordinates
    //   winCols - Array of win column coordinates
    //   winMark - Winning marker or -1 if game not over

    // Call native method
    return tttGame.IsGameOver(row, column);
}

// Get current turn count
exports.PrintBoard = function PrintBoard(winRows, winCols)
{
    // Call native method
    tttGame.PrintBoard(winRows, winCols);
}

