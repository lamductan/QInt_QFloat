#include "QInt.h"
void Init(QInt &a)
{
	for (int i = 0; i <SIZE_OF_DATA; i++)
	{
		a.data[i] = 0;
	}
}

void SetBit(QInt &a, int i, int bit)
{
	a.data[i / 8] ^= (-bit ^ a.data[i / 8]) & (1 << (7 - i % 8));
}

bool GetBit(QInt a, int i)
{
	return (a.data[i / 8] >> (7 - i % 8)) & 1;
}

string QIntStrDiv2(string a) //Chia chuỗi số cho 2 
{
	string res = "";
	int quo = 0, rem = 0;
	int temp;
	for (int i = 0; i < a.length(); i++)
	{
		temp = 10 * rem + a[i] - 48;
		quo = temp / 2;
		rem = temp % 2;
		res = res + to_string(quo);
	}
	if (res[0] == 48)
		res.erase(res.begin());
	return res;
}

void strToQInt(string X, QInt &a) //Chuyển chuỗi số sang QInt 
{
	int i = LENGTH_OF_NUMBER-1; // bắt đầu set bit tại vị trí cuối cùng
	while (X != "")
	{
		int bit = (X[X.length() - 1] - 48) % 2; // Tính phần dư
		SetBit(a, i, bit); // Tạo bit (biến bit) tại vị trí bit i của biến a
		X = QIntStrDiv2(X); // Chia chuỗi số X cho 2
		i--;
	}
}

void TwoComplement(QInt &x)
{
	QInt TC;
	int pos;
	int k;
	for (int i = LENGTH_OF_NUMBER-1; i >= 0; i--)
	{
		k = !!((x.data[i / 8] << (i % 8)) & 0x80);
		if (k == 0) continue;
		else
		{
			pos = i;
			break;
		}
	}
	for (int i = pos - 1; i >= 0; i--)
	{
		k = !!((x.data[i / 8] << (i % 8)) & 0x80);
		SetBit(x, i, 1 - k);

	}
}

void ScanQInt(QInt &x,string strNum)
{
	/*bool check = 1;
	string strNum;

	do {
		cin >> strNum;
		x.decNum = strNum;
		check = 1;
		if (strNum[0] == '-' || (strNum[0] >= 48 && strNum[0] <= 57))
			check = 1;
		else
		{
			check = 0;
			continue;
		}
		for (int i = 1; i<strNum.length(); i++)
		{
			if (strNum[i] >= 48 && strNum[i] <= 57) continue;
			else
			{
				check = 0;
				break;
			}
		}
		if (strNum.length()>LIM || check == 0)
			cout << "Invalid Number. Please retry with another number" << endl;
	} while (strNum.length() > LIM || check == 0);*/
	Init(x);
	if (strNum[0] == '-')
	{
		strNum.erase(strNum.begin());
		strToQInt(strNum, x);
		TwoComplement(x);
	}
	else strToQInt(strNum, x);
}
void StringNumToQInt(string X, QInt &a)
{
	Init(a);
	if (X[0] == '-')
	{
		X.erase(X.begin());
		strToQInt(X, a);
		TwoComplement(a);
	}
	else strToQInt(X, a);
}
string QIntToBit(QInt x)
{
	string bit;
	bit.resize(LENGTH_OF_NUMBER);
	int k = 0;
	for (int i = 0; i < SIZE_OF_DATA; i++)
	{
		for (int j = 0; j < BITS_PER_BYTE; j++) {
			bit[k] = !!((x.data[i] << j) & 0x80) + 48;
		}
	}
	return bit;
}

string QIntAddStringNum(string a, string b,int base)
{
	int len1 = a.length(), len2 = b.length(), tmp;
	int carry = 0;
	if (len1 < len2) {
		swap(a, b);
		swap(len1, len2);
	}
	string res(len1, 0);
	int d = len1 - len2;
	for (int i = len1 - 1; i >= d; i--) {
		tmp = a[i] + b[i - d] - 96 + carry;
		if (tmp >= base) {
			res[i] = tmp - base + 48;
			carry = 1;
		}
		else {
			res[i] = tmp + 48;
			carry = 0;
		}
	}
	for (int i = d - 1; i >= 0; i--) {
		tmp = a[i] - 48 + carry;
		if (tmp >= base) {
			res[i] = tmp - base + 48;
			carry = 1;
		}
		else {
			res[i] = tmp + 48;
			carry = 0;
		}
	}

	if (carry == 1) res.insert(res.begin(), '1');
	return res;
}

void ShiftRight(QInt &a, int k)
{
	bool tmp = GetBit(a, k);
	for (int i = 127 - k; i >= 0; i--) {
		SetBit(a, i + k, GetBit(a, i));
	}
	for (int i = 0; i < k; i++) {
		SetBit(a, i, tmp);
	}
}

void ShiftRight(QInt &A, QInt &Q, bool &Qt)
{
	bool cuoiA = GetBit(A, 127); //Bit cuoi cua A
	Qt = GetBit(Q, 127); //Bit cuoi cua Q
	ShiftRight(A, 1);
	ShiftRight(Q, 1);
	SetBit(Q, 0, cuoiA);
}

void ShiftLeft(QInt &a, int k)
{
	for (int i = k; i < 128; i++) {
		SetBit(a, i - k, GetBit(a, i));
	}
	for (int i = 127 - k + 1; i < 128; i++) {
		SetBit(a, i, 0);
	}
}

void ShiftLeft(QInt &A, QInt &Q)
{
	bool dauQ = GetBit(Q, 0);
	ShiftLeft(A, 1);
	ShiftLeft(Q, 1);
	SetBit(A, 127, dauQ);
}
QInt operator + (QInt a, QInt b)
{
	QInt c;
	int temp = 0;
	int res = 0;
	for (int i = 127; i >= 0; i--)
	{
		res = !!((a.data[i / 8] << (i % 8)) & 0x80) + !!((b.data[i / 8] << (i % 8)) & 0x80) + temp;
		temp = res / 2;
		res = res % 2;
		SetBit(c, i, res);
	}
	return c;
}
QInt operator - (QInt a, QInt b)
{
	QInt c;
	int temp = 0;
	int res = 0;
	for (int i = LENGTH_OF_NUMBER-1; i >= 0; i--)
	{
		int sub1 = !!((a.data[i / 8] << (i % 8)) & 0x80);
		int sub2 = !!((b.data[i / 8] << (i % 8)) & 0x80);
		sub2 += temp;
		temp = 0;
		if (sub1 >= sub2) {
			res = sub1 - sub2;
			SetBit(c, i, res);
		}
		else
		{
			sub1 += 2;
			temp = 1;
			res = sub1 - sub2;
			SetBit(c, i, res);
		}
	}

	return c;
}

bool isZero(QInt A)
{
	for (int i = 0; i <SIZE_OF_DATA; i++) {
		if (A.data[i] != 0) return false;
	}
	return true;
}

QInt operator *(QInt Q, QInt M)
{
	QInt A;
	bool Qt = 0;

	Init(A);
	for (int i = 0; i < LENGTH_OF_NUMBER; i++) {
		if (GetBit(Q, LENGTH_OF_NUMBER-1) == 1 && Qt == 0) {
			A = A - M;
		}
		else if (GetBit(Q, LENGTH_OF_NUMBER-1) == 0 && Qt == 1) {
			A = A + M;
		}
		ShiftRight(A, Q, Qt);
	}
	return Q;
}

QInt operator /(QInt &Q, QInt &M)
{
	QInt A;
	Init(A);

	for (int i = 0; i < LENGTH_OF_NUMBER; i++) {
		ShiftLeft(A, Q);
		A = A - M;
		if (GetBit(A, 0) == 1) {
			SetBit(Q, LENGTH_OF_NUMBER-1, 0);
			A = A + M;
		}
		else {
			SetBit(Q, LENGTH_OF_NUMBER-1, 1);
		}
	}
	return Q;
}

QInt operator %(QInt &Q, QInt &M)
{
	QInt A;
	Init(A);

	for (int i = 0; i < LENGTH_OF_NUMBER; i++) {
		ShiftLeft(A, Q);
		A = A - M;
		if (GetBit(A, 0) == 1) {
			SetBit(Q, 127, 0);
			A = A + M;
		}
		else {
			SetBit(Q, 127, 1);
		}
	}
	return A;
}

string QIntDecToBin(QInt x)
{
	string BitString;
	BitString.resize(LENGTH_OF_NUMBER);
	for (int i = 0; i < LENGTH_OF_NUMBER; i++)
	{
		BitString[i] = !!((x.data[i / 8] << (i % 8)) & 0x80)+48;
	}
	return BitString;
}

string QIntChangeBinBlock(int start, int end, string b, int numOfBits, int sizeOfBlock)
{
	string res;
	int exp = numOfBits / sizeOfBlock - start / sizeOfBlock - 1;
	long  val = 0;
	for (int i = end; i >= start; i--)
	{
		val += (b[i] - 48) * pow(2, sizeOfBlock - (i - start) - 1);
	}
	int lim = LIM;
	long  tail;
	long  baseMod;
	vector<string> PowOfTwo;
	createPowOfTwo(PowOfTwo);
	res = MulNumWithInt(PowOfTwo[exp*SIZE_OF_BLOCK], val);
	return res;
}
void ScanBinary(string &bin)
{
	cin >> bin;
	cout << endl;
}
string QIntModifyStringNum(string &a)
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
	a.erase(0, delPos);
	return a;
}

void QIntModifyBitString(string &bit)
{
	int lim = LENGTH_OF_NUMBER - bit.length();
	for (int i = 0; i < lim; i++)
	{
		bit = "0" + bit;
	}
}
QInt ConvertBinToDec(string &bit)
{
	int pos;
	QIntModifyBitString(bit);
	int sign = (bit[0] - 48);
	string res = "0", temp;
	if (sign == 1)
	{
		for (int i = LENGTH_OF_NUMBER; i >= 0; i--)
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
	while (end < LENGTH_OF_NUMBER)
	{
		temp = QIntChangeBinBlock(start, end, bit, LENGTH_OF_NUMBER, SIZE_OF_BLOCK);
		res = QIntAddStringNum(temp, res);
		start += SIZE_OF_BLOCK;
		end += SIZE_OF_BLOCK;
	}
	QInt a;
	QIntModifyStringNum(res);
	if (sign == 1) res = "-" + res;
	a.decNum = res;
	ScanQInt(a, res);
	return a;
}
string QIntToDec(QInt a)
{
	string bit = QIntDecToBin(a);
	QInt temp;
	temp = ConvertBinToDec(bit);
	return temp.decNum;
}
string QIntBinToHex(string &bit)
{
	string res;
	int temp = 0;
	QIntModifyBitString(bit);

	for (int i = LENGTH_OF_NUMBER-1; i >= 0; i--)
	{
		if ((LENGTH_OF_NUMBER - i-1) % 4 == 0 && (LENGTH_OF_NUMBER - i-1) > 0)
		{
			if (temp >= 0 && temp <= 9) res = to_string(temp) + res;
			else
			{
				char a = temp + 55;
				std::stringstream ss;
				ss << a;
				string l;
				ss >> l;
				res = l + res;
			}
			temp = 0;
		}
		temp += (bit[i] - 48) * pow(2, (LENGTH_OF_NUMBER - i-1) % BIN_FOR_HEX);
	}
	QIntModifyStringNum(res);
	return res;
}
string QIntDecToHex(QInt x)
{
	string bit = QIntDecToBin(x);
	return QIntModifyStringNum(QIntBinToHex(bit));
}
string QIntHexToBin(string hex)
{
	string block_Value = "";
	int x;
	string bit = "";
	for (int i = 0; i < hex.length(); i++)
	{
		if (hex[i] >= 65) x = hex[i] - 55;
		else x = hex[i] - 48;
		while (x != 0)
		{
			block_Value = to_string(x % 2) + block_Value;
			x = x / 2;
		}
		int k = BIN_FOR_HEX - block_Value.length();
		if (k != 0)
		{
			for (int i = 0; i < k; i++)
			{
				block_Value = "0" + block_Value;
			}
		}
		bit = bit + block_Value;
		block_Value = "";
	}
	return bit;
}
QInt RotateRight(QInt x)
{
	string bit = QIntDecToBin(x);
	QIntModifyStringNum(bit);
	string head = bit.substr(bit.length() - 1, 1);
	string tail = bit.substr(0, bit.length() - 2);
	string res = head + tail;
	return ConvertBinToDec(res);
}
QInt QIntHexToDec(string hex)
{
	string b = QIntHexToBin(hex);
	QIntModifyBitString(b);
	QInt x =  ConvertBinToDec(b);
	return x;
}

