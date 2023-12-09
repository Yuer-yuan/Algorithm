# Seam Carving
> [specifications](https://coursera.cs.princeton.edu/algs4/assignments/seam/specification.php)
- energy
  - that of a pixel represents its importance
  - $dual gradient$ energy function -- simple to implement
    - $E(x,y) = \sqrt[2]{\Delta_x^2(x, y) + \Delta_y^2(x, y)}$
    - $\Delta_{a}^2 = R_{a}^2 + G_{a}^2 + B_{a}^2, a \in \{x, y\}$
  - those of edge pixels are set to $1000$ which is strictly larger than that of any pixel
- seam
  - a vertical (or horizontal) path in which difference of $x$ (or $y$) between injected pixels is at most $1$
