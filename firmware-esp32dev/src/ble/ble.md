mtu
---

ble mtu is currently requested by the app to be 1023.
it's possible to request this change as the server but there is not that much info on it
in the api

data structure
--------------

since the bitmaps are not compressed in any manner,
the bandwidth used to transfer them is quite large
every pixel takes up 3 bytes
(the 45*25 format is transmittet by the first two bytes)
besides this format, data is only pixels from top left to bottom right

with this format, there are 45*25*3+2 bytes used for one bitmap.
this is roughly 3.4kB of data. even with this big of an MTU, this data has to be split into several characteristics.
for the sake of randomness, this splitting up the data will be done into 5 characteristics, which will recieve 675 bytes each.
there is also a sixth characteristic used for "control".
is has a bit scheme for buffering an incoming matrix and then displaying the buffer once everything is transmitted. this is also where the size of the matrix is transmitted.

characteristics
---------------

- general control service
c1911100-51fd-402c-a17a-c09a33fd9c81
    - control characteristic
    c1911101-51fd-402c-a17a-c09a33fd9c81
    0: control byte
        0: on/off
        1-7: reserved

- bitmap service
c1911000-51fd-402c-a17a-c09a33fd9c81
    - control characteristic (r/w)
    c1911001-51fd-402c-a17a-c09a33fd9c81
        0: control byte (uint8)
        1: image width (uint8)
        2: image height (uint8)

    - bitmap characteristics (r/w)
        - c1911002-51fd-402c-a17a-c09a33fd9c81
        - c1911003-51fd-402c-a17a-c09a33fd9c81
        - c1911004-51fd-402c-a17a-c09a33fd9c81
        - c1911005-51fd-402c-a17a-c09a33fd9c81
        - c1911006-51fd-402c-a17a-c09a33fd9c81
        
