#pragma once
#include"fraction.h"
class expression
{

	static constexpr int numberLimit = 4;
	static constexpr char ops[] = "+-*/";
	vector<fraction> nums;
	vector<char> chars;
	pair<int, int> brackets{ -1,-1 };
	fraction ans;
	string exp;
	bool invalid = 0;
	static int getPriority(char ch) {

		switch (ch) {
		case '(':
			return 1;
		case '+':
		case '-':
			return 2;

		case '*':
		case '/':
			return 3;

		default:
			return 4;
		}
	}
	fraction cal(fraction&a, fraction &b, char op) {
		if (a.toString() == "NAN" || b.toString() == "NAN")
			return fraction();
		if (op == '+') return a + b;
		if (op == '-') return a - b;
		if (op == '*') return a * b;
		if (op == '/') {
			if (b == fraction("0")) {
				return fraction();
			}
			return a / b;
		}
		return fraction();
	}
	fraction calAns() {
		queue<pair<fraction, char>> que;
		stack< char> op;
		int i = 0;
		while (i < exp.size()) {
			if (isdigit(exp[i])) {  // ���������
				que.push({ fraction(exp.substr(i,exp.find(' ',i) - i)),1 });
				i = exp.find(' ', i) + 1;
			}
			else if (exp[i] == '(') {  // (:������
				op.push(exp[i]);
				i++;
			}
			else if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/') {  // ������
				if (op.empty()) {             // ���ջ�գ�ֱ��ѹ��ջ
					op.push(exp[i]);
					i++;
				}
				else {
					// �Ƚ�ջop���Ĳ�������ch�����ȼ�
					// ���ch�����ȼ��ߣ���ֱ��ѹ��ջ
					// �����Ƴ�ջ�еĲ�������ֱ��������С��ch�����ȼ�������������������ջ�ѿ�
					while (!op.empty()) {
						char c = op.top();
						if (getPriority(exp[i]) <= getPriority(c)) {
							// ���ȼ��ͻ����
							que.push({ fraction(),c });
							op.pop();
						}
						else {
							break;// ch���ȼ�����ջ�в�����}
						}  // while����
					}
					op.push(exp[i]);
					// ��ֹ���ϵ��Ƴ�������������ջ��;����ch���ȼ�����
					i++;
					// else
				}
			}
			else if (exp[i] == ')') {
				// ����������ţ�һֱ�Ƴ�ջ�в�������ֱ������������(
				while (op.top() != '(') {
					que.push({ fraction(),op.top() });
					op.pop();
				}
				op.pop();  // ��������(�Ƴ�ջ
				i++;
			}
			else
			{
				i++;// ����ǿհ׷����ͽ�����һ���ַ��Ĵ���
			}
		}                      // �ڶ���while����
		while (!op.empty()) {
			que.push({ fraction(),op.top() });
			op.pop();
		}
		stack<fraction> stk;
		while (que.size()) {
			if (que.front().first.toString() != "NAN") {
				stk.push(que.front().first);
				que.pop();
			}
			else {
				fraction b = stk.top();
				stk.pop();
				fraction a = stk.top();
				stk.pop();
				char c = que.front().second;
				que.pop();
				stk.push(cal(a, b, c));
				if (stk.top() < fraction("0")) {
					return fraction();
				}
			}
		}
		return stk.top();
	}

public:
	expression(long long limit) {
		int cnt = rand() % (numberLimit - 1) + 2;

		if (cnt > 2 && rand() % 2) {
			brackets.first = rand() % (cnt - 1);
			brackets.second = rand() % (cnt - brackets.first - 1) + brackets.first + 1;
		}
		for (int i = 0; i < cnt; i++)
		{
			nums.emplace_back(limit);
		}
		for (int i = 0; i < cnt - 1; i++)
		{
			chars.emplace_back(ops[rand() % 4]);
		}

		for (int i = 0; i < cnt; i++)
		{
			if (i == brackets.first)  exp += '(';
			exp += ' ';
			exp += nums[i].toString();
			exp += ' ';
			if (i == brackets.second)  exp += ')';
			if (i < cnt - 1) exp += chars[i];
		}
		ans = calAns();
		if (ans.toString() == "NAN") {
			*this = expression(limit);
		}
	}
	string toString() {
		return exp;
	}
	fraction getAns() {
		return ans;
	}
};

