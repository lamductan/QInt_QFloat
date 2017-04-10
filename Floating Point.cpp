
#include "Floating Point.h"

QFloat::QFloat() {
    for (int i = 0; i < NBYTES; ++i)
        data[i] = 0;
}

QFloat& QFloat::operator=(char x) {
    for (int i = 0; i < NBYTES; ++i)
        data[i] = x;
    return *this;
}

//So sanh hai so nguyen lon
int compareInt(string a, string b) {
	if (a[0] == '-' && b[0] != '-') return -1;
	if (a[0] != '-' && b[0] == '-') return 1;
	if (a[0] != '-' && b[0] != '-') {
		int len1 = a.length(), len2 = b.length();
		if (len1 > len2) return 1;
		else if (len1 < len2) return -1;
		else {
			for (int i = 0; i < len1; i++)
				if (a[i] > b[i]) return 1;
				else if (a[i] < b[i]) return -1;
		}
		return 0;
	}
	else {
		a.erase(0, 1);
		b.erase(0, 1);
		return -(compareInt(a, b));
	}
}

int compareFloat(string a, string b) {
	if (a[0] == '-' && b[0] != '-') return -1;
	if (a[0] != '-' && b[0] == '-') return 1;
	if (a[0] != '-' && b[0] != '-') {
		int k1, k2;
		bool isNegative = false;
		k1 = a.find('.');
		k2 = b.find('.');

		if (k1 == string::npos && k2 == string::npos)
			return compareInt(a, b);

		string a1 = a.substr(0, k1);
		string b1 = b.substr(0, k2);
		string a2 = (k1 != string::npos) ? a.substr(k1 + 1) : ".0";
		string b2 = (k2 != string::npos) ? b.substr(k2 + 1) : ".0";
		if (a[0] == '-') isNegative = true;
		int cmp = compareInt(a1, b1);
		int res = 0;
		if (cmp == 0) {
			if (a2 < b2) res = -1;
			else if (a2 > b2) res = 1;
		}
		else res = cmp;
		if (isNegative) res = -res;

		return res;

	}
}

//Cong hai so nguyen lon
string add(string a, string b, int base) {
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
//Nhân chuỗi với 1 số
string MulNumWithInt(string x, int val)
{
	string temp = "0";
	for (int i = 0; i < val; i++)
	{
		temp = add(temp, x, 10);
	}
	return temp;
}

//Tru hai chuoi so
string sub(string a, string b, int base) {
	if (compareFloat(a, b) < 0) swap(a, b);
	int len1 = a.length(), len2 = b.length();
	string res = a;
	int d = len1 - len2;
	int tmp, carry = 0;
	for (int i = len1 - 1; i >= d; i--) {
		tmp = a[i] - b[i - d] - carry;
		if (tmp < 0) {
			res[i] = tmp + 48 + base;
			carry = 1;
		}
		else {
			res[i] = tmp + 48;
			carry = 0;
		}
	}
	for (int i = d - 1; i >= 0; i--) {
		tmp = a[i] - 48 - carry;
		if (tmp < 0) {
			res[i] = tmp + 48 + base;
			carry = 1;
		}
		else {
			res[i] = tmp + 48;
			carry = 0;
		}
	}
	return res;
}

//Gan gia tri bit thu i cua a bang gia tri bit
void SetBit(QFloat &a, int bit, int i) {
	int k = i / 8;
	a.data[k] ^= (-bit ^ a.data[k]) & (1 << (7 - i % 8));
}

//Lay gia tri cua bit thu i cua so nguyen x
int bitValue(int x, int i) {
	return ((x >> (31 - i % 32)) & 1);
}

//Lay gia tri cua bit thu i cua QFloat a
int bitValue(QFloat a, int pos) {
	return ((a.data[pos / 8] >> (7 - pos % 8)) & 1);
}

//In QFloat duoi dang nhi phan
void PrintBinary(QFloat &a) {
	for (int i = 0; i < NBYTES; i++) {
		for (int j = 7; j >= 0; --j)
			cout << ((a.data[i] >> j) & 1);
		cout << " ";
	}
}

//Lay phan nguyen cua chuoi so x
string truncateQFloat(string x) {
	string res = x;
	int k = res.find('.');
	if (k != string::npos) 
		res.erase(res.begin() + k, res.end());
	return res;
}

//Nhan hai chuoi so x
string doubleStr(string x)
{
	int len = x.length();
	string res;
	int k = x.find('.');
	int carry = 0, tmp;

	if (k != string::npos) {
		for (int i = len - 1; i > k; --i) {
			tmp = (x[i] - 48) * 2 + carry;
			if (tmp >= 10) {
				res.insert(res.begin(), char(tmp + 38));
				carry = 1;
			}
			else {
				res.insert(res.begin(), char(tmp + 48));
				carry = 0;
			}
		}

		res.insert(res.begin(), '.');

		for (int i = k - 1; i >= 0; --i) {
			tmp = (x[i] - 48) * 2 + carry;
			if (tmp >= 10) {
				res.insert(res.begin(), char(tmp + 38));
				carry = 1;
			}
			else {
				res.insert(res.begin(), char(tmp + 48));
				carry = 0;
			}
		}
	}
	else {
		for (int i = len - 1; i >= 0; --i) {
			tmp = (x[i] - 48) * 2 + carry;
			if (tmp >= 10) {
				res.insert(res.begin(), char(tmp + 38));
				carry = 1;
			}
			else {
				res.insert(res.begin(), char(tmp + 48));
				carry = 0;
			}
		}
	}
	if (carry == 1) res.insert(res.begin(), '1');
	//cout << "double = " << res << endl;

	return res;
}

void createPowOfTwo(vector<string>& PowOfTwo, int MaxiExp) {
	PowOfTwo.push_back("1");
	string tmp = "1";
	int len = 2;
	for (int i = 1; i <= MaxiExp; ++i) {
		tmp = doubleStr(tmp);
		PowOfTwo.push_back(tmp);
	}
}
//
////Tao so lon nhat
//void createINF(string &INF, vector<string>& PowOfTwo) {
//	INF = sub(PowOfTwo[MaxExp + 1], PowOfTwo[MaxExp - SIGN]);
//}

string multiplyStr(string a, char b) {
	string res = "";
	int len = a.length();
	int k = a.find('.');
	if (k != string::npos) 
		a.erase(k, 1);
	res.resize(len);
	for (int i = 0; i < len; ++i)
		a[i] -= 48;
	b -= 48;
	int carry = 0, tmp;
	for (int i = len - 1; i >= 0; --i) {
		tmp = a[i] * b + carry;
		res[i] = tmp % 10;
		carry = tmp / 10;
	}
	if (carry != 0) res.insert(0, 1, carry), len++;
	for (int i = 0; i < len; ++i)
		res[i] += 48;
	return res;
}

string multiplyStr(string a, string b) {
	if (a.length() < b.length())
		swap(a, b);
	string res = "", tmp;
	int len = b.length();
	int k1 = a.find('.');
	int k2 = b.find('.');
	if (k1 != string::npos)
		a.erase(k1, 1), k1 = a.length() - k1;
	else k1 = 0;
	if (k2 != string::npos) {
		b.erase(k2, 1);
		len--;
		k2 = len - k2;
	}
	else k2 = 0;
	for (int i = len - 1; i >= 0; --i) {
		tmp = multiplyStr(a, b[i]);
		for (int j = i + 1; j < len; ++j)
			tmp += "0";
		res = add(res, tmp, 10);
	}

	if (k1 + k2 != 0)
		res.insert(res.end() - (k1 + k2), 1, '.');
	while (res[0] == '0' && res[0] != '.')
		res.erase(0, 1);
	if (res[0] == '.')
		res.insert(0, 1, '0');
	return res;
}

//Chia hai chuoi so x
string StrDiv2(string x) {
	string res = x;
	int len = x.length();
	int rem = 0, tmp;
	for (int i = 0; i < len; ++i) {
		tmp = rem * 10 + (x[i] - 48);
		res[i] = tmp / 2 + 48;
		rem = tmp % 2;
	}
	while (res[0] == '0')
		res.erase(0, 1);
	if (res == "")
		res = "0";
	return res;
}

string toBinary(string a) {
	string res = "";
	string x = a;
	while (x != "0") {
		int bit = x.back() % 2;
		if (bit == 1) res = "1" + res;
		else res = "0" + res;
		x = StrDiv2(x);
	}
	return res;
}

//Kiem tra co phai so 0 hay khong
bool checkDecimalZero(string x) {
	int k = x.find('.');
	int len = x.length();
	if (k != string::npos) {
		for (int i = 0; i < len; ++i)
		if (x[i] != '0') return false;
		return true;
	}
	else {
		for (int i = 0; i < k; ++i)
		if (x[i] != '0') return false;
		for (int i = k + 1; i < len; ++i)
		if (x[i] != '0') return false;
		return true;
	}
}

string StrToStrBit(string x, int &exp) {
	int k = x.find('.');
	string intPart, fractionPart;
	if (k == string::npos) {
		intPart = x;
		fractionPart = "0";
	}
	else {
		intPart = x.substr(0, k);
		fractionPart = x.substr(k);
		fractionPart.insert(fractionPart.begin(), '0');
	}

	intPart = toBinary(intPart);

	for (int i = 0; i < SIGN; ++i)
		fractionPart = doubleStr(fractionPart);
	//cout << "fractionPart = " << fractionPart << endl;

	fractionPart = fractionPart.substr(0, fractionPart.find('.'));
	fractionPart = toBinary(fractionPart);

	/*cout << "intPart = " << intPart << endl;
	cout << "fractionPart = " << fractionPart << endl;*/

	int fractionLength = fractionPart.length();
	if (intPart != "")
		exp = intPart.length() - 1 + BIAS;
	else
		exp = fractionLength - SIGN + BIAS - 1;

	//cout << "exp = " << exp << endl;
	for (int i = 0; i < SIGN - fractionLength; ++i)
		fractionPart.insert(fractionPart.begin(), '0');

	string res = intPart + fractionPart;
	while (res[0] == '0')
		res.erase(0, 1);
	for (int i = res.length(); i < SIGN + 1; ++i)
		res += "0";
	return res;
}

//Chuyen chuoi so x sang QFloat
void StrToQFloat(string x, QFloat &a) {
	bool isNegative = false;
	if (x[0] == '-') {
		isNegative = true;
		x.erase(0, 1);
	}

	if (checkDecimalZero(x)) {
		a = (char)0;
		return;
	}

	int exp;
	string Sign = StrToStrBit(x, exp);
	if (isNegative) {
		SetBit(a, 1, 0);
	}
	else SetBit(a, 0, 0);

	for (int i = 1; i <= EXP; i++)
		SetBit(a, bitValue(exp, 31 - EXP + i), i);    

	for (int i = EXP + 1; i < EXP + SIGN + 1; i++)
		SetBit(a, Sign[i - EXP] - 48, i);
}

//Shift Right
void ShiftRight(QFloat &a, int n) {
	for (int i = SIGN - n - 1; i >= 1; --i)
		SetBit(a, bitValue(a, i + EXP), i + EXP + n);
	SetBit(a, 1, EXP + n);
	for (int i = 1; i < n; ++i)
		SetBit(a, 0, EXP + i);
}

//Shift Left
void ShiftLeft(QFloat &a, int n) {
	for (int i = 1; i < SIGN - n; ++i)
		SetBit(a, bitValue(a, i + EXP + n), i + EXP);
	for (int i = SIGN - n; i < SIGN; ++i)
		SetBit(a, 0, EXP + i);
}

//Check if QFloat is 0
bool isZero(QFloat a) {
	for (int i = 1; i < NBYTES; ++i)
		if (a.data[i] != 0) return false;
	if (a.data[0] == 0 || a.data[0] == 0x80) return true;
	else return false;
}

//Check if QFloat is denormal
bool isDenormal(QFloat a) {
	if (a.data[0] != 0 && a.data[0] != 0x80) return false;
	if (bitValue(a, 8) != 0) return false;
	else return true;
}

//Create Exponent String for QFloat
string ExpString(QFloat a) {
	string exp;
	for (int i = 1; i <= EXP; ++i)
		exp += to_string(bitValue(a, i));
	return exp;
}

//Calculate exponent of QFloat
int calcExp(QFloat a) {
	int exp = 0;
	for (int i = 1; i <= EXP; ++i)
		exp += bitValue(a, i)*(1 << (EXP - i));
	return exp;
}

//Create Significand String for QFloat
string SignificandStr(QFloat a) {
	string significand = "";

//	if (bitValue(a, 0) == 0) significand += "0";
//	else significand += "1";

	if (isDenormal(a)) significand += "0";
	else significand += "1";

	for (int i = EXP + 1; i < EXP + SIGN + 1; ++i)
		if (bitValue(a, i) == 0) significand += "0";
		else significand += "1";

    return significand;
}

//Create a two's complement of a significand string
string TwoComplementStr(string a) {
	string res = "";
	//cout << "a = " << a << endl;
    for(int i = 0; i < a.length(); ++i)
        a[i] = 97 - a[i];
    //cout << "a = " << a << endl;
    res = add(a, "1", 2);
    //cout << "r = " << res << endl;
    if (res.length() > a.length())
        res.erase(0, 1);
    //cout << "r = " << res << endl;
    res.insert(0, 1, '1');
    //cout << "res = " << res << endl;
	return res;
}

string TwoComplementToSign(string a) {
    string res = "";
    a.erase(0, 1);
    res = sub(a, "1", 2);
    //cout << "res = " << res << endl;
    if (res.length() > a.length())
        res.erase(0, 1);
    for(int i = 0; i < a.length(); ++i)
        res[i] = 97 - res[i];
    res.insert(0, 1, '1');
    return res;
}

bool isNegative(QFloat a) {
	return (bitValue(a, 0) == 1);
}

bool add(QFloat a, QFloat b, QFloat &sum) {
	int expA = calcExp(a);
	int expB = calcExp(b);
	int d = expA - expB;
	if (d < 0) {
		swap(a, b);
		swap(expA, expB);
		d = -d;
	}
	ShiftRight(b, d);
	string x = SignificandStr(a);
	string y = SignificandStr(b);
	if (d != 0) y[0] = '0';

    int signBit1 = bitValue(a, 0);
    int signBit2 = bitValue(b, 0);

    string res;
    if (signBit1 != signBit2) {
        if (signBit1 == 1) {
            x = TwoComplementStr(x);
            y.insert(0, 1, '0');
        }
        else {
            y = TwoComplementStr(y);
            x.insert(0, 1, '0');
        }
        /*cout << "x = " << x << endl;
        cout << "y = " << y << endl;*/
        res = add(x, y, 2);
       // cout << "r = " << res << endl;
        if (res.length() > x.length())
            res.erase(0, 1);
        if (res[0] == '1')
            res = TwoComplementToSign(res);
        //cout << "r = " << res << endl;
    }
    else {
        x.insert(0, 1, '0');
        y.insert(0, 1, '0');

        //cout << "x = " << x << endl;
        //cout << "y = " << y << endl;

        bool isNegative = false;
        if (signBit1 == 1)
            isNegative = true;
        res = add(x, y, 2);
        if (res[0] == '1') {
            res.insert(0, 1, '0');
            res.erase(res.end() - 1);
            ++expA;
        }
        if (isNegative) res[0] = '1';
       // cout << "r = " << res << endl;
    }

    //Convert sum to QFloat
    SetBit(sum, res[0] - 48, 0);
    int countZero = 0;
    for(int i = 1; i < res.length(); ++i)
        if (res[i] == '1') break;
        else countZero++;
    if (countZero == SIGN + 1) {
        sum = 0;
        return true;
    }
    else {
        expA -= countZero;
        //cout << "exp = " << expA << endl;
        if (expA > MaxExp + BIAS) {
            cout << "Overflow" << endl;
            return false;
        }
        //Set Exponent 's Bits
        for(int i = 1; i <= EXP; ++i)
            SetBit(sum, bitValue(expA, 31 - EXP + i), i);
        //Set Significand 's Bits
        for(int i = 0; i < SIGN - countZero - 2; ++i)
            SetBit(sum, res[countZero + 2 + i] - 48, i + EXP + 1);
        for(int i = SIGN - countZero - 2; i < SIGN; ++i)
            SetBit(sum, 0, i + EXP + 1);
    }
//    cout << "sum = ";
//    PrintBinary(sum);
//    cout << endl;
	return true;
}

bool sub(QFloat a, QFloat b, QFloat &sub) {
	SetBit(b, 1 - bitValue(b, 0), 0);
	return add(a, b, sub);
}
//Chuyen chuoi so x sang QFloat
void StrDecToQFloat(string x, QFloat &a) {
	bool isNegative = false;
	if (x[0] == '-') {
		isNegative = true;
		x.erase(0, 1);
	}

	if (checkDecimalZero(x)) {
		a = (char)0;
		return;
	}

	int exp;
	string Sign = StrToStrBit(x, exp);
	if (isNegative) {
		SetBit(a, 1, 0);
	}
	else SetBit(a, 0, 0);

	for (int i = 1; i <= EXP; i++)
		SetBit(a, bitValue(exp, 31 - EXP + i), i);

	for (int i = EXP + 1; i < EXP + SIGN + 1; i++)
		SetBit(a, Sign[i - EXP] - 48, i);
}

void StrBinToQFloat(string x, QFloat& a) {
	for (int i = 0; i < x.length(); ++i)
		SetBit(a, x[i] - 48, i);
}

