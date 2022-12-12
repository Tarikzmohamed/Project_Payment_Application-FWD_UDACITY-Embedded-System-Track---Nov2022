
//
 // Card_Module Aplication File
 // card.c
 // Tarik Zaki Mohamed (tarik.z.ramadan@gmail.com)
 // Application card_Module (card.c) 
 // Start date DD/MM/YYYY 05-11-2022
 // Testing date DD/MM/YYYY 15-11-2022
 // Finish date DD/MM/YYYY 16-11-2022
 // Copyrights (c) Tarik Zaki Mohamed
 // 
 //


 
// ============================= System Header Files Section ======================== //
#include <stdio.h> //using Printf()

#include <string.h>  // using strcpy(), strcmp()
#include <stdlib.h>
#include <ctype.h>  // using isdigit()
// ============================= System Header Files Section ======================== //

// ============================= Start User Header Files Section ======================== //
#include "../Card/Card.h"

 // ============================= End User Header Files Section ======================== //
 
// ============= Implement getCardHolderName function ============= //
EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
	// ==  Enumerator CardHolder_ErrorState with states == //
	// === (CARD_OK,WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN) and initionate it with first element == //
    EN_cardError_t CardHolder_ErrorState = CARD_OK; 

// === define Cardholder name with 24 characters + '\0' == //
    uint8_t CardHolderName[25] = {0}; 

    printf("\n Enter the card holder name: ");
    gets(CardHolderName);
    uint8_t NameLength = strlen(CardHolderName);

// === check if Cardholdername is between 24 alphabetic characters string max and 20 minimum == //
    if( (NULL == CardHolderName) || 
        (NameLength < 20) || 
        (NameLength > 24) || (0 == isStringAlpha(CardHolderName)) )
    {
// === If the cardholder name is NULL, less than 20 characters or more == // isStringAlpha
// === than 24 will return a WRONG_NAME error, else return CARD_OK == //
	    CardHolder_ErrorState = WRONG_NAME;
    }
    else 
    {
    	strcpy(cardData->cardHolderName, CardHolderName);
    	CardHolder_ErrorState = CARD_OK;
    }

    return CardHolder_ErrorState;
}
// ============= End getCardHolderName function ============= //

// ============= Implement getCardExpiryDate function ============= // 
 
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{
	// == Enumerator CardExpiryDate_ErrorState with states == //
	// === (CARD_OK,WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN) and initionate it with first element == //
    EN_cardError_t CardExpiryDate_ErrorState = CARD_OK;

// === define cardExpirationDate with 5 characters + '/0' // 
    uint8_t cardExpirationDate[6] = {0};

    printf("\n Enter the card expiration date: as MM/YY ");
    gets(cardExpirationDate);
    uint8_t DateLength = strlen(cardExpirationDate);

// === check if the card expiry date is NULL, less or more than 5 characters, == //
// === or has the wrong format like not numbers or miss '/' in its correct position == //
// === isdigit() Result when numeric character is passed: Non-zero integer ( x > 0 ) == //
// === isdigit() Result when non-numeric character is passed: 0 == //
    if( (NULL == cardExpirationDate) || (cardExpirationDate[2] != '/')||
        (DateLength != 5) || (isdigit(cardExpirationDate[0]) == 0) ||
       (isdigit(cardExpirationDate[1]) == 0) || (isdigit(cardExpirationDate[3]) == 0) || 
	   (isdigit(cardExpirationDate[4]) == 0) )
	   
    {
		// === if the card expiry date is NULL, less or more than 5 characters, or has the wrong format == //
		// === will return the WRONG_EXP_DATE error, else return CARD_OK == //
        CardExpiryDate_ErrorState = WRONG_EXP_DATE;
    }

    else 
    {
		if((isCMonthValid(cardExpirationDate) == 1))
		{
       strcpy(cardData->cardExpirationDate, cardExpirationDate);
       CardExpiryDate_ErrorState = CARD_OK;
		}
		else
    	{
    	if((isCMonthValid(cardExpirationDate) == 0))
    	CardExpiryDate_ErrorState = WRONG_EXP_DATE;
    	}
    }
    return CardExpiryDate_ErrorState;
}
// ============= End getCardExpiryDate function ============= // 


// ============= Implement getCardPAN function ============= // 

EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
	// ===  Enumerator getCardPAN_ErrorState with states(CARD_OK,WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN) == //
	// === and initionate it with first element == //
    EN_cardError_t getCardPAN_ErrorState = CARD_OK;
    
// === define cardPAN with 19 characters + '\0' == //
    uint8_t cardPAN[20] = {0};
    printf("\n Enter the card primary account number: ");
    gets(cardPAN);
    uint8_t PANLength = strlen(cardPAN);

// === check if the cardPAN is NULL, less 16 or more than 19 characters == //
	// === check if the cardPAN is NULL, less 16 or more than 19 characters == //
    // === will return the WRONG_PAN, else return CARD_OK == //
    if( (NULL == cardPAN) || 
        (PANLength < 16) || 
        (PANLength > 19) || (0 == isStringnumeric(cardPAN)) )
    {
        getCardPAN_ErrorState = WRONG_PAN;
    }
    else
    {
    	strcpy(cardData->primaryAccountNumber, cardPAN);
        getCardPAN_ErrorState = CARD_OK;
    }
    return getCardPAN_ErrorState;
}
// ============= End getCardPAN function ============= // 


// ============= Implement Test functions =================== // 
// ============= Implement getCardHolderNameTest function ============= //

void getCardHolderNameTest(void)
{
	ST_cardData_t testCard;
	const int lenght = 7;

	// === list of tests == //
	uint8_t namesTest[7][30] = { "TarikZakiMohamedMRamadan(24)","AhmedIbrahim(12)","MohamedAOmarAAliAElAsayed(25)","OmarAIbrahimAMohamed(20)","'\0' null (20)","123456789012345678901(21)","ahmedahmedahmedahmed2(21)" };

	// === list of expected output == //
	uint8_t expectedOutputs[7][11] = { "CARD_OK","WRONG_NAME","WRONG_NAME","CARD_OK","WRONG_NAME","WRONG_NAME","WRONG_NAME"};
	printf("Tester Name: Tarik Zaki M. M. Ramadan\n");
	printf("Function Name: getCardHolderName\n");
	for (int i = 0; i < lenght; i++)
	{
		printf("Test Case %d: %s \n", i + 1, namesTest[i]);
		printf("Expected Result: %s ", expectedOutputs[i]);
		printf("Actual Result: %s \n \n", getCardHolderName(&testCard) == CARD_OK ? "CARD_OK" : "WRONG_NAME");
	}
}
// ============== End getCardHolderNameTest function ============= //


// ============= Implement getCardExpiryDateTest function ============= //
void getCardExpiryDateTest(void)
{
	ST_cardData_t testCard;
	const int lenght = 6;

	// === list of tests == //
	uint8_t datesTest[6][7] = { "11/22","1122","11/y6","112/2","1/122","22/33" };

	// === list of expected output == //
	uint8_t expectedOutputs[6][15] = { "CARD_OK","WRONG_EXP_DATE","WRONG_EXP_DATE","WRONG_EXP_DATE","WRONG_EXP_DATE","WRONG_EXP_DATE" };

	printf("Tester Name: Tarik Zaki M. M. Ramadan\n");
	printf("Function Name: getCardExpiryDate\n");
	for (int i = 0; i < lenght; i++)
	{
		printf("Test Case %d: %s \n", i + 1, datesTest[i]);
		printf("Expected Result: %s ", expectedOutputs[i]);
		printf("Actual Result: %s \n \n", getCardExpiryDate(&testCard) == CARD_OK ? "CARD_OK" : "WRONG_EXP_DATE");
	}
}
// ============= End getCardExpiryDateTest function ============= //

// ============= Implement getCardPANTest function ============= //

void getCardPANTest(void)
{
	ST_cardData_t testCard;
	const int lenght = 7;

	// === list of tests == //
	uint8_t PANTest[7][21] = { "2769148304059987","98984958","\0 null","27691483040599871255","1234567890123456a","ahmedahmedahmedah","1234567890123456789" };

	// === list of expected output == //
	uint8_t expectedOutputs[7][10] = { "CARD_OK","WRONG_PAN","WRONG_PAN","WRONG_PAN","WRONG_PAN","WRONG_PAN","CARD_OK" };

	printf("Tester Name: Tarik Zaki M. M. Ramadan\n");
	printf("Function Name: getCardPAN\n");
	for (int i = 0; i < lenght; i++)
	{
		printf("Test Case %d: %s \n", i + 1, PANTest[i]);
		printf("Expected Result: %s ", expectedOutputs[i]);
		printf("Actual Result: %s \n \n", getCardPAN(&testCard) == CARD_OK ? "CARD_OK" : "WRONG_PAN");
	}
}
// ============= End getCardPANTest function ============= //


// ============= End Test functions =================== // 


// ============= check for alphabetic character function =================== //
 _Bool isStringAlpha(uint8_t* CardHolderName)
{
	// ========= get the length of string ===== //
	
	 uint8_t NameLength = strlen(CardHolderName);

	// ========= check each character ===== //
	for (uint8_t i = 0; i < NameLength; i++)
	{
		// ====== Note: You can get a different non-zero integer when alphabetic character is passed to isalpha() on your system. === //
		// ========= But, when you pass non-alphabetic character to isalpha(), it always returns 0. ===== //
		if (isalpha(CardHolderName[i]) == 0 )
		{
			// ========= if there is non-alphabetic character ===== //
			return 0; 
			
		}
	}
	return 1;
}
// ============= End check for alphabetic character function =================== //


// ============= check for numeric character function =================== //
 _Bool isStringnumeric(uint8_t* cardPAN)
{
	// ========= get the length of string ===== //
	
	 uint8_t PANLength = strlen(cardPAN);

	// ========= check each character ===== //
	for (uint8_t i = 0; i < PANLength; i++)
	{
		// ======The isdigit() function checks whether a character is numeric character (0-9) or not.  === //
		// ====== Note: Function isdigit() takes a single argument in the form of an integer and returns the value of type int.  === //
		// ====== Even though, isdigit() takes integer as an argument, character is passed to the function.  === //
 		// ======Internally, the character is converted to its ASCII value for the check.  === //
 		// ==== Note: You get a different Non-zero integer ( x > 0 ) when numeric character is passed to isdigit() on your system. === //
		// ========= But, when you pass non-numeric character to isdigit(), it always returns 0. ===== //

		if (isdigit(cardPAN[i]) == 0 )
		{
			// ========= if there is non-numeric character ===== //
			return 0; 
			
		}
	}
	return 1;
}
// ============= End check for alphabetic character function =================== //

//
// ============= check for Valid Month function =================== //
 _Bool isCMonthValid(uint8_t* cardExpirationDate)
{
	// ========= check characters of month ===== //
 	// ==== Note: when you check cardExpirationDate month and it is true, it returns 1. === //
	// ========= But, when you check cardExpirationDate month and it is not true, it always returns 0. ===== //
	// if((0 == cardExpirationDate[0]) || (1 == cardExpirationDate[0]))
	//	{
			if(('1' == cardExpirationDate[0]))
				{
				if(('0' == cardExpirationDate[1]) || ('1' == cardExpirationDate[1]) || ('2' == cardExpirationDate[1]))
						return 1;
				}
			else 
			{	
			if (('0' == cardExpirationDate[0]))
				{
				if(('1' == cardExpirationDate[1]) || ('2' == cardExpirationDate[1]) || ('3' == cardExpirationDate[1]) 
				|| ('4' == cardExpirationDate[1]) || ('5' == cardExpirationDate[1]) || ('6' == cardExpirationDate[1])
				|| ('7' == cardExpirationDate[1]) || ('8' == cardExpirationDate[1]) || ('9' == cardExpirationDate[1]))
						return 1;
				}
			}
	//	}
		return 0;
}
// ============= End check for Valid Month function =================== //
