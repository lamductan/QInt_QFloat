#include "Floating Point.h"

void ModifyBitString(string &);
string ChangeBinBlock(int start, int end, string b, int numOfBits, int sizeOfBlock);
string AddStringNum(string a, string b);
string ModifyStringNum(string &a);
string BinToDec(string &bit);
string QFloatToString(QFloat a);
string DoubleToString(double x);
string QFloatBinToDec(QFloat a, int exp_size = EXP, int sign = SIGN);
string QFloatBinToDec(string bit, int exp_size = EXP, int sign = SIGN);
