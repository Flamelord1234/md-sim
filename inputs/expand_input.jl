module buildInfiles
using Printf
export buildInfile;

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

# Creates an infile for given simulation sidelen, with same density as liquid256
#
# parameter - sidelen: length of simulation box side
# parameter - N: number of particles
# returns: filename of o
function buildInfile(sidelen, N)
    if N == 256 || N == 2048 return end
    positions = rand(Float64, (N,3)) .* sidelen;

    output = @sprintf("%f\n", sidelen);
    for i = 1:N
        output *= @sprintf("%s\n", sprint(show, positions[i,:])[2:end-1])
    end

    outfile = @sprintf("inputs/liquid%d.txt", N)
    write(outfile, output)
    return outfile
end
end