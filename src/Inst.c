#include "Inst.h"

void write_insts(Inst *insts, size_t num_insts, FILE *file) {
    fwrite(insts, sizeof(Inst), num_insts, file);
}

void read_insts(Inst *insts, size_t num_insts, FILE *file) {
    fread(insts, sizeof(Inst), num_insts, file);
}
