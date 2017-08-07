/*
 * 解释器模式：
 * 给定一个语言，定义它的文法的一种表示，并定义一个解释器，
 * 这个解释器使用该表示来解释语言中的句子。
 */
#include <iostream>
#include <memory>

using namespace std;

class Expression
{
public:
    virtual void Interpret() = 0;
};

class TerminalExpression : public Expression
{
public:
    virtual void Interpret() override
    {
        cout << "TerminalExpression" << endl;
    }
};

class NonterminalExpression : public Expression
{
public:
    virtual void Interpret() override
    {
        cout << "NonterminalExpression" << endl;
        if (expression_)
            expression_->Interpret();
    }

    void setExpression(shared_ptr<Expression>& expression)
    {
        expression_ = expression;
    }
private:
    shared_ptr<Expression> expression_;
};

int main()
{
    shared_ptr<Expression> tp = make_shared<TerminalExpression>();
    shared_ptr<Expression> ntp = make_shared<NonterminalExpression>();

    static_pointer_cast<NonterminalExpression>(ntp)->setExpression(tp);

    ntp->Interpret();

    return 0;
}