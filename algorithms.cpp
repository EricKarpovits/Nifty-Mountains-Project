#include "declarations.h"

// This function draws the paths for each of the greedy algorithm variations
// Returns the total elevation change of the path
int DrawPath(apmatrix<short> elevation, int startingRow, int startingcolumn, ALLEGRO_COLOR colour, ALGORITHM algorithm, bool draw) {
    // Declare variables
    int fwdUp = 0, fwd = 0, fwdDown = 0;
    int totalElevChange = 0;
    int currentRow = startingRow;
    NEXT_ROW_CHANGE nextRow;

    for (int column = startingcolumn; column < elevation.numcols() - 1; column++) {

        // Greedy algorithm
        if (algorithm == GREEDY_FORWARD) {

            // Find next step, decide which is best and finally select it
            NextStepAlgoGreedy(fwdUp, fwdDown, fwd, elevation, currentRow, column);
            nextRow = DecideStep(fwdUp, fwdDown, fwd);
            totalElevChange += SelectNextRow(fwdUp, fwdDown, fwd, nextRow, currentRow);

        // Greedy algorithm that stays towards the lowest elevation possible
        } else if (algorithm == GREEDY_LOWEST_ELEVATION) {

            // Find next step, decide which is best and finally select it
            NextStepAlgoLowestPossible(fwdUp, fwdDown, fwd, elevation, currentRow, column);
            nextRow = DecideStep(fwdUp, fwdDown, fwd);

            // Need to use this next step greedy algorithm to find the absolute value delta change of the elevation change
            NextStepAlgoGreedy(fwdUp, fwdDown, fwd, elevation, currentRow, column);
            totalElevChange += SelectNextRow(fwdUp, fwdDown, fwd, nextRow, currentRow);

        // Greedy algorithm reverse part 1; for now goes forward from the specific x,y location
        } else if (algorithm == GREEDY_REVERSE) {

            NextStepAlgoGreedy(fwdUp, fwdDown, fwd, elevation, currentRow, column);
            nextRow = DecideStep(fwdUp, fwdDown, fwd);
            totalElevChange += SelectNextRow(fwdUp, fwdDown, fwd, nextRow, currentRow);
        }

        // Draw the path pixel by pixel
        if (!draw && algorithm != GREEDY_REVERSE) {
            al_draw_filled_rectangle(column, currentRow, column + 1, currentRow + 1, colour);
        // Makes pixels more visible, for best paths
        } else if (draw){
            al_draw_filled_rectangle(column, currentRow, column + 2, currentRow + 2, colour);
        }
        if (column % 100 == 0) {
            al_flip_display();
        }
    }

    // Second part of the greedy algorithm that actually goes in reverse
    if (algorithm == GREEDY_REVERSE) {
        currentRow = startingRow;
        for (int column = startingcolumn; column > 0; column--) {

            NextStepAlgoReverse(fwdUp, fwdDown, fwd, elevation, currentRow, column);
            nextRow = DecideStep(fwdUp, fwdDown, fwd);

            totalElevChange += SelectNextRow(fwdUp, fwdDown, fwd, nextRow, currentRow);

            if (draw){
                al_draw_filled_rectangle(column, currentRow, column + 2, currentRow + 2, colour);
                if (column % 100 == 0) {
                    al_flip_display();
                }
            }
        }
    }
    return totalElevChange;
}

// Find the possible values of the next step of the greedy algorithm
void NextStepAlgoGreedy(int &fwdUp, int &fwdDown, int &fwd, apmatrix<short> &elevation, int currentRow, int column) {

    if (currentRow > 0) {
        fwdUp = abs(elevation[currentRow][column] - elevation[currentRow - 1][column + 1]);
    } else{
        // -1 is a value that no elevation can reach and it is a must as it is impossible to find the elevation above row 0
        fwdUp = -1;
    }

    if (currentRow < elevation.numrows() - 1) {
        fwdDown = abs(elevation[currentRow][column] - elevation[currentRow + 1][column + 1]);
    } else {
        // When the current row is at the bottom, cannot go fwd-down as it is the boundary of matrix
        fwdDown = -1;
    }

    // Can always go forward
    fwd = abs(elevation[currentRow][column] - elevation[currentRow][column + 1]);
}

// This variation of the greedy algorithm finds the values of the next step that are the lowest elevation possible, prefers downhill
void NextStepAlgoLowestPossible(int &fwdUp, int &fwdDown, int &fwd, apmatrix<short> &elevation, int currentRow, int column) {

    if (currentRow > 0) {
        fwdUp = elevation[currentRow - 1][column + 1];
    } else {
        fwdUp = -1;
    }

    if (currentRow < elevation.numrows() - 1) {
        fwdDown = elevation[currentRow + 1][column + 1];
    } else {
        fwdDown = -1;
    }

    fwd = elevation[currentRow][column + 1];
}

// This variation of the greedy algorithm finds the values of the next step in the reverse direction
void NextStepAlgoReverse(int &fwdUp, int &fwdDown, int &fwd, apmatrix<short> &elevation, int currentRow, int column) {

    if (currentRow > 0) {
        fwdUp = abs(elevation[currentRow][column] - elevation[currentRow - 1][column - 1]);
    } else {
        fwdUp = -1;
    }

    if (currentRow < elevation.numrows() - 1) {
        fwdDown = abs(elevation[currentRow][column] - elevation[currentRow + 1][column - 1]);
    } else {
        fwdDown = -1;
    }

    fwd = abs(elevation[currentRow][column] - elevation[currentRow][column - 1]);
}

// Greedy algorithm, decisions of next step, prefers going straight, however will take the lowest option, probably the most efficient
// way to make this algorithm
NEXT_ROW_CHANGE DecideStep(int fwdUp, int fwdDown, int fwd) {

    // The requirement is to move forward if all elevations are equal
    NEXT_ROW_CHANGE nextRowChange = STRAIGHT;
    int bestRow = fwd;

    if (fwdUp != -1 && fwdUp < bestRow) {
        nextRowChange = UP;
        bestRow = fwdUp;
    }

    if (fwdDown != -1 && fwdDown < bestRow) {
        nextRowChange = DOWN;
        bestRow = fwdDown;
    }

    // In case both forward up and forward down elevations are equal and less than forward
    // the requirement is to randomly choose between them
    // Above logic would always choose forward up as lowest, so we adding randomizer to
    // choose forward down 50% of the cases

    if(fwdUp == fwdDown && fwdUp < fwd && (rand() % 2 == 1)) {
          nextRowChange = DOWN;
    }

    return nextRowChange;
}

// This function selects the next row and modifies current row and returns the elevation of the next step
int SelectNextRow(int fwdUp, int fwdDown, int fwd, int nextRow, int &currentRow) {

    if(nextRow == STRAIGHT) {
        return fwd;
    } else if (nextRow == UP) {
        currentRow --;
        return fwdUp;
    } else {
        currentRow ++;
        return fwdDown;
    }
}

// This function finds the best elevation change and returns the row is starts on. It also will modify the best column
// if the specific algorithm needs it.
int FindBestRow(int totalElevChange, int startingRow, int &bestElevChange, int bestRow, int &bestcolumn, int startingcolumn) {

    if (startingRow == 0) {
        bestElevChange = totalElevChange;
        bestcolumn = startingcolumn;
        return startingRow;
    } else if (totalElevChange < bestElevChange) {
        bestcolumn = startingcolumn;
        bestElevChange = totalElevChange;
        return startingRow;
    }
    return bestRow;
}
