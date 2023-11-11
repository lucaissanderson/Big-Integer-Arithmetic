/****************************
    Arithmetic.cpp
    lzsander

*****************************/


#include <iostream>
#include <fstream>
#include <string>
#include "BigInteger.h"

using namespace std;

#define MAX_LEN 300

int main(int argc, char** argv){

    // I/O code heavily influenced from FileIO.cpp example

    ifstream in;
    ofstream out;
    string line;

    // check number of args
    if(argc != 3){
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return(EXIT_FAILURE);
    }

    // open files 
    in.open(argv[1]);
    if(!in.is_open()){
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return(EXIT_FAILURE);
    }

    out.open(argv[2]);
    if(!out.is_open()){
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return(EXIT_FAILURE);
    }

    getline(in, line);
    BigInteger A(line);

    getline(in, line);

    getline(in, line);
    BigInteger B(line);

    out << A << endl << endl;
    out << B << endl << endl;
    out << A+B << endl << endl;
    out << A-B << endl << endl;
    out << A-A << endl << endl;
    out << (3*A)-(2*B) << endl << endl;
    out << A*B << endl << endl;
    out << A*A << endl << endl;
    out << B*B << endl << endl;
    out << 9*(A*A*A*A) + 16*(B*B*B*B*B) << endl;

    in.close();
    out.close();

    return 0;
}
