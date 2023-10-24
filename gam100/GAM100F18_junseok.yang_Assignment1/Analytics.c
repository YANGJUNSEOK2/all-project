/******************************************************************************/
/*!
\file   Analytics.c
\author  junseok.yang
\par    Course: GAM100
\par    Copyright ?2016 DigiPen (USA) Corporation.
\brief	this program is initializes and counts.
*/
/******************************************************************************/

#include "stdafx.h"
#include "Analytics.h"

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

// Define a structure containing all analytics data.

// Analytics for a single line of input.
static  int lineTokenCount;         // Total number of tokens on the current line.
static  int lineCharacterCount;     // Total number of characters on the current line, excluding whitespace.
static  int lineMaxTokenLength;     // Character length of the longest token on the line.

                                        // Analytics for all lines of input during a single session.
static  int totalTokenCount;        // Total number of tokens on all lines.
static  int totalCharacterCount;    // Total number of characters on all lines, excluding whitespace.
static  int totalMaxTokenLength;    // Character length of the longest token on the line.

                                        //------------------------------------------------------------------------------
                                        // Public Variables:
                                        //------------------------------------------------------------------------------

                                        //------------------------------------------------------------------------------
                                        // Private Variables:
                                        // WARNING: DO NOT ADD, REMOVE, OR MODIFY ANY PRIVATE VARIABLES!
                                        //------------------------------------------------------------------------------


                                        //------------------------------------------------------------------------------
                                        // Private Function Declarations:
                                        //------------------------------------------------------------------------------

                                        //------------------------------------------------------------------------------
                                        // Public Functions:
                                        //------------------------------------------------------------------------------

                                        // Initialize the analytics data (set all variables to zero).
void AnalyticsInit()
{
    lineTokenCount = 0, lineCharacterCount = 0, lineMaxTokenLength = 0,
        totalTokenCount = 0, totalCharacterCount = 0, totalMaxTokenLength = 0;
    // TODO: Initialize (zero out) all of the analytics data.
    //   Note: You may either call memset on the entire structure or
    //   initialize each individual variable separately.
}

// Increment the number of tokens that have been encountered.
void AnalyticsIncreaseTokenCount()
{
    lineTokenCount++;
    // TODO: Increment the line token count by 1.
}

// Update the line character counts.
void AnalyticsUpdateCharacterCount(int tokenLength)
{
    lineCharacterCount += tokenLength;
    // TODO: Add the current token length to the line character count.
}

// Update the maximum token length.
void AnalyticsUpdateMaxTokenLength(int tokenLength)
{
    lineMaxTokenLength = max(lineMaxTokenLength, tokenLength);
    // TODO: Determine the longest token length for the current line.
    // Hint: a = max(a, b)
}

// Add the line analytics to the total analytics.
void AnalyticsAddLineDataToTotal()
{
    totalCharacterCount += lineCharacterCount;
    // TODO: Add the line character count to the total character count.
    totalTokenCount += lineTokenCount;
    // TODO: Add the line token count to the total token count.
    totalMaxTokenLength = max(totalMaxTokenLength, lineMaxTokenLength);
    /*totalMaxTokenLength = max(totalMaxTokenLength, totalCharacterCount);*/
    // TODO: Determine the longest token length for the entire session (all lines).
    // Hint: a = max(a, b)
}

// Reset (zero out) the analytics data for a single line of text.
void AnalyticsResetLineData()
{
    lineTokenCount = 0, lineCharacterCount = 0, lineMaxTokenLength = 0;

    // TODO: Reset (zero out) the analytics data for a single line of text.
}

//------------------------------------------------------------------------------
// Public Functions: DO NOT MODIFY THIS CODE!
//------------------------------------------------------------------------------

// Print out the analytics data for a single line of text.
// WARNING: DO NOT MODIFY THIS FUNCTION!
void AnalyticsPrintLineData()
{
    printf("Line Analytics: Token Count = %d, Character Count = %d, Max Token Length = %d\n",
        lineTokenCount,
        lineCharacterCount,
        lineMaxTokenLength);
}

// Print out the analytics data for all lines of text in a single session.
// WARNING: DO NOT MODIFY THIS FUNCTION!
void AnalyticsPrintTotalData()
{
    printf("Total Analytics: Token Count = %d, Character Count = %d, Max Token Length = %d\n",
        totalTokenCount,
        totalCharacterCount,
        totalMaxTokenLength);
}

// Verify that the line analytics data matches predetermined values.
// WARNING: DO NOT MODIFY THIS FUNCTION!
bool AnalyticsValidateLineData(int tokenCount, int characterCount, int maxTokenLength)
{
    bool isValid =
        (lineTokenCount == tokenCount) &&
        (lineCharacterCount == characterCount) &&
        (lineMaxTokenLength == maxTokenLength);

    return isValid;
}

// Verify that the total analytics data matches predetermined values.
// WARNING: DO NOT MODIFY THIS FUNCTION!
bool AnalyticsValidateTotalData(int tokenCount, int characterCount, int maxTokenLength)
{
    bool isValid =
        (totalTokenCount == tokenCount) &&
        (totalCharacterCount == characterCount) &&
        (totalMaxTokenLength == maxTokenLength);

    return isValid;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

