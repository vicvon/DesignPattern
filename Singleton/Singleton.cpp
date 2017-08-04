/*
 * 单例模式：
 * 保证一个类仅有一个实例，并提供一个访问它的全局访问点。
 */
#include <iostream>

using namespace std;

class Singleton
{
public:
    static Singleton & getInstance()
    {
        static Singleton singleton;
        return singleton;
    }
private:
    Singleton() = default;
    Singleton(const Singleton &) = default;
    Singleton & operator = (const Singleton &) = default;
};

int main()
{
    Singleton& s = Singleton::getInstance();
    return 0;
}