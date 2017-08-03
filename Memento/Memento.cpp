/*
 * 备忘录模式：
 * 在不破坏封装性的前提下，捕获一个对象的内部状态，并在该对象之外
 * 保存这个状态。这样以后就可将该对象恢复到原先保存的状态。
 */
#include <iostream>
#include <string>
#include <memory>

using namespace std;

class Memento
{
public:
    Memento(string st):state_(st)
    {
    }

    string getState()
    {
        return state_;
    }
private:
    string state_;
};

class Originator
{
public:
    void setState(string& st)
    {
        state_ = st;
    }

    shared_ptr<Memento> createMemento()
    {
        return make_shared<Memento>(state_);
    }

    void recoverState(shared_ptr<Memento>& memento)
    {
        state_ = memento->getState();
    }

    void showState()
    {
        cout << state_ << endl;
    }
private:
    string state_;
};

class Caretaker
{
public:
    shared_ptr<Memento> getMemento()
    {
        return memento_;
    }

    void setMemento(shared_ptr<Memento>& memento)
    {
        memento_ = memento;
    }
private:
    shared_ptr<Memento> memento_;
};

int main()
{
    unique_ptr<Originator> ori = make_unique<Originator>();
    ori->setState(string("A"));
    ori->showState();

    unique_ptr<Caretaker> care = make_unique<Caretaker>();
    care->setMemento(ori->createMemento());

    ori->setState(string("B"));
    ori->showState();

    ori->recoverState(care->getMemento());
    ori->showState();
    return 0;
}