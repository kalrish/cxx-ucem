#  cxx-ucem
C++ infrastructure for the Unicode Character Encoding Model


##  What is this?
This project provides C++ foundations to accommodate components that abide by the Unicode Character Encoding Model, such as coded character sets, character encoding forms and character encoding schemes.


##  Build and installation

###  Building
This library is composed only of headers — there's nothing to compile. The only step to carry out is to wrap the headers with inclusion guards and some boilerplate, done with a Bash script. The build process is managed by the Tup build system — refer to its documentation for information on how to use it.

Requirements:

 -  Tup
 -  GNU Bash

     Version 4.3 works.

 -  cat, from GNU coreutils, or similar

###  Documentation
The documentation is in HTML format. Building it is optional. Doxygen is used for the task. Note that it has to run on the processed headers, i.e., after the build is finished. Simply run, from the top directory:

    $  doxygen

Requirements:

 -  Doxygen

     Version 1.8.11 works.

 -  Clang

     Doxygen is able to use the Clang parser for more accurate information. This feature is currently enabled in the configuration file, `Doxyfile`. It hasn't been tested disabled. The tag to look out for to disable it is `CLANG_ASSISTED_PARSING`.

 -  dot, from Graphviz

     Doxygen is able to use the dot tool of Graphviz to generate better inheritance diagrams. This feature is currently enabled in the configuration file, `Doxyfile`. Doxygen's behavior when it's enabled is to assume that dot is available, so, if it's not available, the feature should be turned off; look out for the `HAVE_DOT` tag.

The full documentation is hosted over at [the GitHub project site](https://kalrish.github.io/cxx-ucem).

###  Installation
A helper Bash script is provided for the task of installing the files meant to be installed. It handles the standard installation directory variables as well as `DESTDIR`, and assumes the defaults mandated by GNU. Values are to be specified in its commandline as arguments of the form "key=value".

Requirements:

 -  GNU Bash

     Version 4.3 works.

 -  install, from GNU coreutils, or similar
 -  tput, from ncurses

     The script makes use of tput _if available_ to colorize the output.

Commands:

    $  # The following are just example values; the defaults are those mandated by GNU
    $  bash install.bash DESTDIR=pkg prefix=/usr includedir=/usr/gcc/include libdir=/lib


##  Namespaces
The project doesn't just provide a library, but also lays the foundations for implementations of components that abide to the Unicode Character Encoding Model. To arrange for them, a common name assignation scheme must be rolled. It is now detailed.

###  Preamble
Let `uppercasize` and `lowercasize` be functions that take a single argument and turn all of its letter characters into upper- or lowercase, respectively.

Let `underscorize` be a function that takes a single argument and turns all of its hyphens (`-`) and spaces (` `) into underscores (`_`).

Let `ctns` be a function that maps component types to names as follows:

| Component type                   |  Coded name                         |
|----------------------------------|-------------------------------------|
| Coded character set              |  `CODED_CHARACTER_SET`              |
| Coded character set translator   |  `CODED_CHARACTER_SET_TRANSLATOR`   |
| Character encoding form          |  `CHARACTER_ENCODING_FORM`          |
| Character encoding scheme        |  `CHARACTER_ENCODING_SCHEME`        |

Let `ctnp` be a function that maps component types to names as follows:

| Component type                   |  Coded name                     |
|----------------------------------|---------------------------------|
| Coded character set              |  `coded_character_sets`         |
| Coded character set translator   |  `coded_character_translators`  |
| Character encoding form          |  `character_encoding_forms`     |
| Character encoding scheme        |  `character_encoding_schemes`   |

Let `libssv` be a function that applies system-specific variations to library names.

###  C++
####  Global
The namespace `Unicode_CharacterEncodingModel` is hereby reserved.

All macro names that start with `UNICODE_CHARACTER_ENCODING_MODEL` are hereby reserved.

####  Per-component
Let `TYPE` represent the component's type.

Let `NAME` represent the component's name, if it's a coded character set, a character encoding form or a character encoding scheme. If it's a coded character set translator, let `FROM` represent the name of the coded character set it translates from, and `INTO`, the name of the coded character sets it translates into.

Each component must be assigned a C++ name, which must derive from its name and be suitable for use as a C++ identifier. Let `CXXNAME` represent it.

Each component is hereby reserved, within the namespace `Unicode_CharacterEncodingModel`:

 -  the symbol `$(ctnp ${TYPE})::${CXXNAME}`, which must correspond to either a class or a namespace
 -  the namespace `$(ctnp ${TYPE})::detail::${CXXNAME}`, for private use and not meant to contain any symbol part of the public interface
 -  all macro names that start with `UNICODE_CHARACTER_ENCODING_MODEL_$(ctns ${TYPE})_$(underscorize $(uppercasize ${NAME}))`
 -  the macro names `UNICODE_CHARACTER_ENCODING_MODEL_INCLUSION_GUARD_$(ctns ${TYPE})_$(underscorize $(uppercasize ${NAME}))_hpp` and `UNICODE_CHARACTER_ENCODING_MODEL_INCLUSION_GUARD_$(ctns ${TYPE})_$(underscorize $(uppercasize ${NAME}))_tpp`, meant to be inclusion guards

Thus, for example, an implementation of the UTF-8 character encoding form, given a C++ name of `utf8`, would be reserved:

 -  the symbol `Unicode_CharacterEncodingModel::character_encoding_forms::utf8`, which would have to correspond to either a class or a namespace
 -  the namespace `Unicode_CharacterEncodingModel::character_encoding_forms::detail::utf8`, for private use
 -  all macro names that start with `UNICODE_CHARACTER_ENCODING_MODEL_CHARACTER_ENCODING_FORM_UTF_8`
 -  the macro names that start with `UNICODE_CHARACTER_ENCODING_MODEL_INCLUSION_GUARD_CHARACTER_ENCODING_FORM_UTF_8_hpp` and `UNICODE_CHARACTER_ENCODING_MODEL_INCLUSION_GUARD_CHARACTER_ENCODING_FORM_UTF_8_tpp`

###  Headers
The directory `${includedir}/unicode-character-encoding-model` is hereby reserved.

Every coded character set, character encoding form and character encoding scheme is hereby reserved, in the directory `${includedir}/unicode-character-encoding-model/$(ctnp ${TYPE})`:

 -  the file `${NAME}.hpp`
 -  the file `${NAME}.tpp`
 -  the directory `${NAME}`

Thus, for example, an implementation of the UTF-16BE character encoding scheme would be reserved:

 -  the file `${includedir}/unicode-character-encoding-model/character_encoding_schemes/UTF-16BE.hpp`
 -  the file `${includedir}/unicode-character-encoding-model/character_encoding_schemes/UTF-16BE.tpp`
 -  the directory `${includedir}/unicode-character-encoding-model/character_encoding_schemes/UTF-16BE`

Every coded character set translator is hereby reserved, in the directory `${includedir}/unicode-character-encoding-model/$(ctnp ${TYPE})`:

 -  the file `${FROM}-${INTO}.hpp`
 -  the file `${FROM}-${INTO}.tpp`

Thus, for example, a translator from ASCII to UCS would be reserved:

 -  the file `${includedir}/unicode-character-encoding-model/coded_character_translators/ASCII-UCS.hpp`
 -  the file `${includedir}/unicode-character-encoding-model/coded_character_translators/ASCII-UCS.tpp`

###  Libraries
The directory `${libdir}/unicode-character-encoding-model` is hereby reserved.

Each component is hereby reserved, in the directory `${libdir}/unicode-character-encoding-model/$(ctnp ${TYPE})`:

 -  the file `$(libssv ${NAME})`

Thus, for example, an implementation of the UTF-32BE character encoding scheme would be reserved:

 -  the file `${libdir}/unicode-character-encoding-model/character_encoding_schemes/$(libssv UTF-32BE)` (an example of the final version would be: `/lib/unicode-character-encoding-model/character_encoding_schemes/libUTF-32BE.a`)