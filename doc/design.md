# Design  {#design}

This page details the design that this project follows and tries to provide an attempt of a rationale behind each design choice.


General design of the library
----------------------------------------

The library is designed around the curiously recurring template pattern: it provides class templates from which component implementations ought to inherit passing themselves as one of the template arguments. The provided class templates implement the public interface and call implementation hooks as required. Thanks to the nature of the template system, this dispatch is done statically, that is, without any runtime cost.


Preprocessing of headers
----------------------------------------

Public headers are .hpp.in files. They are to be processed by the Bash script `guardheader.bash`, which protects them with inclusion guards and adds some boilerplate. This practice is not common, which plays against this approach. Nevertheless, I deem this disadvantage surpassed by the benefits this practice brings. An idealistic account would be that inclusion guards ought to be derived from some conventions and file names; therefore, their generation should be automatized, so that they are necessarily in sync with them. In practice, what this approach buys us is the comfort and the certainty that inclusion guards are always in sync with our conventions and the file name and that the mentioned boilerplate is always present.


Split between .hpp and .tpp
----------------------------------------

Public template and `constexpr` functions are declared in .hpp.in files and defined in .tpp files, that is, they are not declared & defined in one go, as usual. This helps keeping public headers clean.


Constexpr functions
----------------------------------------

The library includes many constexpr methods meant to be used as a compile-time facility. They all end with the suffix `_constexpry`. Their semantics are similar but not always identical to those of their regular cousins. They must not be used at runtime, as they usually assume valid input –and thus lack error checking– and are slow.

### Why is there no constexpr version of the `maps` method?
The use case of the `maps` method is to check whether a coded character set or a character encoding form maps a nonnegative integer, which makes sense if the input may not be valid. Constexpry methods, on the other hand, all operate under the assumption that the input is valid — and, being valid including that all nonnegative integers are mapped, why would one check that they are?


C++ dialects and toolchains
----------------------------------------

Despite there being a C++ standard, there's fragmentation among the so-called C++ implementations. The two main reasons behind this are its heavy use and a certain lack of features that it has carried for years. This lack moved vendors to roll their own solutions and even ‘flavours’ of the language — so much so that the monikers ‘GNU++’ and ‘MSVC++’ will be understandable to most experienced and even not-so-experienced programmers.

Recently, C++ –the language as defined by the standard, not the ecosystem– has evolved greatly — namely, with C++11. Many great features have been added, and they're put to good use in this project. The problem is that not all implementations support them. The situation outlined above gave rise to the mindset that it's applications or libraries that should “support” particular flavours of the language, so much so that any project seeking to make use of some of the newer features is subject to facing the question whether it “supports” this or that toolchain and being –unfairly– judged accordingly. I believe this is wrong, though I do understand that the main motivation behind software development is marketing and that marketing requires to deliver on a timeline that holds no respect for such ‘idealistic’ points of view. The approach taken by this project is to abide by the latest C++ **standard** and freely use new features *as long as* there's at least one ‘free’ (in some sense of the term) implementation of them. This is a pragmatic take on the matter not only regarding actual ‘runnability’ but also testing: the fact is that most of us don't program following the formal rules of the programming language of choice, but driven by the trial-and-error process of the compiler at hand, so programming “in the air”, without the backing of a trustable parser, would be really dangerous.

“Ok, I get it that it doesn't make sense that a library support a language implementation, but I need to sell a product, so I would like to know if I can take this project of yours, throw it at my particular compiler and expect everything to work out”, might be asked. It would be difficult to maintain a complete and up-to-date list of implementations that support the features used in this project. As of this writing, I have tested it on gcc 5.3 and Clang 3.8 on Windows. MSVC 19.00.23918 couldn't handle it. Nevertheless, it's possible to mix Clang- and MSVC-compiled objects, giving up some features — namely, link-time code generation. Anyway, Clang can create Windows programs, so it could be considered as an alternative.


Attitude towards the C++ standard library
----------------------------------------

The standard library is used freely _where convenient_. Due to the nature of the design of the project, things like containers are completely unuseful. There are a couple places where standard library offerings like `std::array` could be employed, but are not; usually, there's a rationale behind the decision not to use them explained in the source code. Put special attention where standard library things would become part of the interface, as they wouldn't be under our control.