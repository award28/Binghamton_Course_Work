def gcdI(i, j)
	while i != j do
		if i > j
			i = i - j
		else
			j = j - i
		end
	end
	return i
end


def gcdF(i, j)
	  return j if !(i % j)
		return gcdF(j, i % j)
end


if ARGV.length != 2 
	  puts "gcd_full.rb usage: [I] [J]" 
		  exit
end

puts gcdI(ARGV[0].to_i, ARGV[1].to_i)
