_EXIT	= 1
_READ	= 3
_WRITE	= 4
_STDOUT	= 1
_STDIN	= 1
_GETCHAR = 117
MAXBUFF	= 100

.SECT .TEXT
start:
0:	PUSH	endpro1-prompt1
	PUSH	prompt1
	PUSH	_STDOUT
	PUSH	_WRITE
	SYS
	ADD	SP,8
	
	PUSH	4
	PUSH	buff
	CALL	getline
	ADD	SP,4
	
	PUSH	buff
	CALL	gettrans
	ADD	SP,4
	ADD	AX,1
	
1:	CMP	AX,0
	JE	2f
	PUSH	endpro0-prompt0
	PUSH	prompt0
	PUSH	_STDOUT
	PUSH	_WRITE
	SYS
	ADD	SP,8
	
	PUSH	MAXBUFF
	PUSH	buff
	CALL	getline
	ADD	SP,2
	
	PUSH	buff
	CALL	translate
	ADD	SP,4

	CALL	print_summary
	CALL	printnl
	
	JMP	1b

2:	PUSH	0
	PUSH	_EXIT
	SYS
	
getline:
	PUSH	BX
	PUSH	CX
	PUSH	BP
	MOV	BP,SP
	MOV	BX,8(BP)
	MOV	CX,8(BP)
	ADD	CX,10(BP)
	SUB	CX,1

1:	CMP	CX,BX
	JE	2f
	PUSH	_GETCHAR
	SYS

	ADD	SP,2
	CMPB	AL,-1
	JE	2f
	MOVB	(BX),AL
	INC	BX
	CMPB	AL,'\n'
	JNE	1b

2:	MOVB	(BX),0
	MOV	AX,BX
	SUB	AX,8(BP)
	POP	BP
	POP	CX
	POP	BX
	RET

gettrans:
	PUSH	BX
	PUSH	BP
	MOV	BP,SP
	MOV	BX,6(BP)
	MOVB	CL,(BX)
	MOVB	(inchar),CL

1:	INC	BX
	CMPB	(BX),' '
	JE	1b
	MOVB	CL,(BX)
	MOVB	(outchar),CL

	MOV	AX,1
	POP	BP
	POP	BX
	RET

translate:
	PUSH	BX
	PUSH	BP
	MOV	BP,SP
	MOV	BX,6(BP)

1:	CMPB	(BX),'\n'
	JE	4f
	INC	(charct)
	CMPB	(BX),' '
	JE	2f
	MOVB	CL,(inchar)
	CMPB	(BX),CL
	JE	3f

2:	PUSH	1
	PUSH	BX
	PUSH	_STDOUT
	PUSH	_WRITE
	SYS
	ADD	SP,8
	INC	BX
	JMP	1b

3:	MOVB	CL,(outchar)
	MOVB	(BX),CL
	PUSH	1
	PUSH	BX
	PUSH	_STDOUT
	PUSH	_WRITE
	SYS
	ADD	SP,8
	INC	(wordct)
	INC	BX
	JMP	1b

4:	CALL	printnl
	INC	(linect)

	MOVB	CL,(linect)
	MOVB	(BX),CL
	PUSH	1
	PUSH	BX
	PUSH	_STDOUT
	PUSH	_WRITE
	SYS
	ADD	SP,8
	CALL	printnl
	POP	BP
	POP	BX
	RET
	
print_summary:
	PUSH	(linect)
	PUSH	(wordct)	! EXTRA FEATURE: Instead of countinig words, this counts number of translations.
	PUSH	(charct)
	CALL	rab_print_summary
	ADD	SP,6
	RET
	
.SECT .DATA
prompt0:
	.ASCII	"Enter what you would like to translate: "
endpro0:

prompt1:
	.ASCII	"Enter translation rule: "
endpro1:

outchar:
	.BYTE	0
inchar:
	.BYTE	0
charct:
	.WORD	0
wordct:
	.WORD	0
linect:
	.WORD	0
	
.SECT .BSS
buff:
	.SPACE MAXBUFF
