BITS 64

SECTION .text
GLOBAL strlen

strlen:
       PUSH RBP
       MOV RBP, RSP
       XOR RCX, RCX

while:
       CMP BYTE [RDI + RCX], 0
       JE finish
       INC RCX
       JMP while

finish:
       MOV RAX, RCX
       MOV RSP, RBP
       POP RBP
       RET