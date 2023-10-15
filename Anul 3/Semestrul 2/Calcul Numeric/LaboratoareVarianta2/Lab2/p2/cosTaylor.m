function cosValue=cosTaylor(x)
  cosValue = 0;
  nextTerm = 1; %primul termen
  n=1; %rangul ultimuluui termen calculat

  %generam termeni cat timp avem o valoare reprezentabila
  while (cosValue + nextTerm) ~= cosValue
    cosValue = cosValue + nextTerm;
    nextTerm = - nextTerm * x^2 / (n*(n+1));
    n = n + 2;
  end
  