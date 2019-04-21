# Paint Bucket
## Getting Start
compile the file first,
```
make
```

## Run

### Input

The program should be invoked like this:
```
./paintBucket [image*.in] [x] [y] [color] [image*.out]
```
- [image*.in]: The input image file. This file has h + 1 lines. two integers w and h, which specify the size of the image (w*h). In the following h lines, each
line has w characters (from 0 to F), indicates the color of each pixel from the upper left corner to the bottom right corner on the image.

- [x]: An integer to specify the x-coordinate of the selected pixel. x = 0 means the leftmost column.
(0 ≤ x < w)
- [y]: An integer to specify the y-coordinate of the selected pixel. y = 0 means the first (uppermost) row. (0 ≤ y < h)
- [color]: An character to indicate the color to fill. (0 ~ 9 and A ~ F)
