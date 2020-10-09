#ifndef RECEIPT_H
#define RECEIPT_H

class Receipt {
private:
	int id;
	double amount;
	double dph;
public:
	void SetId(int id);
	int GetId() const;
	double GetAmount() const;
	double GetDph() const;
	Receipt(double, double);
	void ToString() const;
};

#endif // !RECEIPT_H