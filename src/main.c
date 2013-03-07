#include "Inst.h"
#include "VM.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
/*
    Inst insts[] = {
        INST_PUSH, 21, 0, 0, 0, // TODO: handle endianness problems
        INST_DUP,
        INST_ADD,
        INST_PRINT,
        INST_HALT
    };

    size_t num_insts = sizeof(insts) / sizeof(Inst);
*/

    if(argc != 2) {
        fprintf(stderr, "usage: boris <input file>\n");
        return 1;
    }

    // Open the input file for reading in binary mode
    FILE *file = fopen(argv[1], "rb");

    if(file == NULL) {
        fprintf(stderr, "error: could not open input file\n");
        return 2;
    }

    // Get the length of the file
    fseek(file, 0, SEEK_END);
    long num_insts = ftell(file);

    // Go back to the start of the file
    rewind(file);

    // Read in the instructions
    Inst *insts = malloc(num_insts * sizeof(Inst));
    read_insts(insts, num_insts, file);

    fclose(file);

    // Run the code
    VM_run(insts, num_insts);

    return 0;
}
