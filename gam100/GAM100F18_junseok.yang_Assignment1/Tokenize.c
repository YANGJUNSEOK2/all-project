/******************************************************************************/
/*!
\file   Tokenize.c
\author junseok.yang
\par    Course: GAM100
\par    Copyright ?2016 DigiPen (USA) Corporation.
\brief
*/
/******************************************************************************/

#include "stdafx.h"
#include "Analytics.h"
#include "Game.h"
#include "Tokenize.h"

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Initialize the Tokenize module.
void TokenizeInit()
{
    AnalyticsInit();
    // TODO: Initialize the Analytics module.
}

// Tokenize and parse a single line of text.
void TokenizeParseLine(char* inputBuffer, rsize_t bufferLength)
{
    // Pointer to keep track of the current location in the string (for tokenizing).
    char* nextToken = inputBuffer;

    while (true)
    {
        // Extract the next token from the string.
        char* token = strtok_s(nextToken, " \t\n", &nextToken);

        //printf_s("%s\n", token);
        if (token == NULL)
        {
            break;
        }
        // TODO: Break out of the while loop if a token was not found (token == NULL).
        AnalyticsIncreaseTokenCount();
        // TODO: Increase the token count for the current line of text.
        int length = strlen(token);
        // TODO: Determine the number of characters in the token.
        AnalyticsUpdateCharacterCount(length);
        // TODO: Update the character count for the current line of text.
        AnalyticsUpdateMaxTokenLength(length);
        // TODO: Update the maximum token length for the current line of text.

        // EXAMPLE: If the user enters "hello", then respond with "Hello World!".
        if (strncmp(token, "hello", (unsigned)_countof("hello")) == 0)
        {
            printf("Hello World!\n");
        }
       /* if (token=="quit"|| "QUIT")*/
        if (strncmp(token, "QUIT", (unsigned)_countof("QUIT")) == 0|| strncmp(token, "quit", (unsigned)_countof("quit")) == 0)
            // TODO: Check for a "quit" or "QUIT" token.
        {
            GameExit();
            // TODO: Tell the Game module to stop running.
        }
    }
    AnalyticsPrintLineData();
    // TODO: Print the analytics data for a single line of text.
    AnalyticsAddLineDataToTotal();
    // TODO: Add the line analytics data to the total analytics.
    AnalyticsResetLineData();
    // TODO: Reset the analytics data for a single line of text.
    AnalyticsPrintTotalData();
    // TODO: Print the analytics data for the entire session (Total).
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------
