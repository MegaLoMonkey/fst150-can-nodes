# Sensor Mounting Design

Placeholder for mechanical mounting design documentation. To be completed alongside enclosure CAD work.

## Sections to add

- Tyre node mounting: position, angle, distance to tyre surface
- Steering angle node mounting: column bracket, magnet placement
- Enclosure design considerations (heat, water, vibration)
- Field of view analysis for tyre nodes
- Suspension travel clearance requirements
- Brake heat isolation

## Design decisions to document

- Direct-above tread mounting vs sidewall view
- HDPE film or germanium window vs recessed lens
- Enclosure material (PETG, ASA, PEEK)
- Mount attachment method

## Field of view calculation

MLX90640-D55 has 55 degrees horizontal x 35 degrees vertical FOV.

At a mounting height of h millimetres above the tyre:
- FOV width = 2 * h * tan(27.5 deg)
- FOV depth = 2 * h * tan(17.5 deg)

Example at 300 mm mounting height:
- FOV width: 312 mm
- FOV depth: 189 mm

Tyre tread on FST-150 is approximately 180-200 mm wide. The tread will occupy roughly half the FOV width, giving about 16 pixels across the tread which is adequate for the 3-band average approach.
