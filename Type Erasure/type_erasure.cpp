// Type Erasure pattern
// Running in Browser : https://godbolt.org/z/YVCr8s
// References : https://www.modernescpp.com/index.php/component/content/article/51-blog/modern-c/399-c-core-guidelines-type-erasure-with-templates

#include <iostream>
#include <memory>
#include <string>
#include <typeinfo>
#include <utility>
#include <vector>

class Object {
public:
    struct Concept {
        virtual ~Concept() {}
        virtual std::string getName() const = 0;
    };

    template <typename T>
    struct Model : Concept {
        Model(const T& t)
            : object(t)
        {
            std::cout << "Model Constructor (Copy " << typeid(T).name() << " object)" << std::endl;
        }

        std::string getName() const override
        {
            std::cout << "Model::getName() Call" << std::endl;
            return object.getName();
        }

    private:
        T object;
    };

    template <typename T>
    Object(const T& obj)
        : object(std::make_shared<Model<T>>(std::move(obj)))
    {
        std::cout << "Object Constructor (Copy " << typeid(T).name() << " object)" << std::endl;
    }

    ~Object() { std::cout << "Object Destructor (Type Erased)" << std::endl; }

    std::string getName() const
    {
        std::cout << "Object::getName() Call" << std::endl;
        return object->getName();
    }

private:
    std::shared_ptr<const Concept> object;
};

void printName(std::vector<Object> vec)
{
    for (const auto& v : vec)
        std::cout << v.getName() << std::endl;
}

struct Foo {
    Foo() { std::cout << "Foo Constructor" << std::endl; }
    Foo(const Foo&) { std::cout << "Foo Copy Constructor" << std::endl; }
    ~Foo() { std::cout << "Foo Destructor" << std::endl; }

    std::string getName() const
    {
        std::cout << "Foo::getName() Call" << std::endl;
        return "Foo";
    }
};

struct Bar {
    Bar() { std::cout << "Bar Constructor" << std::endl; }
    Bar(const Bar&) { std::cout << "Bar Copy Constructor" << std::endl; }
    ~Bar() { std::cout << "Bar Destructor" << std::endl; }

    std::string getName() const
    {
        std::cout << "Bar::getName() Call" << std::endl;
        return "Bar";
    }
};

int main()
{
    std::vector<Object> vec{ Object{ Foo{} }, Object(Bar()) };

    std::cout << std::endl;

    printName(vec);

    std::cout << std::endl;

    return 0;
}