Chapter 4 C++ Code

Includes 6 implementation files and 7 required headers.
Test code, checking scripts and raw extraction copies are excluded.
Keep all code and header files in the same folder.

Standalone program: 06_queue_simulation.cpp
Other .cpp files contain reusable algorithms/templates, without main().
Do not compile all .cpp files together.

Compile and run:
  g++ -std=c++17 -O0 -g0 06_queue_simulation.cpp -o simulator
  ./simulator

Example input (servers, arrival bounds, service bounds, customers):
  1
  1 1
  3 3
  5
Expected integer average waiting time: 4.

Online compiler: import the .cpp and .h files into the same project folder,
select 06_queue_simulation.cpp and run it.

The chapter implementation was verified on writecode.in through a separate
basic test and six test groups (4,690 assertions), all with exit code 0.
Those test entry points are intentionally not included in this package.
