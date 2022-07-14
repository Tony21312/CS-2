#include <iostream>
#include <iomanip>
#include "Login.h" // Registration class definition
#include "OrderDatabase.h" // OrderDatabase class definition
#include "MakingOrder.h" // MakingOrder class definition

extern int inputAnInteger( int begin, int end = INT_MAX );
extern Date computeCurrentDate();

Login::Login( AccountDatabase &theAccountDatabase, OrderDatabase &theOrderDatabase )
   : accountDatabase( theAccountDatabase ),
     orderDatabase( theOrderDatabase )
{
}

void Login::run()
{
   string email;
   string password;

   authenticateUser( email, password );

   if( email == "0" )
      return;

   MakingOrder makingOrder( email, accountDatabase );

   bool backToTop = false;
   while( !backToTop )
   {
      cout << "\n1. Making order\n"
           << "2. Display Cart\n"
           << "3. Proceed to Checkout\n"
           << "4. Order history\n"
           << "5. Back to top\n\n";

      int choice;
      do cout << "Enter your choice: (1~5): ";
      while( ( choice = inputAnInteger( 1, 5 ) ) == -1 );

      switch( choice )
      {
      case 1:
         makingOrder.run();
         break;
      case 2:
         displayCart( email );
         break;
      case 3:
         checkout( email );
         break;
      case 4:
         displayOrderHistory( email );
         break;
      case 5:
         backToTop = true; // this session should end
      }
   }
}

void Login::authenticateUser( string &email, string &password )
{
    while (1)
    {
        cout << "\nEmail (Account number) (0 to end): ";
        cin >> email;
        cin.ignore();
        if (email == "0")
            return;
        if (accountDatabase.existAccount(email))
        {
            cout << "\nPassword:";
            cin >> password;
            cin.ignore();
            if (!accountDatabase.authenticateUser(email, password))
            {
                cout << "\nInvalid password. Please try again.\n";
                continue;
            }
            break;
        }
        else
        {
            cout << "\nNo account exists with the e-mail!\n";
            email = "0";
            continue;
        }        

    }
 
}

void Login::displayCart( string email )
{
   Account currentAccount( email );

   currentAccount.setCart( accountDatabase.getCart( email ) );

   currentAccount.displayCart();
}

void Login::checkout( string email )
{
    if (accountDatabase.emptyCart(email))
    {
        cout << "\nYou shopping cart is empty!\n";
        return;
    }
    Order temp;
    Date tempDate(computeCurrentDate());
    string name, address, account;
    int dateCode;
    temp.setOrderDetails(accountDatabase.getCart(email));
    temp.setOrderNumber(orderDatabase.generateOrderNumber());
    cout << "\nOrder Number: " << temp.getOrderNumber() << endl;
    cout << "\nFull name: ";
    cin >> name;
    cout << "\nShipping Address: ";
    cin >> address;
    cout << "\nBank account: ";
    cin >> account;
    cout << endl << setw(9) << "Item Code" << setw(44) << "Item" << setw(7) << "Price" << setw(10) << "Quantity" << setw(10) << "Subtotal" << endl;  //added
    accountDatabase.displayOrders(email);  //added
    cout << "\nChoose a delivery date\n";
    
    for (int n = 1; n <= 28; n++)
    {
        cout << setw(2) << n << ". ";
        cout << (tempDate + n + 4) << ' ';
        if (n % 4 == 0)
            cout << endl;
    }
    cin.ignore();
    do {
        cout << '?';
    } while ((dateCode = inputAnInteger(1, 28)) == -1);
    Date tmp(tempDate + 4 + dateCode);
    temp.setEmail(name);
    temp.setDeliveryDate(tmp);
    orderDatabase.pushBack(temp);
    accountDatabase.resetCart(email);
}

void Login::displayOrderHistory( string email )
{
   if( !orderDatabase.existOrders( email ) )
   {
      cout << "\nYou have no order history!\n";
      return;
   }

   string name = accountDatabase.getName( email );

   orderDatabase.displayOrders( email, name );
}

Date Login::deliveryDate()
{
   Date date = computeCurrentDate() + 4;
   cout << "\nChoose a delivery date\n";
   for( int i = 1; i <= 28; i++ )
   {
      cout << setw( 2 ) << i << ". " << date + i;
      if( i % 4 == 0 )
         cout << endl;
      else
         cout << "  ";
   }

   int dateCode;
   do cout << "? ";
   while( ( dateCode = inputAnInteger( 1, 28 ) ) == -1 );

   return date + dateCode;
}