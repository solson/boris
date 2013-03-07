#ifndef __VM_H__
#define __VM_H__

#include "Inst.h"
#include <stddef.h>

// The maximum allowed size of the data stack at runtime
#define STACK_SIZE 2048

void VM_run(Inst *insts, size_t num_insts);

#endif /* __VM_H__ */
