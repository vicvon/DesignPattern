/*
* ����ģʽ��
* ���������㷨���壬�ֱ��װ������������֮����Ի���ת������ģʽ���㷨�ı仯��
* ����Ӱ�쵽ʹ���㷨�Ŀͻ�
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