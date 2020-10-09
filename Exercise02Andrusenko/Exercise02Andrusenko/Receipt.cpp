#include "Receipt.h"
#include <iostream>

void Receipt::SetId(int id) {
	this->id = id;
}

int Receipt::GetId() const {
	return this->id;
}

double Receipt::GetAmount() const
{
	return amount;
}

double Receipt::GetDph() const
{
	return dph;
}

Receipt::Receipt(double amount, double dph) {
	this->amount = amount;
	this->dph = dph;
}

void Receipt::ToString() const
{
	std::cout << "Receipt{ id:" << id << ", amount: " << amount << ", dph: " << dph << "}" << std::endl;
}
