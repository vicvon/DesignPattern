/*
 * 迭代器模式：
 * 提供一种方法顺序访问一个聚合对象中各个元素，而又不暴露该对象的内部表示
 */
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class AbstractIterator
{
public:
    virtual const string& First() const = 0;
    virtual const string& Next() const = 0;
    virtual const string& GetCur() const = 0;
    virtual bool IsDone() = 0;
};

class Aggregate
{
public:
    virtual AbstractIterator* createIterator() = 0;
    virtual size_t Count() const = 0;
    virtual const string& operator[] (const size_t index) const = 0;
    virtual string& operator[] (const size_t index) = 0;
};

class ConcreteIterator : public AbstractIterator
{
public:
    ConcreteIterator(Aggregate* aggregate) :current(0), aggregate_(aggregate)
    {
    }

    virtual const string& First() const override
    {
        return aggregate_->operator[](0);
    }

    virtual const string& Next() const override
    {
        ++current;
        if (current < aggregate_->Count())
            return aggregate_->operator[](current);
        return "";
    }

    virtual const string& GetCur() const override
    {
        return aggregate_->operator[](current);
    }

    virtual bool IsDone() override
    {
        if (current >= aggregate_->Count())
            return true;
        return false;
    }

private:
    mutable size_t current;
    Aggregate* aggregate_;
};

class ConcreteAggregate : public Aggregate
{
public:
    virtual AbstractIterator* createIterator() override
    {
        return new ConcreteIterator(this);
    }

    virtual size_t Count() const override
    {
        return vecStr_.size();
    }

    virtual const string& operator[] (const size_t index) const override
    {
        if (index < vecStr_.size())
        {
            return vecStr_[index];
        }
        return "";
    }

    virtual string& operator[] (const size_t index) override
    {
        if (index < vecStr_.size())
        {
            return vecStr_[index];
        }
        vecStr_.resize(index + 1);
        return vecStr_[index];
    }
private:
    vector<string> vecStr_;
};

int main()
{
    Aggregate* aggregate = new ConcreteAggregate;
    aggregate->operator[](0) = "Hello";
    aggregate->operator[](1) = "World";
    aggregate->operator[](2) = "!";

    AbstractIterator* iterator = aggregate->createIterator();

    cout << "First: " << iterator->First() << endl;
    while (!iterator->IsDone())
    {
        cout << iterator->Next() << endl;
    }

    delete iterator;
    delete aggregate;

    return 0;
}