# I2C_IR_Sensor_On_Pi

Current efforts on porting the C# program from windows to Raspberry Pi so that I can get the interactive Harry 
Potter wands to work on a single IoT board. 

Settup:
Connect the yellow i2c sensor wire to SDA pin, green wire to SCL pin, red to 5v pin, and black wire to ground

Download the .c file contained in this repository and compile. 

This currently only prints the output data being recieved from the i2c sensor and doesn't have any real functions
yet. 

Work in progress to implement command functions for light control and voice control. 
