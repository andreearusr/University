% A: cel putin o bila extrasa este rosie
% B: toate bilele extrase au aceeasi culoare
% => A si B : toate 3 rosii

function PAB=simulare_ii(N=5000)
PAB=0;
urn=['r','r','r','r','r','b','b','b','g','g'];
for rep=1:N
    balls=randsample(urn,3);
    if balls(1)=='r'&& balls(2)=='r'&&balls(3)=='r'
        PAB++;
    end
end
PAB=PAB/N;