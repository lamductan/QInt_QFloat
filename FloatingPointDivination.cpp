
#include "Floating Point.h"

string EraseZero(string &a)
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
int CompareBitString(string a, string b)
{
	int l = a.length()-b.length();
	if (l < 0)
	{
		for (int i = 0; i < -l; i++) {
			a = "0" + a;
		}
	}
	else
	{
		for (int i = 0; i < l; i++){
			b = "0" + b;
		}
	}
	for (int i = 0; i < a.length(); i++)
	{
		if (a[i] < b[i]) return -1;
		if (a[i] > b[i]) return 1;
		else continue;
	}
}

// Chia 2 chuỗi bit không dấu
string BitDiv(string a, string b, int &check)
{
	string temp = "";
	int pos = 0;
	string res = "";
	EraseZero(b);
	while (pos < a.length())
	{
	
			std::stringstream ss;
			ss << a[pos];
			string l;
			ss >> l;
			temp += l;
		if (CompareBitString(temp, b) == -1)
		{
			pos++;
		}
		else
		{
			temp = sub(temp, b, 2);
			res  = res+ "1";
			EraseZero(temp);
			pos++;
		}
	}
	if (res == "") check=1;
	while (res.length()<= SIGN)
	{
		temp = temp + "0";
		if (CompareBitString(temp, b) == -1)
		{
			res = res + "0";
		}
		else
		{
			temp = sub(temp, b, 2);
			res = res + "1";
			EraseZero(temp);
		}
	}
	return res;
}
void InverseBitString(string &bit)
{
	string temp;
	int l = bit.length();
	temp.resize(l);
	for (int i = 0; i < l; i++)
	{
		temp[i] = bit[l - i-1];
	}
	bit = temp;
}
void Divide(QFloat x, QFloat y, QFloat& res)
{
	if (isZero(x)) // Kiểm tra số chia bằng hay khác 0
	{
		res = 0;
		return;
	}
	if (isZero(y)) // Kiểm tra số bị chia bằng hay khác 0
	{
		cout << "Error" << endl;
		return;
	}
		int expA = calcExp(x);  // Tính giá trị phần mũ số thứ nhất
		int expB = calcExp(y);  // Tính giá trị phần mũ số thứ hai
		int exp = expA - expB+BIAS; // Giá trị phần mũ của kết quả

		expA -= MaxExp;
		expB -= MaxExp;
		int signBit1 = bitValue(x, 0);  // Bit dấu số chia
		int signBit2 = bitValue(y, 0);  // Bit dấu số bị chia 

		string sign1 = SignificandStr(x);  // Lấy phần định trị. Ví dụ, số 1.0101 tương ứng sign1= "10101";
		string sign2 = SignificandStr(y);
		
		//sign1.erase(sign1.begin());
		//sign2.erase(sign2.begin());
	
		//InverseBitString(sign1);
		//InverseBitString(sign2);
		if (exp > MaxExp + BIAS) {
			cout << "Overflow" << endl;
			return;
		}
		
		// Chia 2 phần định trị cho nhau
		int check;
		string res1 = BitDiv(sign1, sign2,check);

		if (check==1)
		{
			exp--;
		}
		//res1.erase(res1.begin());
		//Set sign of product
			SetBit(res, bitValue(x, 0) != bitValue(y, 0), 0);
		//Set Exponent 's Bits
		for (int i = 1; i <= EXP; ++i)
			SetBit(res, bitValue(exp, 31 - EXP + i), i);
		if (exp != 0) {
			for (int i = 1; i <= SIGN; ++i)
				SetBit(res, res1[i] - 48, i + EXP);
		}
}


