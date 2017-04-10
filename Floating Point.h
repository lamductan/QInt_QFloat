#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;
#define SIGN 112
#define BIAS 16383
#define EXP 15
const int NBYTES = 16;
const int MaxExp = 16383;

//#define SIGN 23
//#define BIAS 127
//#define EXP 8
//const int NBYTES = 4;
//const int MaxExp = 127;

struct QFloat {
	char data[NBYTES];
	QFloat();
	QFloat& operator=(char x);
};

int compareInt(string, string);
int compareFloat(string, string);
string add(string, string, int base = 10);
string sub(string, string, int base = 10);

void SetBit(QFloat &, int, int);
int bitValue(int, int);
int bitValue(QFloat, int);
void PrintBinary(QFloat &);

string truncateQFloat(string);
string doubleStr(string);
string StrDiv2(string);
void createPowOfTwo(vector<string>&, int maxE = 120);
//void createINF(string &, vector<string>&);

string multiplyStr(string, char);
string multiplyStr(string, string);

string toBinary(string a);
bool checkDecimalZero(string);
string StrToStrBit(string x, int &exp);
void StrToQFloat(string x, QFloat &a);
void ShiftRight(QFloat &a, int n);
void ShiftLeft(QFloat &a, int n);
bool isZero(QFloat a);
bool isDenormal(QFloat a);
string ExpString(QFloat a);
int calcExp(QFloat a);
string SignificandStr(QFloat a);
string TwoComplementStr(string a);
string TwoComplementToSign(string a);
bool isNegative(QFloat a);

bool add(QFloat a, QFloat b, QFloat &sum);
bool sub(QFloat a, QFloat b, QFloat &sub);

string MulNumWithInt(string x, int val);

void StrDecToQFloat(string x, QFloat &a);
void StrBinToQFloat(string x, QFloat &a);