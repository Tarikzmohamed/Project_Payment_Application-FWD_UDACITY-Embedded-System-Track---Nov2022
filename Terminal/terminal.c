
//
 // Terminal_Module Aplication File
 // terminal.c
 // Tarik Zaki Mohamed (tarik.z.ramadan@gmail.com)
 // Application Terminal_Module (terminal.c) 
 // Start date DD/MM/YYYY 05-11-2022
 // Testing date DD/MM/YYYY 15-11-2022
 // Finish date DD/MM/YYYY 16-11-2022
 // Copyrights (c) Tarik Zaki Mohamed
 // 
 //


// ========= include header file with location relative to main location ======== //

#include "../Card/card.h"
#include "../Terminal/terminal.h"

#include <stdio.h> //using Printf()
#include <string.h>  // using strcpy()
#include <stdlib.h>
#include <ctype.h>  // using isdigit()
#include <time.h>


// ============= Implement isValidCardPAN function ============= // 
EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData)
{
	uint8_t lenght = 0, tmp = 0, sum = 0;

	// =============== get number lenght ================= //
	lenght = strlen(cardData->primaryAccountNumber);

	// ==== flag to get every other number to mul by 2 === //
	_Bool everyother = 0; 

	// ========= check number from second right to left ========= //
	for (char i = lenght - 1; i >= 0; i--)
	{
		// ========= convert char to integer ========= //
		tmp = cardData->primaryAccountNumber[i] - '0';
		
		// ========= mul ever other digit by 2 ======= //
		tmp = (everyother) ? tmp * 2 : tmp;

// ========= if the number was two digits number sub 9 from it ======= //
		tmp = (tmp > 9) ? tmp - 9 : tmp; 
		
		// ========= get numbers sum ======= //
		sum += tmp;

		everyother = !everyother;
	}
	// ========= if the first digit of the sum is zero then the number is valid  Luhn number ======= //
	return (sum % 10 == 0)?TERMINAL_OK :INVALID_CARD;
}
// ============ End of isValidCardPAN function =========== // 





//
// ============= Implement getTransactionDate function using user Input ============= // 

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
    EN_terminalError_t TransactionDate_ErrorState = TERMINAL_OK;

    uint8_t transactionDate[11] = {0};

    printf(" Enter the transaction date: ");
    gets(transactionDate);

    uint8_t TransactionDateLength = strlen(transactionDate);
// === isdigit() Result when numeric character is passed: Non-zero integer ( x > 0 ) == //
// === isdigit() Result when non-numeric character is passed: 0 == //
    if( (NULL == transactionDate) || 
        (TransactionDateLength != 10) || 
        (transactionDate[2] != '/') || (transactionDate[5] != '/') ||
       (isdigit(transactionDate[0]) == 0) || (isdigit(transactionDate[1]) == 0) || 
	   (isdigit(transactionDate[3]) == 0) || (isdigit(transactionDate[4]) == 0) ||
       (isdigit(transactionDate[6]) == 0) || (isdigit(transactionDate[7]) == 0) || 
	   (isdigit(transactionDate[8]) == 0) || (isdigit(transactionDate[9]) == 0) )
    {
    	// === if the transaction Date is NULL, less or more than 5 characters, or has the wrong format == //
		// === will return the WRONG_DATE error, else return TERMINAL_OK == //
        TransactionDate_ErrorState = WRONG_DATE;
    }
    else
	{
		if((isTMonthValid(transactionDate) == 1))
    	{
        	strcpy(termData->transactionDate, transactionDate);
        	TransactionDate_ErrorState = TERMINAL_OK;
    	}
    	else
    	{
    	  if((isTMonthValid(transactionDate) == 0))
 			TransactionDate_ErrorState = WRONG_DATE;	
		}
 	} 
    return TransactionDate_ErrorState;
}
// ============= End of getTransactionDate function using user Input ============= // 


// ========== Implement isCardExpired function ============= // 
EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData)
{
	// ===== check if the user enter the current millennium 20xx ======= //
	if (termData->transactionDate[6] == '2' && termData->transactionDate[7] == '0')
	{
		
		// ===== in case if transaction year was lower than expiry year then the card is still valid ======= //
		
		// ===== if transaction date decade was less than the card 's  ======= //
		if (termData->transactionDate[8] < cardData->cardExpirationDate[3])
		{
			
			return TERMINAL_OK;	
		}
		// ===== if transaction date decade was bigger or equal than the card 's  ======= //
		else if (termData->transactionDate[8] == cardData->cardExpirationDate[3])
		{
			// ===== check year ======= //
			if (termData->transactionDate[9] < cardData->cardExpirationDate[4])
			{
				return TERMINAL_OK;
			}
		}
		// ===== in case if transaction year was equal to the expiry year  ======= //
		if  (termData->transactionDate[9] == cardData->cardExpirationDate[4] && termData->transactionDate[8] == cardData->cardExpirationDate[3])
		{
			// ===== check the expiration month ======= //
			if (termData->transactionDate[4] <= cardData->cardExpirationDate[1] && termData->transactionDate[3] <= cardData->cardExpirationDate[0])
			{
				// ===== card is still vaild ======= //
				return TERMINAL_OK;
			}
		}
	}
	// ======= if any case fail then the card would be expired ======= //
	return EXPIRED_CARD;
}
// ============= End of isCardExpired function ============= //






// ============ Implement setMaxAmount function ============= // 

// ======= maxAmount is set by float number in app.c fixed value in code. ======= //

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount)
{

	if (maxAmount <= 0) 
	return INVALID_MAX_AMOUNT;
	if(termData->maxTransAmount = maxAmount);
	return TERMINAL_OK;
}
// ============ End of setMaxAmount function ============= // 


// ============= Implement getTransactionAmount function ============= // 

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
EN_terminalError_t TransactionAmount_ErrorState = TERMINAL_OK;

    float transAmount = 0;
    printf("\n Enter transaction amount: ");
    scanf("%f", &transAmount);

    if( (0 >= transAmount) )
    {
        TransactionAmount_ErrorState = INVALID_AMOUNT;
    }
    else
    {
        termData->transAmount = transAmount;
    }
    return TransactionAmount_ErrorState;
}

// ============= End of getTransactionAmount function ============= // 


// ============= Implement isBelowMaxAmount function ============= // 
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {
	if ((termData->transAmount) > (termData->maxTransAmount)) 	{
		return EXCEED_MAX_AMOUNT;
	}
	else
	{
		return TERMINAL_OK;
	}
}
// ============= End of isBelowMaxAmount function ============= //







// =========================== Test functions ========================== // 
// ============= Implement isValidCardPANTest function ============= //
void isValidCardPANTest(void)
{
	const uint8_t Cases = 5;
	ST_cardData_t Testcards[5] = 
	{ 
		{.primaryAccountNumber = "2769148304059987"},
		{.primaryAccountNumber = "2769148304059983"}, //Invalid Card number
		{.primaryAccountNumber = "921343273359840960"},
		{.primaryAccountNumber = "36859963594020925"},  //Invalid Card number
		{.primaryAccountNumber = "2747732760863908339"} 
	};

// =============  list of expected output ============= //
	uint8_t expectedOutputs[5][13] = { "TERMINAL_OK","INVALID_CARD","TERMINAL_OK","INVALID_CARD","TERMINAL_OK" };
	printf("Tester Name: Tarik Zaki M. M. Ramadan\n");
	printf("Function Name: isValidCardPAN\n \n");
	for (uint8_t i = 0; i < Cases; i++)
	{
		printf("Test Case %d: %s \n", i + 1, Testcards[i].primaryAccountNumber);
		printf("Expected Result: %s \n", expectedOutputs[i]);
		printf("Actual Result: %s \n", isValidCardPAN(&Testcards[i]) == TERMINAL_OK ? "TERMINAL_OK" : "INVALID_CARD");
	}
}
// ============= End of isValidCardPANTest function ============= //



// ============= Implement getTransactionDateTest function ============= // 
void getTransactionDateTest(void)
{
	ST_terminalData_t testTerminal ;
	const uint8_t Cases = 6;

	// ============= list of tests ============= //
	uint8_t TransactionDatesTest[6][12] = { "22/11/2022","ta/11/2022","055","22/11/20222","221/1/2022","22/33/2022" };
	
	// ============= list of expected output ============= //
	uint8_t expectedOutputs[6][12] = { "TERMINAL_OK","WRONG_DATE","WRONG_DATE","WRONG_DATE","WRONG_DATE","WRONG_DATE" };

	printf("Tester Name: Tarik Zaki M. M. Ramadan\n");
	printf("Function Name: getTransactionDate\n \n");
	for (uint8_t i = 0; i < Cases; i++)
	{
		printf("Test Case %d: %s \n", i + 1, TransactionDatesTest[i]);
		printf("Expected Result: %s ", expectedOutputs[i]);
		printf("Actual Result: %s \n \n ", getTransactionDate(&testTerminal) == TERMINAL_OK ? "TERMINAL_OK" : "WRONG_DATE");
	}
}
// ============= End of getTransactionDateTest function ============= // 

// ============= Implement isCardExpiredTest function ============= // 
void isCardExpiredTest(void)
{
	const uint8_t Cases = 4;

	ST_cardData_t TestCard = { .cardExpirationDate = "11/22" };

	ST_terminalData_t TestTerminals[4] = {
		{ .transactionDate = "31/04/2021" }, 
		{ .transactionDate = "31/10/2022" }, 
		{ .transactionDate = "31/05/2023" },
		{ .transactionDate = "31/12/2022" }
		};
	
	// ============= list of expected output ============= //
	uint8_t expectedOutputs[4][13] = { "TERMINAL_OK","TERMINAL_OK","EXPIRED_CARD","EXPIRED_CARD" };
	
	printf("Tester Name: Tarik Zaki M. M. Ramadan\n");
	printf("Function Name: isCardExpired\n \n");
	printf("please note that the card expiry date is 11/22\n");
	for (int i = 0; i < Cases; i++)
	{

		printf("Test Case %d: %s \n", i + 1, TestTerminals[i].transactionDate);
		printf("Expected Result: %s \n", expectedOutputs[i]);

		printf("Actual Result: %s \n \n", isCardExpired(&TestCard,&TestTerminals[i]) == TERMINAL_OK ? "TERMINAL_OK" : "EXPIRED_CARD");
	}
}
// ============= End of isCardExpiredTest function ============= // 


// ============= Implement setMaxAmountTest function ============= //
void setMaxAmountTest(void)
{
	const uint8_t Cases = 4;

	ST_terminalData_t testTerminal; 
	float maxAmounts[] = { 4000,-500,2500.5,0 };

// =============  list of expected output ============= //
	uint8_t expectedOutputs[4][19] = { "TERMINAL_OK","INVALID_MAX_AMOUNT","TERMINAL_OK","INVALID_MAX_AMOUNT" };
	printf("Tester Name: Tarik Zaki M. M. Ramadan\n \n");
	printf("Function Name: setMaxAmount\n");
	for (uint8_t i = 0; i < Cases; i++)
	{
		printf("Test Case %d: %f \n", i + 1, maxAmounts[i]);
		printf("Expected Result: %s \n", expectedOutputs[i]);
		printf("Actual Result: %s \n \n", setMaxAmount(&testTerminal,maxAmounts[i]) == TERMINAL_OK ? "TERMINAL_OK" : "INVALID_MAX_AMOUNT");
	}
}
// ============= End of setMaxAmountTest function ============= //

// ============= Implement getTransactionAmountTest function ============= // 
void getTransactionAmountTest(void)
{
	
	ST_terminalData_t testTerminal;
	const uint8_t Cases = 3;

	// ============= list of tests ============= //
	float AmountsTest[] = { 550.0,-50,0};
	
	// ============= list of expected output ============= //
	uint8_t expectedOutputs[3][15] = {"TERMINAL_OK","INVALID_AMOUNT","INVALID_AMOUNT" };

	printf("Tester Name: Tarik Zaki M. M. Ramadan\n");
	printf("Function Name: getTransactionAmount\n \n");
	for (uint8_t i = 0; i < Cases; i++)
	{

		printf("Test Case %d: %f \n", i + 1, AmountsTest[i]);
		printf("Expected Result: %s ", expectedOutputs[i]);
		printf("Actual Result: %s \n \n", getTransactionAmount(&testTerminal) == TERMINAL_OK ? "TERMINAL_OK" : "INVALID_AMOUNT");
	}
}
// ============= End of getTransactionAmountTest function ============= // 

// ============= Implement isBelowMaxAmountTest function ============= //
void isBelowMaxAmountTest(void)
{
	const uint8_t Cases = 3;
	ST_terminalData_t TestTerminals[] =
	{ 
		{.transAmount= 4950.5,.maxTransAmount = 6000.0},
		{.transAmount= 6000.0,.maxTransAmount = 6000.0},
		{.transAmount= 10000 ,.maxTransAmount = 6000.0}
	};

	// =============  list of expected output ============= //
	uint8_t expectedOutputs[3][18] = { "TERMINAL_OK","TERMINAL_OK","EXCEED_MAX_AMOUNT"};
	printf("Tester Name: Tarik Zaki M. M. Ramadan\n");
	printf("Function Name: isBelowMaxAmountTest\n \n");
	printf("please note that the max amount is set to be 6000.0\n");
	for (int i = 0; i < Cases; i++)
	{
		printf("Test Case %d: %f \n", i + 1, TestTerminals[i].transAmount);
		printf("Expected Result: %s \n", expectedOutputs[i]);
		printf("Actual Result: %s \n \n", isBelowMaxAmount(&TestTerminals[i]) == TERMINAL_OK ? "TERMINAL_OK" : "EXCEED_MAX_AMOUNT");
	}
}
// ============= End of isBelowMaxAmountTest function ============= //


//
// ============= check for Valid Month function =================== //
 _Bool isTMonthValid(uint8_t* transactionDate)
{
	// ========= check characters of month ===== //
 	// ==== Note: when you check transactionDate month and it is true, it returns 1. === //
	// ========= But, when you check transactionDate month and it is not true, it always returns 0. ===== //
	// if((0 == transactionDate[3]) || (1 == transactionDate[3]))
	//	{
			if(('1' == transactionDate[3]))
				{
				if(('0' == transactionDate[4]) || ('1' == transactionDate[4]) || ('2' == transactionDate[4]))
						return 1;
				}
			else 
			{	
			if (('0' == transactionDate[3]))
				{
				if(('1' == transactionDate[4]) || ('2' == transactionDate[4]) || ('3' == transactionDate[4]) 
				|| ('4' == transactionDate[4]) || ('5' == transactionDate[4]) || ('6' == transactionDate[4])
				|| ('7' == transactionDate[4]) || ('8' == transactionDate[4]) || ('9' == transactionDate[4]))
						return 1;
				}
			}
	//	}
		return 0;
}
// ============= End check for Valid Month function =================== //

