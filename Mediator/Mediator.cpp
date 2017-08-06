/*
 * 中介者模式：
 * 用一个中介对象来封装一系列的对象交互。中介者使各对象不需要显式地相互作用，
 * 从而使得耦合松散，而且可以独立地改变它们之间的交互。
 */
#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Mediator;

class Colleague : public enable_shared_from_this<Colleague>
{
public:
    Colleague(shared_ptr<Mediator>& mediator) :mediator_(mediator)
    {
    }
protected:
    shared_ptr<Mediator> mediator_;
};

class Mediator
{
public:
    virtual void Send(string& message, shared_ptr<Colleague>& colleague) = 0;
};

class ConcreteColleagueA : public Colleague
{
public:
    ConcreteColleagueA(shared_ptr<Mediator>& mediator) :Colleague(mediator)
    {
    }

    void Send(string& message)
    {
        mediator_->Send(message, shared_from_this());
    }

    void Notify(string& message)
    {
        cout << "ConcreteColleagueA receive message: " << message << endl;
    }
};

class ConcreteColleagueB : public Colleague
{
public:
    ConcreteColleagueB(shared_ptr<Mediator>& mediator) :Colleague(mediator)
    {
    }

    void Send(string& message)
    {
        mediator_->Send(message, shared_from_this());
    }

    void Notify(string& message)
    {
        cout << "ConcreteColleagueB receive message: " << message << endl;
    }
};

class ConcreteMediator : public Mediator
{
public:
    void setColleagueA(shared_ptr<ConcreteColleagueA>& colleague)
    {
        colleagueA_ = colleague;
    }

    void setColleagueB(shared_ptr<ConcreteColleagueB>& colleague)
    {
        colleagueB_ = colleague;
    }

    virtual void Send(string& message, shared_ptr<Colleague>& colleague) override
    {
        if (colleagueA_ == colleague)
        {
            colleagueB_->Notify(message);
        }
        else if (colleagueB_ == colleague)
        {
            colleagueA_->Notify(message);
        }
    }
private:
    shared_ptr<ConcreteColleagueA> colleagueA_;
    shared_ptr<ConcreteColleagueB> colleagueB_;
};

int main()
{
    shared_ptr<Mediator> mediator = make_shared<ConcreteMediator>();

    shared_ptr<ConcreteColleagueA> cA = make_shared<ConcreteColleagueA>(mediator);
    shared_ptr<ConcreteColleagueB> cB = make_shared<ConcreteColleagueB>(mediator);

    static_pointer_cast<ConcreteMediator>(mediator)->setColleagueA(cA);
    static_pointer_cast<ConcreteMediator>(mediator)->setColleagueB(cB);

    cA->Send(string("Hello B"));
    cB->Send(string("Hello A"));

    return 0;
}