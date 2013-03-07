#ifndef __INST_H__
#define __INST_H__

#include <inttypes.h>
#include <stdio.h>

enum InstType {
    INST_NOP = 0,
    INST_PUSH,
    INST_DUP,
    INST_DROP,
    INST_SWAP,
    INST_ADD,
    INST_PRINT,
    INST_HALT
};

// A single boris instruction (machine representation)
typedef uint8_t Inst;

// Write the given instructions to the given file handle.
void write_insts(Inst *insts, size_t num_insts, FILE *file);

// Read `num_insts` instructions from the given file handle into the given
// instruction array.
void read_insts(Inst *insts, size_t num_insts, FILE *file);

#endif /* __INST_H__ */
