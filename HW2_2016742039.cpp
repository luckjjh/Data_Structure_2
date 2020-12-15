//2016742039 정정현
#include <iostream>
#include <stack>
#include <fstream>
#include<string>
#include<cstring>
#include<vector>
using namespace std;
const static int MAX_ROW = 3;
const static int MAX_COL = 3;//연산자가 들어갈 array의 크기를 상수로 지정해 확장성 높임
bool is_balance(const string& input);
vector<char> make_post_fix(const string& input);
bool is_prime(stack<char> input,char inO);
char read_calculate(string input,char at[MAX_ROW][MAX_COL],char sh[MAX_ROW][MAX_COL],char ad[MAX_ROW][MAX_COL]);
int main() 
{
	ifstream inputOper("operations.txt");//operator 저장된 txt 파일 열기
	char atOper[MAX_ROW][MAX_COL] = { {0,} };//@operator 저장 array
	char sharpOper[MAX_ROW][MAX_COL] = { {0,} };//#operator 저장 array
	char andOper[MAX_ROW][MAX_COL] = { {0,} };//&operator 저장 array
	string line;//문자열 저장 위한 buffer
	while (!inputOper.eof()) {
		getline(inputOper, line);
		if (line[0] == '@') {//@연산자 저장
			for (size_t i = 0; i < sizeof(atOper[0]); i++) {
				getline(inputOper, line);
				int col = 0;
				for (size_t j = 0; j < line.size(); j++) {
					if (line[j] != ' ')
						atOper[i][col++] = line[j];
				}
			}
		}
		else if (line[0] == '#') {//#연산자 저장
			for (size_t i = 0; i < sizeof(sharpOper[0]); i++) {
				getline(inputOper, line);
				int col = 0;
				for (size_t j = 0; j < line.size(); j++) {
					if (line[j] != ' ')
						sharpOper[i][col++] = line[j];
				}
			}
		}
		else if (line[0] == '&') {//&연산자 저장
			for (size_t i = 0; i < sizeof(andOper[0]); i++) {
				getline(inputOper, line);
				int col = 0;
				for (size_t j = 0; j < line.size(); j++) {
					if (line[j] != ' ')
						andOper[i][col++] = line[j];
				}
			}
		}
		else cout << "지정되지 않은 연산자를 입력했습니다.";
	}
	inputOper.close();
	//operator들 연산 결과 저장 완료
	//연산 내용 입력
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
			operators.pop();//남은 오른쪽 괄호 stack에서 삭제
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
			result.pop();//맨위에 있던 operator 다른 곳에 저장 되었음으로 pop
			operand = result.top();// 맨위에 있는 operand로 변경
			result.pop();//operand 저장했음으로 pop
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