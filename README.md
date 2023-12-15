**Usage:**
```console
gcc -O3 -o md src/*.c
./md <run name>
```
Windows:
```
gcc -pthread -O3 -o md src/util.c src/domains.c src/drag.c src/energies.c src/forces.c src/momentums.c src/positions.c src/pressure.c src/temperature.c src/velocities.c src/md.c src/main.c

./md.exe <run name>
```
where the input positions are located at `inputs/<run name>.txt` and the output will be placed at `outputs/<run name>.xyz`.

NOTE: input file format has been changed, one line has been inserted that has the
PBC sidelength (also the simulation bound, or twice the side of each box)