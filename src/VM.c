#include "VM.h"
#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>

// PUSH and DROP are used (only) inside VM_run to make dealing with the data
// stack more convenient.
#define PUSH(x) { \
    int32_t __val = (x); \
    data_p++; \
    if(data_p >= data_end) { \
        fprintf(stderr, "VM_run(): data stack overflow\n"); \
        return; \
    } \
    *data_p = __val; \
}

// Complain if there are less than n items on the data stack
#define CHECK_UNDERFLOW(inst, n) { \
    if(data_p - (n) < data) { \
        fprintf(stderr, "VM_run(): " inst ": data stack underflow\n"); \
        return; \
    } \
}

// This is where the magic happens. This function is the only thing that
// actually executes boris instructions.
void VM_run(Inst *insts, size_t num_insts) {
    if(insts == NULL) {
        fprintf(stderr, "VM_run(): got a null instruction sequence\n");
        return;
    }

    // The instruction pointer
    Inst *ip = insts;

    // The end of the instruction list
    Inst *end = insts + num_insts;

    // The data stack and pointer
    int32_t data[STACK_SIZE];
    int32_t *data_p = data;
    int32_t *data_end = data + STACK_SIZE;

    // The run loop shall run indefinitely except for two cases:
    //   1) A 'halt' instruction is executed.
    //   2) Some kind of exception occurs (such as running out of
    //      instructions, dividing by 0, etc.)
    while(true) {
        if(ip >= end) {
            fprintf(stderr, "VM_run(): pc ran past the end of the instructions\n");
            return;
        }

        // The current executing instruction
        Inst curr_inst = *ip;

        // Note: we increment the ip before executing the current instruction.
        ip++;

        switch(curr_inst) {
        case INST_NOP:
            // Do no operation. That was easy.
            break;

        case INST_PUSH:
            // The next four bytes of the instruction sequence are to be
            // treated as a single 32-bit integer. This integer will be pushed
            // to the top of the data stack.

            // Since the ip was already incremented, the integer is made up of
            // these bytes: ip[0], ip[1], ip[2], ip[3]
            if(ip + 3 >= end) {
                fprintf(stderr, "VM_run(): push: need at least 4 bytes left in instruction sequence\n");
                return;
            }

            // Get the integer from the instruction sequence and push it on
            // the data stack
            int32_t val = *((int32_t*) ip);
            PUSH(val);

            // Increment the ip past the value
            ip += 4;
            break;

        case INST_DUP:
            CHECK_UNDERFLOW("dup", 1);

            // Duplicate the top item of the data stack
            PUSH(*data_p);
            break;

        case INST_DROP:
            CHECK_UNDERFLOW("drop", 1);

            // Pop the top item from the data stack, discarding it
            data_p--;
            break;

        case INST_SWAP:
            CHECK_UNDERFLOW("swap", 2);

            // Swap the top two items on the stack
            int32_t tmp = data_p[0];
            data_p[0] = data_p[-1];
            data_p[-1] = tmp;
            break;

        case INST_ADD:
            CHECK_UNDERFLOW("add", 2);

            // Add the top two items on the stack, consuming them and leaving
            // the result
            data_p[-1] += data_p[0];
            data_p--;
            break;

        case INST_PRINT:
            CHECK_UNDERFLOW("print", 1);

            // Print the top item on the stack, consuming it
            printf("%"PRIi32"\n", *data_p);
            data_p--;
            break;

        case INST_HALT:
            // Return from VM_run safely
            return;

        default:
            fprintf(stderr, "VM_run(): unrecognized instruction type 0x%hhu\n", curr_inst);
            return;
        }
    }
}
