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
[SECTION .text]
global  getDivisorCount

getDivisorCount:
	push	ebp
	mov	ebp, esp

;add code from here
  mov edx, 0 ;leert edx

  mov ebx, 0 ;zählt teiler
  mov eax, [esp+8]
  mov ecx, eax ;setzt ecx auf den wert von eax
  
  schleife: mov eax, [esp+8] ;gibt eax wen wert vom stackpointer
            div ecx ; teilt eax durch ecx
            cmp edx, 0 ;prüft, ob rest der division = 0 ist
            je schleife2 ;springt in schleife2 wenn ja
            cmp ecx, 0 ;verhindert teilen durch 0
            je end ;wenn ecx 0, wird zum ende gesprungen
            mov edx, 0 ;leert das edx register
            loop schleife ;führt die schleife von neuem aus
          
  schleife2: add ebx, 1 ;wenn teiler, dann 1 addiert
             dec ecx ;dekrementiert ecx um 1
             cmp ecx, 0 ;verhindert teilen durch 0
             je end ;wenn ecx 0, springe zum ende
             mov edx, 0 ;leert das edx register
             jmp schleife ;springt zurück in die schleife
  end:
;to here
	mov eax, ebx
	xor ebx, ebx
    pop	ebp	
	ret
