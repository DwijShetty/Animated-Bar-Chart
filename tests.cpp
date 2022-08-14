#include <iostream>
#include "barchartanimate.h"
#include <sstream>

using namespace std;


bool testBarDefaultConstructor() {
    Bar b;
    if (b.getName() != "") {
        cout << "testBarDefaultConstructor: getName failed" << endl;
        return false;
    } else if (b.getValue() != 0) {
        cout << "testBarDefaultConstructor: getValue failed" << endl;
        return false;
    } else if (b.getCategory() != "") {
        cout << "testBarDefaultConstructor: getCategory failed" << endl;
        return false;
    }
    cout << "testBarDefaultConstructor: all passed!" << endl;
    return true;
}

bool testBarParamConstructor() {
    Bar b("Chicago", 9234324, "US");
    if (b.getName() != "Chicago") {
        cout << "testBarParamConstructor: getName failed" << endl;
        return false;
    } else if (b.getValue() != 9234324) {
        cout << "testBarParamConstructor: getValue failed" << endl;
        return false;
    } else if (b.getCategory() != "US") {
        cout << "testBarParamConstructor: getCategory failed" << endl;
        return false;
    }
    cout << "testBarParamConstructor: all passed!" << endl;
    return true;
}

bool testBarChartDefConstructor() {
    BarChart bc;
    if (bc.getSize() != 0) {
        cout << "testBarChartDefConstructor: getSize failed" << endl;
        return false;
    } else if (!bc.getFrame().empty()) {
        cout << "testBarChartDefConstructor: getFrame failed" << endl;
        return false;
    }
    cout << "testBarChartDefConstructor: all passed!" << endl;
    return true;
}

bool testBarChartParamConstructor() {
    BarChart bc(10);
    if (bc.getSize() != 0) {
        cout << "testBarChartParamConstructor: getSize failed" << endl;
        return false;
    }
    cout << "testBarChartParamConstructor: all passed!" << endl;
    return true;
}

bool testAddBar() {
    BarChart bc(10);
    bc.addBar("Chicago", 50, "USA");
    if (bc[0].getName() != "Chicago") {
        cout << "testAddBar: getName failed" << endl;
        return false;
    } else if (bc[0].getValue() != 50) {
        cout << "testAddBar: getValue failed" << endl;
        return false;
    } else if (bc[0].getCategory() != "USA") {
        cout << "testAddBar: getCategory failed" << endl;
        return false;
    }
    cout << "testAddBar: all passed!" << endl;
    return true;
}

bool testAddBarLimit() {
    BarChart bc(1);
    bc.addBar("New York", 50, "USA");
    bool exp_value = bc.addBar("Chicago", 50, "USA");
    if (exp_value != false) {
        cout << "testAddBarLimit: adding more than capacity failed" << endl;
        return false;
    }
    cout << "testAddBarLimit: all passed!" << endl;
    return true;
}

bool testCopyConstructor() {
    BarChart bc(1);
    bc.addBar("New York", 50, "USA");
    BarChart bc2(bc);
    if (!(bc2[0].getName() == "New York" && bc2[0].getValue() == 50 &&
          bc2[0].getCategory() == "USA" && bc2.getSize() == 1)) {
        cout << "testCopyConstructor: copying bars failed" << endl;
        return false;
    } else if (bc.getSize() != 0) {
        cout << "testCopyConstructor: original barchart not empty" << endl;
        return false;
    }
    cout << "testCopyConstructor: all passed!" << endl;
    return true;
}

bool testGetAndSet() {
    BarChart bc;
    bc.setFrame("1989");
    if (bc.getFrame() != "1989") {
        cout << "testGetAndSet: getFrame not equal to setFrame" << endl;
        return false;
    }
    cout << "testGetAndSet: all passed!" << endl;
    return true;
}

bool testCopyOperator() {
    BarChart bc1;
    BarChart bc2;
    bc1.addBar("New York", 50, "USA");
    bc1.addBar("LA", 20, "USA");
    bc1.addBar("Chicago", 40, "USA");
    bc2.addBar("Mumbai", 10, "India");
    bc2.addBar("Beijing", 30, "China");
    bc1 = bc2;
    if (bc1.getSize() != 2 || bc2.getSize() != 2) {
        cout << "testCopyOperator: size after copying mismatch" << endl;
        return false;
    }
    if (!(bc1[0].getName() == "Beijing" && bc1[0].getValue() == 30 &&
          bc1[0].getCategory() == "China" && bc2[0].getName() == "Beijing" &&
          bc2[0].getValue() == 30 && bc2[0].getCategory() == "China")) {
        cout << "testCopyOperator: copying bars failed" << endl;
        return false;
    }
    if (!(bc1[1].getName() == "Mumbai" && bc1[1].getValue() == 10 &&
          bc1[1].getCategory() == "India" && bc2[1].getName() == "Mumbai" &&
          bc2[1].getValue() == 10 && bc2[1].getCategory() == "India")) {
        cout << "testCopyOperator: copying bars failed" << endl;
        return false;
    }
    cout << "testCopyOperator: all passed!" << endl;
    return true;
}

bool testClear() {
    BarChart bc(4);
    bc.addBar("New York", 50, "USA");
    bc.clear();
    if (bc.getSize() != 0) {
        cout << "testClear: clear failed" << endl;
        return false;
    }
    if (bc.getCapacity() != 4) {
        cout << "testClear: clear failed" << endl;
        return false;
    }
    cout << "testClear: all passed!" << endl;
    return true;
}

bool testDump() {
    stringstream ss;
    string line;
    BarChart bc(2);
    bc.setFrame("1984");
    bc.addBar("New York", 40, "USA");
    bc.addBar("Chicago", 50, "USA");
    bc.dump(ss);
    getline(ss, line);
    if (line != "frame: 1984") {
        cout << "testDump: dump line 1 failed" << endl;
        return false;
    }
    getline(ss, line);
    if (line != "Chicago 50 USA") {
        cout << "testDump: dump line 2 failed" << endl;
        return false;
    }
    getline(ss, line);
    if (line != "New York 40 USA") {
        cout << "testDump: dump line 3 failed" << endl;
        return false;
    }
    cout << "testDump: all passed!" << endl;
    return true;
}

bool testGraph() {
    stringstream ss;
    string line;
    BarChart bc(10);
    map<string, string> cMap;
    cMap["USA"] = CYAN;
    cMap["India"] = GREEN;
    bc.setFrame("1984");
    bc.addBar("New York", 50, "USA");
    bc.addBar("Mumbai", 10, "India");
    bc.addBar("Beijing", 30, "China");
    bc.addBar("Chicago", 5, "USA");
    bc.graph(ss, cMap, 3);
    getline(ss, line);
    if (line != CYAN + "⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈" +
                "⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈ New York 50") {
        cout << "testGraph: graph line 1 failed" << endl;
        return false;
    }
    getline(ss, line);
    if (line != WHITE + "⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈" +
                "⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈ Beijing 30") {
        cout << "testGraph: graph line 2 failed" << endl;
        return false;
    }
    getline(ss, line);
    if (line != GREEN + "⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈⧈ Mumbai 10") {
        cout << "testGraph: graph line 3 failed" << endl;
        return false;
    }
    cout << "testGraph: all passed!" << endl;
    return true;
}

bool testBarchartAnimateParamConstructor(){
    BarChartAnimate bca("Title", "xLabel", "source");
    if (bca.getTile() != "Title") {
        cout << "testBarchartAnimateParamConstructor: getTitle failed" << endl;
        return false;
    }
    if (bca.getxLabel() != "xLabel") {
        cout << "testBarchartAnimateParamConstructor: getxLabel failed" << endl;
        return false;
    }
    if (bca.getSource() != "source") {
        cout << "testBarchartAnimateParamConstructor: getsource failed" << endl;
        return false;
    }
    if (bca.getSize() != 0){
        cout << "testBarchartAnimateParamConstructor: getSize failed" << endl;
    }
    if (bca.getCapacity() != 4){
        cout << "testBarchartAnimateParamConstructor: getcapacity failed" << endl;
    }
    cout << "testBarchartAnimateParamConstructor: all passed!" << endl;
    return true;
}

bool testAddFrame(){
    string filename = "cities.txt";
    ifstream inFile(filename);
    if (!inFile.is_open()){
        cout << "testAddFrame: error opening file" << endl;
        return false;
    }
    string title;
    getline(inFile, title);
    string xlabel;
    getline(inFile, xlabel);
    string source;
    getline(inFile, source);

    BarChartAnimate bca(title, xlabel, source);
    for (int i = 0; i < 2; ++i) {
        if (!inFile.eof()) {
            bca.addFrame(inFile);
        }
    }
    if (bca[0][0].getName() != "Beijing"){
        cout << "testAddFrame: frame 0 bar 0 getName failed" << endl;
    }
    if (bca[0][0].getValue() != 672){
        cout << "testAddFrame: frame 0 bar 0 getValue failed" << endl;
    }
    if (bca[0][0].getCategory() != "East Asia"){
        cout << "testAddFrame: frame 0 bar 0 getCategory failed" << endl;
    }
    cout << "testAddFrame: all passed!" << endl;
    return true;
}

bool testanimate(){

}

int main() {
    testBarDefaultConstructor();
    testBarParamConstructor();
    testBarChartDefConstructor();
    testBarChartParamConstructor();
    testAddBar();
    testAddBarLimit();
    testCopyConstructor();
    testGetAndSet();
    testClear();
    testDump();
    testGraph();
    testBarchartAnimateParamConstructor();
    testAddFrame();
    return 0;
}