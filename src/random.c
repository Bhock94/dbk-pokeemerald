#include "global.h"
#include "random.h"

// The number 1103515245 comes from the example implementation of rand and srand
// in the ISO C standard.

EWRAM_DATA static u8 sUnknown = 0;
EWRAM_DATA static u32 sRandCount = 0;

// IWRAM common
u32 gRngValue;
u32 gRng2Value;

u16 Random(void)
{
    gRngValue = 1103515245 * gRngValue + 24691;
    sRandCount++;
    return gRngValue >> 16;
}

void SeedRng(u16 seed)
{
    gRngValue = seed;
    sUnknown = 0;
}

void SeedRng2(u16 seed)
{
    gRng2Value = seed;
}

u16 Random2(void)
{
    gRng2Value = 1103515245 * gRng2Value + 24691;
    return gRng2Value >> 16;
}

s32 RandomDBK(s32 max)
{
    s32 RAND_MAX = 32767;
    u32 num_bins, num_rand, bin_size, defect;
    s32 x;

    num_bins = max + 1;
    num_rand = RAND_MAX + 1;
    bin_size = num_rand / num_bins;
    defect   = num_rand % num_bins;

    do {
     x = Random32();
    }
    while (num_rand - defect <= x);

    return x/bin_size;
}