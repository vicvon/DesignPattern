/*
 * 享元模式：
 * 运用共享技术有效地支持大量细粒度的对象。
 */
#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>

using namespace std;

class Flyweight
{
public:
    virtual void Operation() = 0;
};

class ConcreteFlyweight : public Flyweight
{
public:
    ConcreteFlyweight(string& state):extrinsicstate_(state)
    {
    }
    virtual void Operation() override
    {
        cout << "ConcreteFlyweight " << extrinsicstate_ << endl;
    }
private:
    string extrinsicstate_;
};

class FlyweightFactory
{
public:
    shared_ptr<Flyweight> getFlyweight(string& state)
    {
        auto it = hashFlyweight_.find(state);
        if (it == hashFlyweight_.end())
        {
            auto itt = hashFlyweight_.insert(unordered_map<string, shared_ptr<Flyweight>>::value_type(state,
                make_shared<ConcreteFlyweight>(state)));
            return itt.first->second;
        }
        else
        {
            return it->second;
        }
    }

    size_t count() const
    {
        return hashFlyweight_.size();
    }
private:
    unordered_map<string, shared_ptr<Flyweight>> hashFlyweight_;
};

int main()
{
    FlyweightFactory factory;
    shared_ptr<Flyweight> fw = factory.getFlyweight(string("one"));
    fw->Operation();

    shared_ptr<Flyweight> fw1 = factory.getFlyweight(string("two"));
    fw1->Operation();

    shared_ptr<Flyweight> fw2 = factory.getFlyweight(string("one"));
    fw2->Operation();

    cout << "Factory Size: " << factory.count() << endl;
    return 0;
}