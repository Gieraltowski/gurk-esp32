MOV_REG 0x0001 // rdest = rsrc
MOV_WREG 0x0002 // rdest = value 
MOV_MEM 0x0003 // rdest = memadress
MOV_WMEM 0x0004 // memadress = value

ADD 0x0005 // rdest = rsrc0 + rsrc1
SUB 0x0006 // rdest = rsrc0 - rsrc1
MUL 0x0007 // rdest = rsrc0 * rsrc1
SUB 0x0008 // rdest = rsrc0 / rsrc1

AND 0x0009 // rdest = rsrc0 & rsrc1
OR 0x000A // rdest = rsrc0 | rsrc1
XOR 0x000B // rdest = rsrc0 ^ rsrc1
NOR 0x000C // rdest = -(rsrc0 | rsrc1)
NOT 0x000D // rdest = -rsrc0
XNOR 0x000E // rdest = -(rsrc0 ^ rsrc1)

JMP 0x000F // PC = rdest
JZ 0x0010 // if rsrc = 0: PC = rdest
JNZ 0x0011 // if rsrc != 0: PC = rdest
JC 0x0012 // if carry: PC = rdest
JNC 0x0013 // if not carry: PC = rdest
JO 0x0014 // if overflow: PC = rdest
JNO 0x0015 // if not overflow: PC = rdest
JE 0x0016 // if rsrc0 = rsrc1: PC = rdest
JNE 0x0017 // if rsrc0 != rsrc1: PC = rdest
JB 0x0018 // if rsrc0 < rsrc1: PC = rdest
JNB 0x0019 // if rsrc0 >= rsrc1: PC = rdest
JA 0x001A // if rsrc0 > rsrc1: PC = rdest
JNA 0x001B // if rsrc0 <= rsrc1: PC = rdest

SHL 0x001C // rdest = rsrc0 << value
SHR 0x001D // rdest = rsrc0 >> value
SAL 0x001E // rdest = rsrc0 << value
SAR 0x001F // rdest = rsrc0 >> value
ROL 0x0020 // rdest = rl(rsrc0, rsrc1)
ROR 0x0021 // rdest = rr(rsrc0, rsrc1)

SYS_CALL 0x0022 // no input