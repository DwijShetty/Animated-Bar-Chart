// Bar Chart Animation
//
// This application uses BarChartAnimate (which uses BarChart, which uses Bar)
// to produce an animated bar chart.
//
// Once your three class/abstraction files are completed and tested, run with
// this application to see your final creation.
//
// The creative components includes the ability to input the file name and
// run the given file. Along with that, there's also an option to select the
// playback speed of the whole application using the msInterval variable from
// animate function.
//
// Shanon Reckinger
// U. of Illinois, Chicago
// CS 251: Fall 2021
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "barchartanimate.h"
using namespace std;


int main() {
    string filename;
	cout << "Enter data file to animate: " << endl;
    cin >> filename;
	ifstream inFile(filename);
    if(!inFile.is_open()){
        cout << "invalid data file" << endl;
        return 1;
    }
    cout << "Select a playback speed: " << endl;
    cout << "1) 0.5X" <<endl;
    cout << "2) 1X" <<endl;
    cout << "3) 2X" <<endl;
    cout << "4) 4X" <<endl;
    int speed;
    unsigned int msInterval = 50000;
    cin >> speed;
    switch (speed) {
        case 1: msInterval*=2;
            break;
        case 2: msInterval/= 1;
            break;
        case 3: msInterval/= 2;
            break;
        case 4: msInterval/= 4;
            break;
        default: cout << "invalid speed option" << endl;
            return  1;
    }
	string title;
	getline(inFile, title);
	string xlabel;
	getline(inFile, xlabel);
	string source;
	getline(inFile, source);

	BarChartAnimate bca(title, xlabel, source);
	bca.setmsInterval(msInterval);
	while (!inFile.eof()) {
		bca.addFrame(inFile);
	}
	
	bca.animate(cout, 15, -1);

    return 0;
}
