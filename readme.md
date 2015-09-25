### How TO

* download and install the arduino IDE: https://www.arduino.cc/en/Main/Software
* install the serial driver and hardware profile for the sparkfun pro micro as described here
   * windows: https://learn.sparkfun.com/tutorials/pro-micro--fio-v3-hookup-guide#installing-windows
   * mac: https://learn.sparkfun.com/tutorials/pro-micro--fio-v3-hookup-guide#installing-mac--linux
* download and install the DHT library: https://learn.adafruit.com/dht/using-a-dhtxx-sensor
* start your arduino IDE
* either copy and paste the code into - or open the "innovative_citizen_bot.ino" file with your IDE
* select "Sparkfun pro micro 5V / 16 MHz" from "tools/board"
* select the port connected to your pro micro from "tools/Serial port"
* set the correct pins (see comments in the code)
* hit the upload button (arrow to the right, top left toolbar)
* when the upload is done, see what your bot is doing by opening the Serial Monitor of the IDE (magnification glass, top right toolbar)


### SETUP

* Check out light sensor measurments at night and set "lichtNacht" in the code accordingly
* Check out the waterlevel in the growbed when the flood cycle is done
   * if waterlevel is to low, increase "duration" in the code
   * if waterlevel is to high, decrease "duration" in the code


### ATTENTION

* be carefull, you're playing with 220V AC and water
   * do not touch the relayboard or pump wires when you're system is plugged in
   * do not let the water overflow and short out the electronics

* if things go wrong, for example you're growbed is about to overflow/spill just disconnect the pump plug from your power outlet

### DISCLAIMER

* you alone are responisble for dead or harmed plants, fish, people, pets!
* you alone are responsible for damage to any inanimate objects!
* do not let the robot run unsupervised!
