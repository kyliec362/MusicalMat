# MusicalMat
Java applet code and Arduino code for musical mat project

Project Overview

The code supplied in this repository is part of a musical mat project. The musical mat is similar to a Dance Dance Revolution (DDR) mat in function, but differs in hardware. DDR mats use mechanical switches to detect input while my musical mat uses inductive sensing. I used LC circuit along with the LDC1614 Texas Instrucments board (http://www.ti.com/tool/ldc1614evm) to detect input. The board registers can be written to and read using an Arduino; I used the Arduino Micro for my project. The Arduino program simulates keyboard presses in response to different mat inputs, and the Java code uses listeners to listen for keyboard input. When specific keys are "pressed", the Java code plays a corresponding piano note. 

