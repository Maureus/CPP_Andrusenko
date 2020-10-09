#include <iostream>
#include <stdio.h>
#include <exception>

#include "Receipt.h"
#include "CashRegister.h"


using namespace std;

int main()
{

    CashRegister* cashRegister = new CashRegister();
    try {
        Receipt r1 = cashRegister->CreateReceipt(30, 30 * 0.2);
        r1.ToString();
        Receipt r2 = cashRegister->CreateReceipt(35, 35 * 0.2);
        r2.ToString();
        Receipt r3 = cashRegister->CreateReceipt(40, 40 * 0.2);
        r3.ToString();
        Receipt r4 = cashRegister->CreateReceipt(45, 45 * 0.2);
        r4.ToString();
        Receipt r5 = cashRegister->CreateReceipt(50, 50 * 0.2);
        r5.ToString();
        Receipt r6 = cashRegister->CreateReceipt(55, 55 * 0.2);
        r6.ToString();
        Receipt r7 = cashRegister->CreateReceipt(60, 60 * 0.2);
        r7.ToString();
        Receipt r8 = cashRegister->CreateReceipt(65, 65 * 0.2);
        r8.ToString();
        Receipt r9 = cashRegister->CreateReceipt(70, 70 * 0.2);
        r9.ToString();
        Receipt r10 = cashRegister->CreateReceipt(75, 75 * 0.2);
        r10.ToString();
        Receipt r11 = cashRegister->CreateReceipt(80, 80 * 0.2);
        r11.ToString();

        Receipt searchedReceipt = cashRegister->GetReceipt(1001);
        searchedReceipt.ToString();

        cout << "Total sales: " << cashRegister->GetAmount() << endl;
        cout << "Total sales+dph: " << cashRegister->GetAmaountInclDph() << endl;

    }
    catch (const exception& e) {
        cerr << "Got exception: " << e.what() << endl;
        return -1;
    }




    delete cashRegister;

    return 0;
}