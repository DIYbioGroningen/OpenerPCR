# H bridge

The Pelter elements needs direct current. The direction of that current determines if a Peltier side cools or heats. The OpenerPCR needs to be able to let the Peltier cool and heat, so the current through the Peltier needs to be reversed. An H bridge can be used to achieve this.

There are multiple ways to create an H bridge: amongst others, using relays and using transistors. For the OpenerPCR project we chose to use relays (for now).

```
Signal
  |
+-+--+
|    |
|    A-  
|    |
|    B-
|    |
|    C-
|    |
+-+--+
  |
 GND
```