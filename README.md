# Obd-Bluetooth
## OBD Physical
![examples](/images/obd2_samping.jpg) 
## Step TODO List
0. [x] Cofigure the bluetooh connection
0. [x] Set Obd to manufacture default
0. [x] Reset OBD or Check OBD Version
0. [x] Set communication protocol
0. [x] Get protocol OBD
0. [x] Get battery OBD
0. [ ] Save the Battery Value
0. [ ] Save the Speed Value
0. [ ] Save the Coolant Temperature Value
0. [ ] Save the Engine Load Value
### Configure Bluetooth in Order
0. ``AT`` test AT Command of HC-05.
0. ``AT+RESET`` Set to first initialization, this command does'nt set to default from manufacture.
0. ``AT+NAME=MATADOR-TRACKING`` set name to the device.
0. ``AT+ROLE=1`` set the role as ``MASTER``.
0. ``AT+CMODE=0`` set mode to fixed device address, in this case only one connection. But if this device is changed the mode to ``1``, it will can connect to any address.
0. ``AT+BIND=0000,00,111111`` save the object connection.
0. ``AT+INIT`` Initializing to Serial Port Protocol.
0. ``AT+PAIR=0000,00,111111,20`` pair to the slave object, OBDII.
0. ``AT+LINK=0000,00,111111`` connect to the device that previously paired.
0. finished, this connection like two wires as ``tx`` and ``rx``.
## OBD Configuring
0. ``AT D`` set obd to manufacture default
0. ``AT Z`` resetting and get version of OBD
0. ``AT SP <VALUE>`` Set communication protocol, in this project set ``0`` to switch ``AUTO`` protocol
0. ``AT DP`` Show the OBD protocol
0. ``AT RV`` Show the value of battery's vehichle.
## Additional for STATUS HC-05
0. ``AT+STATE`` will respone ``+STATE:INITIALIZED`` until ``AT+INIT``.
0. if the respone ``+STATE:INQUIRING`` it means that the device has done ``AT+INQ`` and ``AT+INQM=<mode>,<amount device>,<interval timeout>``
0. it will respone ``+STATE:PAIRING`` when HC-05 configured to ``AT+PAIR=<****,**,******>,<interval timeout>``. To unpair the device, command ``AT+RMAAD`` or ``AT+RESET``. In ``RESET`` condition, the device will give state in ``INITIALIZED``.
