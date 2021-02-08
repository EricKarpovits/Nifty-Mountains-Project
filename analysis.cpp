#include "declarations.h"

// This function prints out a detailed anaylsis for the user
void PrintAnalysis(int bestGreedyTotalElev, int bestArbitraryTotalElev, int bestLowAsPossibleTotalElev, int bestFloydTotalElev) {

    // Analysis for the user
    cout << fixed << showpoint;
    cout << setprecision(2);

    cout << "The greedy walks best total elevation change is " << bestGreedyTotalElev << "m" << endl;

    cout << endl << "The arbitrary walks best total elevation change is " << bestArbitraryTotalElev << "m. The path is shorter by ";
    cout << bestGreedyTotalElev - bestArbitraryTotalElev << "m (compared to greedy)." << endl << "The path has an efficiency better by ";
    cout << float(bestGreedyTotalElev) / bestArbitraryTotalElev << " times (compared to greedy)." << endl;

    cout << endl << "The low as possible best total elevation change is " << bestLowAsPossibleTotalElev << "m. The path is shorter by ";
    cout << bestGreedyTotalElev - bestLowAsPossibleTotalElev << "m (compared to greedy)." << endl << "The path has an efficiency better by ";
    cout << float(bestGreedyTotalElev) / bestLowAsPossibleTotalElev << " times (compared to greedy)." << endl;

    cout << endl << "The floyd best total elevation change is " << bestLowAsPossibleTotalElev << "m. The path is shorter by ";
    cout << bestGreedyTotalElev - bestFloydTotalElev << "m (compared to greedy)." << endl <<"The path has an efficiency better by ";
    cout << float(bestGreedyTotalElev) / bestFloydTotalElev << " times (compared to greedy)." << endl;

}
