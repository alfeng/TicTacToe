package com.mythica.ticmytac

import android.os.Bundle
import android.os.Handler
import android.util.Log
import android.view.KeyEvent
import android.view.View
import android.widget.Button
import android.widget.ImageButton
import androidx.appcompat.app.AppCompatActivity
import androidx.core.content.ContextCompat
import kotlinx.android.synthetic.main.activity_main.*

// Single activity app
class MainActivity : AppCompatActivity()
{
    // Kotlin doesn't support the 'static' keyword, this is their workaround
    companion object
    {
        // Tag used for LogCat
        @Suppress("SpellCheckingInspection")
        private const val LOG_TAG = "TICTAC"

        // Used to load the 'native-lib' library on application startup.
        init
        {
            System.loadLibrary("native-lib")
        }
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    private external fun newGame()
    private external fun doTurn(row: Int, col: Int)
    private external fun doAITurn(turnData: CellData)
    private external fun isGameOver(rows: ArrayList<Int>, cols: ArrayList<Int>): Int

    // Keep track whos turn it is
    private var curPlayer = MarkerType.X
    private var humanPlayer = MarkerType.X
    private var aiPlayer = MarkerType.O

    // Button colors
    private var winColor: Int = 0
    private var buttonColor = IntArray(3)

    // Marker types
    enum class MarkerType(val value: Int) { NONE(0), X(1), O(2) }

    // Data associated with each button
    data class CellData(val row: Int = 0, val col: Int = 0)

    // Play buttons
    private val buttonMap = mapOf( R.id.button00 to CellData(0,0),
                                   R.id.button01 to CellData(0,1),
                                   R.id.button02 to CellData(0,2),
                                   R.id.button10 to CellData(1,0),
                                   R.id.button11 to CellData(1,1),
                                   R.id.button12 to CellData(1,2),
                                   R.id.button20 to CellData(2,0),
                                   R.id.button21 to CellData(2,1),
                                   R.id.button22 to CellData(2,2) )

    // Activity initialization
    override fun onCreate(savedInstanceState: Bundle?)
    {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        // Set button colors
        winColor = ContextCompat.getColor(this, R.color.winColor)
        buttonColor[0] = ContextCompat.getColor(this, R.color.nilColor)
        buttonColor[1] = ContextCompat.getColor(this, R.color.xColor)
        buttonColor[2] = ContextCompat.getColor(this, R.color.oColor)

        // Reset game board
        resetGameBoard()

        // Set onClickListener for new game button
        val button = findViewById<Button>(R.id.newGameButton)
        button.setOnClickListener(::onNewGameClick)

        // Set onClickListener for game buttons
        for ((key, value) in buttonMap)
        {
            val imgButton = findViewById<ImageButton>(key)
            imgButton.setOnClickListener(::onCellClick)
        }

        // Example of a call to a native method
//        textCopyright.text = stringFromJNI()
    }

    private fun onNewGameClick(view: View)
    {
        // Reset game AI
        newGame()

        // Reset game board
        resetGameBoard()
    }

    // Handler for play buttons
    private fun onCellClick(view: View)
    {
        // Ignore input unless it's the player's turn
        if (curPlayer == humanPlayer)
        {
            // Make human move
            makeHumanMove(view)

            // Switch to AI player
            switchPlayers()

            // Make move for AI
            if (!checkGameOver())
                Handler().postDelayed({makeAIMove()}, 500)
        }
    }

    // Make move for AI
    private fun makeHumanMove(view: View)
    {
        // Mark human button
        val button = this.findViewById(view.id) as ImageButton
        button.setColorFilter(buttonColor[curPlayer.value])
        button.isClickable = false

        // Do game turn
        if (buttonMap[view.id] != null)
            doTurn(buttonMap[view.id]?.row!!, buttonMap[view.id]?.col!!)
    }

    // Make move for AI
    private fun makeAIMove()
    {
        // Do AI turn
        curPlayer = aiPlayer
        val turnData = CellData(0,0)
        doAITurn(turnData)

        // Determine which button AI played
        for ((key, value) in buttonMap)
        {
            if ((value.row == turnData.row) && (value.col == turnData.col))
            {
                // Mark AI button
                val button = this.findViewById(key) as ImageButton
                button.setColorFilter(buttonColor[curPlayer.value])
                button.isClickable = false
            }
        }

        // Switch to human player
        switchPlayers()

        // Check for end game
        checkGameOver()
    }

    // Reset game board to initial state
    private fun resetGameBoard()
    {
        // Human goes first
        textCopyright.text = resources.getString(R.string.human_turn)
        curPlayer = humanPlayer

        // Reset color & state of all buttons
        for ((key, value) in buttonMap)
        {
            val button = this.findViewById(key) as ImageButton
            button.setColorFilter(buttonColor[MarkerType.NONE.value])
            button.isClickable = true
        }
    }

    // Check for end of game
    private fun checkGameOver() : Boolean
    {
        // Winner info.
        var rc = false
        val rows = arrayListOf<Int>(0, 1, 2)
        val cols = arrayListOf<Int>(0, 1, 2)

        // Check for end of game
        val winner = isGameOver(rows, cols)
        if (winner >= 0)
        {
            // Prevent button clicks
            curPlayer = MarkerType.NONE
            rc = true

            // Display winner
            textCopyright.text = resources.getString(R.string.game_over)
            if (winner == aiPlayer.value)
                textCopyright.text = resources.getString(R.string.ai_wins)
            else if (winner == humanPlayer.value)
                textCopyright.text = resources.getString(R.string.human_wins)

            // Highlight winning row if one is specified
            Log.v(LOG_TAG,"WINNING ROWS: " + Integer.toString(rows.size))
            if ((rows.size > 0) && (rows.size == cols.size))
            {
                // Highlight winning cells ('until' goes to rows.size-1)
                for (i in 0 until rows.size)
                {
                    // Search for each winning cell in the map
                    for ((key, value) in buttonMap)
                    {
                        // Find matching cell
                        if ((value.row == rows[i]) && (value.col == cols[i]))
                        {
                            // Blink winning cells (for now just change colors)
                            val button = this.findViewById(key) as ImageButton
                            button.setColorFilter(winColor)

                            Log.v(LOG_TAG,"(" + rows[i] + "," + cols[i] + ")")
                        }
                    }
                }
            }
        }

        // Signal game over
        return rc
    }

    // Goto next player
    private fun switchPlayers()
    {
        // Determine current player
        if (curPlayer == humanPlayer)
        {
            // Switch to AI player
            textCopyright.text = resources.getString(R.string.ai_turn)
            curPlayer = aiPlayer
        }
        else
        {
            // Switch to human player
            textCopyright.text = resources.getString(R.string.human_turn)
            curPlayer = humanPlayer
        }
    }

    // Get keyboard input
    override fun onKeyUp(keyCode: Int, event: KeyEvent?): Boolean
    {
        var handled = false
        if (KeyEvent.KEYCODE_MENU == keyCode)
        {
            Log.v(LOG_TAG,"KEYCODE_MENU pressed")
            handled = true
        }
        else if (KeyEvent.KEYCODE_7 == keyCode)
        {
            Log.v(LOG_TAG,"KEYCODE_7 pressed")
            handled = true
        }

        return handled || super.onKeyDown(keyCode, event)
    }
}
