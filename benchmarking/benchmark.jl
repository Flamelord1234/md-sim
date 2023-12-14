module BenchmarkParallelCode
include("../inputs/expand_input.jl")
using Dates, .buildInfiles
export runTest

# converts a DateTime object to seconds
# note: only goes up to days because i am not running these tests across separate months
function getseconds(t::DateTime)
    return ((day(t)*24 + hour(t))*60 + minute(t))*60 + second(t) + 0.001*millisecond(t)
end

# times running a given line of shell code
#
# parameter - cmd: shell command to run
# return: runtime in seconds
function timeRun(cmd)
    tic = getseconds(Dates.now())
    run(cmd)
    toc = getseconds(Dates.now())
    return toc - tic
end

# Runs both tests for a sidelength, and then returns data as a row array
#
# parameter - sidelen: sidelen for test to run (may change)
# return: row vector of [(num particles) (sequential runtime) (parallel runtime)]
function runTest(sidelen)
    # note: we can change which one we give as input
    # current formula matches density of liquid{256,2048}
    N = Int(round(256 * (sidelen / 6.8)^3));
    infile = buildInfile(sidelen, N)

    # CHANGE THESE BASED ON SYSTEM -- win should have ./md.exe, mac has ./md
    parallelCmd = `./md-parallel.exe $infile`
    sequentialCmd = `./md-sequential.exe $infile`
    
    tpar = timeRun(parallelCmd)
    tseq = timeRun(sequentialCmd)
    return [N tseq tpar]
end
end