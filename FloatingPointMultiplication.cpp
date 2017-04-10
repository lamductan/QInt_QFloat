#include "Floating Point.h"

void ShiftRight(int C, string &A, string &Q, int nbit) {
    for(int i = nbit - 2; i >= 0; --i)
        Q[i + 1] = Q[i];
    Q[0] = A[nbit - 1];
    for(int i = nbit - 2; i >= 0; --i)
        A[i + 1] = A[i];
    A[0] = C + 48;
}

string multiplySignificand(string Q, string M, int nbit) {
    int nSteps = nbit;
    string A(nbit, '0');
    int C = 0;
    while (nSteps--) {
        if (Q[nbit - 1] == '1') {
            A = add(A, M, 2);
			if (A.length() > nbit) {
				C = 1;
				A.erase(0, 1);
			}
        }
		
		ShiftRight(C, A, Q, nbit);
		C = 0;
    }
    return A + Q;
}

bool multiply(QFloat a, QFloat b, QFloat& res) {
	if (isZero(a) || isZero(b)) {
		res = 0;
		return true;
	}
	int expA = calcExp(a);
	int expB = calcExp(b);
	int exp = expA + expB - BIAS;

	string x = SignificandStr(a);
	string y = SignificandStr(b);
	int signBit1 = bitValue(a, 0);
	int signBit2 = bitValue(b, 0);

	string res1 = multiplySignificand(x, y, SIGN + 1);
	if (res1[0] == '1') {
		exp++;
	}
	else res1.erase(0, 1);
	res1.erase(res1.begin() + SIGN + 1, res1.end());
	//cout << "res1 = " << res1 << endl;

	if (exp > MaxExp + BIAS) {
		cout << "Overflow" << endl;
		return false;
	}
	//cout << "exp = " << exp << endl;
	//Set sign of product
	SetBit(res, bitValue(a, 0) != bitValue(b, 0), 0);
	//Set Exponent 's Bits
	for (int i = 1; i <= EXP; ++i)
		SetBit(res, bitValue(exp, 31 - EXP + i), i);
	if (exp != 0) {
		for (int i = 1; i <= SIGN; ++i)
			SetBit(res, res1[i] - 48, i + EXP);
	}
	return true;
}