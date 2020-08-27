BITS 64

SECTION .text
GLOBAL strpbrk

strpbrk:
    PUSH RBP
    MOV RBP, RSP
    XOR RCX, RCX
    XOR R8, R8

while:
    MOV AL, BYTE [RDI + RCX]
    MOV BL, BYTE [RSI + R8]

    CMP BYTE AL, 0
    JE fail
    CMP BYTE BL, 0
    JE dump
    INC R8
    CMP AL, BL
    JE finish
    JMP while

dump:
    INC RCX
    XOR R8, R8
    JMP while

fail:
    MOV RAX, 0
    MOV RSP, RBP
    POP RBP
    RET

finish:
    ADD RDI, RCX
    MOV RAX, RDI
    MOV RSP, RBP
    POP RBP
    RET