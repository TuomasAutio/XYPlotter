/*
 * LimitedInt.cpp
 *
 *  Created on: 6 Sep 2020
 *      Author: Lauri
 */

#include "LimitedInt.h"

LimitedInt::LimitedInt(int value, int minimum, int maximum) : val(value), min(minimum), max(maximum)  {
	// TODO Auto-generated constructor stub

}

LimitedInt::~LimitedInt() {
	// TODO Auto-generated destructor stub
}


LimitedInt LimitedInt::operator ++(){
	if(val+1 < max){
		++val;
	}else{
		val = max;
	}
	return *this;
}
LimitedInt LimitedInt::operator --(){
	if(val-1 > min){
		--val;
	}else{
		val = min;
	}
	return *this;
}
LimitedInt LimitedInt::operator +=(const int param){
	if(val+param < max){
		val += param;
	}else{
		val = max;
	}
	return *this;

}
LimitedInt LimitedInt::operator -=(const int param){
	if(val-param > min){
		val += param;
	}else{
		val = min;
	}
	return *this;
}
LimitedInt LimitedInt::operator =(const int param){
	if (param > max){
		val = max;
	}else if( param < min){
		val = min;
	}else {
		val = param;
	}
	return *this;
}
bool LimitedInt::operator==(const LimitedInt &param){
	return val == (int)param;
}
LimitedInt::operator int() const{
	return val;
}
