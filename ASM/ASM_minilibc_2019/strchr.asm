BITS 64

SECTION .text
GLOBAL strchr

strchr:
    PUSH RBP
    MOV RBP, RSP
    XOR RCX, RCX

while:
    CMP BYTE [RDI + RCX], SIL
    JE finish
    CMP BYTE [RDI + RCX], 0
    JE fail
    INC RCX
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

