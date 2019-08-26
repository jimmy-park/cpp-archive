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
    - <https://www.modernescpp.com/index.php/thread-safe-initialization-of-a-singleton>
  - ~~CRTP~~
    - <https://stackoverflow.com/questions/4173254/what-is-the-curiously-recurring-template-pattern-crtp/4173298#4173298>
  - ~~Type Erasure~~
    - <https://www.modernescpp.com/index.php/c-core-guidelines-type-erasure-with-templates>
    - <https://mropert.github.io/2017/11/30/polymorphic_ducks/>
    - <https://mropert.github.io/2017/12/17/better_polymorphic_ducks/>
    - <http://www.goldsborough.me/cpp/2018/05/22/00-32-43-type_erasure_for_unopinionated_interfaces_in_c++/>
  - Expression Templates
    - <https://www.modernescpp.com/index.php/expression-templates>
  - State Machine
    - <https://www.youtube.com/watch?v=ojZbFIQSdl8>
    - <https://khuttun.github.io/2017/02/04/implementing-state-machines-with-std-variant.html>
    - <https://github.com/boostcon/cppnow_presentations_2019/raw/master/05-07-2019_tuesday/Rise_of_the_State_Machines__Kris_Jusiak__cppnow_05072019.pdf>
  - Policy Based Design
- Logging
  - Async, Worker Thread (sleep and work), Circular Queue, System Crash Catch
  - [g2log](https://www.codeproject.com/Articles/288827/g-log-An-efficient-asynchronous-logger-using-Cplus)
  - [llcpp - A quest for faster C++ logging](https://github.com/blapid/llcpp)
    - <https://blapid.github.io/cpp/2017/10/31/llcpp-a-quest-for-faster-logging-intro.html>
- Memory Management
  - [Find memory leaks with the CRT library](https://docs.microsoft.com/en-us/visualstudio/debugger/finding-memory-leaks-using-the-crt-library?view=vs-2019)
  - [Visual Leak Detector](https://github.com/KindDragon/vld)
- Template Metaprogramming
  - SFINAE (+ enable_if, decltype, declval, auto, lambda  
    - <https://jguegant.github.io/blogs/tech/sfinae-introduction.html>
  - vs. constexpr
    - <http://sweeper.egloos.com/3147813>
- Lambda Expression
  - Lambda Overloading
    - <https://dev.to/tmr232/that-overloaded-trick-overloading-lambdas-in-c17>
- Task (Future, Promise, and std::async)
  - <https://www.modernescpp.com/index.php/tag/tasks>
- Concurrency and Parallism
  - Performance Comparison
    - <https://www.modernescpp.com/index.php/my-conclusion-summation-of-a-vector-in-three-variants>
- Network
  - Modern Socket Programming
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
- News, Blogs, and Communities
  - [Awesome C++](https://github.com/fffaraz/awesome-cpp)
    - [Awesome Modern C++](https://github.com/rigtorp/awesome-modern-cpp)
  - [Standard C++](https://isocpp.org/)
  - [Moderness C++](https://www.modernescpp.com/index.php)
  - [Fluent C++](https://www.fluentcpp.com/)
  - [C++ Reddit](https://www.reddit.com/r/cpp/)
  - [GeeksForGeeks](https://www.geeksforgeeks.org/category/cpp/)
  - [Microsoft C++ Team Blog](https://devblogs.microsoft.com/cppblog/)
- Online C++ Compiler
  - [Compiler Explorer](https://godbolt.org/)
  - [Quick C++ Benchmark](http://quick-bench.com/)
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
