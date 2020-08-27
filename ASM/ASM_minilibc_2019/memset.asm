BITS 64

SECTION .text
GLOBAL memset

memset:
    PUSH RBP
    MOV RBP, RSP
    XOR RCX, RCX

while:
    CMP RCX, RDX
    JE finish
    MOV [RDI + RCX], SIL
    INC RCX
    JMP while

finish:
    MOV RAX, RDI
    MOV RSP, RBP
    POP RBP
    RET
