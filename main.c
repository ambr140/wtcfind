#include "main.h"
// #include "cJSON/cJSON.h"
#include "md5.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// HashFunction MD5 = Hashing.md5();
long seedLo;
long seedHi;
long seedLoHash;
long seedHiHash;

static inline uint64_t rotl(const uint64_t x, int k) {
  return (x << k) | (x >> (64 - k));
}
long toUnsignedLong(int x) { return (long)x & 4294967295L; }

int remainderUnsigned(int dividend, int divisor) {
  return (int)(toUnsignedLong(dividend) % toUnsignedLong(divisor));
}
int flipchar(char *flip, int l) {
  char fliped[l];
  for (int i = 0; i <= l; i++) {
    fliped[l - i] = flip[i];
    // printf("%i,%i,%c\n", l - i, i, flip[i]);
  }
  memcpy(flip, fliped, l);
}
void rev(char *arr, int n) {

  // Two pointers
  int l = 0, r = n - 1;
  while (l < r) {

    // Swap the elements
    char temp = arr[l];
    arr[l] = arr[r];
    arr[r] = temp;

    // Move pointers towards middle
    l++;
    r--;
  }
}

int removedarrycalc(int arr[], int len, int indxe) {
  int i;
  int temp = arr[indxe];
  for (i = indxe; i < len - 1; i++)
    arr[i] = arr[i + 1];
  // printf("%i:%i\n", count, indxe);
  return temp;
}
void LootTableRNG(char *identifier) {
  uint8_t bs[16];
  md5String(identifier, bs);
  // FILE *fp;
  // fp = fopen("md.bin", "wb");
  rev(bs, 8);
  rev(&bs[8], 8);
  // fwrite(bs, 16, 1, fp);
  memcpy(&seedLoHash, bs, 8);
  memcpy(&seedHiHash, &bs[8], 8);
  // printf("%li\n", seedLoHash);
  // printf("%li\n", seedHiHash);
  //   fromBytes(bs[8], bs[9], bs[10], bs[11], bs[12], bs[13], bs[14], bs[15]);
}

void setSeed(long seed) {
  long l2 = seed ^ 0x6a09e667f3bcc909;
  // printf("%li\n", l2);
  long l3 = l2 + 0x9e3779b97f4a7c15;
  // XOR happens before mixing in 1.20-pre5 and later
  // printf("%li\n", mixStafford13(l2 ^ seedLoHash));
  seedLo = mixStafford13(l2 ^ seedLoHash);
  seedHi = mixStafford13(l3 ^ seedHiHash);

  if (seedLo == 0 | seedHi == 0) {
    seedLo = -7046029254386353131L;
    seedHi = 7640891576956012809L;
  }
  // printf("%li\n", seedLo);
  // printf("%li\n", seedHi);
}

long mixStafford13(long v) {
  //  printf("%lb\n", v);
  v = (v ^
       (v >> 30) &
           0b0000000000000000000000000000001111111111111111111111111111111111) *
      0xbf58476d1ce4e5b9;
  v = (v ^
       ((v >> 27) &
        0b0000000000000000000000000001111111111111111111111111111111111111)) *
      0x94d049bb133111eb;
  // printf("%li\n", v);
  return (v ^
          ((v >> 31) &
           0b0000000000000000000000000000000111111111111111111111111111111111));
}

uint64_t nextLong(void) {
  const uint64_t result = rotl(seedLo + seedHi, 17) + seedLo;

  seedHi ^= seedLo;
  seedLo = rotl(seedLo, 49) ^ seedHi ^ (seedHi << 21); // a, b
  seedHi = rotl(seedHi, 28);                           // c

  // printf("j%li\n", result);
  return result;
}

long nextBits(int i) { return nextLong() >> (64 - i); }
float nextFloat() { return (float)nextBits(24) * 5.9604645E-8F; }
double nextDouble() { return (double)nextBits(53) * 1.110223E-16F; }
int nextInt() { return (int)nextLong(); }
int nextInti(int i) {
  if (i <= 0) {
    printf("i must be <= 0");
  } else {
    long l = toUnsignedLong(nextInt());
    // printf("l = %li\n", l);
    long m = l * (long)i;
    long n = m & 4294967295L;
    if (n < (long)i) {
      for (int j = (-i + 1) % i; n < (long)j; n = m & 4294967295L) {
        l = toUnsignedLong(nextInt());
        m = l * (long)i;
      }
    }
    long o = m >> 32;
    return (int)o;
  }
}
bool test_mossandsp(long seed) {
  // Rewrite this for each loot table. Be careful since loot tables might do
  // extra calls besides what you target, which this method must do as well.
  // That is, this method should imitate a full call to the loot table. You must
  // look in the code to determine exactly the nature of the needed test, or
  // experiment

  LootTableRNG("minecraft:trade_set/wandering_trader/common");
  setSeed(seed);
  // determines melon slice count
  int val = 0;
  int valre = 0;
  int leftover = 76;
  bool moss = false;
  bool oak = false;
  int arr[leftover];
  for (int i = 0; i < leftover; i++) {
    arr[i] = i;
  }
  // memset(arr, 100, sizeof(arr)); // TODO: chang 100
  for (int i = 0; i < 5; i++) {
    val = nextInti(leftover);
    // printf("%i\n", cJSON_GetArraySize(json));
    valre = removedarrycalc(arr, leftover, val);
    // arr[i] = valre;
    //  printf("%i\n", valre);
    leftover--;
    if (valre == 69) {
      moss = true;
    }
    if (valre == 48) {
      oak = true;
    }
  }
  if (moss && oak) {
    return true;
  } else {
    return !true;
  }
}
bool test_ptandwit(long seed) {
  // Rewrite this for each loot table. Be careful since loot tables might do
  // extra calls besides what you target, which this method must do as well.
  // That is, this method should imitate a full call to the loot table. You must
  // look in the code to determine exactly the nature of the needed test, or
  // experiment

  LootTableRNG("minecraft:trade_set/wandering_trader/buying");
  setSeed(seed);
  // determines melon slice count
  int val = 0;
  int valre = 0;
  int leftover = 6;
  bool potto = false;
  bool hey = false;
  int arr[leftover];
  for (int i = 0; i < leftover; i++) {
    arr[i] = i;
  }
  // memset(arr, 100, sizeof(arr)); // TODO: chang 100
  for (int i = 0; i < 2; i++) {
    val = nextInti(leftover);
    // printf("%i\n", cJSON_GetArraySize(json));
    valre = removedarrycalc(arr, leftover, val);
    // printf("%i\n", valre);
    leftover--;
    if (valre == 4) {
      potto = true;
    }
    if (valre == 5) {
      hey = true;
    }
  }
  if (potto && hey) {
    return true;
  } else {
    return !true;
  }
}

int main(int argc, char *argv[]) {
  int max = 0;
  // Loot tables can be found by renaming the 1.20-pre2 jar to a .zip
  // then navigating to /data/minecraft/loot_tables
  // The needed string is at the bottom of a loot table
  // You also must modify the test_loot function
  int count = 0;
  for (int i = 0; count < 100000; i++) {
    if (test_mossandsp(i) && test_ptandwit(i)) {
      printf("%i\n", i);
      count++;
    }
  }
}
