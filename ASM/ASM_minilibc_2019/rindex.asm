BITS 64

SECTION .text
GLOBAL rindex

rindex:
    PUSH RBP
    MOV RBP, RSP
    XOR RCX, RCX
    JMP len

len:
    CMP BYTE [RDI + RCX], 0
    JE while
    INC RCX
    JMP len

while:
    CMP BYTE [RDI + RCX], SIL
    JE finish
    CMP RCX, 0
    JL fail
    DEC RCX
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

