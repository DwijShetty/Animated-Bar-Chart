// barchart.h
// The class barchart.h creates constructors which set the default parameter, a
// parameterized constructor, a copy constructor which creates a copy of the
// existing copy constructor and a copy operator which copies one BarChart to
// another along with a [] which accesses the bars publicly. There are also
// the destructor which clears memory along which clear function which assigns
// the BarChart to default values. set and get functions have also been
// created for the frame, size and capacity which set and get the value. The
// addBar function adds the values of a bar to a barchart and the dump function
// which is used to output the values and is used to output the values. The
// graph function takes the values of a bar and assigns a color to each
// category using the colorMap map and the COLORS vector.

#include <iostream>
#include <algorithm>
#include <map>
#include "myrandom.h" // used in autograder, do not remove
#include "bar.h"

using namespace std;

// Constants used for bar chart animation.  You will primarily
// use these in barchartanimate.h, but you might find some useful here.
const string BOX = "\u29C8";
const string CLEARCONSOLE = "\033[2J";

// Color codes for Mimir (light mode)
// const string RED("\033[1;36m");
// const string PURPLE("\033[1;32m");
// const string BLUE("\033[1;33m");
// const string CYAN("\033[1;31m");
// const string GREEN("\033[1;35m");
// const string GOLD("\033[1;34m");
const string BLACK("\033[1;37m");
// const string RESET("\033[0m");
// const vector<string> COLORS = {RED, PURPLE, BLUE, CYAN, GREEN, GOLD, BLACK};

// Color codes for Replit (dark mode terminal)
const string CYAN("\033[1;36m");
const string GREEN("\033[1;32m");
const string GOLD("\033[1;33m");
const string RED("\033[1;31m");
const string PURPLE("\033[1;35m");
const string BLUE("\033[1;34m");
const string WHITE("\033[1;37m");
const string RESET("\033[0m");
const vector<string> COLORS = {CYAN, GREEN, GOLD, RED, PURPLE, BLUE, WHITE};

//
// BarChart
//
class BarChart {
private:
    //
    // Private member variables for the abstraction.
    // This implementation uses a low-level C array, bars, to store a list of
    // Bars.  As a result, you must also keep track of the number of elements
    // stored (size) and the capacity of the array (capacity).  This is not a
    // dynamic array, so it does not expand.
    //
    Bar *bars;  // pointer to a C-style array
    long capacity;
    long size;
    string frame = "";

public:

    // default constructor:
    BarChart() {
        bars = nullptr;
        capacity = 0;
        size = 0;
    }

    // parameterized constructor:
    // Parameter passed in determines memory allocated for bars.
    explicit BarChart(long n) {
        bars = new Bar[n];
        capacity = n;
        size = 0;
    }

    //
    // copy constructor:
    //
    // Called automatically by C++ to create an BarChart that contains
    // a copy of an existing BarChart.  Example: this occurs when passing
    // BarChart as a parameter by value.
    //
    BarChart(BarChart &other) {

        // NOTE: we can "move" the elements over by simply pointing to the
        // array in the other barchart

        this->bars = other.bars;

        // we have the same size and capacity as the other barchart

        this->capacity = other.capacity;
        this->size = other.size;

        // clear the data members of the other barchart since we now own the data:
        //
        other.bars = nullptr;
        other.size = 0;
        other.capacity = 0;

        // done, this barchart now contains the data from the other barchart, and
        // the other barchart is now completely empty:

    }

    //
    // copy operator=
    //
    // Called when you assign one BarChart into another, i.e. this = other;
    //
    BarChart &operator=(const BarChart &other) {
        // special case: are we assigning to ourself?
        if (this == &other)
            return *this;

        // unlike a copy constructor, *this* vector exists and so we first
        // have to free the memory associated with this vector:
        delete[] this->bars;

        // allocate this array with same capacity as the other:
        this->bars = new Bar[other.capacity];
        this->capacity = other.capacity;
        this->size = other.size;
        this->frame = other.frame; // all values of other bar chart is added to
        // this.

        // now make a copy the elements from the other vector into this one:
        for (long i = 0; i < other.size; ++i) {
            this->bars[i] = other.bars[i];
        }

        return *this;
    }

    // clear
    // frees memory and resets all private member variables to default values.
    void clear() {
        delete[] bars;
        bars = nullptr;
        capacity = 0;
        size = 0;

    }

    //
    // destructor:
    //
    // Called automatically by C++ to free the memory associated by the
    // BarChart.
    //
    virtual ~BarChart() {
        delete[] bars;
    }

    // setFrame
    void setFrame(const string &f) {
        this->frame = f;
    }

    // getFrame()
    // Returns the frame of the BarChart object.
    string getFrame() {
        return this->frame;
    }

    //getCapacity()
    // Returns the capacity of the Barchart object.
    int getCapacity() {
        return this->capacity;
    }


    // addBar
    // adds a Bar to the BarChart.
    // returns true if successful
    // returns false if there is not room
    bool addBar(string name, int value, string category) {
        if (this->size >= capacity) {
            return false;
        }
//        long insert = 0;
//        if (size > 0) {
//            while (bars[insert].getValue() > value) {
//                insert++;
//            }
//        }
//        for (long i = size; i > insert; i--) {
//            this->bars[i].setName(this->bars[i - 1].getName());
//            this->bars[i].setValue(this->bars[i - 1].getValue());
//            this->bars[i].setCategory(this->bars[i - 1].getCategory());
//        }
        Bar b(name, value, category);
//        this->bars[size].setName(name);
//        this->bars[size].setValue(value);
//        this->bars[size].setCategory(category);
        this->bars[size] = b;
        this->size++;
        return true;
    }

    // getSize()
    // Returns the size (number of bars) of the BarChart object.
    long getSize() {
        return this->size;
    }

    // operator[]
    // Returns Bar element in BarChart.
    // This gives public access to Bars stored in the Barchart.
    // If i is out of bounds, throw an out_of_range error message:
    // "BarChart: i out of bounds"
    Bar &operator[](long i) {
        if (i >= size) {
            throw out_of_range("BarChart: i out of bounds");
        }
        return bars[i];
    }

    // dump
    // Used for printing the BarChart object.
    // Recommended for debugging purposes.  output is any stream (cout,
    // file stream, or string stream).
    // Format:
    // "frame: 1
    // aname 5 category1
    // bname 4 category2
    // cname 3 category3" <-newline here
    void dump(ostream &output) {
        sort(this->bars, this->bars + this->size, greater<Bar>());
        output << "frame: " << this->frame << endl;
        for (long i = 0; i < size; ++i) {
            output << bars[i].getName() << " " << bars[i].getValue() <<
                   " " << bars[i].getCategory() << endl; // outputs the values
                   // from a given bar
        }
    }

    // graph
    // Used for printing out the bar.
    // output is any stream (cout, file stream, string stream)
    // colorMap maps category -> color
    // top is number of bars you'd like plotted on each frame (top 10? top 12?)
    void graph(ostream &output, map<string, string> &colorMap, int top) {
        int lenMax = 60;  // this is number of BOXs that should be printed
        // for the top bar (max value)
        sort(this->bars, this->bars + this->size, greater<Bar>());
        for (long i = 0; i < top && i < size; i++) {
            string category(this->bars[i].getCategory());
            string color(WHITE);
            if (colorMap.count(category) != 0) {
                color = colorMap[category];  // assigns color value to a
                // category
            }
            string barstr;
            int len = (int) (((float) this->bars[i].getValue()) /
                             this->bars[0].getValue() * lenMax); // finds length
                             // of the bar
            for (int j = 0; j < len; j++) {
                barstr += BOX;
            }
            output << color << barstr << " " << bars[i].getName() << " "
                   << bars[i].getValue() << endl;
        }
    }
};

