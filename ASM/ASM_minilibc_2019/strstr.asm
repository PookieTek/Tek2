BITS 64

SECTION .text
GLOBAL strstr

strstr:
    PUSH RBP
    MOV RBP, RSP
    XOR RCX, RCX
    XOR R8, R8

while:
    XOR R9, R9
    ADD R9, RCX
    ADD R9, R8
    MOV AL, BYTE [RDI + R9]
    MOV BL, BYTE [RSI + R8]

    CMP BYTE AL, 0
    JE fail
    CMP BYTE BL, 0
    JE finish
    CMP AL, BL
    JE found
    JMP dump

found:
    INC R8
    JMP while

fail:
    MOV RAX, 0
    MOV RSP, RBP
    POP RBP
    RET

dump:
    XOR R8, R8
    INC RCX
    JMP while

finish:
    ADD RDI, RCX
    MOV RAX, RDI
    MOV RSP, RBP
    POP RBP
    RET