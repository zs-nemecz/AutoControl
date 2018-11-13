# AutoControl
AutoControl is a client - server application, which simulates the control of a vehicle.
The application has a GUI, with which the user can send commands to the vehicle:

- Ignition On/Off
- Steering Angle
- Acceleration & Speed
- Gear
- Direction signal

The GUI also visualizes the current state of the vehicle.

GUI Lib: GTK+ 3
Client-Server protocol: TCP

Implementation plan:

1st Stage – Planning Phase
    • Select GUI Lib
    • Choose network protocol
    * Select GUI Lib
    * Choose network protocol

2nd Stage
    • Vehicle settings
        ◦ Ignition Switch
        ◦ Steering Angle Slider
        ◦ Speed Slider
        ◦ Gear Buttons
        ◦ Direction Signal Toggle Button
    • Client-Server connection
        ◦ Simple TCP connection
    • Client-Server communication
        ◦ Send settings in independent TCP packages 
    • Current vehicle state
        ◦ Simple text based visualization of the requested settings
        ◦ Direct relationship between requested setting and current state
    * Vehicle settings
        * Ignition Switch
        * Steering Angle Slider
        * Speed Slider
        * Gear Buttons
        * Direction Signal Toggle Button
    * Client-Server connection
        * Simple TCP connection
    * Client-Server communication
        * Send settings in independent TCP packages 
    * Current vehicle state
        * Simple text based visualization of the requested settings
        * Direct relationship between requested setting and current state

3rd Stage
    • Vehicle settings
    • Client-Server connection
        ◦ Establish heartbeat signal
    • Client-Server communication
        ◦ CRC implementation
    • Current vehicle state
        ◦ Simulate Steering Rack Behavior
        ◦ Lag between requested speed – current speed
    * Vehicle settings
    * Client-Server connection
        * Establish heartbeat signal
    * Client-Server communication
        * CRC implementation
    * Current vehicle state
        * Simulate Steering Rack Behavior
        * Lag between requested speed – current speed
