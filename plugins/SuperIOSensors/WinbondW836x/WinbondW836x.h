/*
 *  W836x.h
 *  HWSensors
 *
 *  Based on code from Open Hardware Monitor project by Michael Möller (C) 2011
 *
 *  Created by mozo on 14/10/10.
 *  Copyright 2010 mozodojo. All rights reserved.
 *
 */

/*
 
 Version: MPL 1.1/GPL 2.0/LGPL 2.1
 
 The contents of this file are subject to the Mozilla Public License Version
 1.1 (the "License"); you may not use this file except in compliance with
 the License. You may obtain a copy of the License at
 
 http://www.mozilla.org/MPL/
 
 Software distributed under the License is distributed on an "AS IS" basis,
 WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 for the specific language governing rights and limitations under the License.
 
 The Original Code is the Open Hardware Monitor code.
 
 The Initial Developer of the Original Code is 
 Michael Möller <m.moeller@gmx.ch>.
 Portions created by the Initial Developer are Copyright (C) 2011
 the Initial Developer. All Rights Reserved.
 
 Contributor(s):
 
 Alternatively, the contents of this file may be used under the terms of
 either the GNU General Public License Version 2 or later (the "GPL"), or
 the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 in which case the provisions of the GPL or the LGPL are applicable instead
 of those above. If you wish to allow use of your version of this file only
 under the terms of either the GPL or the LGPL, and not to allow others to
 use your version of this file under the terms of the MPL, indicate your
 decision by deleting the provisions above and replace them with the notice
 and other provisions required by the GPL or the LGPL. If you do not delete
 the provisions above, a recipient may use your version of this file under
 the terms of any one of the MPL, the GPL or the LGPL.
 
 */

#include <IOKit/IOService.h>
#include <IOKit/IORegistryEntry.h>
#include <IOKit/IOPlatformExpert.h>
#include <IOKit/IODeviceTreeSupport.h>
#include <IOKit/IOKitKeys.h>

#include "../SuperIOFamily/SuperIOFamily.h"

const UInt8 WINBOND_HARDWARE_MONITOR_LDN		= 0x0B;

const UInt16 WINBOND_VENDOR_ID              = 0x5CA3;
const UInt8 WINBOND_HIGH_BYTE               = 0x80;

// Winbond Hardware Monitor
const UInt8 WINBOND_ADDRESS_REGISTER_OFFSET	= 0x05;
const UInt8 WINBOND_DATA_REGISTER_OFFSET		= 0x06;

// Winbond Hardware Monitor Registers
const UInt8 WINBOND_BANK_SELECT_REGISTER		= 0x4E;
const UInt8 WINBOND_VENDOR_ID_REGISTER      = 0x4F;
const UInt8 WINBOND_TEMPERATURE_SOURCE_SELECT_REG	= 0x49;

//private string[] TEMPERATURE_NAME = 
//new string[] {"CPU", "Ambient", "System", "Memory"};
const UInt16 WINBOND_TEMPERATURE[]      = { 0x150, 0x250, 0x27 };
const UInt16 NUVOTON_TEMPERATURE[]      = { 0x150, 0x670, 0x27 };
const UInt16 NUVOTON_NEW_TEMPERATURE1[] = { 0x75, 0x77, 0x73, 0x79 };
const UInt16 NUVOTON_NEW_TEMPERATURE2[] = { 0x402, 0x401, 0x404, 0x405 };


// Voltages                               VCORE   AVSB   3VCC   AVCC  +12V1  -12V2  -5VIN3  3VSB   VBAT
const UInt16 WINBOND_VOLTAGE_REG[]    = { 0x20,  0x21,  0x23,  0x22,  0x24,  0x25,  0x26,  0x550, 0x551 };
const float  WINBOND_VOLTAGE_SCALE[]  = { 8,     8,     16,    16,    8,     8,     8,     16,    16 };
const UInt16 WINBOND_VOLTAGE_VBAT_REG = 0x0551;
const UInt16 NUVOTON_VOLTAGE_REG[]    = { 0x480, 0x482, 0x483, 0x484, 0x485, 0x481, 0x486, 0x487, 0x488 };


const UInt8 WINBOND_TACHOMETER[]			= { 0x28, 0x29, 0x2A, 0x3F, 0x53 };
const UInt8 WINBOND_TACHOMETER_BANK[] = { 0, 0, 0, 0, 5 };

//                                        SYSFAN, CPUFAN, AUXFAN
const UInt16 NUVOTON_TACHOMETER[]     = { 0x4C0,  0x4C2,  0x4C4,  0x4C6, 0x4C8, 0x4CA};

const UInt8 WINBOND_TACHOMETER_DIV0[]		  = { 0x47, 0x47, 0x4B, 0x59, 0x59 };
const UInt8 WINBOND_TACHOMETER_DIV0_BIT[]	= { 4,    6,    6,    0,    2 };
const UInt8 WINBOND_TACHOMETER_DIV1[]		  = { 0x47, 0x47, 0x4B, 0x59, 0x59 };
const UInt8 WINBOND_TACHOMETER_DIV1_BIT[]	= { 5,    7,    7,    1,    3 };
const UInt8 WINBOND_TACHOMETER_DIV2[]		  = { 0x5D, 0x5D, 0x5D, 0x4C, 0x59 };
const UInt8 WINBOND_TACHOMETER_DIV2_BIT[]	= { 5,    6,    7,    7,    7 };

const UInt8 WINBOND_TACHOMETER_DIVISOR[]	= { 0x47, 0x4B, 0x4C, 0x59, 0x5D };
const UInt8 WINBOND_TACHOMETER_DIVISOR0[]	= { 36, 38, 30, 8, 10 };
const UInt8 WINBOND_TACHOMETER_DIVISOR1[]	= { 37, 39, 31, 9, 11 };
const UInt8 WINBOND_TACHOMETER_DIVISOR2[]	= { 5, 6, 7, 23, 15 };

// Fan Control
const UInt8 WINBOND_FAN_CONFIG[]			  = { 0x04, 0x04, 0x12, 0x62 };
const UInt8 WINBOND_FAN_CONTROL_BIT[]		= { 0x02, 0x04, 0x01, 0x04 };
const UInt8 WINBOND_FAN_MODE_BIT[]			= { 0x00, 0x01, 0x00, 0x06 };
const UInt8 WINBOND_FAN_OUTPUT[]			  = { 0x01, 0x03, 0x11, 0x61 };

enum W836xModel {
  W83627DHG  = 0xA020,
  W83627UHG  = 0xA230,
  W83627DHGP = 0xB070,
  W83627EHF  = 0x8800,
  W83627HF   = 0x5200,
  W83627THF  = 0x8280,
  W83627SF   = 0x5950,
  W83637HF   = 0x7080,
  W83667HG   = 0xA510,
  W83667HGB  = 0xB350,
  W83687THF  = 0x8541,
  W83697HF   = 0x6010,
  W83697SF   = 0x6810,
  NCT6681    = 0xB270,
  NCT6683    = 0xC730,
  NCT6771F   = 0xB470,
  NCT6776F   = 0xC330,
  NCT6779D   = 0xC560,
  NCT6791D   = 0xC803,
  NCT6792D   = 0xC911,
  NCT6793D   = 0xD121,
  NCT6795D   = 0xD352,
  NCT6796D   = 0xD423,
  NCT6798D   = 0xD428,
  NCT679BD   = 0xD42B,
  NCT6797D   = 0xD451,
};

class W836x;

class W836xSensor : public SuperIOSensor {
    OSDeclareDefaultStructors(W836xSensor)
    
public:
    static SuperIOSensor *withOwner(SuperIOMonitor *aOwner,
                                    const char* aKey,
                                    const char* aType,
                                    unsigned char aSize,
                                    SuperIOSensorGroup aGroup,
                                    unsigned long aIndex,
                                    long aRi = 0,
                                    long aRf = 1,
                                    long aVf = 0);
    
    virtual long	getValue();
//    virtual void    setValue(UInt16 value);
};


class W836x : public SuperIOMonitor {
  OSDeclareDefaultStructors(W836x)
    
public:
	virtual bool		init(OSDictionary *properties=0);
	virtual IOService*	probe(IOService *provider, SInt32 *score);
  virtual bool		start(IOService *provider);
	virtual void		stop(IOService *provider);
	virtual void		free(void);

private:
  char            vendor[40];
  char            product[40];
    
	UInt8           fanLimit;
	UInt16          fanValue[5];
	bool            fanValueObsolete[5];
	
	void            writeByte(UInt8 bank, UInt8 reg, UInt8 value);
	UInt8           readByte(UInt8 bank, UInt8 reg);
  UInt64          setBit(UInt64 target, UInt16 bit, UInt32 value);
	
	virtual bool		probePort();
    //  virtual bool			startPlugin();
	virtual void		enter();
	virtual void		exit();
    
	virtual long		readTemperature(unsigned long index);
	virtual long		readVoltage(unsigned long index);
	void            updateTachometers();
	virtual long		readTachometer(unsigned long index);
	
	virtual const char *	getModelName();
	
public:
    SuperIOSensor * addSensor(const char* key,
                              const char* type,
                              unsigned int size,
                              SuperIOSensorGroup group,
                              unsigned long index,
                              long aRi = 0,
                              long aRf = 1,
                              long aVf = 0);
    
    virtual IOReturn callPlatformFunction(const OSSymbol *functionName,
                                          bool waitForFunction,
                                          void *param1,
                                          void *param2,
                                          void *param3,
                                          void *param4);
};
