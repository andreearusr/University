bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,printf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import printf msvcrt.dll
; our data is declared here (the variables needed by our program)
segment data use32 class=data
        a dw 1234h,5678h,90h
        len_a equ ($-a)/2
        b dw 4h,0abcdh,10h,1122h
        len_b equ ($-b)/2
        c resb (len_a+len_b)
        format db "%x",10,0
        
; our code starts here
segment code use32 class=code
    start:
        ; ...Se dau 2 siruri de cuvinte a si b. Sa se obtina sirul c astfel: 
        ; concatenati sirul octetilor low din primul sir cu sirul octetilor high din al doilea sir
        ; sirul c se va ordona crescator
        ; nr din siruri se vor interpreta cu semn
        ; afisati sirul c(numere in baza 16)
    
        mov ESI,a
        mov EDI,c
        cld 
        mov ECX,len_a
        jecxz sari
        
        sir_a:
            lodsb   ; AL<- octetul low de la adresa lui a
            stosb   ; punem in sirul destinatie octetul low 
            inc ESI
        loop sir_a
        
        sari:
        mov ESI,b
        cld 
        mov ECX,len_b
        jecxz final 
        
        sir_b:
            lodsb 
            lodsb    ; AL<- octetul high de la adresa lui b
            stosb 
        loop sir_b 
        
        final:
        mov DL,1
        repeta:
            cmp DL,0
            jz final2
            
            mov DL,0
            mov ECX, len_a+len_b-1
            mov ESI,c
        
            sir_c:
                mov AL, [ESI]
                mov BL, [ESI+1]
                cmp AL,BL
                jle urmatorul
            
                mov [ESI],BL
                mov [ESI+1],AL 
                mov DL,1
           
                urmatorul:
                    inc ESI 
            loop sir_c
        jmp repeta
        
        final2:
        
        mov ESI,c 
        mov ECX,len_a+len_b
        jecxz final3
        afisare:
            mov EAX,0
            lodsb   ; AL<- primul octet din sirul c 
            PUSHAD

            push dword EAX
            push dword format 
            call [printf]
            add ESP,4*2
            POPAD
            
        loop afisare
      
        final3:
            
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
