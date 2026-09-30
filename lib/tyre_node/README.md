# Tyre node library

Code specific to the tyre temperature nodes.

## Planned modules

- `mlx90640_reader.h` / `mlx90640_reader.cpp` - MLX90640 sensor initialisation and pixel array reading
- `band_averager.h` / `band_averager.cpp` - inner, middle, outer band temperature averaging
- `tyre_isolator.h` / `tyre_isolator.cpp` - identify which pixels are on the tyre surface vs bodywork
- `brake_rejector.h` / `brake_rejector.cpp` - reject hot pixels that are the brake disc, not the tyre
