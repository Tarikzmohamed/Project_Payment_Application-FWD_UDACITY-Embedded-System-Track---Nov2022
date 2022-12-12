
//
 // Application.c
 // app.c
 // Tarik Zaki Mohamed (tarik.z.ramadan@gmail.com)
 // Application Sequence of Operation 
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

#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "../Server/server.h"
#include "../Application/app.h"

// ============================= Start GLOBAL VARIABLES Section ======================== //


// ============================= End GLOBAL VARIABLES Section ======================== //

// ============================= Function to start the SALE_Transaction application ======================== //
/*
void appStart(void)
{

printf("\n SALE_Transaction Starting .... \n"); // SALE_Transaction Start
	// ==============================  Card_Module Starts Here ======================= //	
	ST_cardData_t card; //Define structure for CardHolder 
	EN_cardError_t CardHolderName_ErrorState = getCardHolderName(&card);
	    if( (CardHolderName_ErrorState != CARD_OK) )
			{
    	printf("Invalid Card Holder Name. try again\n"); 
		system("pause");
        return;
    		}
	EN_cardError_t CardExpDate_ErrorState = getCardExpiryDate(&card);
	    if( (CardExpDate_ErrorState != CARD_OK) )
			{
    	printf("Invalid Card Expiration Date. try again\n"); 
		system("pause");
        return;
    		}
	EN_cardError_t getCardPAN_ErrorState = getCardPAN(&card);
	    if( (getCardPAN_ErrorState != CARD_OK) )
			{
    	printf("Invalid Card Primary account number. try again\n"); 
		system("pause");
        return;
    		}
	printf("\n------- all card data collected -------\n");
	system("pause");
	// ==============================  Card_Module Ends Here ======================= //
		
	// ==============================  Terminal_Module Starts Here ======================= //
	
	ST_terminalData_t terminal; //Define structure for terminalData
		if( (getCardPAN_ErrorState != CARD_OK) )
		{
		if (isValidCardPAN(&card) != TERMINAL_OK)
			{
			printf("Invalid card PAN (Not Luhn Number) try again\n");
			system("pause");
        	return;
			}
		}
EN_terminalError_t terminalTransactionDate_ErrorState = getTransactionDate(&terminal);
	    if( (terminalTransactionDate_ErrorState  != TERMINAL_OK) )
			{
    	printf("Invalid Transaction Date. try again\n"); 
		system("pause");
        return;
    		}
   EN_terminalError_t ExpiredCard_ErrorState = isCardExpired(&card, &terminal);
    if( (ExpiredCard_ErrorState != TERMINAL_OK))
    {
        printf("Declined Expired card. try again\n");
		system("pause");
        return;
    }
    EN_terminalError_t TransAmount_ErrorState = getTransactionAmount(&terminal);
    if( (TransAmount_ErrorState != TERMINAL_OK))
    {
        printf("Declined Invalid Transaction Amount. try again\n");
		system("pause");
        return;
    }    	
		// ===================== hard coded max amount to be 6000.0 ================== //
		setMaxAmount(&terminal, 6000.0); 
    EN_terminalError_t TransAmountLimit_ErrorState = isBelowMaxAmount(&terminal);
    if( (EXCEED_MAX_AMOUNT == TransAmountLimit_ErrorState) )
    {
        printf("Declined Amount Exceeding limit 6000.0 is the maximum allowed. try again\n");
		system("pause");
        return;
    }
		printf("\n------- terminal data collected  -------\n");
		system("pause");
	// ==============================  Terminal_Module Ends Here ======================= //
			
	// ==============================  Server_Module Starts Here ======================= //
			ST_transaction_t transData = { .cardHolderData = card , .terminalData = terminal };
		
		// ============================== all state msgs ======================= //
			char statemsg[5][27] = { "TANSACTION_APPROVED", "DECLINED_INSUFFECIENT_FUND", "DECLINED_STOLEN_CARD", "DECLINED_FRAUD_CARD", "INTERNAL_SERVER_ERROR" };
			
		// ============== recieve Transaction Data from the server data base =============== //
			EN_transState_t state = recieveTransactionData(&transData);
			
		// ============== print server state msg =============== //
			printf("\n Transaction shortened state: %s \n",statemsg[(int)state]);
			system("pause");
			listSavedTransactions(); 
			system("pause");
			system("cls");		
}
*/

//
void appStart(void)
{

printf("\n SALE_Transaction Starting .... \n"); // SALE_Transaction Start
{
	// ==============================  Card_Module Starts Here ======================= //	
	ST_cardData_t card; //Define structure for CardHolder 
	ST_terminalData_t terminal; //Define structure for terminalData

	// ==== get card name ===== //
	while (getCardHolderName(&card) != CARD_OK)
	{
		printf("Wrong Name try again\n"); 
	}
	// === get card expiry date ==== //
	while (getCardExpiryDate(&card) != CARD_OK)
	{
		printf("Wrong Expiry Date try again\n");
	}
	
	// === check on card number and format and see if it Luhn number or not  ==== //
	while (1)
	{
		if (getCardPAN(&card) != CARD_OK)
		{
			printf("Wrong card Pan try again\n");
		}
		else
		{
			if (isValidCardPAN(&card) == TERMINAL_OK)
			{
				break;
			}
			else
			{
				printf("Wrong card Pan (Not Luhn Number) try again\n");
			}
		}

	}
	printf("\n------- all card data collected -------\n");
	system("pause");
	

	// ==============================  Terminal_Module Starts Here ======================= //

	// =================== get transaction date number ==================== //
	while (getTransactionDate(&terminal) != TERMINAL_OK) 
	{
		printf("Wrong transaction date number \n");
	}
	// ====== if the card isn't expired   ======== //
	if (isCardExpired(&card,&terminal) == TERMINAL_OK)
	{
		// ================= get transaction amount ============================ //
		while (getTransactionAmount(&terminal) != TERMINAL_OK)
		{
			printf("Wrong transaction amount enter number > 0 \n");
		}
		// ===================== hard coded max amount to be 6000.0 ================== //
		setMaxAmount(&terminal, 6000.0); 
		
		// ========= check if the transaction amount is higher than max amount ========= //
		if (isBelowMaxAmount(&terminal) != TERMINAL_OK)
		{
			printf("Declined Amount Exceeding Limit 6000.0\n"); 
			system("pause");
		}
		else
		{
			printf("\n------- terminal data collected  -------\n");
			system("pause");

	// ==============================  Terminal_Module Ends Here ======================= //

	// ==============================  Server_Module Starts Here ======================= //
			ST_transaction_t transData = { .cardHolderData = card , .terminalData = terminal };
			
			// ============================== all state msgs ======================= //
			char statemsg[5][27] = { "TANSACTION_APPROVED", "DECLINED_INSUFFECIENT_FUND", "DECLINED_STOLEN_CARD", "FRAUD_CARD", "INTERNAL_SERVER_ERROR" };
			
			// ============== recieve Transaction Data from the server data base =============== //
			EN_transState_t state = recieveTransactionData(&transData);
			
			// ============== print server state msg =============== //
			printf("\n Transaction shortened state: %s \n",statemsg[(int)state]);
			system("pause");
			listSavedTransactions(); 
			system("pause");
			system("cls");
		}

	}
	else 
	{
		printf("Declined Expired card  \n"); 
		system("pause");
    	system("cls");
	}
}
	// ==============================  Server_Module Ends Here ======================= //
}
// ============================= End of the SALE_Transaction application function ======================== //
//
// ============================= Function to start the SALE_Transaction Test application ======================== //

void appSalestestStart(void)
{

printf("\n SALE_Transaction Tests Starting .... \n"); // SALE_Transaction Tests

 while(1)
    {
    	// Starting Sales Application program Testing Screen //

        uint8_t  Sales_Application_program_Testing_state = 0;
        uint8_t  Sales_Application_program_Testing_Card_Module_state = 0;
       	uint8_t  Sales_Application_program_Testing_Terminal_Module_state = 0;
        uint8_t  Sales_Application_program_Testing_Server_Module_state = 0;
// Starting Sales Application program Testing Screen //
    	system("pause");
    	system("cls");
    	printf("\n Thanks for using the Payment application");
    	printf("\n Copyrights (c)2022 --- Author: Tarik Zaki Mohamed ----\n");
    	printf("\n This is for FWD_UDACITY_Embedded_System_Track ----\n");
        printf("\n 1. Test Card Module");
        printf("\n 2. Test Terminal Module");
        printf("\n 3. Test Server Module");
        printf("\n 4. Exit.");
        printf("\n [>]: ");
        Sales_Application_program_Testing_state = getch();

        switch(Sales_Application_program_Testing_state)
        {
            case '1': 
                  system("cls");
                  printf("\n Test Card Module Processing..... \n");
					getCardHolderNameTest();
					system("pause");
					system("cls");
					printf("\n Test Card Module Processing..... \n");
					getCardExpiryDateTest();
					system("pause");
					system("cls");
					printf("\n Test Card Module Processing..... \n");
					getCardPANTest();
					system("pause");
					system("cls");
                break;
            case '2': 
                	printf("\n Test Terminal Module Processing..... \n");
 					getTransactionDateTest();
					system("pause");
					system("cls");
					printf("\n Test Terminal Module Processing..... \n");
					isCardExpiredTest(); 
					system("pause");
					system("cls");
					printf("\n Test Terminal Module Processing..... \n");
					getTransactionAmountTest();
					system("pause");
					system("cls");
					printf("\n Test Terminal Module Processing..... \n");
					isBelowMaxAmountTest();
					system("pause");
					system("cls");
					printf("\n Test Terminal Module Processing..... \n");
					setMaxAmountTest();
					system("pause");
					system("cls");
					printf("\n Test Terminal Module Processing..... \n");
					isValidCardPANTest();
					system("pause");
					system("cls"); 
                break;
             case '3':  
                    printf("\n Test Server Module Processing..... \n");
					recieveTransactionDataTest(); 
					system("pause");
					system("cls");
					printf("\n Test Server Module Processing..... \n");
					isValidAccountTest();
					system("pause");
					system("cls"); 
					printf("\n Test Server Module Processing..... \n");
					isBlockedAccountTest(); 
					system("pause");
					system("cls");
					printf("\n Test Server Module Processing..... \n");
					isAmountAvailableTest(); 
					system("pause");
					system("cls");
					printf("\n Test Server Module Processing..... \n");
					saveTransactionTest();
					system("pause");
					system("cls");
					printf("\n Test Server Module Processing..... \n");
					listSavedTransactionsTest();
					system("pause");
					system("cls"); 
                break; 
             case '4': 
                    system("cls");
                    printf("\n Exit Program and Return to Main Screen Menu \n"); // Exit if you choose 4
                    return ;
                break; 
             default: 
                    system("cls");
                    printf("\n Invalid Input and Return to Main Screen Menu \n"); // Exit if you choose any other numbers other than 1 to 4
                return ;
                break;
        } 
    }
	return ;
}

/*
// ============================= Function to start the REFUND_Transaction application ======================== //

void appREFUNDStart(void)
{


printf("\n REFUND_Transaction under development \n"); // REFUND_Transaction Start


}


// ============================= Function to start the REFUND_Transaction Test application ======================== //

void appREFUNDtestStart(void)
{


printf("\n REFUND_Transaction Tests under development \n"); // REFUND_Transaction Tests


}
*/

/*
// ============================= Function to start the Pre-Authorization_Transaction application ======================== //
void appPre_AuthorizationStart(void)
{

printf("\n Pre-Authorization_Transaction under development \n"); // Pre-Authorization_Transaction Start

}
// ============================= Function to start the Pre-Authorization_Transaction Test application ======================== //

void appPre-AuthorizationtestStart(void)
{

printf("\n Pre-Authorization_Transaction Tests under development \n"); // Pre-Authorization_Transaction Tests

}
*/

/*
// ============================= Function to start the VOID_Transaction application ======================== //

void appVOIDStart(void)
{

printf("\n VOID_Transaction under development \n"); // VOID_Transaction Start

}
// ============================= Function to start the VOID_Transaction Test application ======================== //

void appVOIDtestStart(void)
{

printf("\n VOID_Transaction Tests under development \n"); // VOID_Transaction Tests


}
*/
