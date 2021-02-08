#include "declarations.h"

// This function reads in the data from "colorado.dat"
int ReadInData (int row, int cols, apmatrix<short> &elevation) {

    // Initialize the file
    ifstream file("colorado.dat");

    // Check if file was opened properly and that there is a file
    if (!file) {
        return -1;
    }

    // Iterate through the file to load the array
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < cols; j++) {
            file >> elevation[i][j];
        }
    }
    // Close the file
    file.close();

    return 0;
}

// This function returns the minimum value in the map
short FindMin(const apmatrix<short> &elevations) {

    // Declare variables
    int minNumber;

    // Setting the min number to the first element
    minNumber = elevations[0][0];

    // Compares the min number to all elements of the matrix if one of them is less than the current min number, it replaces it
    for (int i = 0; i < elevations.numrows(); i++) {
        for (int j = 0; j < elevations.numcols(); j++) {
            if (minNumber > elevations[i][j]){
                minNumber = elevations[i][j];
            }
        }
    }
    return minNumber;
}

// This function returns the maximum value in the map
short FindMax(const apmatrix<short> &elevations) {
    // Declare variables
    int maxNumber;

    // Setting the min number to the first element
    maxNumber = elevations[0][0];

    // Compares the max number to all elements of the matrix if one of them is greater than the current max number, it replaces it
    for (int i = 0; i < elevations.numrows(); i++) {
        for (int j = 0; j < elevations.numcols(); j++) {
            if (maxNumber < elevations[i][j]){
                maxNumber = elevations[i][j];
            }
        }
    }
    return maxNumber;
}

// This reads in the matrix and draws the map
// Returns nothing
void DrawMap(apmatrix<short> &elevations, int maxNumber, int minNumber) {

    int red = 0, green = 0, blue = 0;
    float fraction;

    // Here I am drawing pixel by pixel
    for (int i = 0; i < elevations.numrows(); i++) {
        for (int j = 0; j < elevations.numcols(); j++) {

            // For this map drawing I interpolated colours from green to brown (graphics extension #2)
            // Instead of having 1 monochromatic colour I did a lot of research how to interpolate colours
            // The interpolation is done in RGB and the difference in colours is not big enough for RBG,
            // therefore there is not as much detailing to interpolate colours in RGB. If I had more time
            // I would have done the interpolation in HSV as there is more separation between colours and would
            // allow for details.

            fraction = (float(elevations[i][j]) - minNumber) / (maxNumber - minNumber);

            red = (105 - 0) * fraction + 0;
            green = (0 - 155) * fraction + 155;
            blue = (0 - 155) * fraction + 155;

            al_draw_filled_rectangle(j, i, j + 1, i + 1, al_map_rgb(red, green, blue));
        }
    }
}
