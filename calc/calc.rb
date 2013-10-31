def add(args)
	puts args.reduce(:+)
end

def subtract(args)
	puts args.reduce(:-)
end

def multiply(args)
	puts args.reduce(:*)
end

def divide(args)
	puts args.reduce(:/)
end

def dispatch(command, args)
	mapping = {
		"add" => method(:add),
		"subtract" => method(:subtract),
		"multiply" => method(:multiply),
		"divide" => method(:divide),
	}
	mapping[command].(args)
end


while true
	sentence = gets
	words = sentence.split
	command = words[0]
	arguments = words.drop(1).map(&:to_f)
	puts "Filtered: " + command.to_s + " " + arguments.map(&:to_s).join(" ")
	begin
		dispatch command, arguments
	rescue Exception=>e
		puts "Error!!!"
	end
end
