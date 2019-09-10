# Personal C++ Archive

From Renaissance to the Modern C++ (For Smoothly Arriving on C++20!)

<!-- @import "[TOC]" {cmd="toc" depthFrom=1 depthTo=6 orderedList=false} -->

<!-- code_chunk_output -->

- [Personal C++ Archive](#personal-c-archive)
  - [My Roadmap](#my-roadmap)
  - [Book](#book)
  - [Online Material](#online-material)
  - [For Korean](#for-korean)

<!-- /code_chunk_output -->

## My Roadmap
  
- Design Patterns
  - ~~Singleton~~
    - [Thread-Safe Initialization of a Singleton](https://www.modernescpp.com/index.php/thread-safe-initialization-of-a-singleton)
  - ~~CRTP~~
    - [What is the curiously recurring template pattern (CRTP)?](https://stackoverflow.com/questions/4173254/what-is-the-curiously-recurring-template-pattern-crtp/4173298#4173298)
    - [The cost of dynamic (virtual calls) vs. static (CRTP) dispatch in C++](https://eli.thegreenplace.net/2013/12/05/the-cost-of-dynamic-virtual-calls-vs-static-crtp-dispatch-in-c)
  - ~~Type Erasure~~
    - [C++ Core Guidelines: Type Erasure with Templates](https://www.modernescpp.com/index.php/c-core-guidelines-type-erasure-with-templates)
    - [Polymorphic ducks](https://mropert.github.io/2017/11/30/polymorphic_ducks/)
    - [Better polymorphic ducks](https://mropert.github.io/2017/12/17/better_polymorphic_ducks/)
    - [Type Erasure for Unopinionated Interfaces in C++](http://www.goldsborough.me/cpp/2018/05/22/00-32-43-type_erasure_for_unopinionated_interfaces_in_c++/)
  - Expression Templates
    - [Expression Templates](https://www.modernescpp.com/index.php/expression-templates)
  - State Machine
    - [Using Types Effectively](https://www.youtube.com/watch?v=ojZbFIQSdl8)
    - [Implementing State Machines with std::variant](https://khuttun.github.io/2017/02/04/implementing-state-machines-with-std-variant.html)
    - [Rise of the State Machine](https://github.com/boostcon/cppnow_presentations_2019/raw/master/05-07-2019_tuesday/Rise_of_the_State_Machines__Kris_Jusiak__cppnow_05072019.pdf)
  - Policy Based Design
- ~~Logging~~
  - Signal/Exception Handler, Asynchronous I/O, Concurrent Queue, JSON Format
  - [g3log](https://github.com/KjellKod/g3log)
  - [spdlog](https://github.com/gabime/spdlog)
- Testing
  - [Testing tools in Visual Studio](https://docs.microsoft.com/en-us/visualstudio/test/improve-code-quality?view=vs-2019)
  - [doctest](https://github.com/onqtam/doctest)
- Memory Management
  - [Find memory leaks with the CRT library](https://docs.microsoft.com/en-us/visualstudio/debugger/finding-memory-leaks-using-the-crt-library?view=vs-2019)
  - [Visual Leak Detector](https://github.com/KindDragon/vld)
- Template Metaprogramming
  - SFINAE (+ enable_if, decltype, declval, auto, lambda)
    - [An introduction to C++'s SFINAE concept: compile-time introspection of a class member](https://jguegant.github.io/blogs/tech/sfinae-introduction.html)
  - vs. constexpr
    - <http://sweeper.egloos.com/3147813>
- Lambda Expression
  - [That `overloaded` Trick: Overloading Lambdas in C++17](https://dev.to/tmr232/that-overloaded-trick-overloading-lambdas-in-c17)
- Concurrency and Parallism
  - Task-based Parallism (Future, Promise, and std::async)
    - <https://www.modernescpp.com/index.php/tag/tasks>
  - Performance Comparison
    - <https://www.modernescpp.com/index.php/my-conclusion-summation-of-a-vector-in-three-variants>
- Network
  - Socket Programming in a Modern C++ Way
  - HTTP 3.0 (and QUIC)
  - P2P (NAT Traversal, STUN, TURN, ICE)
- Distributed Hash Table
  - Kademlia
  - Mainline
- Probabilistic Data Structure
  - Bloom Filter
- Build System
  - CMake
  - [Conan](https://conan.io/)
  - [vcpkg](https://github.com/microsoft/vcpkg)
- Cross-Platform Library
  - Header-Only Library
- and Beyond C++20...

## Book

- [The Definitive C++ Book Guide and List](https://stackoverflow.com/questions/388242/the-definitive-c-book-guide-and-list)
- [A Tour of C++ 2nd Edition](https://www.amazon.com/dp/0134997832) (Bjarne Stroustrup, July 2018)
- [Effective Modern C++](https://www.amazon.com/dp/1491903996/) (Scott Meyers, December 2014)
  - [Effective C++ 3rd Edition](https://www.amazon.com/dp/0321334876/) (Scott Meyers, May 2005)
- [Professional C++ 4th Edition](https://www.amazon.com/Professional-C-Marc-Gregoire/dp/1119421306/) (Marc Gregoire, April 2018)
- [Large-Scale C++ Volume I: Process and Architecture](https://www.amazon.com/Large-Scale-Volume-Architecture-Addison-Wesley-Professional/dp/0201717069) (John Lakos, December 2019)

## Online Material

- Tutorials and References
  - [Learn C++](https://www.learncpp.com/)
  - [C++ Reference](https://en.cppreference.com/w/)
  - [The C++ Annotations](http://www.icce.rug.nl/documents/cplusplus/)
  - [Modern C++ Features](https://github.com/AnthonyCalandra/modern-cpp-features)
- News, Blogs, and Communities
  - [Awesome C++](https://github.com/fffaraz/awesome-cpp)
    - [Awesome Modern C++](https://github.com/rigtorp/awesome-modern-cpp)
  - [Standard C++](https://isocpp.org/)
  - [Moderness C++](https://www.modernescpp.com/index.php)
  - [Fluent C++](https://www.fluentcpp.com/)
  - [C++ Reddit](https://www.reddit.com/r/cpp/)
  - [GeeksForGeeks](https://www.geeksforgeeks.org/category/cpp/)
  - [Microsoft C++ Team Blog](https://devblogs.microsoft.com/cppblog/)
  - [Sutter's Mill](https://herbsutter.com/)
  - [Bartek's coding blog](https://www.bfilipek.com/)
- Online C++ Compiler
  - [Compiler Explorer](https://godbolt.org/)
  - [Quick C++ Benchmark](http://quick-bench.com/)
  - [Coliru](https://coliru.stacked-crooked.com/)
- Coding Convention
  - [C++ Core Guidelines](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)
  - [C++ Dos and Don'ts](https://chromium.googlesource.com/chromium/src/+/HEAD/styleguide/c++/c++-dos-and-donts.md)
  - [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)
  - [WebKit Code Style Guidelines](https://webkit.org/code-style-guidelines/)

## For Korean

- [TCP School](http://tcpschool.com/cpp/intro)
- [ModernCppStudy](https://github.com/jwvg0425/ModernCppStudy/wiki)
- [소년코딩 C++ 이야기](https://boycoding.tistory.com/category/C%2B%2B%20%EC%9D%B4%EC%95%BC%EA%B8%B0)
- [모두의 코드 씹어먹는 C++ 강좌](https://modoocode.com/135)
- [C++ Template Note](https://wikidocs.net/391)
- [Google C++ Style Guide 번역](https://blog.naver.com/jerrypoiu/221500900533)
