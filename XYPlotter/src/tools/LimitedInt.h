/*
 * LimitedInt.h
 *
 *  Created on: 6 Sep 2020
 *      Author: Lauri
 */

#ifndef TOOLS_LIMITEDINT_H_
#define TOOLS_LIMITEDINT_H_

class LimitedInt {
public:
	LimitedInt(int, int , int );
	virtual ~LimitedInt();
	LimitedInt operator ++();
	LimitedInt operator --();
	LimitedInt operator ++(int);
	LimitedInt operator --(int);

	LimitedInt operator +=(const int);
	LimitedInt operator -=(const int);
	LimitedInt operator =(const int);
	bool operator==(const LimitedInt &);
	operator int() const;

private:
	int val, min, max;
};

#endif /* TOOLS_LIMITEDINT_H_ */
