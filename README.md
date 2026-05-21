# Bike LED Controller
This project is sponsored by JLCPCB

<img width="310" height="162" alt="images" src="https://github.com/user-attachments/assets/635f907e-68a6-49c5-8ab6-bc3624ed3ef1" />

## Introduction
The goal of this project is to add more customizability to bike lights. When I was looking though lights for my bike I found that there was a limited amount of colors and patterns I could use. I wanted to create lights and controllers so I could have a better understanding of what was going on in the controller in terms of current consumption and speed of the bike, things that also were not present in other controllers. In this project, I designed a custom bike ring + a custom led controller board so that I could 
## Custom LED Ring
For the ring, I decided to split the base and top  of the ring into 8 seperate segments. This was due to the size of the ring being way to big for my bike & in terms of the print time & assembely ease, 8 segments seemed to do the best in those 2 categories. 

For the bottom, in order to connect the segments together, I decided to designed them so they would have a insert slot + a segment that goes into it. For the top, I ended up coating it in a layer of FLEX-SEAL in order to act as a water reppelent + a diffusior once I sanded it down to a degree. Here is one fully assmebled ring in action:

### LED Ring GIF
<img width="800" height="450" alt="ezgif-7266f13484eda068" src="https://github.com/user-attachments/assets/ef9d0f5c-7c45-4fb9-8c3e-157a56eaa6a9" />


## Custom LED Controller
For the LED contoller, I had multiple goals in mine. The main goal I had was the ability for the contoller to convert a higher voltage input to a stable 5V. To do this, I used the TPS566238RQFR buck converter to convert the input voltage (designed for 2S) into 5V. I also used a AMS1117 to convert the 5V supply into 3.3V for the digital IC's and the ESP32. Speaking of digital IC's, I used 5 in this design, a INA236 to meausre the voltage, current, & power output of the controller, a TMP117 to measure the tempature of the board / enclousre enviroment, a BMI270 to measure the speed of the bike for custom effects, a SN74LVC2T45DCUR to convert the ESP32's 3.3V logic into a usable 5V logic level for the LED, and last but not least the CP2102N to allow communication between the USB pherephial and the ESP32 via UART. Here are the schematics, PCB layouts, & the 3D view.

### Schematic
<img width="1866" height="1357" alt="Screenshot 2026-05-21 102934" src="https://github.com/user-attachments/assets/00151efb-65a4-4ce6-912d-51e49ed2e5ba" />

### PCB Layout
<img width="1222" height="892" alt="Screenshot 2026-05-21 111619" src="https://github.com/user-attachments/assets/09f5952b-3895-4173-8223-493bcacb87b6" />

### 3D View
<img width="1848" height="1177" alt="Screenshot 2026-05-21 093614" src="https://github.com/user-attachments/assets/32b05e0e-50e6-4d1c-897e-7988da2bfbc8" />
