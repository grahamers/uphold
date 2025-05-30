*************************
*** Build Environment ***
*************************

Linux LAPTOP-RG7C6MND 6.6.87.1-microsoft-standard-WSL2 #1 SMP PREEMPT_DYNAMIC Mon Apr 21 17:08:54 UTC 2025 x86_64 x86_64 x86_64 GNU/Linux
g++ (Ubuntu 9.3.0-10ubuntu2) 9.3.0
cmake version 3.16.3

**************************
*** Build Instructions ***
**************************

cd build
cmake ..
cd ../build

***************
*** General ***
***************

There is no shared library built (time constraints) however the src directory contains all the functions needed
to implment test. Free functions in "uphold" namespace are used. There is no need for an object, though putting the functions in there would be trivial. I was more focussed
on getting the results right. There are a set of input values in tests/tests.txt
which are a superset of the tests defined in the spec.


./main ../tests/tests.txt

and should give output like;


James Bond 007
PI=03.14
It's 03:13pm
It's 12:13pm
000099UR001337
jon 002 jon002
fill 000000000002, bobBBBBBB000000112323
Jonny000000000001
fill  bob
graham 001
001jon 022 jon022
""
Hello World!
0042
Order 12345
abc00123def
Ratio 003.1416 and count 007
00007 is a code
Agent code is 09
ID: 00009
Items 005 012 123
abc-09:def
Zero 0000
Val 00000123
Mix 0003.0014 and 0042abc
Edge12.99
EndsWith09
009Starts
Just.05
007
00100


Additionally there is a tests directory where the tests are validated. gtest etc is not used, its a basic test
harness that has inputs and expected outputs. Its run as follows, from the build directory, after executables are build;

./tests ../tests/tests.txt ../tests/expected.txt

It should give output like;

PASS: input: James Bond 7, 3, output: James Bond 007
PASS: input: PI=3.14, 2, output: PI=03.14
PASS: input: It's 3:13pm, 2, output: It's 03:13pm
PASS: input: It's 12:13pm, 2, output: It's 12:13pm
PASS: input: 99UR1337, 6, output: 000099UR001337
PASS: input: jon 2 jon02, 3, output: jon 002 jon002
PASS: input: fill 2, bobBBBBBB112323, 12, output: fill 000000000002, bobBBBBBB000000112323
PASS: input: Jonny1, 12, output: Jonny000000000001
PASS: input: fill  bob, 9, output: fill  bob
PASS: input: graham 1, 3, output: graham 001
PASS: input: 1jon 22 jon022, 3, output: 001jon 022 jon022
PASS: input: "", 3  , output: ""
PASS: input: Hello World!, 4  , output: Hello World!
PASS: input: 42, 4  , output: 0042
PASS: input: Order 12345, 3  , output: Order 12345
PASS: input: abc123def, 5  , output: abc00123def
PASS: input: Ratio 3.1416 and count 7, 3  , output: Ratio 003.1416 and count 007
PASS: input: 007 is a code, 5  , output: 00007 is a code
PASS: input: Agent code is 9, 2  , output: Agent code is 09
PASS: input: ID: 0009, 5  , output: ID: 00009
PASS: input: Items 5 12 123, 3  , output: Items 005 012 123
PASS: input: abc-9:def, 2  , output: abc-09:def
PASS: input: Zero 0, 4  , output: Zero 0000
PASS: input: Val 123, 8  , output: Val 00000123
PASS: input: Mix 3.14 and 42abc, 4  , output: Mix 0003.0014 and 0042abc
PASS: input: Edge12.99, 2  , output: Edge12.99
PASS: input: EndsWith9, 2  , output: EndsWith09
PASS: input: 9Starts, 3  , output: 009Starts
PASS: input: Just.5, 2  , output: Just.05
PASS: input: 7, 3  , output: 007
PASS: input: 00100, 5, output: 00100


Finally: There is a set of errors defined in tests/errors.txt where the error handling is illustrated (bad inputs etc).

The way the inputs are structured (files) you can easily add your own "gotcha" cases. Would be delighted to discuss approach etc. I have
an awful feeling there's a STL approach out there.


Time complexity O(N)  - we iterate over the input string EXACTLY once (rfind is used to get the padding value) and
after that I iterate from start. No over laps. I avoided iterators because using rbegin and rend and base to convert to
a regular (forward) iterator, can be error prone.

Space complexity O(N + X)  (I refer to 'X' as padding in code).
