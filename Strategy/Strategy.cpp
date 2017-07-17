/*
* 策略模式：
* 它定义了算法家族，分别封装起来，让它们之间可以互相转换，此模式让算法的变化，
* 不会影响到使用算法的客户
*/
#include <iostream>
#include <memory>

using namespace std;

class Strategy
{
public:
    virtual void AlgorithmInterface() = 0;
    virtual ~Strategy()
    {
    }
};

class ConcretStrategyA :public Strategy
{
public:
    virtual void AlgorithmInterface() override
    {
        cout << "Algorithm A implement" << endl;
    }
};

class ConcretStrategyB :public Strategy
{
public:
    virtual void AlgorithmInterface() override
    {
        cout << "Algorithm B implement" << endl;
    }
};

class Context
{
public:
    Context(unique_ptr<Strategy> &st)
    {
        st_ = move(st);
    }

    void ContextInterface()
    {
        st_->AlgorithmInterface();
    }
private:
    unique_ptr<Strategy> st_;
};

int main()
{
    {
        unique_ptr<Strategy> st = make_unique<ConcretStrategyA>();
        unique_ptr<Context> context = make_unique<Context>(st);
        context->ContextInterface();
    }
    {
        unique_ptr<Strategy> st = make_unique<ConcretStrategyB>();
        unique_ptr<Context> context = make_unique<Context>(st);
        context->ContextInterface();
    }
}