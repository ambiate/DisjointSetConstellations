/*
 *Author: Jonathan Lee Drouillard
 *Description: Given a set points and a distance, calculate
               the amount of constellations (points with a
               delta less than or equal to the distance).
 *Date Created: 20120907
 *Date Last Modified: 20120911

 *Data Abstraction
    Creates integer caseNumber for current test case, output purposes.
    Creates integer numTestCases for number of test cases.
    Creates integer numPairs to store the number of pairs in a test case.
    Creates double delta for the max distance between points to be a constellation.
    Creates disjointSet dset to store sets of numbers, each corresponding to a point.
    Creates array of Points points for storing x and y pair coordinates.
    Creates integer MAX_STARS for allocation of the disjoint set.
 *Input
    Read in amount of test cases as an integer.
    Read in number of pairs for a test case as an integer.
    Read in delta as double for measuring distance between points.
    Read in points as pairs of doubles in a x y coordinate setup.
    Continue this process until all test cases are finished.
 *Process/Implementation
    User inputs amount of test cases for the program.  For each test case, the
    user inputs an amount of stars and a max distance between stars to be a
    constellation.  User then inputs the amount of stars as x y coordinate pairs.
    
    Program reads in n test cases, and begins to loop n test case times.
    Program reads in amount of stars and a distance between stars.
    Program begins to loop for the amount of stars, placing each one into an
    array of points/coordinate pairs.
    Program creates a disjoint set and initializes it to the amount of stars.
    If there are 0 stars in the test case, the program will return 0 constellations.
    Program loops from first coordinate pair to next to last coordinate pair in
    the array.
    While looping through each of the coordinate pairs, the program will
    once again loop through the pair of coordinates in front of the outer loop.
    This way, a coordinate pair is never checked twice against another pair.
    The each point in the array will be compared to the next point in the array
    up to the end point.
    The program will check each coordinate pair to see if the distance between
    the point of interest and the following points creates a constellation.
    If the distance not greater than the program's inputted delta, the program
    will check if the points are already in the same set.  If they points are not
    in the same set, an union will be performed to place them in the same set.
    This continues on until all except the last element of the outer loop have
    performed the distance/in set check.  Afterwards, the program asks the
    disjoint set to provide the number of constellations.  This is calculated by
    checking which sets still have their own set number.  The program continues
    this process until it runs out of test cases.
 *Output
    Case number corresponding to a test case,
    followed by the amount of constellations found for that test case.
 *Assumptions
    Assumes the user follows all input methods in order, ie:
    -#1- n test cases (n<=50)
    -#2- n amount of stars (0<=n<=1000)
    -#3- f distance (0.00<=f<=1000.00)
    -#4- f x coordinate (-1000.00<=f<=1000.00)
    -#5- f y coordinate (-1000.00<=f<=1000.00)
    Any deviations from this input/order will output unexpected results.
**/


#include <iostream> //cout, cin
#include <utility>  //pair
#include <vector>   //vector
#include <cmath>    //sqrt, pow
using namespace std; //eliminates std::

typedef pair<double, double> Point; //XY Coordinate Pair
const int MAX_STARS = 1000; //Maximum number of stars is 1,000.

class disjointSet{
private:
    vector<int> pset;
public:
    //************************************************************
    // description: Resets the pset.                             *
    // return: N/A                                               *
    // pre: MAX_STARS is defined.                                *
    // post: pset is cleared and all values set to 0.            *
    //************************************************************
    disjointSet(){
        pset.assign(MAX_STARS,0);
    }

    //************************************************************
    // description: Initializes the pset.                        *
    // return: N/A                                               *
    // pre: N is > 0                                             *
    // post: pset has all values set to corresponding position.  *
    //************************************************************
    void initSet(int N){
        for(int i = 0; i < N; i++)
            pset[i] = i;
    }

    //************************************************************
    // description: Finds the parent set of a set.               *
    // return: Integer                                           *
    // pre: initSet called.                                      *
    // post: N/A                                                 *
    //************************************************************
    int findSet(int i){
       if (pset[i] == i)
           return i;
       else
           return (pset[i]=findSet(pset[i]));
    }

    //************************************************************
    // description: Determines if two sets belong to same set.   *
    // return: Boolean                                           *
    // pre: initSet called.                                      *
    // post: N/A                                                 *
    //************************************************************
    bool isSameSet(int i, int j){
        return findSet(i) == findSet(j);
    }

    //************************************************************
    // description: Unions one set with another set.             *
    // return: N/A                                               *
    // pre: initSet called.                                      *
    //      Child set's parent is set to the unioned set.        *
    // post: Values in pset change.                              *
    //************************************************************
    void unionSet(int i, int j){
        pset[findSet(i)] = findSet(j);
    }

    //************************************************************
    // description: Counts the number of sets.                   *
    // return: Integer                                           *
    // pre: initSet called.                                      *
    // post: N/A                                                 *
    //************************************************************
    int countSets(int N){
        int count = 0;
        for(int i = 0; i < N; i++)
            if(pset[i] == i)
                count++;
        return count;
    }
};

int main() {
    int caseNumber = 1; //Current case (output purposes)
    double delta; //Max distance between stars to not be constellation.
    int numTestCases; //Number of test cases.
    int numPairs; //Number of pairs in a test case.

    cin >> numTestCases; //Input: Number of test cases

    while(numTestCases != 0) { //For Each test case
        int count = 0; //Counter for reading in correct amount pairs
        disjointSet dset; //Disjoint set to keep track of constellations.

        cin >> numPairs >> delta; //Input: Number of pairs and max delta.

        dset.initSet(numPairs); //Initialize disjoint set.

        Point *points = new Point[numPairs]; //Stores each coordinate pair for the test case.

        while(count < numPairs) { //Read in all pairs for current test case.
            cin >> points[count].first >> points[count].second; //Input: Store each pair.
            count++;
        }

        if (numPairs < 1)  //Base case.
            cout << "Case " << caseNumber << ": " << "0" << endl;
        else {
            for(int i = 0; i < numPairs-1; i++) //All except last pair.
                for(int j = i+1; j < numPairs; j++) //All past outer loop's current index
                    if(sqrt(pow(points[j].second - points[i].second, 2) + //Calc distance
                            pow(points[j].first - points[i].first, 2)) <= delta)
                        if (!dset.isSameSet(i, j)) //If points not in the same set
                            dset.unionSet(i, j); //Union the set.
            cout << "Case " << caseNumber << ": " << dset.countSets(numPairs) << endl;
        }
        numTestCases--; //Decrement number of test cases remaining
        caseNumber++; //Increment current case number.

        delete points; //Clean up our trash.
    }
    return 0;
}

