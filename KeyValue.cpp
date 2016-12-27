// 
// 
// 

#include "KeyValue.h"

KeyValue::KeyValue(Keys k, int v)
{
	_key = k;
	_value = v;
}

Keys KeyValue::key()
{
	return _key;
}

int KeyValue::value()
{
	return _value;
}
