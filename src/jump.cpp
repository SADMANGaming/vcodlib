/*
Inline asm notes

- __attribute__ ((naked)): no prologue/epilogue
- extern "C": no name mangling
- asm volatile: no optimizaion/reordering

- pushal: save general-purpose registers
- popal: restore general-purpose registers

asm volatile (
    // Instructions
    : // Output operands
    : // Input operands (m = memory, r = register)
    : // Clobber list
);
*/

#include "jump.hpp"

extern cvar_t *jump_height;

extern pmove_t *pm;

extern uintptr_t resume_addr_Jump_Check;
extern uintptr_t resume_addr_Jump_Check_2;

extern customPlayerState_t customPlayerState[MAX_CLIENTS];

int playerstateToClientNum(playerState_t* ps)
{
    return (int)(((byte *)ps - (byte *)sv.gameClients) / sv.gameClientSize);
}

float getJumpHeight()
{
    playerState_t *ps = ((pmove_t*)*((int*)pm))->ps;
    int id = playerstateToClientNum(ps);

    if(customPlayerState[id].overrideJumpHeight)
        return customPlayerState[id].jumpHeight;
    return jump_height->value;
}

// Update ps->velocity[2]
__attribute__ ((naked)) void hook_Jump_Check_Naked()
{
    asm volatile (
        "push %%eax\n"
        "call setJumpHeight\n"
        "pop %%eax\n"
        "jmp *%0\n"
        :
        : "r"(resume_addr_Jump_Check)
        :
    );
}
extern "C" void setJumpHeight()
{
    float height = getJumpHeight() * 2;
    asm volatile (
        "fmul %0\n"
        :
        : "m"(height)
        :
    );
}

// Update ps->jumpTime
/*
Had to:
- start at the mov instruction
- add eax to the clobber list
not to prevent landing faster when jumping on objects instead of continuing to ascend.
*/
__attribute__ ((naked)) void hook_Jump_Check_Naked_2()
{
    asm volatile (
        "mov (%%ebx), %%eax\n"
        "fld 0x1C(%%eax)\n"

        "pushal\n"
        "call setJumpHeight_2\n"
        "popal\n"

        "jmp *%0\n"
        :
        : "r"(resume_addr_Jump_Check_2)
        : "%eax"
    );
}
extern "C" void setJumpHeight_2()
{
    float height = getJumpHeight();
    asm volatile (
        "fadd %0\n"
        :
        : "m"(height)
        :
    );
}