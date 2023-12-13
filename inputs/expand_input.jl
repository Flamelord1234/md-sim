using Printf

# Reads the contents of the file into an array of floats.
#
# parameter - infile: path to the file to read
# parameter - separator: separator used to separate values in infile
# returns: M-by-N array of numeric values.
function read_infile(infile)
    text = read(infile, String)
    lines = split(text, "\n")
    line1 = split(lines[1])
    out = Array{Float64}(undef, length(lines)-1, length(line1))
    for i = eachindex(lines)
        if lines[i] != ""
            vals = split(lines[i])
            for j = eachindex(vals)
                out[i, j] = parse(Float64, vals[j])
            end
        end
    end
    return out
end

# Writes data to a file.
#
# parameter - 📩: matrix of data to store
# parameter - 📭: location to store data
function write_data(📩, 📭)
    t = size(📩)[1]
    📨 = ""
    for i = 1:t
        📨 *= @sprintf("%s\n", sprint(show, 📩[i,:])[2:end-1])
    end
    write(📭, 📨)
end

# Creates an input file that consists of the original file doubled in each dim
#
# parameter - infile: path to the file to read
function main(infile)
    data = read_infile(infile)
    N = size(data)[1]
    out = Array{Float64}(undef, N*8, 3)
    for i = 0:7
        d = [(i & 0b001) ((i & 0b010) >> 1) ((i & 0b100) >> 2)] .* 6.8
        for row = 1:N
            out[row+N*i, :] = data[row, :] .+ d';
        end
    end
    
    write_data(out, "md-sim/inputs/liquid2048.txt")
end

main("liquid256.txt")