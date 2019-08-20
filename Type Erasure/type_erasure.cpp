// Type Erasure pattern
// Running in Browser : https://godbolt.org/z/lg6aWi
// References : https://www.modernescpp.com/index.php/component/content/article/51-blog/modern-c/399-c-core-guidelines-type-erasure-with-templates
//              http://www.goldsborough.me/cpp/2018/05/22/00-32-43-type_erasure_for_unopinionated_interfaces_in_c++/
//              https://mropert.github.io/2017/11/30/polymorphic_ducks/

#include <iostream>
#include <memory>
#include <string>
#include <typeinfo>
#include <utility>
#include <vector>

class Object {
public:
    template <typename T>
    Object(T&& obj)
        : object_(std::make_shared<Model<T>>(std::forward<T>(obj)))
    {
        std::cout << "Object Constructor (Forward '" << typeid(T).name() << "' object)" << std::endl;
    }

    std::string getName() const
    {
        std::cout << "Object::getName() Call" << std::endl;
        return object_->getName();
    }

private:
    struct Concept {
        virtual ~Concept() = default;
        virtual std::string getName() const = 0;
    };

    template <typename T>
    struct Model : Concept {
        explicit Model(T&& obj)
            : object(std::forward<T>(obj))
        {
            std::cout << "Model Constructor (Forward '" << typeid(T).name() << "' object)" << std::endl;
        }

        std::string getName() const override
        {
            std::cout << "Model::getName() Call" << std::endl;
            return object.getName();
        }

        T object;
    };

    std::shared_ptr<Concept> object_;
};

void printName(const std::vector<Object>& vec)
{
    for (const auto& v : vec)
        std::cout << v.getName() << std::endl;
}

struct Foo {
    Foo() { std::cout << "Foo Constructor" << std::endl; }
    Foo(Foo&&) noexcept { std::cout << "Foo Move Constructor" << std::endl; }
    ~Foo() { std::cout << "Foo Destructor" << std::endl; }

    std::string getName() const
    {
        std::cout << "Foo::getName() Call" << std::endl;
        return "Foo";
    }
};

struct Bar {
    Bar() { std::cout << "Bar Constructor" << std::endl; }
    Bar(Bar&&) noexcept { std::cout << "Bar Move Constructor" << std::endl; }
    ~Bar() { std::cout << "Bar Destructor" << std::endl; }

    std::string getName() const
    {
        std::cout << "Bar::getName() Call" << std::endl;
        return "Bar";
    }
};

int main()
{
    std::vector<Object> vec{ Foo(), Object(Bar()) };

    std::cout << std::endl;

    printName(vec);

    std::cout << std::endl;

    return 0;
}