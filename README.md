# OPTA-PROG-IR-TOAERIS

The purpose of this programming is to establish communication via Modbus with the OPTA and the Aeris IR.

In this case, we are only sending an on/off command for testing, but it is possible to include temperature control among other available functions.

The OPTA sends the ON/OFF command via Modbus to the Aeris IR and then the Aeris equipment sends this same command via IR to the air conditioner.

Remember that the Aeris equipment is configured with a Baud Rate of 34800 and address 1.

The on/off command is as follows:

10 1 - ON.
15 0 - OFF.

# We need to type exactly like this in the serial monitor to send the commands, being 10 1 or 15 0
