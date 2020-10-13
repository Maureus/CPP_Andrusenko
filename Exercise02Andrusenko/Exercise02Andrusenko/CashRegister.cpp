#include "CashRegister.h"
#include <iostream>
#include <exception>
#include <list>
#include <iterator>

#define ID_COUNTER_INIT_VALUE 1000;

using namespace std;

int CashRegister::idCounter = ID_COUNTER_INIT_VALUE;

CashRegister::CashRegister() {

}

CashRegister::~CashRegister() {

}

Receipt& CashRegister::CreateReceipt(double amount, double dph) {
	Receipt newReceipt{ amount, dph };
	if (receipts.size() == 10) {
		throw exception("CashRegister is full");
	}

	newReceipt.SetId(idCounter + receipts.size());
	receipts.push_front(newReceipt);	

	return newReceipt;
}

Receipt& CashRegister::GetReceipt(int id) {
	if (receipts.size() == 0) {
		throw exception("CashRegister is empty");
	}
	else {
		auto it = find_if(receipts.begin(), receipts.end(), [&](Receipt const& r) { return r.GetId() == id; });

		if (it == end(receipts)) {
			throw exception("Receipt not found");
		}
		else {
			return *it;
		}
	}

	throw exception("Unknown");
}

double CashRegister::GetAmount() const {	
	double sum = 0;

	for (auto it = receipts.begin(); it != receipts.end(); ++it) {
		sum += it->GetAmount();
	}

	return sum;
}

double CashRegister::GetAmaountInclDph() const {	
	double sumWithDph = 0;

	for (auto it = receipts.begin(); it != receipts.end(); ++it) {
		sumWithDph += it->GetAmount() + it->GetDph();
	}

	return sumWithDph;
}