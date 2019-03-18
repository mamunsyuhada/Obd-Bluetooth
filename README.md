# Obd-Bluetooth
## OBD Physical
![examples](/images/obd-image.jpg)
Tampak Depan 
![examples](/images/obd2_samping.jpg)
Tampak Samping
## Step TODO List
0. [x] Cofigure the bluetooh connection
0. [ ] Communicatin with obd
0. [ ] Save the RPM Value
0. [ ] Save the Battery Value
0. [ ] Save the Speed Value
0. [ ] Save the Coolant Temperature Value
0. [ ] Save the Engine Load Value
## STATUS HC-05
0. ``AT+STATE`` will respone ``+STATE:INITIALIZED`` until ``AT+INIT``.
0. if the respone ``+STATE:INQUIRING`` it means that the device has done ``AT+INQ`` and ``AT+INQM=<mode>,<amount device>,<interval timeout>``
