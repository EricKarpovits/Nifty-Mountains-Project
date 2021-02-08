/*****************************************************************
 * Eric Karpovits - Nifty Mountains Assignment                   *
 * Includes the Greedy algorithm, 3 algorithm extensions,        *
 * and 1 graphic extension.                                      *
 *                                                               *
 * Last Modified: October 5, 2020                                *
 *****************************************************************/

#include "declarations.h"

ALLEGRO_FONT *arial;
ALLEGRO_DISPLAY *display;

int main(int argc, char *argv[]) {

    // Declare variables
    apmatrix<short> elevations(ROWS, columnS, 0);
    int minNum = 0;
    int maxNum = 0;
    int returnCode = 0;
    int totalElevChange = 0;
    int bestcolumn = 0;
    int bestRow = 0;
    bool draw = false;
    int bestGreedyTotalElev = 0;
    int bestArbitraryTotalElev = 0;
    int bestLowAsPossibleTotalElev = 0;
    int bestFloydTotalElev = 0;

    // Randomize timer
    srand (time(NULL));

    // This function reads in the data from the file, checks for error codes
    returnCode = ReadInData(ROWS, columnS, elevations);
    if (returnCode != 0) {
        return returnCode;
    }

    // Return the minimum value in the map
    minNum = FindMin(elevations);

    // Return the max value in the map
    maxNum = FindMax(elevations);

    // ALLEGRO SETUP STUFF
    returnCode = InitializeAllegro(columnS, ROWS + 200, "Nifty Mountains");
    if (returnCode != 0) {
        return returnCode;
    }
    // Colours
    ALLEGRO_COLOR COLOUR_RED = al_map_rgb(255, 0, 0);	    // Red
    ALLEGRO_COLOR COLOUR_GREEN = al_map_rgb(0, 255, 0);	    // Green
    ALLEGRO_COLOR COLOUR_YELLOW = al_map_rgb(255, 255, 0);	// Yellow
    ALLEGRO_COLOR COLOUR_WHITE = al_map_rgb(255, 255, 255);// White
    ALLEGRO_COLOR COLOUR_PINK = al_map_rgb(255, 0, 255);    // Pink
    ALLEGRO_COLOR COLOUR_ORANGE = al_map_rgb(255, 176, 102);// Orange

    // Draw map
    DrawMap(elevations, maxNum, minNum);

    // Draw a legend
    DrawLegend(COLOUR_WHITE, COLOUR_GREEN, COLOUR_RED, COLOUR_YELLOW, COLOUR_PINK, COLOUR_ORANGE);
    al_flip_display();


    /// Greedy paths and algorithm
    // Draw a red path for every row
    draw = false;
    for (int startingRow = 0; startingRow < ROWS; startingRow++) {
        totalElevChange = DrawPath(elevations, startingRow, START_AT_column_0, COLOUR_RED, GREEDY_FORWARD, draw);
        bestRow = FindBestRow(totalElevChange, startingRow, bestGreedyTotalElev, bestRow, bestcolumn, START_AT_column_0);
    }
    // Draw the best greedy algorithm path
    draw = true;
    DrawPath(elevations, bestRow, START_AT_column_0, COLOUR_GREEN, GREEDY_FORWARD, draw);
    al_draw_textf(arial, COLOUR_GREEN, 20, ROWS + 56, 0,
                  "Best of the greedy walks at row %d with a total elevation of %dm", bestRow, bestGreedyTotalElev);
    al_flip_display();


    /// Greedy algorithm that goes in both directs starting at an arbitrary x,y coordinates Extension #1
    // This extension does not drawing anything as there would be way too many greedy paths starting at multiple columns for each row.
    draw = false;
    int startingcolumn = 0;
    for (int startingRow = 0; startingRow < ROWS; startingRow++) {

        // Randomize starting column for each row
        startingcolumn = rand() % (columnS - 1);

        totalElevChange = DrawPath(elevations, startingRow, startingcolumn, COLOUR_PINK, GREEDY_REVERSE, draw);
        bestRow = FindBestRow(totalElevChange, startingRow, bestArbitraryTotalElev, bestRow, bestcolumn, startingcolumn);
    }

    // Drawing the best arbitrary greedy path that goes in both directions
    draw = true;
    totalElevChange = DrawPath(elevations, bestRow, bestcolumn, COLOUR_PINK, GREEDY_REVERSE, draw);
    al_draw_textf(arial, COLOUR_PINK, 20, ROWS + 79, 0,
                  "Best of both directions algorithm starting at arbitrary locations is at row %d, column %d with a total elevation of %dm",
                  bestRow, bestcolumn, bestArbitraryTotalElev);
    al_flip_display();


    /// Greedy algorithm that stays to the lowest elevation possible (Extension 2)
    // Drawing all the lowest elevation paths in yellow
    draw = false;
    al_draw_text(arial, COLOUR_ORANGE, 20, ROWS + 102, 0, "Low as possible algorithm starting at each row");
    for (int startingRow = 0; startingRow < ROWS; startingRow++) {
        totalElevChange = DrawPath(elevations, startingRow, START_AT_column_0, COLOUR_ORANGE, GREEDY_LOWEST_ELEVATION, draw);
        bestRow = FindBestRow(totalElevChange, startingRow, bestLowAsPossibleTotalElev, bestRow, bestcolumn, START_AT_column_0);
    }

    // Drawing the best lowest greedy algorithm path (Extension #2)
    draw = true;
    totalElevChange = DrawPath(elevations, bestRow, START_AT_column_0, COLOUR_WHITE, GREEDY_LOWEST_ELEVATION, draw);
    al_draw_textf(arial, COLOUR_WHITE, 20, ROWS + 125, 0,
                  "Best of low as possible algorithm is at row %d with a total elevation of %dm", bestRow, bestLowAsPossibleTotalElev);
    al_flip_display();


    /// It's time for the Floyd time!
    // My variation of the Floyd algorithm that took forever to construct, however it was well worth it, with an outstanding total elevation change (around 7000)
    bestFloydTotalElev = FloydMain(elevations, COLOUR_YELLOW);

    // Function that prints out a detailed analysis for the user on the console screen
    PrintAnalysis(bestGreedyTotalElev, bestArbitraryTotalElev, bestLowAsPossibleTotalElev, bestFloydTotalElev);

    // Wait until escape key is pressed to exit
    while (!EscapeKeypress());

    return 0;
}



