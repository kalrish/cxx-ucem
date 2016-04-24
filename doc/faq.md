# FAQ  {#faq}

## Whoa!, ‘abstraction’ and ‘C++’! You realize that's an approach of the past, right?
In the past years, abstraction has been one of the leading motives behind software development. This tendency gave rise to the object-oriented paradigm, which found particular application in C++. Nowadays, both the religious abstracting and the fanatic object-oriented mindsets are deemed inappropriate. The reasons for this are manifold. One of the most important ones is performance scalability. The sacred interface-implementation abstraction, by hiding the underlying data, hides optimization opportunities, while the blessed object model just doesn't play well with caches and the memory locality requirements that modern processors impose on programs to perform well. The problem goes even deeper than some particular paradigms, to programming languages themselves: most artificial languages, including programming languages, take an «atomic approach». Take, for example, logical operations: they are defined on two arguments, not three or an arbitrary number. This approach doesn't match too well the way processors work _efficiently_. A proof of this is the ongoing development of SIMD instructions in commodity processors — it's not happening in special-purpose processors, and it's not some annoying enthusiasts that are behind it, but the very hardware industry. The fact is that Moore's predicted linear growth has slowed already and increasing single-pipe processing power as before is no longer an option — at least, with current lithography. This is relevant to software development because it's the trend commodity processors are following — and commodity processors are the common target of software development.

That's why terms like ‘abstraction’ and ‘object orientation’ (and even ‘C++’, which is treated as a synonym in some contexts) are looked upon with skepticism and meet hard criticism. This project assumes this criticism. The thing is, this project doesn't employ object-orientation or any costly abstractions. Just have a look at the code. All that's used is C++'s mighty powerful type and template systems, leveraged to implement zero-cost abstractions. Classes are used as part of this template mechanism, but they are not to be instantiated (in fact, their constructors are explicitly deleted so as to prevent them from ever being instantiated). There's no state or virtual methods that hinder memory locality expectations.

Now, there *are* some concerns. Namely, the operations are «atomic» (or, in this context, and in general, byte-at-a-time). This means that, while they're perfectly suitable for thread-based parallelization, they may not be suitable for SIMD. However, this is not something that couldn't be added in the future and, in fact, I'm already exploring the possibilities, both for the interface and the implementations.