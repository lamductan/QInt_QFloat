#include <iostream>
#include <string>
#include <sstream>
#define LIM_OF_LENGTH 39
#define FP_LENGTH 10
#define SIZE_OF_BLOCK 8
using namespace std;

#include "Floating Point.h"
void ModifyBitString(string &bit)
{
	int lim = NBYTES * 8 - bit.length();
	for (int i = 0; i < lim; i++)
	{
		bit = "0" + bit;
	}
}

string ChangeBinBlock(int start, int end, string b, int numOfBits, int sizeOfBlock=SIZE_OF_BLOCK)
{
	string res;
	int exp = numOfBits / sizeOfBlock - start / sizeOfBlock - 1;
	long  val = 0;
	for (int i = end; i >= start; i--)
	{
		val += (b[i] - 48) * pow(2, sizeOfBlock - (i - start) - 1);
	}
	int lim = LIM_OF_LENGTH;
	long  tail;
	long  baseMod;
	vector<string> PowOfTwo;
	createPowOfTwo(PowOfTwo);
	res = MulNumWithInt(PowOfTwo[exp*SIZE_OF_BLOCK], val);
	return res;
}
string AddStringNum(string a, string b)
{
	string c;
	int temp = 0;
	int res;
	int al = a.length();
	int bl = b.length();
	if (al<bl)
	for (int i = 0; i <= bl - al; i++)
	{
		a = "0" + a;
	}
	if (bl<al)
	for (int i = 0; i <= al - bl; i++)
	{
		b = "0" + b;
	}
	for (int i = a.length() - 1; i >= 0; i--)
	{
		res = a[i] - 48 + b[i] - 48 + temp;
		temp = res / 10;
		res = res % 10;
		c = to_string(res) + c;
	}
	if (temp != 0) c = to_string(temp) + c;
	return c;
}
string ModifyStringNum(string &a)
{
	int delPos = 0;
	for (int i = 0; i < a.length(); i++)
	{
		if (a[i] == '0') continue;
		else
		{
			delPos = i;
			break;
		}
	}
	int k = 3;
	a.erase(0, delPos);
	return a;
}

string BinToDec(string &bit)
{
	int pos;
	ModifyBitString(bit);
	int sign = (bit[0] - 48);
	string res = "0", temp;
	if (sign == 1)
	{
		for (int i = NBYTES*8 - 1; i >= 0; i--)
		if (bit[i] - 48 == 0) continue;
		else {
			pos = i;
			break;
		}
		for (int i = pos - 1; i >= 0; i--)
		{
			bit[i] = (49 - bit[i]) + 48;
		}
	}
	int start = 0;
	int end = SIZE_OF_BLOCK-1;
	while (end < SIGN+EXP+1)
	{
		temp = ChangeBinBlock(start, end, bit, SIGN+EXP+1);
		res = add(temp, res);
		start += SIZE_OF_BLOCK;
		end += SIZE_OF_BLOCK;
	}
	ModifyStringNum(res);
	if (sign == 1) res = "-" + res;
	return res;
}
string QFloatToString(QFloat a)
{
	string bit;
	for (int i = 0; i < SIGN + EXP + 1; i++)
	{
		int b = bitValue(a, i);
		bit = bit + to_string(b);
	}
	return bit;
}
string DoubleToString(double x)
{
	double fractionalPart = x - (long long)(x);
	long long interPart = (long long)x;
	string res;
	res = res + to_string((long long)x) + ".";
	for (int i = 0; i < FP_LENGTH; i++)
	{
		fractionalPart *= 10;
		if (fractionalPart < 1) res = res + "0";
	}
	long long k = (long long)fractionalPart;
	string FP = to_string(k);
	res += FP;
	return res;
}
string QFloatBinToDec(string bit, int exp_size = EXP, int sign = SIGN)
{
	int length = bit.length();
	string DecNum = "";
	string value;
	int exponent = 0;
	for (int i = 1; i <= exp_size; i++)
	{
		exponent += (bit[i] - 48) * pow(2, exp_size - i);
	}
	exponent -= BIAS;
	value.resize(sign);
	if (bit[0] == '1') DecNum = DecNum + '-';
	for (int i = exp_size + 1; i < length; i++)
	{
		value[i - exp_size - 1] = bit[i];
	}
	if (exponent >= 0)
	{
		string integerPart;
		integerPart.resize(exponent);
		string fractionalPart;
		fractionalPart.resize(sign - exp_size);
		for (int i = 0; i < exponent; i++)
		{
			integerPart[i] = value[i];
		}
		integerPart = "1" + integerPart;
		value.erase(value.begin(), value.begin() + exponent); // phần phân của số chấm động
		fractionalPart = value;
		double x = 0;
		integerPart = BinToDec(integerPart);
		for (int i = 0; i < value.length(); i++)
		{
			x += (value[i] - 48)* pow(2, -(i + 1));
		}
		fractionalPart = DoubleToString(x);
		fractionalPart.erase(fractionalPart.begin(), fractionalPart.begin() + 1);
		return DecNum + integerPart + fractionalPart;
	}
	else
	{
		value = "1" + value;
		for (int i = 1; i < abs(exponent); i++)
		{
			value = "0" + value;
		}
		double x = 0;
		for (int i = 0; i < value.length(); i++)
		{
			x += (value[i] - 48)* pow(2, -(i + 1));
		}
		string fractionalPart = DoubleToString(x);
		return DecNum + fractionalPart;
	}
}
string QFloatBinToDec(QFloat a, int exp_size = EXP, int sign = SIGN)
{
	string bit = QFloatToString(a);
	return QFloatBinToDec(bit, EXP, SIGN);
}
