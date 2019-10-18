# Arduino Development


## Setup
1. Install [VS Code](https://code.visualstudio.com/download) 
2. Install [Arduino IDE](https://www.arduino.cc/en/main/software#download) 
    - recommended versions 1.8.6 or 1.8.8
    - In case the Arduino IDE does not open you need to give permission at _Settings > Security & Privacy > General_
3. Install Extention For Arduino _vsciot-vscode.vscode-arduino_ and restart
4. ```CMD + SHIFT + P``` _Arduino: initialize_
    - Fix missing inlcudes [github issue](https://github.com/microsoft/vscode-cpptools/issues/2610)
        - Add to c_ccp_properties.json:includePath 
            - "/Applications/Arduino.app/Contents/Java/hardware/tools/avr/**"
            - "${workspaceFolder}/**"
        - Add define ```"defines": ["USBCON"]```
    

## Development 
1. ```CMD + SHIFT + P``` > _Arduino: Select Serial_ and select the usbPort
2. ```CMD + SHIFT + P``` > _Arduino: Change Baud Rate_ to be 9600
3. Develop the code
4. ```CMD + SHIFT + P``` > _Arduino: Upload_ 
