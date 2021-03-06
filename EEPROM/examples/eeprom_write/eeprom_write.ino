/*
 * EEPROM Write
 *
 * Stores random values into the EEPROM.
 * These values will stay in the EEPROM when the board is
 * turned off and may be retrieved later by another sketch.
 */

#include <EEPROM.h>

// the current address in the EEPROM (i.e. which byte
// we're going to write to next)
int addr = 0;
#define N512 2000
void setup()
{

	Serial.begin(115200);
	Serial.println("start...");
	if (!EEPROM.begin(N512)) {Serial.println("failed to initialise EEPROM"); delay(1000000);
}
	Serial.println(" bytes read from Flash . Values are:");
	for (int i = 0; i < N512; i++) { Serial.print(byte(EEPROM.read(i))); Serial.print(" "); }
	Serial.println(); 
  Serial.println("writing random n. in memory");
}

void loop()
{
  // need to divide by 4 because analog inputs range from
  // 0 to 1023 and each byte of the EEPROM can only hold a
  // value from 0 to 255.
 // int val = analogRead(10) / 4;
	int val = byte(random(10020));
  // write the value to the appropriate byte of the EEPROM.
  // these values will remain there when the board is
  // turned off.
  EEPROM.write(addr, val);
  Serial.print(val); Serial.print(" "); Serial.print(addr); Serial.print("|");
  // advance to the next address.  there are 512 bytes in
  // the EEPROM, so go back to 0 when we hit 512.
  // save all changes to the flash.
  addr = addr + 1;
  if (addr == N512)
  {
	  Serial.println();
    addr = 0;
    EEPROM.commit();
	Serial.print(N512);
	Serial.println(" bytes written on Flash . Values are:");
	for (int i = 0; i < N512; i++) { Serial.print(byte(EEPROM.read(i))); Serial.print(" "); }
	Serial.println(); Serial.println("----------------------------------");
  }
  
  delay(100);
  
}
