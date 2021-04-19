#include <iostream>
#include <math.h>
#include <string>
#include <stack>
using namespace std;
int isNumber(char s)
{
    return '0' <= s && s <= '9';
}
int isOperator(char s)
{
    return (s == '+') || (s == '-') || (s == '*') || (s == '/') || (s == '^');
}
int prec(char s)
{
    if (s == '+' || s == '-')
        return 1;
    if (s == '*' || s == '/')
        return 2;
    if (s == '^')
        return 3;
    return 0;
}
bool testExpression(string expression)
{
    int x = 0, y = 0;
    for (int i = 0; i < expression.size(); ++i)
    {

        if (expression[i] == '(')
        {
            ++x;
            continue;
        }
        if (expression[i] == ')')
        {
            ++y;
            continue;
        }
        if (isOperator(expression[i]) ||
            isNumber(expression[i]) ||
            expression[i] == '.' ||
            expression[i] == ' ')
        {
            continue;
        }
        return false;
    }
    if (x != y)
    {
        return false;
    }
    return true;
}
string standardizedExpression(string expression)
{
    string ans = "";
    if (!testExpression(expression))
    {
        cout << "Expression wrong";
        return "";
    }
    for (int i = 0; i < expression.size(); ++i)
    {
        if (expression[i] == ' ')
        {
            continue;
        }
        if (expression[i] == '(')
        {
            ans + " " + expression[i];
        }
        if (expression[i] == ')')
        {
            ans = ans + expression[i] + " ";
        }
        if (isOperator(expression[i]))
        {
            ans = ans + " " + expression[i] + " ";
        }
        else
        {
            ans += expression[i];
        }
    }
    return ans;
}
string convertToPrefix(string infix)
{
}
string convertToPostfix(string infix)
{
    string postfix = "";
    stack<char> Op;
    for (int i = 0; i < infix.size(); ++i)
    {
        if (infix[i] == ' ')
        {
            continue;
        }
        if (isNumber(infix[i]))
        {
            while (isNumber(infix[i]) || infix[i] == '.')
            {
                postfix += infix[i];
                ++i;
            }
            postfix += " ";
            continue;
        }
        if (infix[i] == '(')
        {
            Op.push(infix[i]);
        }
        if (isOperator(infix[i]))
        {
            if (Op.empty())
            {
                Op.push(infix[i]);
            }
            else
            {
                while (!Op.empty() && (prec(Op.top()) >= prec(infix[i])))
                {
                    postfix = postfix + Op.top() + " ";
                    Op.pop();
                }
                Op.push(infix[i]);
            }
            continue;
        }
        if (infix[i] == ')')
        {
            while (!Op.empty() && isOperator(Op.top()))
            {
                postfix = postfix + Op.top() + " ";
                Op.pop();
            }
            Op.pop();
            continue;
        }
    }
    while (!Op.empty())
    {
        postfix = postfix + Op.top() + " ";
        Op.pop();
    }
    return postfix;
}
double Calculator(double x, double y, char op)
{
    if (op == '+')
    {
        return x + y;
    }
    if (op == '-')
    {
        return x - y;
    }
    if (op == '*')
    {
        return x * y;
    }
    if (op == '/')
    {
        return x / y;
    }
    if (op == '^')
    {
        int y1 = y;
        return pow(x, y);
    }
    return 0;
}
double calculatorByPostfix(string postfix)
{
    if (postfix.size() == 0)
    {
        return 0;
    }
    stack<char> Op;
    stack<double> Number;
    double x;
    for (int i = 0; i < postfix.size(); ++i)
    {
        if (postfix[i] == ' ')
        {
            continue;
        }
        if (isNumber(postfix[i]))
        {
            double temp = 0;
            int check = 0;
            double fl = 0;
            while (isNumber(postfix[i]) || postfix[i] == '.')
            {
                if (postfix[i] == '.')
                {
                    check = -1;
                    ++i;
                    continue;
                }
                int x = postfix[i] - '0';
                if (check == 0)
                {
                    temp = temp * 10 + x;
                }
                else
                {
                    if (check == -1)
                    {
                        check = 0;
                    }
                    fl = fl * 10 + x;
                    ++check;
                }
                ++i;
            }
            while (check != 0)
            {
                fl = fl / 10;
                --check;
            }
            temp = temp + fl;
            Number.push(temp);
            continue;
        }
        if (isOperator(postfix[i]))
        {
            double y = Number.top();
            Number.pop();
            double x = Number.top();
            Number.pop();
            Number.push(Calculator(x, y, postfix[i]));
        }
    }
    return Number.top();
}
int main()
{
    //string pre = "3 * 41.1 + 7.23 * ( 5 + 32 ) / 2 + 1.3 ^ 3"; //258.355
    string pre;
    cout << "Nhap bieu thuc : ";
    getline(cin, pre);
    pre = standardizedExpression(pre);
    cout << "Bieu thuc : " << pre << endl;
    cout << "Postfix : " << convertToPostfix(pre) << endl;
    cout << "Ket qua tinh : " << calculatorByPostfix(convertToPostfix(pre)) << endl;
    return 0;
}
