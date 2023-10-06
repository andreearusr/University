bits 32

global start
extern exit,printf,scanf,fopen,fclose,fprintf,fscanf
import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll
import fscanf msvcrt.dll

segment data use32 class=data

    nume times 100 db 0
    caracter dd 0
    n dd 0
    mesaj1 db "Dati numele fisierului: ",0,10
    mesaj2 db "Caracter special: ",0,10
    mesaj3 db "Numar: ",0
    
    format db "%s",0
    format1 db "%d",0
    format2 db "%s",0
    format3 db "%s ",0
    format4 db "%c",0
    
    mod_acces db "r",0
    descriptor_fis dd -1
    
    nume_fisier db "output.txt",0
    mod_acces1 db "w",0
    descriptor_fisier dd -1
    
    max_cuv equ 100
    cuvant times 50 db 0
    contor dd 0
    numarare dd 0


segment code use32 class=code
start:
    
    push dword mesaj1
    call [printf]
    add ESP,4*1
    
    push dword nume 
    push dword format2 
    call [scanf]
    add ESP,4*2
    
    push dword mesaj2
    call [printf]
    add ESP,4*1
    
    push dword caracter
    push dword format
    call [scanf]
    add ESP,4*2
    
    push dword mesaj3
    call [printf]
    add ESP,4*1
    
    push dword n
    push dword format1 
    call [scanf]
    add ESP,4*2
    

    push dword mod_acces
    push dword nume
    call [fopen]
    add ESP,4*2
    
    cmp EAX,0
    je final
    mov [descriptor_fis],EAX
    
    
    push dword mod_acces1
    push dword nume_fisier
    call [fopen]
    add ESP,4*2
    
    cmp EAX,0
    je final
    mov [descriptor_fisier],EAX
    

    bucla:
        
        push dword cuvant
        push dword format
        push dword [descriptor_fis]
        call [fscanf]
        add ESP,4*3
        
        
        cmp EAX,1
        jne cleanup
        
        
        
        push dword cuvant
        push dword format3
        call [printf]
        add ESP,4*2
        
         

        mov ESI, cuvant
        cld 
        mov EDX,dword[n]
        repeta:
            mov EAX,0
            lodsb   ;AL<- primul caracter
            cmp AL,0
            jne afisare
            
            
            cmp dword[numarare],EDX
            jb scrie3
            
            afisare:
                inc dword[numarare]
                cmp dword[numarare],EDX
                jb scrie
                je scrie2
                
   
                scrie:
                
                    push dword EAX
                    push dword format4
                    push dword [descriptor_fisier]
                    call [fprintf]
                    add ESP,4*3
                jmp repeta
                    
                scrie2:
                    push dword caracter
                    push dword format4
                    push dword [descriptor_fisier]
                    call [fprintf]
                    add ESP,4*3
                    
                jmp repeta
            
                scrie3:
                    mov EBX,dword[numarare]
                    sub EBX,EDX
                    mov ECX,EBX 
                    rpt:
                        push ecx 
                        push dword caracter
                        push dword format4
                        push dword [descriptor_fisier]
                        call [fprintf]
                        add ESP,4*3
                        pop ecx
                        
                    loop rpt
                    
  
        inc dword[contor] 
         
    jmp bucla
    
    
    cleanup:
    mov dword[contor],EBX
    
    push dword [descriptor_fis]
    call [fclose]
    add ESP,4*1
    
    push dword [descriptor_fisier]
    call [fclose]
    add ESP,4*1
    
    final:
   
    push dword 0
    call [exit]
        