Neopixel Advanced
=================

An advanced example showing some awesome features of Viper
and the ledstrip module.

A complex animation (a pulsating background and two "snakes" moving in opposing
directions) is performed with indipendent layers animated by threads. Before any ledstrip
update (the on() function) the layers are merged together to obtain the correct animation frame.

To avoid conflicts between threads, a lock is needed during layer modification phase.

     
tags: [Neopixel, Drivers]
groups:[Neopixel Driver]
