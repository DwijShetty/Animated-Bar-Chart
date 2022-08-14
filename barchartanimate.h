// barchartanimate.h
// The class BarChartAnimate has a parameterized constructor which sets the
// values and a destructor which allocates memory. It includes addFrame
// which adds all the values of the barcharts together and increases the
// capacity by 2 when the size runs out and also assigns a color to it. There
// also are the get and set function which usually were used to get the values
// of the constructors. There's also the get msInterval function which gets
// the playback speed and is used for the creative component. The animate
// function uses all the values in the frame and puts it together which gives
// us the final result. parseBarLine is used to take data out from each line
// using a delimiter and saves it to out.

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <map>
#include <utility>
#include <vector>
#include <unistd.h>
#include "myrandom.h" // used in autograder, do not remove
#include "barchart.h"

using namespace std;

//
// BarChartAnimate
//
class BarChartAnimate {
private:
    //
    // Private member variables for the abstraction.
    // This implementation uses a low-level C array, bars, to store a list of
    // BarCharts.  As a result, you must also keep track of the number of
    // elements stored (size) and the capacity of the array (capacity).
    // This IS dynamic array, so it must expand automatically, as needed.
    //
    BarChart *barcharts{};  // pointer to a C-style array
    int size{};
    int capacity{};
    map<string, string> colorMap;
    string title, xLabel, source;
    unsigned int microsecond = 50000;

    void parseBarLine(string &line, Bar &out) {
        istringstream ss(line);
        vector<string> tokens;
        string token;
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        int value;
        try {
            value = stoi(tokens[3]);
        } catch (exception &e) {
            cout << e.what();
        }

        Bar b(tokens[1], value, tokens[4]);
        out = b;
    }

public:

    // a parameterized constructor:
    // Like the ourvector, the barcharts C-array should be constructed here
    // with a capacity of 4.
    BarChartAnimate(string title, string xLabel,
                    string source)
            : title(std::move(title)), xLabel(std::move(xLabel)),
              source(std::move(source)) {
        size = 0;
        capacity = 4;
        barcharts = new BarChart[capacity];
    }

    //
    // destructor:
    //
    // Called automatically by C++ to free the memory associated
    // by BarChartAnimate.
    //
    virtual ~BarChartAnimate() {
        delete[] barcharts;
    }

    // addFrame:
    // adds a new BarChart to the BarChartAnimate object from the file stream.
    // if the barcharts has run out of space, double the capacity (see
    // ourvector.h for how to double the capacity).
    // See application.cpp and handout for pre and post conditions.
    void addFrame(ifstream &file) {
        if (size == capacity) {
            int newCapacity = capacity * 2;
            auto *newBC = new BarChart[newCapacity];

            // copy the elements from barcharts to the new array:
            for (int i = 0; i < size; ++i) {
                newBC[i] = barcharts[i];
            }

            // now delete barcharts, and update private data members to point to
            // new array and reflect new capacity:
            delete[] barcharts;
            barcharts = newBC;
            capacity = newCapacity;
        }
        string fileLine;
        getline(file, fileLine);
        if (file.eof()) {
            return;
        }
        getline(file, fileLine);
        int times = stoi(fileLine);
        BarChart bc(times);
        for (int i = 0; i < times; ++i) {
            Bar b;
            getline(file, fileLine);
            parseBarLine(fileLine, b);
            bc.addBar(b.getName(), b.getValue(), b.getCategory());
            if (colorMap.count(b.getCategory()) == 0) {
                unsigned long colorIdx = colorMap.size() % COLORS.size();
                string color = COLORS[colorIdx]; // assigns an index to a
                // category
                colorMap[b.getCategory()] = color;
            }
        }
        istringstream ss(fileLine);
        string frame;
        getline(ss, frame, ',');
        bc.setFrame(frame); // sets frame from line
        this->barcharts[size] = bc; //adds the lines based on the time to
        // barchart
        size++;
    }

    // animate:
    // this function plays each frame stored in barcharts.  In order to see the
    // animation in the terminal, you must pause between each frame.  To do so,
    // type:  usleep(3 * microsecond);
    // Additionally, in order for each frame to print in the same spot in the
    // terminal (at the bottom), you will need to type: output << CLEARCONSOLE;
    // in between each frame.
    void animate(ostream &output, int top, int endIter) {
        if (endIter == -1) {
            endIter = size;
        }
        for (int i = 0; i <= endIter && i < size; ++i) {
            output << CLEARCONSOLE;
            output << WHITE << this->title << endl;
            output << WHITE << this->source << endl;
            this->barcharts[i].graph(output, this->colorMap, top);
            output << WHITE << xLabel << endl;
            output << WHITE << "Frame: " << this->barcharts[i].getFrame()
                   << endl; // outputs the bars and data from previous files
            usleep(3 * microsecond);
        }
    }

    //
    // Public member function.
    // Returns the size of the BarChartAnimate object.
    //
    int getSize() const {
        return this->size;
    }

    //
    // Public member function.
    // Returns BarChart element in BarChartAnimate.
    // This gives public access to BarChart stored in the BarChartAnimate.
    // If i is out of bounds, throw an out_of_range error message:
    // "BarChartAnimate: i out of bounds"
    //
    BarChart &operator[](int i) {
        if (i >= size) {
            throw out_of_range("BarChartAnimate: i out of bounds");
        }
        return barcharts[i];
    }

    string getTile() {
        return this->title;
    }

    string getxLabel() {
        return this->xLabel;
    }

    string getSource() {
        return this->source;
    }

    int getCapacity() const {
        return this->capacity;
    }

    void setmsInterval(unsigned int ms) {
        this->microsecond = ms;
    }
};
