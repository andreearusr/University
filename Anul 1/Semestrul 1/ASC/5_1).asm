bits 32
global maximul


segment code use32 class=code public
maximul:
    ;[ESP]<- adresa de revenire
    ;[ESP+4]<-adresa sirului sir
    ;[ESP+8]<-valoarea contorului
    mov DL,1
    bucla:
        cmp DL,0
        jz final2
        mov DL,0
        mov ESI,[ESP+4]
        mov ECX,[ESP+8]
        dec ECX
        jecxz final2
        cld 
    
        bucla2:
            mov AL,[ESI]
            mov BL,[ESI+1]
            cmp AL,BL 
            jle next 
            
            mov [ESI],BL
            mov [ESI+1],AL
            mov DL,1
            
            next:
                inc ESI 
                
        loop bucla2
    jmp bucla    
        

    final2:
    ret
