[Back to Accessible Spinner Homepage](index.md)
# Instructions for a DIY Accessible Spinner
To make the accessible spinner, we sourced parts from our local hardware store and some online stores. With access to some common makerspace tools and our instructions, we hope you will enjoy creating this toy! Feel free to modify and make improvements as well. We've included rationale for each material choice in case you're curious about whether a particular part can be exchanged or modified. Prices are all approximate and may vary depending on source.
# Materials
## Box and Wheel
Material | Purchasing | Rationale | 
------------ | ------------- | -------------
4 foot by 8 foot sheet of half inch rigid foam insulation | $15 at your local home improvement store. | We use this foam because it is lightweight and durable. Should a student throw the spinner, hopefully the spinner will not be damaged, nor will a person who is hit by the spinner when it is thrown be hurt.
Thick yoga mat in dark neutral color | $10 online or at a department store. | The dark color is beneficial for students with CVI. The mat provides extra cushioning for safety. The mat can be removed and wiped down or rinsed off when necessary.
Ball bearing turntable ring, "lazy susan" | $6, [we bought this hardware](https://www.amazon.com/gp/product/B0006LBVDI/ref=oh_aui_detailpage_o00_s00?ie=UTF8&psc=1) | This ensures that torque on the wheel is not entirely on the motor's axle.
Dimensional puffy paint | A few dollars online or at a craft store. | Good for tactile labels and boundaries on the spinner.
Clay, instamorph, etc. | $10 to $15 online or at a craft store | For example, used to make a handle for manually spinning the spinner, which can be attached with glue or velcro to spinner faces.
Velcro tape | $7 craft stores, online, hardware stores | We used velcro to attach the yoga mat cover, the faces to the wheel, secure interior components so they can be repaired, etc.
3D Printed parts | A few dollars with access to a 3D printer. Try a local library, makerspace, office supply, or school. | Lightweight and replaceable.
Bolts: We used six size 8-32, 0.75 inch long bolts with nylock nuts | A few dollars at a hardware store | removeable and replaceable, durable.
Optional Screws: We used 1 inch long wood screws to secure the bottom piece of insulation foam | A few dollars at a hardware store | Removeable and replaceable, durable.

## Electrical System
Material | Purchasing | Rationale | 
------------ | ------------- | -------------
Small vibration motors | [$10 for 10 motors on amazon](https://www.amazon.com/gp/product/B076ZS77T1/ref=oh_aui_detailpage_o00_s00?ie=UTF8&psc=1) | Provide non-visual, non-auditory feedback about what the spinner is doing.
Small Neodymium magnets | buy online, at hardware or electronics stores, or office supply | We use magnets around the edge of the spinner so that a sensor can notice when the wheel is spinning.
Hall effect sensor | $2 [adafruit hall effect sensor](https://www.adafruit.com/product/158) | This senses magnets so we know when the wheel is spinning and how fast. We can then translate this into non-visual feedback for the user.
Motor, either 2.5-6 volt or 6-24 volt | A few dollars at electronics stores or online. | The motor spins the spinner when activated by an access switch.
3.5 millimeter mono jack | $2 at electronics store or online | This is the jack that most access switches plug into.
Portable phone charger | $10 to $20 online  | We use this as a rechargeable battery to power the spinner.
USB cables | a few dollars | used to power the arduino and shields
Arduino Uno | $20 online | the brains of the operation 
Arduino motor shield | $10 to $20 online | protects the arduino from the motors
Arduino wave shield | $22 online (adafruit) | manages the audio feedback
small speaker | $2 online (adafruit) | The speaker provides audio feedback as the spinner spins.
SD card (very little storage needed) | a few dollars online | used to store the sound files
Insulated wire | a few dollars at electronics or hardware stores or online | a few feet in three or four colors lets us wire the spinner and distinguish between power, ground, and other, for ease of troubleshooting.
Resistors: One 100,000 ohm resistor and one 100 ohm resistor | A few cents online or at electronics stores | particular resistors may vary depending on specific electrical components used.
mini breadboard or protoboard and solder | a few dollars online | used for various circuits
