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


// Code from Ryan Reick at stackoverflow.com
// Assumes 0 <= max <= RAND_MAX
// Returns in the closed interval [0, max]
/*s32 RandomDBK(s32 max) {
    // max <= RAND_MAX < ULONG_MAX, so this is okay.
    u32 num_bins;
    u32 num_rand;
    u32 bin_size;
    u32 defect;
    s32 x;

    num_bins = max + 1,
    num_rand = 32767 + 1,
    bin_size = num_rand / num_bins,
    defect   = num_rand % num_bins;

    do {
    x = Random();
    }
    // This is carefully written not to overflow
    while (num_rand - defect <= x);

    // Truncated division is intentional
    return x/bin_size;
}*/

s32 RandomDBK(s32 n)
{
    s32 limit;
    s32 r;

    limit = 32767 - (32767 % n);

    while((r = Random()) >= limit);

    return r % n;
}