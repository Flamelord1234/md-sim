include("../inputs/expand_input.jl"); include("benchmark.jl")
using .BuildInfiles, .BenchmarkParallelCode, Printf

function main()
    numtests = 2 # parallel should only pick up past 2
    sidelens = range(10.2, step=3.4, length=numtests)
    data = zeros(length(sidelens), 3)
    output = "";
    for i = eachindex(sidelens)
        bench = runTest(sidelens[i])
        data[i,:] = bench
        output *= @sprintf("%s\n", sprint(show, bench)[2:end-1])
    end

    outfile = @sprintf("benchmarking/test%d.txt", i)
    write(outfile, output)
end

main()


# USAGE
# drag relevant executables into the benchmarking folder
# rename files in `benchmark.jl->runTest` to match the executables
# run this file from the command line using `julia run_all_tests.jl`.