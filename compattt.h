// compat.h
#ifndef COMPATTT_H
#define COMPATTT_H

#ifdef __ASSEMBLER__
// Skip typedef for assembler
#else
typedef unsigned int uint;
#endif

#endif // COMPATTT_H
