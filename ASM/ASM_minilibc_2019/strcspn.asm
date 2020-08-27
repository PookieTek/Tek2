BITS 64

SECTION .text
GLOBAL strcspn

strcspn:
    PUSH RBP
    MOV RBP, RSP
    XOR RCX, RCX
    XOR R8, R8

while:
    MOV AL, BYTE [RDI + RCX]
    MOV BL, BYTE [RSI + R8]

    CMP BYTE AL, 0
    JE finish
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

finish:
    MOV RAX, RCX
    MOV RSP, RBP
    POP RBP
    RET