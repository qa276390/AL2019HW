# Optimal Wiring Topology
## Getting Start
compile the file first,
```
make
```

## Run

### Input

The program should be invoked like this:
```
./em [input file] [output file]
```
- [input file]: The input file describes the current source S and sink T information. The first line describes the total
number sources and sinks (m+n). In the following (m+n) lines, each line indicates the x-coordinate,
y-coordinate, and flow of a current source or sink. A source/sink is associated with a
positive/negative flow.

- [output file]: The program first prints the optimal total wire area. Then, the following lines describe the optimal wiring topology. Each line indicates the x coordinate and y coordinate of a source, the x coordinate and y coordinate of a sink, and the corresponding wire width.
All lines are lexicographically sorted in ascending order of (x_source, y_source, x_sink, y_sink, width).
