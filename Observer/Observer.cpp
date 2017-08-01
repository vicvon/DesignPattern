/*
 * 观察者模式：
 * 定义了一种一对多的依赖关系，让多个观察者对象同时监听某一主题对象。
 * 这个主题对象在状态发生变化时，会通知所有观察者对象，使它们能够自动更新自己。
 */
#include <iostream>
#include <memory>
#include <list>
#include <string>

using namespace std;

class Subject;
class Observer;

class Observer
{
public:
    Observer()
    {
    }
    virtual ~Observer()
    {
    }

    virtual void Update() = 0;
};

class Subject
{
public:
    Subject()
    {
    }
    virtual ~Subject()
    {
    }
    virtual void setSubject(string& subject) = 0;
    virtual string getSubject() = 0;

    void Attach(shared_ptr<Observer>& observer)
    {
        observers_.push_back(observer);
    }

    void Detach(shared_ptr<Observer>& observer)
    {
        if (observer != nullptr)
            observers_.remove(observer);
    }

    void Notify()
    {
        for (auto e : observers_)
        {
            e->Update();
        }
    }
private:
    list<shared_ptr<Observer>> observers_;
};

class ConcreteSubject : public Subject
{
public:
    ConcreteSubject()
    {
    }
    virtual ~ConcreteSubject()
    {
    }

    virtual void setSubject(string& subject) override
    {
        subject_ = subject;
    }

    virtual string getSubject() override
    {
        return subject_;
    }
private:
    string subject_;
};

class ConcreteObserverA : public Observer
{
public:
    ConcreteObserverA(shared_ptr<Subject>& subject, string& name):subject_(subject), name_(name)
    {
    }
    virtual ~ConcreteObserverA()
    {
    }

    virtual void Update() override
    {
        cout << subject_.lock()->getSubject() << " notify " << name_ << ":" << endl;
        cout << "ConcreteObserverA Update" << endl;
    }
private:
    string name_;
    weak_ptr<Subject> subject_;  //Subject 包含 Observer的引用, 避免双重引用, 这里使用弱引用
};

class ConcreteObserverB : public Observer
{
public:
    ConcreteObserverB(shared_ptr<Subject>& subject, string& name) :subject_(subject), name_(name)
    {
    }
    virtual ~ConcreteObserverB()
    {
    }

    virtual void Update() override
    {
        cout << subject_.lock()->getSubject() << " notify " << name_ << ":" << endl;
        cout << "ConcreteObserverB Update" << endl;
    }
private:
    string name_;
    weak_ptr<Subject> subject_;
};

int main()
{
    shared_ptr<Subject> sj = make_shared<ConcreteSubject>();
    shared_ptr<Observer> ob1 = make_shared<ConcreteObserverA>(sj, move(string("OB1")));
    shared_ptr<Observer> ob2 = make_shared<ConcreteObserverB>(sj, move(string("OB2")));

    sj->setSubject(move(string("sj")));

    sj->Attach(ob1);
    sj->Attach(ob2);

    sj->Notify();

    sj->Detach(ob2);

    sj->Notify();

    return 0;
}