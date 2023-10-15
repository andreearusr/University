%1. 5r, 3a, 3v. se extrag 3 bile fara repunere
% A: cel putin o bila extrasa este rosie
function PA=simulare_i(N=5000)
PA=0;
urn=['r','r','r','r','r','b','b','b','g','g'];
for rep=1:N
    balls=randsample(urn,3); % 3 el -> fara returnare=replacement=false(implicit)
    if balls(1)=='r'||balls(2)=='r'||balls(3)=='r'
        PA++;
    end
end
PA=PA/N;