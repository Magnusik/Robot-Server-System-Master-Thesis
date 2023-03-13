function [leftover] = modulus(angle,arg)
%modulus function
leftover = angle - (arg*floor(angle/arg));
end

