% A: cel putin o bila extrasa este rosie
% B: toate bilele extrase au aceeasi culoare
% => A si B : toate 3 rosii
% P(A/B) = P(A si B) / P(A)

function P=simulare_iv(N=5000)
PA=0;PAB=0;
urn=['r','r','r','r','r','b','b','b','g','g'];
for rep=1:N
    balls=randsample(urn,3);
    if balls(1)=='r'||balls(2)=='r'||balls(3)=='r'
        PA++;
        if balls(1)=='r'&& balls(2)=='r'&& balls(3)=='r'
            PAB++;
        end
    end
end
P=PAB/PA;