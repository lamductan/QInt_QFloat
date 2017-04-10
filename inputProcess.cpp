#include "InputProcess.h"
//Kiem tra ki tu co nam trong khoang '0' den '9' hoac 'A' den 'F' hay ko
bool checkNormalCharacter(char c) {
	return ((c >= '0' && c <= '9')
		|| (c >= 'a' && c <= 'f')
		|| (c >= 'A' && c <= 'F')
		|| c == '.' || c == '-');
}

//Chuan hoa chuoi phep tinh (dam bao co dau cach giua toan tu va cac toan hang)
void standardlizeStr(string& x) {
	int i = 0;
	int len = x.length();
	while (i < len - 1) {
		if (checkNormalCharacter(x[i]) != checkNormalCharacter(x[i + 1])) {
			x.insert(i + 1, 1, ' ');
			len++;
			i++;
		}
		i++;
	}
}

//Tach chuoi thanh cac token voi ' ' la ki tu phan cach
vector<string> tokenize(string x) {
	int len = x.length();
	vector<string> res;
	char* xt = new char[len + 1];
	strcpy(xt, x.c_str());
	char * p = std::strtok(xt, " ");
	while (p != NULL)
	{
		res.push_back(string(p));
		p = std::strtok(NULL, " ");
	}

	delete[] xt;
	return res;
}

//Kiem tra chuoi co ki tu dac biet hay khong
bool existSpecialCharacter(string x) {
	for (int i = 0; i < x.length(); ++i)
	if (!checkNormalCharacter(x[i]))
		return true;
	return false;
}

//Xu li chuoi input
//base luu co so cua cac toan hang, neu khong dung de chuyen co so thi base.second = 0
//operand luu toan hang, neu chi co mot toan hang thi oerand.second = NULL
//myOperator luu toan tu
void processingInput(string input, pair<int, int>& base, pair<string, string>& operand, string& myOperator) {
	base.second = 0;
	operand.second = "";
	standardlizeStr(input);
	vector<string> token = tokenize(input);

	int mySize = token.size();

	base.first = atoi(token[0].c_str());
	if (mySize == 3) {
		operand.first = token[2];
		if (existSpecialCharacter(token[1]))
			myOperator = token[1];
		else base.second = atoi(token[1].c_str());
	}
	else {
		operand.first = token[1];
		myOperator = token[2];
		operand.second = token[3];
	}
}

//Xu li input QFloat
void solveQFloat(char* inputFileName, char* outputFileName) {
	fstream fin, fout;
	fin.open(inputFileName, fstream::in);
	freopen(outputFileName, "w", stdout);

	string input;
	pair<int, int> base;
	pair<string, string> operand;
	string myOperator;
	QFloat a, b, res;

	while (getline(fin, input)) {
		processingInput(input, base, operand, myOperator);
		if (base.second != 0) {
			if (base.first == 2) {
				StrBinToQFloat(operand.first, a);
				fout << QFloatBinToDec(a);
			}
			else {
				StrDecToQFloat(operand.first, a);
				PrintBinary(a);
			}
		}
		else {
			if (base.first == 2) {
				StrBinToQFloat(operand.first, a);
				StrBinToQFloat(operand.second, b);
			}
			else {
				StrDecToQFloat(operand.first, a);
				StrDecToQFloat(operand.second, b);
			}

			if (myOperator == "+") {
				if (add(a, b, res))
					PrintBinary(res);
				else cout << "Error";
			}
			else if (myOperator == "-") {
				if (sub(a, b, res))
					PrintBinary(res);
				else cout << "Error";
			}
			else if (myOperator == "*") {
				if (multiply(a, b, res))
					PrintBinary(res);
				else cout << "Error";
			}
			else if (myOperator == "/") {
				Divide(a, b, res);
				PrintBinary(res);
			}
		}
		cout << endl;
	}
	fin.close();
	fclose(stdout);
}

// Xử lý QInt
void solveQInt(char* inputFileName, char* outputFileName) {
	fstream fin, fout;
	fin.open(inputFileName, fstream::in);
	freopen(outputFileName, "w", stdout);

	string input;
	pair<int, int> base;
	pair<string, string> operand;
	string myOperator;
	QInt a, b, res;

	while (getline(fin, input)) {
		processingInput(input, base, operand, myOperator);
		if (base.second != 0) {
			if (base.first == 2) {
				a = ConvertBinToDec(operand.first);
				cout << QIntToDec(a);
			}
			if (base.first==10){
				ScanQInt(a,operand.first);
				cout << ModifyStringNum((QIntDecToBin(a)));
			}
			if (base.first == 16)
			{
				QIntHexToDec(operand.first);
				cout << QIntToDec(a);
			}
		}
		else {
			if (base.first == 2) {
				a = ConvertBinToDec(operand.first);
				b = ConvertBinToDec(operand.second);
				
			}
			if (base.first == 10)
			{
				ScanQInt(a, operand.first);
				ScanQInt(b, operand.second);
			}
			if (base.first == 16)
			{
				a = QIntHexToDec(operand.first);
				b = QIntHexToDec(operand.second);
			}
			if (myOperator == "+") res = a + b;
			if (myOperator == "-") res = a - b;
			if (myOperator == "*") res = a*b;
			if (myOperator == "/") res = a / b;
			
			if (myOperator == ">>") {
				ShiftRight(a, atoi(operand.second.c_str()));
				res = a;
			}
			if (myOperator == "<<") {
				ShiftLeft(a, atoi(operand.second.c_str()));
				res = a;
			}
			if (myOperator == "~")
			{
				QInt NegativeOne; 
				ScanQInt(NegativeOne, "-1");
				res = NegativeOne - a;
			}
			if (myOperator == "ror")
			{
				res = RotateRight(a);
			}
			if (base.first==2) cout<< ModifyStringNum(QIntDecToBin(res));
			if (base.first == 10) cout << ModifyStringNum(QIntToDec(res));
			if (base.first == 16) cout << ModifyStringNum(QIntDecToHex(res));
		}
		cout << endl;
	}
	fin.close();
	fclose(stdout);
}