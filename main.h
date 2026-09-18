#ifndef main_H
#define main_H

#include <stdint.h>
long toUnsignedLong(int x);
int remainderUnsigned(int dividend, int divisor);
void LootTableRNG(char *identifier);
void setSeed(long seed);
long mixStafford13(long v);
uint64_t nextLong(void);
long nextBits(int i);
float nextFloat();
int nextInt();
int nextInti(int i);
bool test_loot();
long mixStafford13(long v);
#endif // main_H
