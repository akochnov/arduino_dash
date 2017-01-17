#ifndef IDataProvider_h
#define IDataProvider_h

enum Keys { 
	Mode, 
	VehicleSpeed, 
	EngineSpeed, 
	DisplayMode
};

class IDataProvider
{
  public:
    virtual Keys getKey() = 0;
    virtual uint8_t getValue() = 0;
};

#endif
