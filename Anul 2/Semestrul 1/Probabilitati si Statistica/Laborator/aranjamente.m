function result = aranjamente(v, k)
  combinations = nchoosek(v, k)
  result = [];
  for row = 1:rows(combinations)
    result=[result; perms(combinations(row,:))];
  endfor
  result = sortrows(result);
endfunction

  
  
  
