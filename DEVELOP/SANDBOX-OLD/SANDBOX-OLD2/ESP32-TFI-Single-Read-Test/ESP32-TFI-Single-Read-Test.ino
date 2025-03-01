/*
Example code for Benewake TFMini time-of-flight distance sensor. 
by Peter Jansen (December 11/2017)
This example code is in the public domain.

This example communicates to the TFMini using a SoftwareSerial port at 115200, 
while communicating the distance results through the default Arduino hardware
Serial debug port. 

SoftwareSerial for some boards can be unreliable at high speeds (such as 115200). 
The driver includes some limited error detection and automatic retries, that
means it can generally work with SoftwareSerial on (for example) an UNO without
the end-user noticing many communications glitches, as long as a constant refresh
rate is not required. 

The (UNO) circuit:
 * Uno RX is digital pin 10 (connect to TX of TF Mini)
 * Uno TX is digital pin 11 (connect to RX of TF Mini)

THIS SOFTWARE IS PROVIDED ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE AUTHOR(S) BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  
*/

/*
 * Maple Mini
 * RX1 Pin 25, 5V tolerant -> TX TF Mini
 * TX1 Pin 26, 5V tolerant -> RX TF Mini
 */

/*
 * Bluepill
 * RX1 Pin PA10 (31), 5V tolerant -> TX TF Mini
 * TX1 Pin PA9 (30), 5V tolerant -> RX TF Mini
 */
 
#include "TFMini.h"
TFMini tfmini;

void setup() {
  // Step 1: Initialize hardware serial port (serial debug port)
  Serial.begin(115200);
  // wait for serial port to connect. Needed for native USB port only
  while (!Serial);
     
  Serial.println ("Initializing...");

  // Step 2: Initialize the data rate for the SoftwareSerial port
  Serial1.begin(TFMINI_BAUDRATE);

  // Step 3: Initialize the TF Mini sensor
  tfmini.begin(&Serial1);
  delay(100);
  
  // Step 4: Initialize single measurement mode with external trigger
  tfmini.setSingleScanMode();    
}


void loop() {
  // Take one TF Mini distance measurement
  tfmini.externalTrigger();
  uint16_t dist = tfmini.getDistance();
  uint16_t strength = tfmini.getRecentSignalStrength();

  // Display the measurement
  Serial.print("triggered - ");
  Serial.print(dist);
  Serial.print(",");
  Serial.println(strength);

  // Wait some time before taking the next measurement
  // without delay, measurement is super fast
  delay(1000);  
}
