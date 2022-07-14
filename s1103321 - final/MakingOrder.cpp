#include <iostream>
#include <iomanip>
#include "MakingOrder.h" // MakingOrder class definition

extern int inputAnInteger( int begin, int end = INT_MAX );

MakingOrder::MakingOrder( string theEmail, AccountDatabase &theAccountDatabase )
   : email( theEmail ),
     accountDatabase( theAccountDatabase )
{
}

void MakingOrder::run()
{
    Account currentAccount(email);
    currentAccount.setCart(accountDatabase.getCart(email));
    while (1)
    {
        int foodCode = 0, quantity = 0, choice = 0;
        currentAccount.displayCart();
        do {
            
            cout << "\nEnter foods code  (0 to end): ";
        } while ((foodCode = inputAnInteger(0, 14)) == -1);
        
        if (foodCode == 0)
            return;

        do {
            cout << "\nEnter quantity: ";
        } while ((quantity = inputAnInteger(0,2147283647)) == -1);

        cout << "\n1. Continue Shopping\n"
            << "2. Save Your Shopping Cart\n"
            << "3. Abandon\n";
        do {
            cout << "\nEnter your choice: (1~3): ";
        } while ((choice = inputAnInteger(1, 3)) == -1);

        switch (choice)
        {
        case 1:
            currentAccount.modifyCart(foodCode, quantity);
            continue;
            break;
        case 2:
            currentAccount.modifyCart(foodCode, quantity);
            accountDatabase.modifyCart(currentAccount);
            break;
        case 3:
            currentAccount.resetCart();
            break;

        default:
            break;
        }
        break;
    }

}