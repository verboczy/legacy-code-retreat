# legacy-code-retreat
This is project for legacy code retreat. The original project is [here](https://github.com/jbrains/trivia). It deals with the C++ implementation.

## Prerequisites:
+ g++
+ Make
+ CMake
+ Google Test

## Compilation
+ Navigate into the folder, where the files are.
+ *cmake CMakeLists.txt*
+ *make rungame*
+ *./rungame*

## Testing
+ Navigate into the folder, where the files are.
+ *cmake CMakeLists.txt*
+ *make tests*
+ *./tests*

### Memory check
Valgrind was used to check memory leakage. It did not find any problem.

*valgrind --leak-check=full --show-leak-kinds=all -v ./rungame*
