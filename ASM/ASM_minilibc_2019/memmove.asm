BITS 64

SECTION .text
GLOBAL memmove

memmove:
    PUSH RBP
    MOV RBP, RSP
    XOR RCX, RCX

while:
    CMP RCX, RDX
    JE finish
    MOV AL, BYTE [RSI + RCX]
    MOV [RDI + RCX], AL
    INC RCX
    JMP while

finish:
    MOV RAX, RDI
    MOV RSP, RBP
    POP RBP
    RET