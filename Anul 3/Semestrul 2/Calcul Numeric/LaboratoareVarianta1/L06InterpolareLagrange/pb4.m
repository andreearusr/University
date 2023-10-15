
function pb4()
  x = [2 2.75 4];
  f = 1./x
  val = 3;

  approx = lagr(x, f, [val]);
  disp(approx); % afis aproximarea functiei in 1.25
end
