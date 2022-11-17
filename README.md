# ET-Lions Display

abstract
--------
While the Maschis build non working rockets out of shopping karts,
ETis build flashy working LED matricies.

This won't help our inferior players win anything but at least we look cool while losing.


hardware design
---------------
To keep production both cheap and light in manual labor, the display is
split up into 100mm*100mm PCBs that are relatively cheap to manufacture.
We used JLCPCB for this effort as they are by far the cheapest on the market and broke
students don't have money for pcbway. We also used their assembly services to put the
5 * 5 LEDs per board onto the boards by pick&place.. otherwise we would have had to
solder 1250 LEDs by hand..

The general layout of the PCB is very modular, there are power lines that connect
the 5V and Ground of all PCBs and Data in/ outputs on all 4 sides that make it easy
to route the signal wherever it needs to go.
