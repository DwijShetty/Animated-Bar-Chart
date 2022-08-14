// bar.h
// In this class Bar, we set the values of each bar in a constructor and
// operators that compares the values of each bar. We also create set and get
// function for future use.

#include <iostream>
#include <string>
#include "myrandom.h" // used in autograder, do not remove

using namespace std;

//
// Bar
//
class Bar {
private:
    // Private member variables for a Bar object
    string name;
    int value;
    string category;
    // NOTE: You should not be allocating memory on the heap for this class.

public:

    // default constructor:
    Bar() {
        name = "";
        value = 0;
        category = "";
    }

    //
    // a second constructor:
    //
    // Parameter passed in constructor Bar object.
    //
    Bar(const string &name, int value, const string &category) {
        this->name = name;
        this->value = value;
        this->category = category; // assigns the values to this
    }

    // destructor:
    virtual ~Bar() = default;

    // getName:
    string getName() {
        return this->name;
    }

    // getValue:
    int getValue() const {
        return this->value;
    }

    // getCategory:
    string getCategory() {
        return this->category;
    }

    // operators
    bool operator<(const Bar &other) const {
        return value < other.getValue();
    }

    bool operator<=(const Bar &other) const {
        return value <= other.getValue();
    }

    bool operator>(const Bar &other) const {
        return value > other.getValue();
    }

    bool operator>=(const Bar &other) const {
        return value >= other.getValue();
    }
};

