#include "declarations.h"

extern ALLEGRO_FONT *arial;
extern ALLEGRO_DISPLAY *display;

// Floyd main function, returns best elevation
int FloydMain(apmatrix<short> elevations, ALLEGRO_COLOR YELLOW){

    // Declare variables and matrices
    apmatrix<short> effortSpent(ROWS, columnS, 0);
    apmatrix<NEXT_ROW_CHANGE> floydIndex(ROWS, columnS);
    int bestElevChange = 0;
    int bestRow = 0;

    // Find the least effort spent for all columns
    for (int startingcolumn = 1; startingcolumn < columnS; startingcolumn++) {
        Floyd(elevations, startingcolumn, effortSpent, floydIndex);
    }

    // This finds which row the Floyd path starts at, finds the best total elevation change
    for (int i = 0; i < ROWS; i++) {
        if (i == 0){
            bestElevChange = effortSpent[i][columnS - 1];
            bestRow = i;
        }
        if (effortSpent[i][columnS - 1] < bestElevChange){
            bestElevChange = effortSpent[i][columnS - 1];
            bestRow = i;
        }
    }

    // Has to be drawn from right to left as the the total elevations are at the right
    int currentRow = bestRow;
    for (int currentcolumn = columnS - 1; currentcolumn > -1; currentcolumn--){

        // Basically what is happening is that the program is retracing its steps to draw out how it got to
        // the best total elevation possible
        if (floydIndex[currentRow][currentcolumn] == UP){
            currentRow --;
        } else if (floydIndex[currentRow][currentcolumn] == DOWN){
            currentRow ++;
        }
        al_draw_filled_rectangle(currentcolumn - 1, currentRow - 1, currentcolumn + 1, currentRow + 1, YELLOW);
        if (currentcolumn % 100 == 0) {
            al_flip_display();
        }
    }
    al_draw_textf(arial, YELLOW, 20, ROWS + 148, 0,
                  "Best of floyd walks is at row %d with a total elevation of %dm", currentRow, bestElevChange);
    al_flip_display();

    return bestElevChange;
}

// Floyd algorithm
void Floyd(apmatrix<short> elevation, int column, apmatrix<short> &effortSpent, apmatrix<NEXT_ROW_CHANGE> &floydIndex){
    int fwdDown = 0, fwd = 0, fwdUp = 0;
    int previouscolumn = column - 1;
    int maxArrayRow = elevation.numrows() - 1;

    //This part only applies to the first row since there is no row above the first, and the normal algorithm doesn't work
    fwd = effortSpent[0][previouscolumn] + abs(elevation[0][previouscolumn] - elevation[0][column]);
    fwdUp = effortSpent[1][previouscolumn] + abs(elevation[1][previouscolumn] - elevation[0][column]);

    // Decides more efficient path, prefers going forward
    if (fwd <= fwdUp){
        effortSpent[0][column] = fwd;
        // Basically the Floyd index is a matrix running in parallel keeping track of how to return back to the start from
        // the best total elevation change
        floydIndex[0][column] = STRAIGHT;
    } else {
        effortSpent[0][column] = fwdUp;
        floydIndex[0][column] = DOWN;
    }

    for (int currentRow = 1; currentRow < maxArrayRow; currentRow++){
        int currentElev = elevation[currentRow][column];

        // Go down a row
        fwdDown = effortSpent[currentRow - 1][previouscolumn] + abs(elevation[currentRow - 1][previouscolumn] - currentElev);

        // Stay same row and go straight
        fwd = effortSpent[currentRow][previouscolumn] + abs(elevation[currentRow][previouscolumn] - currentElev);

        // Go up a row
        fwdUp = effortSpent[currentRow + 1][previouscolumn] + abs(elevation[currentRow + 1][previouscolumn] - currentElev);

        // Decides most efficient effort spent to get to a particular spot if there is a more efficient path, prefers forward
        effortSpent[currentRow][column] = fwd;
        floydIndex[currentRow][column] = STRAIGHT;

        if (fwdDown < effortSpent[currentRow][column]){
            effortSpent[currentRow][column] = fwdDown;
            floydIndex[currentRow][column] = UP;
        }
        if (fwdUp < effortSpent[currentRow][column]){
            effortSpent[currentRow][column] = fwdUp;
            floydIndex[currentRow][column] = DOWN;
        }
    }
    //Only for last row since there is no row below it so it needs special treatment
    fwd = effortSpent[maxArrayRow][previouscolumn] + abs(elevation[maxArrayRow][previouscolumn] - elevation[maxArrayRow][column]);
    fwdDown = effortSpent[maxArrayRow - 1][previouscolumn] + abs(elevation[maxArrayRow - 1][previouscolumn] - elevation[maxArrayRow][column]);

    // Decides most efficient path, prefers going fwd
    if (fwd < fwdDown){
        effortSpent[maxArrayRow][column] = fwd;
        floydIndex[maxArrayRow][column] = STRAIGHT;
    } else {
        effortSpent[maxArrayRow][column] = fwdDown;
        floydIndex[maxArrayRow][column] = UP;
    }
}
