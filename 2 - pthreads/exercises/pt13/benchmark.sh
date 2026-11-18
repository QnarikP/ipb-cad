#!/usr/bin/env bash
#
# benchmark.sh - automate the benchmarking of a multi-threaded program (PT13 b)
#
# Usage:
#   ./benchmark.sh <program> <runs> <sleep_seconds> <min_threads> <max_threads>
#
# Example:
#   ./benchmark.sh ./exercisePT13b.exe 4 3 2 8
#   -> runs ./exercisePT13b.exe with 2,3,...,8 worker threads,
#      4 times for each number of threads, sleeping 3 s between
#      successive executions, and prints the average time per thread count.
#
# The program is invoked as:  <program> <number_of_threads>
# Execution time is measured externally (wall-clock), so the program
# itself does not need to print any timing information.

set -u
export LC_ALL=C   # make sure decimal point is "." (awk / printf)

usage() {
    echo "Usage: $0 <program> <runs> <sleep_seconds> <min_threads> <max_threads>" >&2
    echo "Example: $0 ./exercisePT13b.exe 4 3 2 8" >&2
    exit 1
}

is_uint() { [[ "$1" =~ ^[0-9]+$ ]]; }

# ---------- argument validation ----------
[ $# -eq 5 ] || usage

PROG="$1"
RUNS="$2"
PAUSE="$3"
TMIN="$4"
TMAX="$5"

if [ ! -f "$PROG" ] || [ ! -x "$PROG" ]; then
    echo "Error: '$PROG' does not exist or is not executable." >&2
    exit 1
fi
is_uint "$RUNS"  && [ "$RUNS"  -ge 1 ] || { echo "Error: runs must be an integer >= 1." >&2; exit 1; }
is_uint "$PAUSE"                       || { echo "Error: sleep must be an integer >= 0." >&2; exit 1; }
is_uint "$TMIN"  && [ "$TMIN"  -ge 1 ] || { echo "Error: min_threads must be an integer >= 1." >&2; exit 1; }
is_uint "$TMAX"  && [ "$TMAX" -ge "$TMIN" ] || { echo "Error: max_threads must be an integer >= min_threads." >&2; exit 1; }

# ---------- helpers ----------
now() { date +%s%N; }                         # current time in nanoseconds (integer)

echo "Program        : $PROG"
echo "Runs per T     : $RUNS"
echo "Sleep between  : ${PAUSE}s"
echo "Threads range  : $TMIN .. $TMAX"
echo "Host / CPUs    : $(hostname) / $(nproc)"
echo

declare -A AVG
first=1

for (( t = TMIN; t <= TMAX; t++ )); do
    sum=0
    for (( r = 1; r <= RUNS; r++ )); do
        # sleep between successive executions (not before the very first one)
        if [ $first -eq 0 ] && [ "$PAUSE" -gt 0 ]; then
            sleep "$PAUSE"
        fi
        first=0

        start=$(now)
        "$PROG" "$t" > /dev/null
        status=$?
        end=$(now)

        if [ $status -ne 0 ]; then
            echo "Warning: '$PROG $t' exited with status $status (run $r)." >&2
        fi

        dt=$(( end - start ))                 # elapsed time in ns
        sum=$(( sum + dt ))
        printf "threads=%-3d run=%-3d time=%15d ns\n" "$t" "$r" "$dt"
    done
    AVG[$t]=$(( sum / RUNS ))                 # average in ns (integer)
    printf "threads=%-3d AVERAGE  =%15d ns\n\n" "$t" "${AVG[$t]}"
done

# ---------- summary ----------
base=${AVG[$TMIN]}
echo "================ SUMMARY ================"
printf "%-8s %-16s %-10s\n" "Threads" "Avg time (ns)" "Speedup*"
for (( t = TMIN; t <= TMAX; t++ )); do
    sp=$(awk -v b="$base" -v a="${AVG[$t]}" 'BEGIN { printf "%.2f", (a > 0) ? b / a : 0 }')
    printf "%-8d %-16d %-10s\n" "$t" "${AVG[$t]}" "$sp"
done
echo "* speedup relative to $TMIN thread(s)"
