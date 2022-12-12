
//
 // main.c
 // Tarik Zaki Mohamed (tarik.z.ramadan@gmail.com)
 // main Program file (main.c) 
 // Start date DD/MM/YYYY 05-11-2022
 // Testing date DD/MM/YYYY 15-11-2022
 // Finish date DD/MM/YYYY 16-11-2022
 // Copyrights (c) Tarik Zaki Mohamed
 // 
 //

#include <stdio.h> //using Printf()
#include <stdint.h> // using uint8_t
#include <conio.h>  // using getch()
#include <windows.h> // using system()

#include "Application/app.h"


//   
 //   SALE_Transaction, // means to buy something and its price will be deducted from your bank account
 //   REFUND_Transaction, // this means that you will return something and wants your money back to your bank account.
 //   Pre_Authorization_Transaction, // means holding an amount of money from your account, e.g Hotel reservation
 //   VOID_Transaction, // this means canceling the transaction, e.g if the seller entered the wrong amount program_Transactions;
//

int main(void)
{
    // =========== Run the program forever. ============ //
    while(1)
    {
    // =========== Starting Main Program selection Screen ============ //

        uint8_t  machine_program_Transaction_state = 0;

// =========== Starting Main Program selection Screen ============ //
    	system("cls");
    	printf("\n Thanks for using the Payment application");
    	printf("\n Copyrights (c)2022 --- Author: Tarik Zaki Mohamed ----\n");
    	printf("\n This is for FWD_UDACITY_Embedded_System_Track ----\n");
        printf("\n 1. Make New SALE_Transaction");
        printf("\n 2. Make new REFUND_Transaction");
        printf("\n 3. Make new Pre-Authorization_Transaction");
        printf("\n 4. Make new VOID_Transaction");
        printf("\n 5. Make SALE appTests");
        printf("\n 6. Make REFUND appTests");
        printf("\n 7. Make Pre-Authorization appTests");
        printf("\n 8. Make VOID appTests");
        printf("\n 9. Exit.");
        printf("\n [>]: ");
        machine_program_Transaction_state = getch();

        switch(machine_program_Transaction_state)
        {
            case '1': 
                    system("cls");
                    printf("\n SALE Transaction Processing \n");
                    appStart(); // SALE_Transaction
                break;
            case '2': 
                    system("cls");
                    printf("\n REFUND_Transaction under development \n"); // REFUND_Transaction
				//  appREFUNDStart(); // REFUND_Transaction
                break;
             case '3': 
                    system("cls");
                    printf("\n Pre-Authorization Transaction under development \n"); // Pre_Authorization_Transaction
				//  appPre_AuthorizationStart(); // 
                break;
             case '4': 
                    system("cls");
                    printf("\n VOID Transaction under development \n"); // VOID_Transaction
				//  appVOIDStart();  // 
                break; 
             case '5': 
                    system("cls");
                 //   printf("\n Tests under development \n"); // Tests
                 appSalestestStart(); // Tests Sales_Transaction Tests
				break; 
             case '6': 
                    system("cls");
                    printf("\n Tests under development \n"); // Tests REFUND_Transaction Tests
                 // appREFUNDtestStart(); // 
				break;
             case '7': 
                    system("cls");
                    printf("\n Tests under development \n"); // Tests Pre-Authorization_Transaction Tests
                 // appPre-AuthorizationtestStart(); // 
				break;
             case '8': 
                    system("cls");
                    printf("\n Tests under development \n"); // Tests VOID_Transaction Tests
                 // appVOIDtestStart(); // 
				break;
             case '9': 
                    system("cls");
                    printf("\n Exit Program and Return to Main Screen Menu \n"); // Exit if you choose 9
                    return 1;
                break; 
             default: 
                    system("cls");
                    printf("\n Invalid Input and Return to Main Screen Menu \n"); // Exit if you choose any other numbers other than 1 to 8
                return 1;
        }
    }
    return 0;
}
