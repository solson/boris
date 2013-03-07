#ifndef __INST_H__
#define __INST_H__

#include <inttypes.h>

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

#endif /* __INST_H__ */
