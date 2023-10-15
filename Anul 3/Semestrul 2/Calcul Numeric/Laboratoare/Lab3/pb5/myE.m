% pentru a-l gasi pe e, trebuie sa pornim de la un termen cuprins intre 0 si 1/(n+1)
% bazandu-ne pe formula recursiva, deducem primul termen
% putem repeta acest algoritm cat timp diferenta dintre 2 termeni consecutivi este mai mare decat eroarea data la intrare
function e = myE(err)
    n = 1;
    eroare = realmax();

    while eroare > err
        n = n + 1;
        en = 1 / (2*(n+1)); 

        for i = n:-1:2
           en = (1-en) / i;
        end

        e1 = 1 / en;
        enp = 1 / (2*(n + 2));

        for i = n:-1:2
           enp = (1-enp) / i;
        end

        e2 = 1 / enp;
        eroare = abs(e2-e1) / e2;
    end
    e = e2;
end