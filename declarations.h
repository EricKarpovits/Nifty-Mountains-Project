#ifndef DECLARATIONS_H_ // Checking if this header was defined so there are no double inclusions, saves memeory and prevents errors
#define DECLARATIONS_H_

#include <iostream>
#include <vector>
#include <math.h>
#include "apmatrix.h"
#include <fstream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <stdlib.h>
#include <time.h>
#include <iomanip>

using namespace std;

// Enum definitions
typedef enum {
    UP,
    STRAIGHT,
    DOWN
} NEXT_ROW_CHANGE;

typedef enum {
    GREEDY_FORWARD,
    GREEDY_LOWEST_ELEVATION,
    GREEDY_REVERSE,
    FLOYD
} ALGORITHM;

// Constants
const int START_AT_column_0 = 0;
const int columnS = 844;
const int ROWS = 480;

#endif // DECLARATIONS_H_

/// Prototypes
// Allegro prototypes
int InitializeAllegro(int width, int height, const char title[]);
bool EscapeKeypress();
void DrawLegend (ALLEGRO_COLOR WHITE, ALLEGRO_COLOR GREEN,ALLEGRO_COLOR RED, ALLEGRO_COLOR YELLOW, ALLEGRO_COLOR PINK, ALLEGRO_COLOR ORANGE);

// Draw map prototypes
void DrawMap(apmatrix<short> &elevations, int minNumber, int maxNumber);
short FindMin(const apmatrix<short> &elevations);
short FindMax(const apmatrix<short> &elevations);
int ReadInData(int row, int cols, apmatrix<short> &elevations);

// Algorithm prototypes
int DrawPath(apmatrix<short> elevation, int startingRow, int startingcolumn, ALLEGRO_COLOR colour, ALGORITHM algorithm, bool draw);
void NextStepAlgoGreedy(int &fwdUp, int &fwdDown, int &fwd, apmatrix<short> &elevation, int currentRow, int column);
void NextStepAlgoLowestPossible(int &fwdUp, int &fwdDown, int &fwd, apmatrix<short> &elevation, int currentRow, int column);
void NextStepAlgoReverse(int &fwdUp, int &fwdDown, int &fwd, apmatrix<short> &elevation, int currentRow, int column);
NEXT_ROW_CHANGE DecideStep(int fwdUp, int fwdDown, int fwd);
int SelectNextRow (int fwdUp, int fwdDown, int fwd, int nextRow, int &currentRow);
int FloydMain(apmatrix<short> elevations, ALLEGRO_COLOR YELLOW);
void Floyd (apmatrix<short> elevation, int column, apmatrix<short> &effortSpent, apmatrix<NEXT_ROW_CHANGE> &floydIndex);
int FindBestRow(int totalElevChange, int startingRow, int &bestElevChange, int bestRow, int &bestcolumn, int startingcolumn);

// Analysis prototypes
void PrintAnalysis(int bestGreedyTotalElev, int bestArbitraryTotalElev, int bestLowAsPossibleTotalElev, int bestFloydTotalElev);




