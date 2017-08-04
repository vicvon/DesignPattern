/*
 * 命令模式：
 * 将一个请求封装为一个对象，从而使你可用不同的请求对客户进行参数化；
 * 对请求排队或记录请求日志，以及支持可撤销的操作。
 */
#include <iostream>
#include <memory>

using namespace std;

class Receiver
{
public:
    void Action()
    {
        cout << "Receiver Action" << endl;
    }
};

class Command
{
public:
    Command(unique_ptr<Receiver>&& receiver) : receiver_(move(receiver))
    {
    }

    virtual void Execute() = 0;
protected:
    unique_ptr<Receiver> receiver_;
};

class ConcreteCommand : public Command
{
public:
    ConcreteCommand(unique_ptr<Receiver>&& receiver) : Command(move(receiver))
    {
    }

    virtual void Execute() override
    {
        cout << "ConcreteCommand Execute Command" << endl;
        receiver_->Action();
    }
};

class Invoker
{
public:
    Invoker(unique_ptr<Command>&& command) : command_(move(command))
    {
    }
    void Call()
    {
        cout << "Invoker Command" << endl;
        command_->Execute();
    }
private:
    unique_ptr<Command> command_;
};

int main()
{
    unique_ptr<Invoker> invoker = make_unique<Invoker>(make_unique<ConcreteCommand>(make_unique<Receiver>()));

    invoker->Call();

    return 0;
}