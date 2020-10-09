#ifndef CASH_REGISTER_H
#define CASH_REGISTER_H

#include "Receipt.h"
#include <list>
#include <iterator>

using namespace std;

class CashRegister {
	static int idCounter;
	list<Receipt> receipts;
public:
	CashRegister();
	~CashRegister();
	Receipt& CreateReceipt(double, double);
	Receipt& GetReceipt(int);
	double GetAmount() const;
	double GetAmaountInclDph() const;
};

#endif // !CASH_REGISTER_H