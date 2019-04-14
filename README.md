# **A simple bitmap to MiBand firmware binary code converter**

Tested on Mi Band 2.

## **Limitation**

Works only with 24 BPP bitmap, if your image results corrupted please double check your Bitmap pixel depth.

Image will be cropped to get a height multiple of 8.


## **How to use**

Create a BMP image on your image editor of choise, any non black pixel (#000000) will be considered on.

Convert the BMP with the bitmap2miband tool into a hex string (check Tools syntax section for more info).

Check if the result was correct with the viewer tool (check Tools syntax section for more info).

Get a MiBand firmware (For more info take a look [here](https://github.com/Freeyourgadget/Gadgetbridge/wiki/Mi-Band-2-Firmware-Update)).

Open it in a hex editor.

Search for the pattern of the image you want to replace (You can find some of them [here](https://github.com/berryelectronics/miband-2-fw-editor/blob/master/MiBand2-patternsearcher/MiBand2-patternsearcher/vars.cs)).

Replace the pattern with the hex string you got from the image conveter.

Flash the new firmware (You can use [this](https://github.com/Freeyourgadget/Gadgetbridge)).

## **Tools syntax**

### **bitmap2miband**

bitmap2miband */path/to/image.bmp*

You can use stream operator to write the output to a file as follow:

bitmap2miband */path/to/image.bmp* > */path/to/text_file.txt*

### **viewer**

viewer *hex_string* *starting_line_lenght(optional)*

If *starting_line_lenght* is omitted it will be set to 1.

#### **Controls**:

*Enter* - Increase/decrease line lenght.

*S* - Switch Increase/descrease mode.

*Q* - Exit the tool.


## **License and disclaimer**

All the source are under the **BSD 3-clause** license.

Beware that flashing the Mi Band might cause a brick, I take no responsability for any issues that might happen, do it at your own risk.
