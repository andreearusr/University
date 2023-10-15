function sinValue = sinTaylor(x)  
  sinValue = 0;
  nextTerm = x; %primul termen
  n = 1; %rangul ultimuluui termen calculat

  % generam termeni cat timp avem o valoare reprezentabila
  while (sinValue + nextTerm) ~= sinValue
    sinValue = sinValue + nextTerm;
    nextTerm = (- nextTerm * (x^2)) / ((n + 1)*(n + 2));
    n = n + 2;
  end
  
  