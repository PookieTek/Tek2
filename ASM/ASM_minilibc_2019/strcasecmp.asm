BITS 64

SECTION .text
GLOBAL strcasecmp

strcasecmp:
    PUSH RBP
    MOV RBP, RSP
    XOR RCX, RCX

while:
    MOV AL, BYTE [RDI + RCX]
    MOV BL, BYTE [RSI + RCX]

    CMP BL, 00
    JE finish

    INC RCX

    CMP AL, BL
    JE while
    JNE different

different:
    CMP AL, 91
    JL upa

    CMP BL, 91
    JL upb

    CMP AL, BL
    JE while
    JMP fail

upa:
    CMP AL, 65
    JL fail
    ADD AL, 32
    JMP different

upb:
    CMP BL, 65
    JL fail
    ADD BL, 32
    JMP different

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