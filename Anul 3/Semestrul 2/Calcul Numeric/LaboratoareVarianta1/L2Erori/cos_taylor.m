%cos taylor
function s = cos_taylor(xx)
  % reducere la primul cadran
  [x, sin_sign, cos_sign] = reducere_la_primul_cadran(xx);

  s = 0; %suma termenilor
  t = 1; %primul termen
  n = 0;
  while s + t ~= s
      n = n + 1;
      s = s + t;
      t = (-1)^n * ((x^(2*n)) / (factorial(2*n)));
  end
  s = cos_sign * s
end
