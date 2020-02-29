#pragma once

#define VIRT_TO_PHYS(x) (x & ~0x80000000)
#define PHYS_TO_VIRT(x) (x | 0x80000000)
