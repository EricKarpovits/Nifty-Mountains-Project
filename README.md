# Nifty-Mountains-Project - Eric Karpovits

In essentence the goal is to compute the best cumulative elevation change

Given some topographic data it should be possible to calculate a "greedy lowest-elevation-change walk" from one side of a map to the other.

This program reads in a set of topographic mountain elevation data into a 2D array. Then calculates the best lowest-elevation-change path from West-to-East using various algorithms. The program also draws the actual mountain given the data into a 2D map using monochrome or interpolated colors and visualizes various paths through the mountains. This program will also return various total elevation changes given different "best" paths across the mountain and provide path results, a meaningful analysis, and insighful statistics, such as efficiency metrics.

The alogirthms used include: the "greedy" algorithm, 2 improved "greedy" alogortithms, and the [Floyd–Warshall Shortest Path algorithm](https://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm) algorithm which finds the best possible path.

This project is based on and solves the Standford Mountain Climb Project http://nifty.stanford.edu/2016/franke-mountain-paths/
