BITS 64

SECTION .text
GLOBAL strncmp

strncmp:
    PUSH RBP
    MOV RBP, RSP
    XOR RCX, RCX
while:
    CMP RCX, RDX
    JE finish
    MOV AL, BYTE [RDI + RCX]
    MOV BL, BYTE [RSI + RCX]
    CMP AL, 00
    CMP BL, 00
    JE finish
    INC RCX
    CMP AL, BL
    JE while
    JMP fail

fail:
    MOVSX EAX, AL
    MOVSX EBX, BL
    SUB EAX, EBX
    MOVSX RAX, EAX
    MOV RSP, RBP
    POP RBP
    RET

finish:
    MOV RAX, 0
    MOV RSP, RBP
    POP RBP
    RET
