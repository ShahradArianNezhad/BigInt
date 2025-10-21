#ifndef BIGINT_IMPLEMENTATION
#define BIGINT_IMPLEMENTATION

#include <stdio.h>
#include <stdlib.h>

typedef struct BigInt {
    char* digits;
    int len;
    int size;
} BigInt;

static inline BigInt* createBigInt(long initialLength) {
    BigInt* newint = malloc(sizeof(BigInt));
    newint->digits = calloc(initialLength, sizeof(char));
    newint->len = initialLength;
    newint->size = 0;
    return newint;
}
static inline void addBigInt(BigInt* bigInt,int num){
  int i=1,carry=0;
  while(num){ 
    if((bigInt->digits[bigInt->len-i] + num%10 + carry)>9){
      //temp=-10;
      bigInt->digits[bigInt->len-i] += num%10-10+carry;
      if(carry!=0)carry=0;
      carry=1;
    }else{
      bigInt->digits[bigInt->len-i] += num%10+carry;
      if(carry!=0)carry=0;
    }
    if(i>bigInt->size){
      if(bigInt->len>bigInt->size) bigInt->size++;
      else{
        fprintf(stderr, "ERROR: result buffer overflow\n");
        exit(0);
      }
    }
    num/=10;
    i++;
  }
  if(carry){
      if(bigInt->len>bigInt->size) bigInt->size++;
      else{
        fprintf(stderr, "ERROR: result buffer overflow\n");
        exit(0);
      }
    bigInt->digits[bigInt->len-i]=carry;
  }
}

static inline void subtractBigInt(BigInt* a,BigInt* b){
  int prod,j=0;
  for(int i=0;i<=b->size;i++){
    int pos = b->len-i;
    if(b->digits[pos]>a->digits[pos]){
      prod = a->digits[pos] - b->digits[pos] + 10;
      if(a->digits[pos-1]>0)a->digits[pos-1]-=1;
      else{
        while(a->digits[pos-1-j]==0){
          a->digits[pos-1-j]=9;
          j++;
          if(pos-1-j==0){
            fprintf(stderr, "ERROR: The resulting subtraction is a negative number\n");
            exit(1);
          }
        }
        a->digits[pos-1-j]-=1;
        j=0;
      }
      
    }else{
      prod = a->digits[pos] - b->digits[pos];
    }
    a->digits[pos] = prod;
  }
  int start = 0;
  while(start < a->len - 1 && a->digits[start] == 0) start++;
  a->size = a->len - start;
  if(a->size == 0) a->size = 1;
}






static inline void printBigInt(BigInt* bigInt){
  for(int i=0;i<bigInt->size;i++){
    printf("%d",bigInt->digits[bigInt->len-bigInt->size+i]);
  }
  printf("\n");
}

static inline void setBigInt(BigInt* bigInt,int num){
  int i=1;
  while(num){
    bigInt->digits[bigInt->len-i]=num%10;
    num/=10;
    i++;
  }
  bigInt->size = i-1;
}

static inline void bigIntFree(BigInt *num) {
    free(num->digits);
    free(num);
}


static inline void bigIntTrim(BigInt *num) {
    while (num->size > 1 && num->digits[num->size- 1] == 0) {
        num->size--;
    }
}

static inline void multiplyBigInt(BigInt *a, BigInt *b){
  int resLen = a->size + b->size;
  if(resLen < 1) resLen = 1;
  BigInt *result = createBigInt(resLen);

  for(int ia = 0; ia < a->size; ++ia){
    int ai = a->digits[a->len - 1 - ia];
    int carry = 0;
    for(int jb = 0; jb < b->size; ++jb){
      int bj = b->digits[b->len - 1 - jb];
      int posFromRight = ia + jb;
      int pos = result->len - 1 - posFromRight;

      int prod = ai * bj + result->digits[pos] + carry;
      result->digits[pos] = prod % 10;
      carry = prod / 10;
    }
    int posFromRight = ia + b->size;
    while(carry > 0){
      int pos = result->len - 1 - posFromRight;
      if(pos < 0){
        fprintf(stderr, "ERROR: result buffer overflow\n");
        exit(1);
      }
      int sum = result->digits[pos] + carry;
      result->digits[pos] = sum % 10;
      carry = sum / 10;
      posFromRight++;
    }
  }

  int start = 0;
  while(start < result->len - 1 && result->digits[start] == 0) start++;
  result->size = result->len - start;
  if(result->size == 0) result->size = 1;

  free(a->digits);
  a->digits = result->digits;
  a->len = result->len;
  a->size = result->size;

  free(result);
}

static inline BigInt* factorial(int num){
  BigInt* result = createBigInt(10000000);
  setBigInt(result,1);
  BigInt* temp = createBigInt(100);
  for(int i=1;i<=num;i++){
    setBigInt(temp,i);
    multiplyBigInt(result,temp);
  }
  return result;
}




#endif
