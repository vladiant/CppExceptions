# C++ Exception Processing Samples

## Intended usage
* Error tracing (logging)
* Stack unwinding (raset/termination)
* Data passing / Control Flow (when necessary)

## When to use
* As rarely as possible
* Serious/infrequent/unexpected errors
* With as few exception types as possible (as determined by catch functionality)

## Online samples
* [Using return codes](https://godbolt.org/z/9bs7P8WW8)
* [Using exceptions](https://godbolt.org/z/b7qz36WaM)
* [Bad resource management](https://godbolt.org/z/jorv9Go77)
* [RAII resource management](https://godbolt.org/z/b7zf1ajeE)
* [Adding context with cout](https://godbolt.org/z/vs79eYWff)
* [Adding context with repackage](https://godbolt.org/z/4WY97bWa3)
* [Adding context with mutable what()](https://godbolt.org/z/7q9aY7MqY)
* [Checking with exceptions](https://godbolt.org/z/KefGoanWe)
* [Checking with return enum](https://godbolt.org/z/f93b4cebd)
* [Retrying with exceptions](https://godbolt.org/z/va3EzKfKT)
* [Retrying without exceptions](https://godbolt.org/z/bfnhTjabj)
* [Search faulire with exceptions](https://godbolt.org/z/7chjP3K1f)
* [Search failure with Optional monadics](https://godbolt.org/z/rdfY1dEca)
* [Exception data passing](https://godbolt.org/z/7bbxqqzMG)
* [Expected data passing](https://godbolt.org/z/GTzKx34PG)
* [Expected templated data passing](https://godbolt.org/z/8rcYhG6Tn)
* [Exceptional control flow, same operation](https://godbolt.org/z/c63zqsj3x)
* [Expected control flow, generic lambda](https://godbolt.org/z/c63zqsj3x)
* [Exceptional control flow, different operations](https://godbolt.org/z/Pr7cEcao9)
* [Expected control flow, different operations](https://godbolt.org/z/veE64f5vf)
* [OmegaException class](https://godbolt.org/z/YsWEoczsW)


## References
* [Exceptions in C++: Better Design Through Analysis of Real World Usage - Peter Muldoon - CppNow 2023](https://www.youtube.com/watch?v=HXJmrMnnDYQ)
