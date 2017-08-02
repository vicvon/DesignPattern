/*
 * 状态模式：
 * 当一个对象的内在状态改变时允许改变其行为，这个对象看起来像是改变了其类。
 */
#include <iostream>
#include <memory>

using namespace std;

class Context;

class State
{
public:
    virtual void handle(Context* context) = 0;
};

class Context
{
public:
    void changeState(unique_ptr<State>& st)
    {
        state_ = move(st);
    }

    void request()
    {
        state_->handle(this);
    }
private:
    unique_ptr<State> state_;
};

class ConcreteStateC : public State
{
public:
    virtual void handle(Context* context) override
    {
        cout << "Change State C->Final" << endl;
    }
};

class ConcreteStateB : public State
{
public:
    virtual void handle(Context* context) override
    {
        cout << "Change State B->C" << endl;
        unique_ptr<State> s = make_unique<ConcreteStateC>();
        context->changeState(s);
    }
};

class ConcreteStateA : public State
{
public:
    virtual void handle(Context* context) override
    {
        cout << "Change State A->B" << endl;
        unique_ptr<State> s = make_unique<ConcreteStateB>();
        context->changeState(s);
    }
};

int main()
{
    unique_ptr<Context> context = make_unique<Context>();
    unique_ptr<State> st = make_unique<ConcreteStateA>();

    context->changeState(st);

    context->request();
    context->request();
    context->request();

    return 0;
}