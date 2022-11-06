
**Build instructions
1. To build Mefodij run:
g++ -g $(find ./src -type f -iregex ".*\.cpp" ! -name "test.cpp") -o build/mefodij
2. To build unit tests with g++ run: 
g++ -g $(find ./src -type f -iregex ".*\.cpp" ! -name "main.cpp") -lgtest -lpthread -o build/test