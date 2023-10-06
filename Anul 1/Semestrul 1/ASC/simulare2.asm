bits 32

global start
extern exit,scanf,printf

import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data 

    mesaj db "Cuvant: ",0,10
    mesaj2 db "Numar: ",0,10
    mesaj3 db "Cuvant criptat: ",0
    cuvant times 20 db 0
    cuvant_criptat times 100 db 0
    numar dd 0
    doi db 2
    litera db "p",0
    
    sir_vocale db "aeiou"
    l equ $-sir_vocale
    
    format db "%s",0
    format_nr db "%u",0

; Se citeste de la tastatura un cuvant (sir de caract de maxim 20 caract) si un nr reprezentat pe un octet.
; daca nr par => criptarea cuvantului prin adunarea la fiecare caracter a numarului 20
; daca nr impar => criptarea cuvantului prin adaugarea dupa fiecare vocala a gruparii "p"+vocala
; +afisarea cuvantului criptat 

; ex: cuvant:arici numar:2 => u?}w}
; cuvant:arici numar:3 => aparipicipi
segment code use 32 class=code
    start:
    
        push dword mesaj
        call [printf]
        add ESP,4*1
        
        push dword cuvant
        push dword format
        call [scanf]
        add ESP,4*2
        
        push dword mesaj2
        call [printf]
        add ESP,4*1
        
        push dword numar
        push dword format_nr
        call [scanf]
        add ESP,4*2
        
        mov EAX,0
        mov AL, byte[numar]
        mov DL,AL  ; in DL avem numarul reprezentat pe un octet
        
        div byte[doi]  ; AL cat   AH rest
        cmp AH,0
        je criptare1
        jne criptare2
        
        
        criptare1:
            mov ESI,cuvant
            mov EDI,cuvant_criptat
            cld
            
            repeta:
                LODSB   ;AL <- primul caracter
                cmp AL,0
                je cleanup
                
                add AL,20
                STOSB
                
            jmp repeta
            
            
        criptare2:
            mov ESI,cuvant
            mov EDI,cuvant_criptat      
            cld
            
            repeta2:
                LODSB   ;AL <- primul caracter
                cmp AL,0
                je cleanup
                mov DL,AL
                mov EBX, 0
                
                repeta3:
                    
                    mov CL, byte[sir_vocale+EBX]
                    
                    cmp CL,0
                    je cont
                    
                    cmp DL,CL
                    je continua
                    
                    inc EBX
                    
                jmp repeta3
                    
                
                continua:
                    STOSB
                    mov AL, byte[litera]
                    STOSB 
                    
                    mov AL,DL
                ;    dec ESI 
                    STOSB 
                ;    inc ESI
                jmp repeta2

                    
                cont:
                    STOSB
                
            jmp repeta2
            
        cleanup:
        
            push dword mesaj3
            call [printf]
            add ESP,4*1
            
            push dword cuvant_criptat
            push dword format
            call [printf]
            add ESP,4*2
        
        
        

    push dword 0
    call [exit]