#pragma once
#include <string>
using namespace std;

#define NameToString(name) printer(#name)
string printer(char const*);