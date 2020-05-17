%include "../machine/csym.inc"	; Innerhalb des Include-Files 'csym.inc'
				; wird das Macro CSYM(name) definiert,
				; das dem uebergebenen Symbolnamen in
				; Abhaegigkeit vom verwendeten Generierungs-
				; system einen Unterstrich ('_') voranstellt.

; EXPORTIERTE FUNKTIONEN

csym switchContext

[GLOBAL switchContext]

; IMPLEMENTIERUNG DER FUNKTIONEN

[SECTION .text]

; switchContext: Der Coroutinenwechsel
;
; C-Prototyp:
;
;     void switchContext (void*& from, void*& to);
;

switchContext:
;	fuegt hier Euren Code ein!
	push ebp
	mov ebp, esp
	
	;retten nichtflüchtige register
	push edi
	push esi
	push ebx
	
	mov eax, [ebp + 8] ;laden wert von from auf eax
	mov [eax], esp	;sichern den stackpointer an der adresse, auf die from verweist
	mov eax, [ebp + 12] ;laden den wert von to auf eax
	mov esp, [eax]	;setzen den neuen esp 
	
	;poppen register wieder
	pop ebx
	pop esi
	pop edi
	pop ebp

;Ende
	ret		; Ruecksprung zum Aufrufer

