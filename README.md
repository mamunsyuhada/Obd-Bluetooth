# Obd-Bluetooth
## OBD Physical
![examples](/images/obd2_samping.jpg) 
## Step TODO List
### [x] Cofigure the bluetooh connection
### [ ] Communicatin with obd
0. [ ] Save the RPM Value
0. [ ] Save the Battery Value
0. [ ] Save the Speed Value
0. [ ] Save the Coolant Temperature Value
0. [ ] Save the Engine Load Value
## STATUS HC-05
0. ``AT+STATE`` will respone ``+STATE:INITIALIZED`` until ``AT+INIT``.
0. if the respone ``+STATE:INQUIRING`` it means that the device has done ``AT+INQ`` and ``AT+INQM=<mode>,<amount device>,<interval timeout>``
0. it will respone ``+STATE:PAIRING`` when HC-05 configured to ``AT+PAIR=<****,**,******>,<interval timeout>``. To unpair the device, command ``AT+RMAAD`` or ``AT+RESET``. In ``RESET`` condition, the device will give state in ``INITIALIZED``.
