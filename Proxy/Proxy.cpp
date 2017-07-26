/*
 * 代理模式：
 * 为其他对象提供一种代理以控制对这个对象的访问
 */
#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Subject
{
public:
    virtual void request() = 0;
};

class RealSubject : public Subject
{
public:
    RealSubject(string name = "default"):name_(name)
    {
    }
    virtual void request() override
    {
        cout << name_ << " Real Subject Request" << endl;
    }
private:
    string name_;
};

class Proxy : public Subject
{
public:
    Proxy(unique_ptr<RealSubject>& realSubject)
    {
        realSubject_ = move(realSubject);
    }

    Proxy(string name)
    {
        realSubject_ = make_unique<RealSubject>(name);
    }

    virtual void request() override
    {
        if (realSubject_ == nullptr)
        {
            cout << "no real subject" << endl;
        }
        else
        {
            realSubject_->request();
        }
    }
private:
    unique_ptr<RealSubject> realSubject_;
};

int main()
{
    {
        unique_ptr<RealSubject> realSubject = make_unique<RealSubject>();
        unique_ptr<Proxy> proxy = make_unique<Proxy>(realSubject);
        proxy->request();
    }

    {
        unique_ptr<Proxy> proxy = make_unique<Proxy>("HI");
        proxy->request();
    }
    return 0;
}