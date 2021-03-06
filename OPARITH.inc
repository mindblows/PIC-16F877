;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                            OERA��ES ARITM�TICAS                             *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                                                                             *
;*                                   UTFPR                                     *
;*                 UNIVERSIDADE TECNOL�GICA FEDERAL DO PARAN�                 *
;*                                                                             *
;*                                Ruahn Fuser                                  *
;*                                                                             *
;*                               VERS�O: 1.0.0                                 *
;*                                                                             *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;*                            DESCRI��O DO ARQUIVO                            *
;* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
;
; Include de Opera��es aritm�ticas
;
;
;
;
;
;
;


MULTIPLICA_4x4

	clrw
	bcf STATUS,C
	btfsc MULT_1,0
	addwf MULT_2,W
	rlf MULT_2,F
	btfsc MULT_1,1
	addwf MULT_2,W
	rlf MULT_2,F
	btfsc MULT_1,2
	addwf MULT_2,W
	rlf MULT_2,F
	btfsc MULT_1,3
	addwf MULT_2,W
	movwf PRODUTO
	rlf MULT_2,F
	swapf MULT_2,F

return
;
MULTIPLICA_8x8

	clrf PRODUTO_H
	clrf PRODUTO_L

TESTE_ZERO

	movf MULT_1,W
	xorlw 0x00
	btfsc STATUS,Z
return

	movf MULT_2,W
	xorlw 0x00

	btfsc STATUS,Z
return

MULTIPLICA

	movf MULT_2,W
	addwf PRODUTO_L,F
	btfsc STATUS,C
	incf PRODUTO_H,F
	decfsz MULT_1,F
	goto MULTIPLICA

return
;---------------------------------------------------------------

MULTIPLICA_10x8

	clrf PRODUTO_H
	clrf PRODUTO_L

	movf MULT_2,W
	movwf MULT_TMP

TESTA_MULT_1

	btfsc MULT_1_H,1
	goto TESTA_MULT_2
	btfsc MULT_1_H,0
	goto TESTA_MULT_2


	movf MULT_1_L,W
	xorlw 0x00
	btfsc STATUS,Z

return

TESTA_MULT_2

	movf MULT_2,W
	xorlw 0x00
	btfsc STATUS,Z

return

MULTIPLICAX

	movf MULT_1_L,W
	addwf PRODUTO_L,F
	btfsc STATUS,C

	incf PRODUTO_H,F
	movf MULT_1_H,W
	addwf PRODUTO_H
	decfsz MULT_TMP,F
	goto MULTIPLICAX

return
;************************************************************
;***********************************************************
;************************************************************

;dividendo/divisor = quociente + resto.



DIVIDE_16x16

	clrf QUOCIENTE_H
	clrf QUOCIENTE_L
	movf DIVIDENDO_L,W
	movwf RESTOTMP_L
	movf DIVIDENDO_H,W
	movwf RESTOTMP_H

T_DIVIDENDO
	movf	DIVIDENDO_H,W
	movwf	DIVIDENDOTMP_H
	movf	DIVIDENDO_L,W
	movwf	DIVIDENDOTMP_L
	movf	DIVISOR_H,W
	movwf	DIVISORTMP_H
	movf	DIVISOR_L,W
	movwf	DIVISORTMP_L
	
	movf DIVISORTMP_L,W
	subwf DIVIDENDOTMP_L,W
	movlw 0x01
	btfss STATUS,C
	subwf DIVIDENDOTMP_H,W
	btfss STATUS,C
	goto DIV
	movf DIVIDENDO_L,W
	movwf RESTO_L 
	movf DIVIDENDO_H,W
	movwf RESTO_H 

DIV

	call SUBTRAI_16x16
	movlw 0x01
	btfss STATUS,C

return

	addwf QUOCIENTE_L,F
	btfsc STATUS,C
	incf QUOCIENTE_H,F
	movf RESTOTMP_L,W
	movwf RESTO_L
	movf RESTOTMP_H,W
	movwf RESTO_H

goto DIV

SUBTRAI_16x16

	movf DIVISOR_L,W
	subwf RESTOTMP_L,F
	movlw 0x01
	btfss STATUS,C
	subwf RESTOTMP_H,F
	btfss STATUS,C
	goto EMPRESTA
	movf DIVISOR_H,W
	subwf RESTOTMP_H,F

return

EMPRESTA

	movf DIVISOR_H,W
	subwf RESTOTMP_H,F
	bcf STATUS,C
return

DIVIDE_8x8

clrf QUOCIENTE
movf DIVIDENDO,W
movwf RESTO

DIV2

movf DIVISOR,W
subwf RESTO,W
btfss STATUS,C
return
movwf RESTO
incf QUOCIENTE,F

goto DIV2

SUBTRAI_16x162

movf MINUENDO_L,W
movwf DIFERENCA_L
movf MINUENDO_H,W
movwf DIFERENCA_H

movf SUBTRAENDO_L,W
subwf DIFERENCA_L,F
movlw 0x01
btfss STATUS,C
subwf DIFERENCA_H,F
btfss STATUS,C
call EMPRESTA2
movf SUBTRAENDO_H,W
subwf DIFERENCA_H,F

return

EMPRESTA2

movf SUBTRAENDO_H,W
subwf DIFERENCA_H,F
bcf STATUS,C

return