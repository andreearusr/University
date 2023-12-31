%semn + exponent deplasat + semnificant

function rez = reprezentare(x)
  if isa(x, 'single')
    precizie = 32;
  else
    precizie = 64;
  end

  %disp("precizie");
  %disp(precizie);

  result = '';
  repr_byte = typecast(x, 'uint8');
  for i = length(repr_byte):-1:1
    byte = repr_byte(i);
    binary = dec2bin(byte);
    bin_str = num2str(binary);

    while length(bin_str) < 8
        bin_str = strcat('0', bin_str);
    end
    result = strcat(result, bin_str);
  end

  if precizie == 32
    rez = strcat(result(1), '-', result(2:9), '-', result(10:32)); % 1bit+ 8biti + 23biti = 32biti
  else
    rez = strcat(result(1), '-', result(2:12), '-', result(13:64)); % 1bit+ 11biti + 52biti = 64biti
  end

end
