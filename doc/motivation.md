# Motivation  {#motivation}

Motivation
========================================


On information storage and processing in computers
----------------------------------------

Computer memory is a sequence of bits, which hold one of two values usually represented as «0» and «1». The implication that follows from the nature of computer memory is that any information to be stored in it must be expressed in bits. In some cases, the mapping between semantic values and computer memory representation is trivial, that is, there's easy agreement on it. Thus, for boolean information, the convention is that the true value is represented with 1 and the false value with 0. Nonnegative integers can also be represented with relative ease, by mapping each digit of their binary positional representation to a memory bit.

But things are not that simple, as computers don't operate on single bits, but on fixed-length sequences of them called _bytes_; memory addresses do not refer to bits, but to bytes. Nowadays, the most common length or _binary width_ of bytes is 8. The fact that the memory and working units are not the same complicates the matter of information storage and, in some cases, introduces some problems. For single boolean values, this distinction means that the computer values to which they may be mapped are more than two. Thus, the convention at the byte level is extended so that, while 0 still represents the false value, any other byte value represents the true value. This holds true, in fact, for the C and C++ programming languages, among others. For integers, though, it's the truly infamous issue of endianness that arises upon this distinction. Take, for example, a nonnegative integer. If it compares less than or equal to the number of different values that may be stored in a single byte, the mapping remains relatively trivial. But if it's greater than the number of different combinations a single byte can hold, more than one byte will be required to store it — and, how should the partition happen?, and in which order should the bytes come?

Text encoding is not trivial at any of those two levels. Leaving aside the problems met when trying to grasp the very concept of text, there's no intuitive mapping between text and bits or bytes. Thus, a more elaborate model is required to take care of it. The fact that working with text has been needed since very early in computer history has lead to the development of a variety of approaches in which the problems pointed out have since been dealt with, originating abstractions that nowadays reach their peak in the form of the Unicode Character Encoding Model, for which this project aims to provide a C++ infrastructure.


The Unicode Character Encoding Model
----------------------------------------

Let's now walk through the abstraction levels distinguished by the Unicode Character Encoding Model.

### Coded character sets
As we have seen, it's particularly straightforward and intuitive to map nonnegative integers to bit sequences. Thus, a first and helpful step in the way of text encoding would be to map characters and nonnegative integers, in the hope that, with such a mapping in hand, the only matter left to be resolved would be the serialization of the nonnegative integers — a task for which there are solutions already.

We shall first proceed by defining a set of abstract characters (or _abstract character repertoire_) and claiming a set of nonnegative integers that will take part in the mapping. The integers need not form a contiguous range (in fact, the Universal Coded Character Set is made up of many contiguous ranges with unmapped integers in between). Our next step is the actual solution to the issue we are out to solve with this approach: to map between characters and nonnegative integers. For every association between a character and a nonnegative integer, we shall say that the character is thereby a _coded character_ that's _assigned_ to the nonnegative integer, which we shall call its _code point_. The set of code points is the _code space_, and the set of associations (or the mapping) is the _coded character set_. I'm not a native speaker, and it took me a while to realize that a «coded character set» was a «set of coded characters». I mention it just in case, as realizing that helped me grasp the concept.

Coded character sets are the basic product that both ISO and character encoding committees produce. The most famous coded character set is, without a doubt, ASCII — who hasn't heard about it? Indeed, ASCII maps a (small) set of characters to a set of nonnegative integers:

![The ASCII coded character set.](ascii-chart.png)

Another example of a generally-known about coded character set is the Universal Coded Character Set, abbreviated as «UCS» and often referred to –imprecisely– as «Unicode». As of this writing, it contains nearly 100,000 characters, so I think it's reasonable not to include a fancy chart, isn't it? ;)

By the way, you may have noted that, in the above chart, some code points didn't seem to have a character assigned. “What's going on there?”, you could ask. What happens is that the _concept_ of character, on which coded character sets are built, conflicts with the _notion_ of character — if someone talked about a character, we would think about the letter ‘a’ or, at most, about some punctuation characters; the ‘carriage return’ would certainly not come to mind. This distinction between the _concept_ and the _notion_ or _intuition_ is important to keep in mind.

### Character encoding forms
Now that we have nonnegative integers, it seems about time to think about a way to serialize them. Take, for example, the ASCII coded character set. Its code space is the contiguous range 0-127, so a single byte –given that bytes are 8-bit wide– will be enough to store any code point. In fact, we'll even have a spare bit. We could thus consider padding the memory representation of the code point so that this free bit be in front of or behind the bits we use, and even putting it to use — for example, as a synchronization mechanism.

“Not that fast”, we are told. “Have you actually looked at ASCII? You can consider yourself fortunate if you can write something meaningful in your language with the characters it encodes!”. Indeed, ASCII is small; that's why the industry started turning to the Universal Coded Character Set, around two decades ago. And here lies the problem: the UCS is _huge_. Its maximum code point is 10FFFF, which takes 21 bits in binary representation. Thus, if we follow the same approach as above to serialize UCS code points, we'll normally have to use four bytes for each. The thing is, the characters that the average Joe uses more often are located at the beginning of the UCS code space, such that the code points of most of them would just take seven or eight bits — a byte, that is. It seems wasteful to use four bytes for every code point when most of them could use just one, doesn't it?

This is where _character encoding forms_ come in. Indeed, this is a somewhat recent abstraction — because, until recently, coded character sets employed relatively few code points that fitted each in a single byte. Abstractions, after all, arise from use — the very etymology of the word says it. But this is a digress. The thing is, we are faced with the need to encode code points in a storage-efficient manner. What's going to be our take at it?

The matter in question requires us to define a new concept, the _code unit_, which is a nonnegative integer type that occupies a fixed binary width. Thus, for example, UTF-8 uses 8-bit wide code units, while UTF-16 uses 16-bit wide ones. A _character encoding form_ then maps nonnegative integers to code unit sequences, such that the code unit sequences may have a fixed length –in which case we shall speak of a _fixed-width_ character encoding form– or a variable length –which we will unimaginatively dub a _variable-width_ character encoding form–. UTF-32 is a fixed-width character encoding form because all the code unit sequences that it maps are 1-unit long, while UTF-8 and UTF-16 are variable-width character encoding forms, as the code unit sequences they map do not all have the same length — in UTF-8, they span from 1 to 4 code units, while in UTF-16 they range from 1 to 2. Going from nonnegative integers to code unit sequences is _encoding_, while going the opposite direction –from code unit sequences to nonnegative integers– is _decoding_.

“And how does that help save space? Fixed-width character encoding forms are surely *not* the solution, I mean, the UTF-32 character encoding form is exactly what you described earlier…”. Indeed. It's variable-width character encoding forms that are the solution _to the problem of space efficiency_ — keep in mind that solutions are always defined in terms of needs or problems — if we needed to operate with ease on code points, UTF-32 would be a great candidate.

“What about good old ASCII?”, could now be asked. “After all”, it could be argued, “ASCII didn't make as many distinctions. How does it fit in this model?”. Well, ASCII may now be thought of not only as a coded character set, but also as a fixed-width character encoding form with 7-bit wide code units.

### Character encoding schemes
But code units may be larger than the basic working unit, the byte, so their serialization may not be trivial. UTF-16, for example, has 16-bit wide code units, which surpass the common binary width of bytes. Thus, yet another step is needed before we reach bare bits: the _character encoding scheme_. They come in three flavours:

 * First, we have _simple_ character encoding schemes, which map single code units to unique byte sequences. This mapping faces the _endianness_ issue when code units have a binary width larger than that of bytes. Endianness is the order in which the bytes serialized integers are split in come. Take, for example, the nonnegative integer 476. Its representation in the binary positional system is `111011100` — that's nine bits. If our bytes are 8-bit wide, it must be split in two bytes — let them be `00000001` and `11011100`. But, which order should they follow? The most intuitive answer seems to be «the most significant one should come first» — this is _big endian_, and it nicely follows the general pattern of positional numeral systems, to which we are accustomed. However, there are arguments in the opposite direction as well — that «least significant» bytes should come first — that's _little endian_. So it's not obvious, hence the choice. Thus, UTF-16 and UTF-32 are open to two different simple character encoding schemes: a big endian and a little endian one, named using the suffixes ‘BE’ and ‘LE’, respectively (e.g. ‘UTF-32BE’, ‘UTF-16LE’).
 * Next come _compound_ character encoding schemes, which are made up of two or more simple character encoding schemes plus a mechanism to shift between them. The Unicode Character Encoding Model doesn't go into much detail with regards to this ‘mechanism’. Anyway, the most widely-known example is the byte order mark, a sequence of bytes at the start of a stream of encoded text that signals the endianness of the rest of the stream.
 * Finally, there are _compressing_ character encoding schemes, which map code unit sequences to byte sequences “while minimizing the length of the byte sequence”. These aren't specified with much detail either.


The ‘why’ behind this project
----------------------------------------

Despite the usefulness of the Unicode Character Encoding Model in conceptualizing the encoding of text, there's no library implementing it — at least, not in C++. Some may raise their eyebrows upon this assertion; they might ask with irony how's it possible that there aren't any when the fact is that text encoding has been dealt with for many years. Indeed, there are dozens of mildly popular encoders and decoders and whatnot out there — but they aren't structured following the Unicode Character Encoding Model. Decoders and encoders, for instance, usually comprise both a character encoding form and one or more character encoding schemes. The fact that implementations don't abide by a model leads to divergence in several regards. An outstanding one is the interface, which varies wildly from one to another. Another one is the quality. This project aims at offering a C++ infrastructure for the Unicode Character Encoding Model on top of which to implement instances of the various components it defines.