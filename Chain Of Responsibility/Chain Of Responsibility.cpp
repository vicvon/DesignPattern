/*
 * 职责链模式：
 * 使多个对象都有机会处理请求，从而避免请求的发送者和接收者之间的耦合关系。将这个对象连成一条链，
 * 并沿着这条链传递该请求，直到有一个对象处理它为止。
 */
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class Handler
{
public:
    void setHandler(shared_ptr<Handler>& handler)
    {
        handler_ = handler;
    }

    virtual void HandleRequest(int request) = 0;
protected:
    shared_ptr<Handler> handler_;
};

class ConcreteHandlerA : public Handler
{
public:
    virtual void HandleRequest(int request) override
    {
        if (request >= 0 && request <= 10)
        {
            cout << "ConcreteHandlerA accept " << request << endl;
        }
        else
        {
            if (handler_ != nullptr)
            {
                handler_->HandleRequest(request);
            }
            else
            {
                cout << request << "Nobody Can accept!" << endl;
            }
        }
    }
};

class ConcreteHandlerB : public Handler
{
public:
    virtual void HandleRequest(int request) override
    {
        if (request >= 11 && request <= 20)
        {
            cout << "ConcreteHandlerB accept " << request << endl;
        }
        else
        {
            if (handler_ != nullptr)
            {
                handler_->HandleRequest(request);
            }
            else
            {
                cout << request << "Nobody Can accept!" << endl;
            }
        }
    }
};

class ConcreteHandlerC : public Handler
{
public:
    virtual void HandleRequest(int request) override
    {
        if (request >= 21 && request <= 30)
        {
            cout << "ConcreteHandlerC accept " << request << endl;
        }
        else
        {
            if (handler_ != nullptr)
            {
                handler_->HandleRequest(request);
            }
            else
            {
                cout << request << " Nobody Can accept!" << endl;
            }
        }
    }
};

int main()
{
    shared_ptr<Handler> handler1 = make_shared<ConcreteHandlerA>();
    shared_ptr<Handler> handler2 = make_shared<ConcreteHandlerB>();
    shared_ptr<Handler> handler3 = make_shared<ConcreteHandlerC>();

    handler1->setHandler(handler2);
    handler2->setHandler(handler3);

    vector<int> vecReq{1, 3, 5, 11, 15, 20, 25, 35};

    cout << "----------Start from handler1----------" << endl;
    for (auto e : vecReq)
    {
        handler1->HandleRequest(e);
    }

    cout << "----------Start from handler2----------" << endl;
    for (auto e : vecReq)
    {
        handler2->HandleRequest(e);
    }

    cout << "----------Start from handler3----------" << endl;
    for (auto e : vecReq)
    {
        handler3->HandleRequest(e);
    }

    return 0;
}