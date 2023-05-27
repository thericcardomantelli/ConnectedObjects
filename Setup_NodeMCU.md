Procedure for setting up NodeMCU.

**1. Download and install the Arduino IDE:**
   - Go to the [Arduino website](www.arduino.cc/en/Main/Software) and download the Arduino IDE (version 1.8.6 in the tutorial).

**2. Add support for ESP8266:**
   - Open the Arduino IDE.
   - Go to **File** -> **Preferences**.
   - In the Preferences window, locate the **Additional Boards Manager URLs** field.
   - Copy and paste the following link into the field: `http://arduino.esp8266.com/stable/package_esp8266com_index.json`
   - Click **OK** to confirm and close the Preferences window.

**3. Install the ESP8266 board package:**
   - Go to **Tools** -> **Board** -> **Boards Manager**.
   - In the Boards Manager window, search for "esp8266".
   - Select **ESP8266 by ESP8266 COMMUNITY** with version 2.4.2 (or the latest version available).
   - Click **Install**.

**4. Installation completed:**
   You have now successfully installed the ESP8266 board support in your Arduino IDE. You can select and program the NodeMCU using the IDE.

With this procedure, you have properly configured NodeMCU in your Arduino IDE development environment. 
