# SH_Simulator
Swift-Hohenberg model simulator. \
This simulator was used in our paper 
"Morikawa, K., Kuroda, D. & Inoue, Y. Impact of environmental asymmetry on epithelial morphogenesis. 
Sci Rep 12, 11326 (2022). https://doi.org/10.1038/s41598-022-15343-y"
.


## Equations ##
SH_Type0:
$$\frac{\partial w}{\partial t} = -a\Delta^2 w - b\Delta w - cw - dw^2 - ew^3$$


SH_Type1 (used in our paper):
$$\frac{\partial w}{\partial t} = -\Delta^2 w - \Delta w - \alpha(R(w - (1 - \Lambda)) - R(-w - \Lambda))$$
$$R(x) = \max(x, 0)$$

## How to make and run ##
    make

    ./SH.out <directory>

example:

    ./SH.out example_type1
