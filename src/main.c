#include "Inst.h"
#include "VM.h"

int main() {
    Inst insts[] = {
        INST_PUSH, 21, 0, 0, 0, // TODO: handle endianness problems
        INST_DUP,
        INST_ADD,
        INST_PRINT,
        INST_HALT
    };

    size_t num_insts = sizeof(insts) / sizeof(Inst);

    VM_run(insts, num_insts);

    return 0;
}
