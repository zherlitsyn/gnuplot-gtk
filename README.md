# gnuplot-gtk
A fork of gnuplot with terminal based on GTK 

![Example 0](https://github.com/zherlitsyn/gnuplot-gtk/blob/master/image0.png "Example 0")

**Animated plot**

```c
#include <unistd.h>
#include <stdio.h>
#include <math.h>

int main()
{
    FILE *gp = popen("gnuplot_gtk", "w");
    fprintf(gp, "set term gtkcairo size 642,882");

    float sinus[720];
    for(int i = 0; i < 720; i++)
        sinus[i] = sin(i * M_PI / 180);

    for(int i = 0; i < 720; i++)
    {
        fprintf(gp, "set multiplot layout 3, 1\n"
                    "plot '-' u 1:2 w line title 'sin(x)'\n");

        for(int j = 0; j < i; j++)
        {
            if(!(j % 2))
                fprintf(gp, "%i %f\n", j, sinus[j]);
        }

        fprintf(gp, "e\n"
                    "plot '-' u 1:2 w boxes ls 2 title 'sin(x)'\n");

        for(int j = 0; j < i; j++)
        {
            if(!(j % 10))
                fprintf(gp, "%i %f\n", j, sinus[j]);
        }

        fprintf(gp, "e\n"
                    "plot log(x) ls 3\n"
                    "unset multiplot\n");

        usleep(10000);
    }

    return 0;
}
```

![Example 1](https://github.com/zherlitsyn/gnuplot-gtk/blob/master/image1.gif "Example 1")

## Installation

**Build**
```
git clone https://github.com/zherlitsyn/gnuplot-gtk
cd gnuplot-gtk
make
```

**Install**

Use `checkinstall`

or

`makepkg -si`
> On Arch-based distributions

## Original repository
https://sourceforge.net/p/gnuplot/gnuplot-main/ci/master/tree/
