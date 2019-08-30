#include "singleton.h"
#include <iostream>

class A : public Singleton<A> {
public:
    void Implementation()
    {
        std::cout << "Implementation A" << std::endl;
    }
};

class B : public Singleton<B> {
public:
    void Implementation()
    {
        std::cout << "Implementation B" << std::endl;
    }
};

class C : public Singleton<C> {
};

template <typename T>
void Execute(T& base)
{
    base.Interface();
}

int main()
{
    Execute(A::GetInstance());
    Execute(B::GetInstance());
    Execute(C::GetInstance());

    return 0;
}