
%1. permutarile sirului de caractere 'word'
w='word'
perms(w)

%2. perechile neordonate de cifre din vect, folosind nchoosek
v=[2 3 5 7]
nchoosek(v, 2)

%3. aranjamente de n luate cate k, ale unui vector cu n elem
function aranjamente=aranjamente(v,k)
combinari=nchoosek(v,k);
aranjamente=[ ];
for i=1:nchoosek(length(v),k)
    aranjamente=[aranjamente;perms(combinari(i,:))];
end
