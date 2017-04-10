#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#define LENGTH_OF_NUMBER 128
#define LIM 39
#define SIZE_OF_DATA 16
#define BITS_PER_BYTE 8
#define SIZE_OF_BLOCK 8
#define BIN_FOR_HEX 4
using namespace std;
#include "Floating Point.h"
typedef struct QInt
{
	string decNum;
	char data[16];
};
void Init(QInt &a);
void SetBit(QInt &a, int i, int bit);
bool GetBit(QInt a, int i);
string QIntStrDiv2(string a);
void strToQInt(string X, QInt &a);
void TwoComplement(QInt &x);
void ScanQInt(QInt &x, string strNum);
string QIntToString(QInt x);
string QIntAddStringNum(string a, string b,int base=10);
void ShiftRight(QInt &a, int k);
void ShiftRight(QInt &A, QInt &Q, bool &Qt);
void ShiftLeft(QInt &a, int k);
void ShiftLeft(QInt &A, QInt &Q);
QInt operator + (QInt a, QInt b);
QInt operator - (QInt a, QInt b);
bool isZero(QInt A);
QInt operator *(QInt Q, QInt M);
QInt operator /(QInt &Q, QInt &M);
QInt operator %(QInt &Q, QInt &M);
string QIntDecToBin(QInt x);
string QIntChangeBinBlock(int start, int end, string b, int numOfBits, int sizeOfBlock);
void ScanBinary(string &bin);
string QIntModifyStringNum(string &a);
void QIntModifyBitString(string &bit);
QInt ConvertBinToDec(string &bit);
string QIntBinToHex(string &bit);
string QIntDecToHex(QInt x);
string QIntHexToBin(string hex);
QInt QIntHexToDec(string hex);
string QIntToDec(QInt a);
void StringNumToQInt(string X, QInt &a);
QInt RotateRight(QInt x);

