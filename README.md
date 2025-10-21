# BigInt, no more limits.
a simple C header file that allows users to store extremely large integers and use basic arithmetic operations on them

## Requirements
1. just C and a C compiler!

## Installation
just include the header file and youre ready to go!


## Usage
after including the header file there are really easy function you can use like createBigInt and printBigInt to work with it!

- example:
```C
#include "src/BigInt.h"

int main(){
  BigInt* result = factorial(50);
  printBigInt(result);
}
```
- output :    

30414093201713378043612608166064768844377641568960512000000000000
