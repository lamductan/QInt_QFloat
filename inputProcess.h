#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <fstream>

#include "Floating Point.h"
#include "FloatingPointMultiplication.h"
#include "FloatingPointDivination.h"
#include "QFloatBinToDec.h"
#include "QInt.h"
using namespace std;

bool checkNormalCharacter(char);
void standardlizeStr(string&);
vector<string> tokenize(string);
bool existSpecialCharacter(string);
void processingInput(string input, pair<int, int>& base, pair<string, string>& operand, string& myOperator);

void solveQFloat(char*, char*);
void solveQInt(char*, char*);

