bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
        s dd 12345678h, 1A2C3C4Dh, 98FCDC76h
        len_s equ ($-s)/4
        d times len_s db 0
        len_d dw 0
        zece db 10
        cifre db 0,0,0
        len_cif db 0

; our code starts here
segment code use32 class=code
    start:
        ; ...Se da un sir de dublucuvinte. Sa se obtina sirul format din octetii inferiori ai cuv superioare
        ; din elementele sirului de dublucuvinte care sunt palindrom in scrierea in baza 10
        mov ESI,s
        mov EDI,d 
        cld
        mov ECX, len_s
        jecxz sfarsit
        
        repeta1:
            lodsw
            lodsb
            mov AH,0
            push EDI 
            mov EDI,cifre
            mov BL,AL
            repeta2:
                div byte[zece]
                ROR AX,8
                inc byte[len_cif]
                mov AH,0
                cmp AL,0
            jne repeta2
            
            pop EDI
            mov AL,BL
            cmp byte[len_cif],2
            jb caz1
            je caz2
            ja caz3
            caz1:
                jmp palindrom
            jmp sf_cazuri
            caz2:
                mov BL, [cifre]
                cmp BL,[cifre+1]
                je palindrom
                jne not_palindrom
            jmp sf_cazuri
            caz3:
                mov BL,[cifre]
                cmp BL,[cifre+2]
                je palindrom
                jne not_palindrom
            
            sf_cazuri:
                palindrom:
                    stosb
                    inc word[len_d]
                not_palindrom:
                    mov byte[len_cif],0
                    lodsb
        loop repeta1
        sfarsit:
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
