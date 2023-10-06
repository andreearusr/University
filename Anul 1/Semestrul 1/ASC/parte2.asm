bits 32

global start
extern exit,printf
import exit msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    sir1 dd 1245AB36h,23456789h,1212F1EEh
    len equ ($-sir1)/4
    
    sir2 times len db 0
    sir3 times len db 0
    
    format db "%d",0
    spatiu db " ",0
    zece db 10
    cifre times 10 db 0
    
segment code use32 class=code
start:
    
    mov ESI,sir1 
    mov EDI,sir2
    mov ECX,len
    ;jecxz final
    cld 
    mov EAX,0
    bucla:
        lodsb
        lodsb; AL<-octetul bun
        mov DL,AL
        
        cmp AL,0
        jg aici
        
        stosb
        
        aici:
        add ESI,2
    loop bucla
    
    mov ESI,sir2
    cld

    repeta:
        lodsb   ;AL<-primul octet
        cmp AL,0
        je final 
            mov ECX,8
            repeta2:
        
            shl AL,1 
            jc afisare
            
            pushad  
            mov EAX,0
            push dword EAX
            push dword format
            call [printf] 
            add ESP,4*2
            popad 
            
            jmp aici2
        
            afisare:
                pushad
                mov EAX,1
                push dword EAX
                push dword format
                call [printf] 
                add ESP,4*2
                popad
            aici2:
            loop repeta2
        pushad
        push dword spatiu
        call [printf]
        add ESP,4*1
        popad
    jmp repeta
     
    final:
    mov ECX,len
    mov ESI,sir2
    mov EDI,sir3
    cld 
    mov EAX,0
    baza10:
        push ECX 
        
        lodsb    ;AL<-primul octet din sir2
        push ESI 
        
        cmp AL,0
        jge ok
        
        mov BL,AL
        mov AL,"-"
        stosb 
        neg BL 
        mov AL,BL 
        
        ok:
            mov EDX,0
            cifre10:
                mov AH,0
                div byte[zece]    ;AL cat   AH rest
                cmp AL,0
                je out1
                
                add AH,"0"
                mov [cifre+EDX],AH
                inc EDX 
                jmp cifre10
                
        
                out1:
                    add AH,"0"
                    mov [cifre+EDX],AH
                    mov ESI,EDX 
                    dec ESI 
                    add ESI,cifre
                    mov ECX,EDX 
                    
                    mutare:
                        std 
                        lodsb 
                        cld 
                        stosb 
                        
                    loop mutare
        pop ESI 
        pop ECX 
        
        loop baza10
              
        
                
                



        
   ; final:
    push dword 0
    call [exit]
    