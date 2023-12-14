include("../inputs/expand_input.jl"); using .buildInfiles;

function main()
    buildInfile(3.0, 22)
end

main()


# USAGE
# drag relevant executables into the benchmarking folder
# rename files in `benchmark.jl->runTest` to match the executables
# run this file from the command line using `julia run_all_tests.jl`.