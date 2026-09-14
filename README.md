# FdF

[English](./README.md) | [한국어](./README.ko.md)

A wireframe terrain visualizer implemented in C with MiniLibX.  
The program reads height and color data from a rectangular `.fdf` map, converts the data into projected screen coordinates, and connects adjacent points with color-interpolated line segments.

![FdF demo](./video.gif)

## 1. Features

- Parsing of rectangular height maps from `.fdf` files
- Optional hexadecimal color values for individual points
- Fixed isometric-style projection from map coordinates to screen coordinates
- Scale reduction when projected coordinates exceed the 1000 × 800 window
- Line rasterization for horizontal and vertical neighbors using Bresenham's algorithm
- RGB interpolation along line segments
- Validation for argument count, file extension, file opening, and rectangular map shape
- Resource cleanup when exiting with `Esc`

## 2. Rendering Pipeline

The program separates map processing from pixel rendering:

1. Read the file line by line with `get_next_line`.
2. Split each row into height/color tokens.
3. Validate that every row contains the same number of points.
4. Convert the tokens into a two-dimensional array of points.
5. Apply the projection and move negative coordinates into the visible area.
6. Reduce the projected scale if it exceeds the window dimensions.
7. Connect each point to its right and lower neighbors.
8. Write the resulting pixels to a MiniLibX image buffer and display the image.

## 3. Core Implementation

### Map parsing

Each token is converted into a point containing its map position, height, and color.  
When a color is omitted, the point uses white (`0xFFFFFF`).

### Projection and scale adjustment

The renderer rotates the map coordinates by 45 degrees, applies the height value to the projected vertical coordinate, and scales the result for display. Negative projected coordinates are shifted into the visible area. If the result is larger than the fixed window, a common reduction ratio is applied.

### Line and color rendering

Adjacent points are connected using separate Bresenham routines for x-major and y-major lines. While each line is rasterized, its RGB values are interpolated from the start point's color to the end point's color.

Pixels are written directly into a MiniLibX image buffer before the completed image is sent to the window.

## 4. Environment

This project targets Linux and X11.

Required tools and libraries:

- A C compiler (`cc`)
- `make`
- X11 and Xext development libraries
- zlib and a BSD compatibility library
- MiniLibX, included in `minilibx-linux`
- A custom Libft, included in `src_files/my_libft`

On Ubuntu or Debian-based systems:

```bash
sudo apt update
sudo apt install build-essential libx11-dev libxext-dev zlib1g-dev libbsd-dev
```

## 5. Build

```bash
git clone https://github.com/hoysong/fdf_fil_de_fer.git
cd fdf_fil_de_fer
make -C minilibx-linux
make
```

The build creates an executable named `fdf`.

To remove generated files:

```bash
make clean
make fclean
make re
```

## 6. Run

Pass exactly one `.fdf` map file:

```bash
./fdf test_maps/42.fdf
```

Other included examples:

```bash
./fdf test_maps/pylone.fdf
./fdf test_maps/mars.fdf
./fdf test_maps/elem-col.fdf
```

## 7. Controls

| Input | Action |
| --- | --- |
| `Esc` | Release allocated resources and exit |

## 8. Map File Format

A map consists of space-separated height values, one row per line. Every row must contain the same number of points.

```text
0  0  0  0
0  5  5  0
0  5 10  0
0  0  0  0
```

A point may optionally include a hexadecimal RGB color after a comma:

```text
0,0xFFFFFF  0,0x00FFFF  0,0xFFFFFF
0,0xFFFF00  8,0xFF0000  0,0x0000FF
0,0xFFFFFF  0,0x00FF00  0,0xFFFFFF
```

Token format:

```text
height
height,0xRRGGBB
```

Positive and negative integer heights are supported. Points without an explicit color are rendered in white.

## 9. Project Structure

```text
.
├── 01_main.c                  # Input validation, MiniLibX setup, and event loop
├── 02_get_parsed_data.c       # File reading, tokenization, and map-shape validation
├── 03_splits_to_points.c      # Height/color conversion and point creation
├── 04_iso_prjc.c              # Projection and coordinate translation
├── 05_adjust_scale.c          # Scale reduction for oversized projections
├── 06_draw_line.c             # Neighbor traversal and Bresenham rasterization
├── 07_put_pixel.c             # Line-progress and color interpolation
├── 08_put_pixel.c             # RGB channel interpolation
├── 09_free_data.c             # Parsed-data cleanup
├── 99_my_mlx_pixel_put.c      # Direct image-buffer pixel writes
├── my_fdf.h                   # Constants, structures, and function declarations
├── test_maps                  # Example FdF maps
├── src_files/my_libft         # Custom C utility library
├── minilibx-linux             # Graphics library
└── video.gif                  # Execution demo
```

## 10. Technical Focus

This project was used to practice:

- Converting structured text input into dynamically allocated data
- Applying rotation, projection, translation, and scaling to coordinates
- Rasterizing line segments without relying on a high-level graphics API
- Interpolating RGB values based on position along a line
- Rendering through an image buffer and managing graphical resources
