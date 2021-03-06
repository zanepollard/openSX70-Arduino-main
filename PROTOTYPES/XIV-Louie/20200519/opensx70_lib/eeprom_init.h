/*
**the openSX70 project**

  It is many things at once, but simply put, openSX70 is an open source
  (hardware and software) project that aims to take the SX70 beyond what
  is possible now in a cheap and non destructive way.
  https://opensx70.com/

  https://github.com/openSX70

  As a legal reminder please note that the code and files is under Creative Commons
  "Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)" is free and open
  for hobbyist NON-COMMERCIAL USE.
  https://creativecommons.org/licenses/by-nc/4.0/

  You are free to:
  Share — copy and redistribute the material in any medium or format
  Adapt — remix, transform, and build upon the material
  The licensor cannot revoke these freedoms as long as you follow the license terms.
  Under the following terms:
  Attribution — You must give appropriate credit, provide a link to the license,
  and indicate if changes were made. You may do so in any reasonable manner, but
  not in any way that suggests the licensor endorses you or your use.

  NonCommercial — You may not use the material for commercial purposes.

  No additional restrictions — You may not apply legal terms or technological
  measures that legally restrict others from doing anything the license permits.

  Notices:
  You do not have to comply with the license for elements of the material in the
  public domain or where your use is permitted by an applicable exception or limitation.

  No warranties are given. The license may not give you all of the permissions necessary
  for your intended use. For example, other rights such as publicity, privacy, or moral r
  ights may limit how you use the material.

*/

#ifndef eeprom_init_h
#define eeprom_init_h

#include "Arduino.h"

void init_EEPROM();

void WritePicture(int _currentPicture);
int ReadPicture();
void WriteISO(int _currentPicture);
int ReadISO();


#endif
