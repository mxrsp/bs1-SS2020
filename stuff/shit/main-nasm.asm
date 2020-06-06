;
;	to compile this code
;	first create an object file
;	nasm -f elf -o main.o main-nasm.asm
;
;	to create an executeable, link it
;	gcc -m32 -o run main.o
;
;	run it:
;	./run

global  getDivisorCount

[SECTION .text]

getDivisorCount:
	push	ebp
	mov	ebp, esp

;add code from here
   
   mov eax, [ebp+8] ;schiebt den wert vom 1. argument auf eax
   mov ebx, 1   ; setzt ebx auf 1(zähler)
   push eax ;pusht eax auf den stack
   mov edx, 0   ;setzt edx auf 0 damit fehler vermieden werden
   mov ecx, 0   ;setzt ecx auf 0, zählt die teiler
   
   schleife:
   cmp ebx, [ebp+8] ;prüft den aktuellen zählstand
   jg end   ;wenn ebx den wert der eingegebenen zahl erreicht hat, wird die schleife abgebrochen
   div ebx  ;teilt eax durch ebx
   cmp edx, 0   ;prüft ob der rest der divsion 0 ist
   je countup   ;wenn gleich, springe zu countup
   jne nocountup  ;wenn ungleich, springe zu nocountup
   
   countup:
   mov edx, 0   ;setzt den rest wieder auf 0
   add ecx, 1   ;inkrementiert ecx(1 teiler wurde gefunden)
   mov eax, 0   ;setzt eax wieder auf 0
   pop eax  ;der von eax ursprünglich gespushte wert landet wieder auf eax
   push eax ;setzt den wert nochmal auf den stack
   inc ebx  ;iterator wird um 1 erhöht
   jmp schleife ;springt wieder zurück in die schleife
   
   nocountup:
   inc ebx  ;iterator wird um 1 erhöht
   mov edx, 0   ;rest wird auf 0 gesetzt
   mov eax, 0   ;setzt eax wieder auf 0
   pop eax  ;der von eax ursprünglich gespushte wert landet wieder auf eax
   push eax ;setzt den wert wieder auf den stack
   jmp schleife ;springe wieder in die schleife
 
   end:
   mov ebx, 0   ;ebx wird auf 0 gesetzt
   mov edx, 0   ;edx wird auf 0 gesetzt
   mov edx, [ebp+12]    ;edx wird der pointer vom 2. argument zugewiesen(zeiger auf adresse)
   mov [edx], ecx   ;schreibt den wert von ecx(anzahl divisoren) auf die addresse von edx
;to here
    pop eax
    mov ecx, 0
    mov eax, 0
    pop	ebp	
	ret
