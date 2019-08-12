// Singleton with CRTP
// Running in Browser : https://godbolt.org/z/J-ZcA8
// References : https://www.modernescpp.com/index.php/thread-safe-initialization-of-a-singleton
//              https://www.modernescpp.com/index.php/component/content/article/42-blog/functional/273-c-is-still-lazy

#pragma once

#include <iostream>

template <typename T>
class Singleton {
public:
    static T& GetInstance()
    {
        static T instance;
        return instance;
    }

    void Interface()
    {
        static_cast<T*>(this)->Implementation();
    }

    void Implementation()
    {
        std::cout << "Implementation Base" << std::endl;
    }

protected:
    Singleton() = default;
    ~Singleton() = default;

private:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};
