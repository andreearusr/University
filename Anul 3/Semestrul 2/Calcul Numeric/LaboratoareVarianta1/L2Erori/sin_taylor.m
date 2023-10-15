%sin taylor
function s = sin_taylor(xx)
  % reducere la primul cadran
  [x, sin_sign, cos_sign] = reducere_la_primul_cadran(xx);

  s = 0; %suma termenilor
  t = x; %primul termen
  n = 1;
  while s + t ~= s
      s = s + t;
      t = -t * x^2 / ((n+1)*(n+2));
      n = n + 2;
  end
  s = sin_sign * s;
end
