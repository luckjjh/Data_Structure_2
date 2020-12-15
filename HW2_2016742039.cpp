//2016742039 ������
#include <iostream>
#include <stack>
#include <fstream>
#include<string>
#include<cstring>
#include<vector>
using namespace std;
const static int MAX_ROW = 3;
const static int MAX_COL = 3;//�����ڰ� �� array�� ũ�⸦ ����� ������ Ȯ�强 ����
bool is_balance(const string& input);
vector<char> make_post_fix(const string& input);
bool is_prime(stack<char> input,char inO);
char read_calculate(string input,char at[MAX_ROW][MAX_COL],char sh[MAX_ROW][MAX_COL],char ad[MAX_ROW][MAX_COL]);
int main() 
{
	ifstream inputOper("operations.txt");//operator ����� txt ���� ����
	char atOper[MAX_ROW][MAX_COL] = { {0,} };//@operator ���� array
	char sharpOper[MAX_ROW][MAX_COL] = { {0,} };//#operator ���� array
	char andOper[MAX_ROW][MAX_COL] = { {0,} };//&operator ���� array
	string line;//���ڿ� ���� ���� buffer
	while (!inputOper.eof()) {
		getline(inputOper, line);
		if (line[0] == '@') {//@������ ����
			for (size_t i = 0; i < sizeof(atOper[0]); i++) {
				getline(inputOper, line);
				int col = 0;
				for (size_t j = 0; j < line.size(); j++) {
					if (line[j] != ' ')
						atOper[i][col++] = line[j];
				}
			}
		}
		else if (line[0] == '#') {//#������ ����
			for (size_t i = 0; i < sizeof(sharpOper[0]); i++) {
				getline(inputOper, line);
				int col = 0;
				for (size_t j = 0; j < line.size(); j++) {
					if (line[j] != ' ')
						sharpOper[i][col++] = line[j];
				}
			}
		}
		else if (line[0] == '&') {//&������ ����
			for (size_t i = 0; i < sizeof(andOper[0]); i++) {
				getline(inputOper, line);
				int col = 0;
				for (size_t j = 0; j < line.size(); j++) {
					if (line[j] != ' ')
						andOper[i][col++] = line[j];
				}
			}
		}
		else cout << "�������� ���� �����ڸ� �Է��߽��ϴ�.";
	}
	inputOper.close();
	//operator�� ���� ��� ���� �Ϸ�
	//���� ���� �Է�
	string input;
	char result;
	while (true) {
		cin >> input;
		if (input == "EOI")
			break;
		if (is_balance(input)) {
			result = read_calculate(input, atOper, sharpOper, andOper);
			cout << result << endl;
		}
		else {
			cout << "Error !"<<endl;
			continue;
		}
	}
	return 0;
}

bool is_balance(const string& input) {
	stack<char> parent;
	int i = 0;
	while (input[i] != '\0') {
		if (input[i] == '[' || input[i] == '{' || input[i] == '(') {
			parent.push(input[i]);
		}
		else {
			if(parent.empty()&&(input[i] == ']' || input[i] == '}' || input[i] == ')'))
				return false;
			else if (input[i] == ']' && parent.top() == '[')
				parent.pop();
			else if (input[i] == '}' && parent.top() == '{')
				parent.pop();
			else if (input[i] == ')' && parent.top() == '(')
				parent.pop();
		}
		i++;
	}
	if (parent.empty())
		return true;
	else return false;
}

vector<char> make_post_fix(const string& input) {
	stack<char> operators;
	vector<char> operations;
	int i = 0;
	while (input[i]!='\0') {
		if (input[i] == '[' || input[i] == '{' || input[i] == '(') {
			operators.push(input[i]);
		}
		else if (input[i] == 'a' || input[i] == 'b' || input[i] == 'c') {
			operations.push_back(input[i]);
		}
		else if (input[i] == '@' || input[i] == '#' || input[i] == '&') {
			while (!operators.empty()
				&& operators.top() != '('
				&& operators.top() != '{'
				&& operators.top() != '['
				&& is_prime(operators,input[i])) {
				operations.push_back(operators.top());
				operators.pop();
			}
			operators.push(input[i]);
		}
		else if (input[i]==')'|| input[i] == '}' || input[i] == ']') {
				operations.push_back(operators.top());
				operators.pop();
			while ((input[i] == ')' && operators.top() != '(')
				|| (input[i] == '}' && operators.top() != '{')
				|| (input[i] == ']' && operators.top() != '[')) {
				if (operators.top() == '@'
					|| operators.top() == '#'
					|| operators.top() == '&') {
					operations.push_back(operators.top());
					operators.pop();
				}
			}
			operators.pop();//���� ������ ��ȣ stack���� ����
		}
		i++;
	}
	while (!operators.empty()) {
		if (operators.top() == '@'
			|| operators.top() == '#'
			|| operators.top() == '&') {
			operations.push_back(operators.top());
		}
		operators.pop();
	}
	return operations;
}

bool is_prime(stack<char> input,char inO) {
	char topO = input.top();
	if ((inO == '@' || inO == '#') && topO == '&')
		return true;
	else if ((inO == '@' || inO == '#') && (topO == '@' || topO == '#'))
		return true;
	else if (inO == '&' && topO == '&')
		return true;
	else
		return false;
}

char read_calculate(string input, 
	char at[MAX_ROW][MAX_COL], 
	char sh[MAX_ROW][MAX_COL], 
	char ad [MAX_ROW][MAX_COL]) {
	vector<char> postFix;
	postFix = make_post_fix(input);
	stack<char> result;
	vector<char>::iterator it;
	for (it=postFix.begin(); it!=postFix.end(); it++) {
		char operand;
		result.push(*it);
		if (*it == '@') {
			result.pop();//������ �ִ� operator �ٸ� ���� ���� �Ǿ������� pop
			operand = result.top();// ������ �ִ� operand�� ����
			result.pop();//operand ������������ pop
			switch (operand) {
			case 'a':
				if (result.top() == 'a') { result.pop(); result.push(at[0][0]);
					break;
				}
				else if (result.top() == 'b') { result.pop(); result.push(at[1][0]);
					break;
				}
				else if (result.top() == 'c') { result.pop(); result.push(at[2][0]);
					break;
				}
			case 'b':
				if (result.top() == 'a') { result.pop(); result.push(at[0][1]);
					break;
				}
				else if (result.top() == 'b') { result.pop(); result.push(at[1][1]);
					break;
				}
				else if (result.top() == 'c') { result.pop(); result.push(at[2][1]);
					break;
				}
			case 'c':
				if (result.top() == 'a') { result.pop(); result.push(at[0][2]);
					break;
				}
				else if (result.top() == 'b') { result.pop(); result.push(at[1][2]);
					break;
				}
				else if (result.top() == 'c') { result.pop(); result.push(at[2][2]);
					break;
				}
			}
		}
		else if (*it == '#') {
			result.pop();
			operand = result.top();
			result.pop();
			switch (operand) {
			case 'a':
				if (result.top() == 'a') { result.pop(); result.push(sh[0][0]);
					break;
				}
				else if (result.top() == 'b') { result.pop(); result.push(sh[1][0]);
					break;
				}
				else if (result.top() == 'c') { result.pop(); result.push(sh[2][0]);
					break;
				}
			case 'b':
				if (result.top() == 'a') { result.pop(); result.push(sh[0][1]);
					break;
				}
				else if (result.top() == 'b') { result.pop(); result.push(sh[1][1]);
					break;
				}
				else if (result.top() == 'c') { result.pop(); result.push(sh[2][1]);
					break;
				}
			case 'c':
				if (result.top() == 'a') { result.pop(); result.push(sh[0][2]);
					break;
				}
				else if (result.top() == 'b') { result.pop(); result.push(sh[1][2]);
					break;
				}
				else if (result.top() == 'c') { result.pop(); result.push(sh[2][2]);
					break;
				}
			}
		}
		else if (*it == '&') {
			result.pop();
			operand = result.top();
			result.pop();
			switch (operand) {
			case 'a':
				if (result.top() == 'a') { result.pop(); result.push(ad[0][0]);
					break;
				}
				else if (result.top() == 'b') { result.pop(); result.push(ad[1][0]);
					break;
				}
				else if (result.top() == 'c') { result.pop(); result.push(ad[2][0]);
					break;
				}
			case 'b':
				if (result.top() == 'a') { result.pop(); result.push(ad[0][1]);
					break;
				}
				else if (result.top() == 'b') { result.pop(); result.push(ad[1][1]);
					break;
				}
				else if (result.top() == 'c') { result.pop(); result.push(ad[2][1]);
					break;
				}
			case 'c':
				if (result.top() == 'a') { result.pop(); result.push(ad[0][2]);
					break;
				}
				else if (result.top() == 'b') { result.pop(); result.push(ad[1][2]);
					break;
				}
				else if (result.top() == 'c') { result.pop(); result.push(ad[2][2]);
					break;
				}
			}
		}
	}
	return result.top();
}