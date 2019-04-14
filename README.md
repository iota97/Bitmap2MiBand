##**A simple bitmap to MiBand firmware binary code converter**

Tested on Mi Band 2.

###**Limitation**

Works only with 24 BPP bitmap, if your image results corrupted please double check your Bitmap pixel depth.

Image will be cropped to get a height multiple of 8.


###**How to use**

Create a BMP image on your image editor of choise, any non black pixel (#000000) will be considered on.

Convert the BMP with this tool into a hex string.

Get a MiBand firmware (For more info take a look [here] (https://github.com/Freeyourgadget/Gadgetbridge/wiki/Mi-Band-2-Firmware-Update)).

Open it in a hex editor.

Search for the pattern of the image you want to replace (You can find some of them [here] (https://github.com/berryelectronics/miband-2-fw-editor/blob/master/MiBand2-patternsearcher/MiBand2-patternsearcher/vars.cs)).

Replace the pattern with the hex string you got from the image conveter.

Flash the new firmware (You can use [this] (https://github.com/Freeyourgadget/Gadgetbridge)).

###**License and disclaimer**

All the source are under the **BSD 3-clause** license.

Beware that flashing the Mi Band might cause a brick, I take no responsability for any issues that might happen, do it at your own risk.
