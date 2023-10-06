bits 32

global start
extern exit,printf,scanf,fopen,fclose,fprintf
import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll

segment data use32 class=data
    
    numar dd 0
    format db "%c",0
    format1 db "%u ",0
    
    sir times 100 dd 0
    doi dw 2
    
    mod_acces db "w",0
    nume_fisier db "simulareASC.txt",0
    descriptor_fis dd -1
    
    contor dd 0
    
segment code use32 class=code 
start:


    push dword mod_acces
    push dword nume_fisier
    call [fopen]
    add ESP,4*2
    
    cmp EAX,0
    je final 
    
    mov [descriptor_fis],EAX
    
    mov EDI,sir 
    cld
    
    bucla:

        push dword numar
        push dword format
        call [scanf]
        add ESP,4*2
        
        mov EAX,[numar]
        cmp EAX,"!"
        je transforma 
        
        
        mov AX,word[numar]
        mov DX,0
        
        div word[doi]   ; AX cat   DX rest
        cmp DX,0
        je aici
        
        mov EAX,[numar]
        STOSD
        inc dword[contor]
      
       aici:
    jmp bucla 
    
    transforma:
        mov ECX,dword[contor]
        dec ECX
        mov ESI,0 
        cld 

        repeta:
            mov EAX,0
            mov EBX,[sir+ESI]  
            mov EDX,[sir+ESI+4] 
      
            cmp EBX,EDX 
            jb next 
            
            mov [sir+ESI],EDX 
            mov [sir+ESI+4],EBX 
            
            next:
            add ESI,4
        loop repeta 
        
        
    mov ESI,sir
    mov ECX,dword[contor]
    
    rpt1:
        mov EAX,0
        lodsd 
        
        push ecx
        push dword EAX 
        push dword format1 
        call[printf]
        add ESP,4*2
        pop ecx 
        
    loop rpt1
    
    
    
    push dword [descriptor_fis]
    call [fclose]
    add ESP,4*1
    
    final:
    
    push dword 0
    call [exit]
    