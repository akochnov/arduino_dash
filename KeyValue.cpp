// 
// 
// 

#include "KeyValue.h"

KeyValueClass::KeyValueClass(Keys k, int v)
{
	_key = k;
	_value = v;
}

Keys KeyValueClass::key()
{
	return _key;
}

int KeyValueClass::value()
{
	return _value;
}
