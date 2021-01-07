#include <iostream>
#include <fstream>
#include <string>
#include "./import/functions.h"
using namespace std;

ifstream in("input");
ofstream out("output.json");

// 1. Put here your document column names, number of rows and columns
const int nCols = 2;
const int nRows = 10;
struct row {
    string id;
    string name;
};
typedef struct row row;

string columnNames[nCols];

void getColumnNames(string*, row);
void rowToStruct(row*);
void pushRow(row*, int);
void insertEntry(string, string, bool, bool);

int main() {

    getColumnNames(columnNames, row());

    out<<"[\n";
    for (int i = 1; i <= nRows; i++) {
        row r;
        rowToStruct(&r);
        pushRow(&r, i);
    }
    out<<"]";
    return 0;
}

// 2. Repeat the process to convert all the column names : s[i] = NameToString(r.<column_name>);
void getColumnNames(string* s, row r) {
    s[0] = NameToString(r.id);
    s[1] = NameToString(r.name);
}

// 3. Complete with your column names
void rowToStruct(row *r) {
    string s;
    
    in>>s;
    r->id = s;
    
    in>>s;
    r->name = s;
}

// Put here you column entry
string spacer = "    ";
string q = "\""; // quote
void pushRow(row* r, int i) {
    out<<spacer<<"{\n";

    insertEntry(columnNames[0], r->id, 1, 0);
    insertEntry(columnNames[1], r->name, 0, 1);

    out<<spacer<<"}";
    if (i == nRows) {
        out<<"\n";
    } else {
        out<<",\n";
    }
}

// last, because last entry should not contain ',' in the end
void insertEntry(string name, string value, bool isNumber, bool last) {
    string cm = !last ? "," : "";
    if (isNumber) {
        out<<spacer<<spacer<<q<<name<<q<<": "<<value<<cm<<"\n";
    } else {
        out<<spacer<<spacer<<q<<name<<q<<": "<<q<<value<<q<<cm<<"\n";
    }
}