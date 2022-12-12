
//
 // Server_Module Aplication File
 // server.c
 // Tarik Zaki Mohamed (tarik.z.ramadan@gmail.com)
 // Application Server_Module (server.c) 
 // Start date DD/MM/YYYY 05-11-2022
 // Testing date DD/MM/YYYY 15-11-2022
 // Finish date DD/MM/YYYY 16-11-2022
 // Copyrights (c) Tarik Zaki Mohamed
 // 
 //
 

// =========== System Header Files Section ============ //
#include <stdio.h> //using Printf()
#include <stdint.h> // using uint8_t
#include <string.h>  // using strcpy()
#include <stdlib.h>
#include <ctype.h>  // using isdigit()
#include <windows.h> // using system()
// =========== End of  System Header Files Section ====== //

// ============================= Start User Header Files Section ======================== //
#include "../Card/Card.h"
#include "../Terminal/Terminal.h"
#include "../Server/server.h"

// ============================= End User Header Files Section ======================== //
 

 
 // ============================= Start GLOBAL VARIABLES Section ======================== //

  // ====================== server-side accounts' database =========================== //
ST_accountsDB_t accountsDB[255] = 
{
	{.balance = 2000.0,.state = RUNNING,.primaryAccountNumber = "083443230346969318" },
	{.balance = 4040.0,.state = RUNNING,.primaryAccountNumber = "8698766429935758" },
	{.balance = 96204, .state = BLOCKED,.primaryAccountNumber = "25558569495666551" },
	{.balance = 267,   .state = RUNNING,.primaryAccountNumber = "35854584549948483" },
	{.balance = 7436,  .state = BLOCKED,.primaryAccountNumber = "52565959245959593" },
	{.balance = 8690,  .state = RUNNING,.primaryAccountNumber = "31310950644454239" },
	{.balance = 6456,  .state = RUNNING,.primaryAccountNumber = "1685392974769326" },
	{.balance = 3386,  .state = RUNNING,.primaryAccountNumber = "5293820871528457" },
	{.balance = 77006,  .state = RUNNING,.primaryAccountNumber = "0175485335942703590" },
	{.balance = 403,  .state = RUNNING,.primaryAccountNumber = "2747732760863908339" }
};

 // ====================== server-side transactions' database initializing ==================== //
ST_transaction_t transactionData[255] = { {0} }; // intitializing the array with zeros //
 // ====================== End of server-side transactions' database initializing ==================== //

 // ============================= End GLOBAL VARIABLES Section ========================= //

 // ====================== Implement recieveTransactionData function ==================== //
EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	ST_accountsDB_t accountref; // accountref
	EN_transState_t state = INTERNAL_SERVER_ERROR;
	
	// =========================== if account is found ====================== //
	if (isValidAccount(&transData->cardHolderData, &accountref) == SERVER_OK)
	{
		// =========================== if the amount is available ====================== //
		if (isAmountAvailable(&transData->terminalData,&accountref)!=LOW_BALANCE) 
		{
			// =========================== the account is not blocked ====================== // 
			if (isBlockedAccount(&accountref) == SERVER_OK)
			{
					// =========================== update the balance ====================== //
					accountref.balance -= transData->terminalData.transAmount;
					state = APPROVED;
			}
			else
			{
				state = DECLINED_STOLEN_CARD;
			}
		}
		else
		{
			state =  DECLINED_INSUFFECIENT_FUND;
		}

	}
	else
	{
		state = FRAUD_CARD;
	}
	// =========================== update transdata ====================== //
	transData->transState = state;

	// ============= if the transaction is approved get reduced balance ========== //
	if (state == APPROVED)
	{
		// =================== get the account new balance ====================== //
		float newBalance = accountref.balance;

		if (newBalance >= 0)
		{
			printf("the New balance after transaction is : %f\n \n", newBalance);
		}
		else
		{
			// =================== server error ====================== //
			printf("INTERNAL_SERVER_ERROR\n");
		}
	}

	// ========================== if transaction is saved ============================ //
	if(saveTransaction(transData)==SERVER_OK)
	{
		return state;
	}
	else
	{
		return INTERNAL_SERVER_ERROR;
	}
}

 // ====================== End of recieveTransactionData function ==================== //

 
  // ====================== Implement isValidAccount function ==================== //
 
 EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence)
{
	// ========== linear search for the account PAN in accounts database ================ //
	for (uint8_t i = 0; i < 255; i++)
	{
	// ========== if the account PAN is found ================ //
	// ======= The strcmp() function is defined in the string.h header file. ====== //
	// ============= Return Value from strcmp() ============= //
	// ============= 0 if strings are equal,  ================ //
	// ========= >0 if the first non-matching character in str1 src is greater (in ASCII) than that of str2 des. === //
	// ======== <0 if the first non-matching character in str1 src is lower (in ASCII) than that of str2. des  ==== //
	// ======== if accountsDB contains also CardHolderName , we Can also check for the same CardHolderName ==== //
	// ((isStringEqual(accountsDB[i].primaryAccountNumber,cardData->primaryAccountNumber)) &&
	// (isStringEqual(accountsDB[i].CardHolderName,cardData->CardHolderName)))
		if (isStringEqual(accountsDB[i].primaryAccountNumber,cardData->primaryAccountNumber))
	//	if (0 == strcmp(accountsDB[i].primaryAccountNumber,cardData->primaryAccountNumber))
		{
			// ========== get the account address in the database ================ //
			*accountRefrence= accountsDB[i]; 
			return SERVER_OK;
		}

	}
	// ========== in case if the search fails set account Refrence to NULL ================ //
	accountRefrence = NULL; 
	return ACCOUNT_NOT_FOUND;
}
 // ====================== End of isValidAccount function ==================== //
 
 _Bool isStringEqual(uint8_t* src, uint8_t* des)
{
	// ========= if the two strings are not equal ===== //
	if (len(src) != len(des)) return 0; 

	uint8_t lenght = len(des);

	
	// ========= check each character ===== //
	for (uint8_t i = 0; i < lenght; i++)
	{
		// ========= if there a different character ===== //
		if (src[i] != des[i])
		{
			return 0; 
			
		}
	}
	return 1;
}

uint8_t len(uint8_t* str)
{
	uint8_t lenght = 0;
	// ========= Transverse throght the arr of string to get it's lenght ===== //
	while (str[lenght] != '\0')
	{
		lenght++;
	}
	return lenght;
}

 
  // ====================== Implement isBlockedAccount function ==================== //
 EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence)
{
	// ====== check account state ===== //
	if (accountRefrence->state == BLOCKED)
	{
		return BLOCKED_ACCOUNT;
	}
	// ====== in case if blocked ===== //
		return SERVER_OK;
}

  // ====================== End isBlockedAccount function ==================== //
  
  
  // ====================== Implement isAmountAvailable function ==================== // 

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence)
{
	if (accountRefrence == NULL || termData == NULL) return ACCOUNT_NOT_FOUND;
	else
	{
		// ====== if the transaction amount is higher than the balance in the account === //
		if (termData->transAmount > accountRefrence->balance)
		{
			return LOW_BALANCE;
		}
	}
	return SERVER_OK;
}
  // ====================== End of isAmountAvailable function ==================== //
 
 
  // ====================== Implement saveTransaction function ==================== //
  uint32_t sequance_no = 0;
EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	// ====== database limit 255 so after the seq exceed that will start from zero and overwrite the data === //
	uint8_t Transaction_no = (sequance_no & 255); 
	ST_transaction_t* ptr = &transactionData[Transaction_no]; 

	// ====== copy all data to the database === //
	ptr->cardHolderData = transData->cardHolderData;
	ptr->terminalData = transData->terminalData;
	ptr->transState = transData->transState; 
	ptr->transactionSequanceNumber = sequance_no;

	// ====== increment sequance number === //
	sequance_no++;

	listSavedTransactions();   
	
	// ====== Assuming that the connection between the terminal and server is always connected //
	return SERVER_OK;
}
 // ====================== End of saveTransaction function ==================== //

 // ====================== Implement listSavedTransactions function ==================== //
void listSavedTransactions(void)
{
	uint8_t no = sequance_no & 255; 
	char state[5][27] = { "APPROVED", "DECLINED_INSUFFECIENT_FUND", "DECLINED_STOLEN_CARD", "FRAUD_CARD", "INTERNAL_SERVER_ERROR" };
	for (uint8_t i = 0; i<no ; i++)
	{
		ST_transaction_t* ptr = &transactionData[i];
		printf("#############################\n");
		printf("Transaction Sequence Number : %lld \n", ptr->transactionSequanceNumber); 
		printf("Transaction Date : %s \n", ptr->terminalData.transactionDate); 
		printf("Transaction Amount : %.4f\n", ptr->terminalData.transAmount);
		uint8_t stindex = ptr->transState; 
		printf("Transaction State : %s \n" ,state[stindex]); 
		printf("Terminal Max Amount : %.4f\n", ptr->terminalData.maxTransAmount); 
		printf("Cardholder Name : %s\n", ptr->cardHolderData.cardHolderName); 
		printf("PAN: %s\n", ptr->cardHolderData.primaryAccountNumber); 
		printf("Card Expiration Date : %s \n", ptr->cardHolderData.cardExpirationDate); 
		printf("#############################\n \n");
	}
}
 // ====================== End of listSavedTransactions function ==================== //
 
  // ====================== Implement recieveTransactionDataTest function ==================== //
 void recieveTransactionDataTest(void)
{
	// ========= create Test cards ========= //

	ST_cardData_t card[4] =
	{
		{.cardExpirationDate = "05/30",.cardHolderName = "TarikzakiMohamedMRamadan",.primaryAccountNumber = "083443230346969318"}, // Approved
		{.cardExpirationDate = "06/23",.cardHolderName = "MahmoudsamirMohmedAhmed",.primaryAccountNumber = "2747732760863908339"},   // DECLINED_INSUFFECIENT_FUND
		{.cardExpirationDate = "06/26",.cardHolderName = "GamalfadlaliMohmedali",.primaryAccountNumber = "25558569495666551"},  // Blocked DECLINED_STOLEN_CARD
		{.cardExpirationDate = "06/26",.cardHolderName = "GamalfadlaliMohmedali",.primaryAccountNumber = "92092671015840642"}  // Fraud card 
	};

	// ========= create Test terminal ============ //
	ST_terminalData_t terminal[4] =
	{
		{.maxTransAmount = 6000,.transactionDate = "16/11/2022",.transAmount = 500}, // Approved
		{.maxTransAmount = 6000,.transactionDate = "16/11/2022",.transAmount = 1500}, // DECLINED_INSUFFECIENT_FUND
		{.maxTransAmount = 6000,.transactionDate = "16/11/2022",.transAmount = 1250}, // Blocked Account, Declined Stolen Card
		{.maxTransAmount = 6000,.transactionDate = "16/11/2022",.transAmount = 1250} // Account is not found in accountsDB array, so it is Fraud Card
	};
	// ========== Test states ================= //
	EN_transState_t state[4] = { APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, FRAUD_CARD };

	printf("Tester Name: Tarik zaki M. M. Ramadan\n");
	printf("Functions Name:  recieveTransactionData \n");

	ST_transaction_t trans1 = { .cardHolderData = card[0],.terminalData = terminal[0],.transactionSequanceNumber = 0,.transState = state[0] };
	printf("Test Case 1: \n");
	recieveTransactionData(&trans1);

	ST_transaction_t trans2 = { .cardHolderData = card[1],.terminalData = terminal[1],.transactionSequanceNumber = 1,.transState = state[1] };
	printf("Test Case 2: \n");
	recieveTransactionData(&trans2);
	
	ST_transaction_t trans3 = { .cardHolderData = card[2],.terminalData = terminal[2],.transactionSequanceNumber = 2,.transState = state[2] };
	printf("Test Case 3: \n");
	recieveTransactionData(&trans3);
	
	ST_transaction_t trans4 = { .cardHolderData = card[3],.terminalData = terminal[3],.transactionSequanceNumber = 3,.transState = state[3] };
	printf("Test Case 4: \n");
	recieveTransactionData(&trans4);

}

  // ====================== End of recieveTransactionDataTest function ==================== //
 
 
   // ====================== Implement isValidAccountTest function ======================== //
  
 void isValidAccountTest(void)
{
	const uint8_t lenght = 2;

	ST_cardData_t TestCards[2] =
	{
		{.primaryAccountNumber = "2559591304059987" }, // not in the data base // 
		{.primaryAccountNumber = "92092671015840642" } // not in the data base // 
	};

	ST_accountsDB_t* Testaccount_ptr = NULL;
	// =========================== list of expected output ================================ //
	uint8_t expectedOutputs[2][18] = { "ACCOUNT_NOT_FOUND" , "ACCOUNT_NOT_FOUND" }; 

	printf("Tester Name: Tarik zaki M. M. Ramadan\n");
	printf("Function Name: isValidAccount\n");
	for (uint8_t i = 0; i < lenght; i++)
	{

		printf("Test Case %d: %s \n", i + 1, TestCards[i].primaryAccountNumber);
		printf("Expected Result: %s \n", expectedOutputs[i]);
		printf("Actual Result: %s \n", isValidAccount(&TestCards[i], Testaccount_ptr) == SERVER_OK ? "SERVER_OK" : "ACCOUNT_NOT_FOUND");
	}
}

  // ====================== End of isValidAccountTest function =========================== //

    // ====================== Implement isBlockedAccountTest function ======================== //
 
 void isBlockedAccountTest(void)
{
	const uint8_t lenght = 5;

	ST_accountsDB_t Testaccounts[5] = { {0} };
	
	// ========= get the first 5 elements in the accounts database =========== //
	for (uint8_t i = 0; i < 5; i++)
	{
		Testaccounts[i] = accountsDB[i];
	}

	// ========= list of expected output =========== //
	uint8_t expectedOutputs[5][10] = { "SERVER_OK","SERVER_OK","BLOCKED","SERVER_OK","BLOCKED" };

	printf("Tester Name: Tarik zaki M. M. Ramadan\n");
	printf("Function Name: isBlockedAccount\n");
	for (uint8_t i = 0; i < lenght; i++)
	{

		printf("Test Case %d: %s \n", i + 1, Testaccounts[i].primaryAccountNumber);
		printf("Expected Result: %s \n", expectedOutputs[i]);
		printf("Actual Result: %s \n", isBlockedAccount(&Testaccounts[i]) == SERVER_OK ? "SERVER_OK" : "BLOCKED");
	}
}
   // ====================== End of isBlockedAccountTest function =========================== //
 
 
    // ====================== Implement isAmountAvailableTest function ======================== //
 
 void isAmountAvailableTest(void)
{
	const uint8_t lenght = 3;
	ST_accountsDB_t TestAccount = { .balance = 5000 };
	ST_terminalData_t Testterminals[3] = { {.transAmount=5500},{.transAmount=5000},{.transAmount=100} };

	// ======== list of expected output ====== //
	uint8_t expextedOutputs[3][12] = { "LOW_BALANCE","SERVER_OK","SERVER_OK"};
	printf("Tester Name: Tarik zaki M. M. Ramadan\n");
	printf("Function Name: isAmountAvailable\n");
	printf("the amount in the Test account is 5000 \n"); 
	for (uint8_t i = 0; i < lenght; i++)
	{

		printf("Test Case %d: %.2f \n", i + 1,Testterminals[i].transAmount);
		printf("Expected Result: %s \n", expextedOutputs[i]);
		printf("Actual Result: %s \n", isAmountAvailable(&Testterminals[i],&TestAccount) == SERVER_OK? "SERVER_OK" : "LOW_BALANCE");
	}
}
 
    // ====================== End of isAmountAvailableTest function =========================== //
 
    // ====================== Implement saveTransactionTest function ======================== //
 void saveTransactionTest(void)
{
	// ====== create Test cards ======= //
	ST_cardData_t card[4] =
	{
		{.cardExpirationDate = "05/30",.cardHolderName = "TarikzakiMohamedMRamadan",.primaryAccountNumber = "083443230346969318"},
		{.cardExpirationDate = "06/23",.cardHolderName = "MahmoudsamirMohmedAhmed",.primaryAccountNumber = "2747732760863908339"},
		{.cardExpirationDate = "06/26",.cardHolderName = "GamalfadlaliMohmedali",.primaryAccountNumber = "25558569495666551"},
		{.cardExpirationDate = "06/26",.cardHolderName = "GamalfadlaliMohmedali",.primaryAccountNumber = "92092671015840642"}
	};

	// ======================= create Test terminal ========================== //  
	ST_terminalData_t terminal[4] =
	{
		{.maxTransAmount = 6000,.transactionDate = "14/12/2022",.transAmount = 500},
		{.maxTransAmount = 6000,.transactionDate = "14/12/2022",.transAmount = 1500},
		{.maxTransAmount = 6000,.transactionDate = "14/12/2022",.transAmount = 1250},
		{.maxTransAmount = 6000,.transactionDate = "14/12/2022",.transAmount = 1250}
	};
	// ============================= Test states =========================== //
	EN_transState_t state[4] = { APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, FRAUD_CARD, };

	printf("Tester Name: Tarik zaki M. M. Ramadan\n");
	printf("Functions Name: saveTransaction & listSavedTransactions\n");
	

	ST_transaction_t trans1 = { .cardHolderData = card[0],.terminalData = terminal[0],.transactionSequanceNumber = 0,.transState = state[0] };
	printf("Test Case 1: \n");
	saveTransaction(&trans1);

	ST_transaction_t trans2 = { .cardHolderData = card[1],.terminalData = terminal[1],.transactionSequanceNumber = 1,.transState = state[1] };
	printf("Test Case 2: \n");
	saveTransaction(&trans2);
	
	ST_transaction_t trans3 = { .cardHolderData = card[2],.terminalData = terminal[2],.transactionSequanceNumber = 2,.transState = state[2] };
	printf("Test Case 3: \n");
	recieveTransactionData(&trans3);
	
	ST_transaction_t trans4 = { .cardHolderData = card[3],.terminalData = terminal[3],.transactionSequanceNumber = 3,.transState = state[3] };
	printf("Test Case 4: \n");
	recieveTransactionData(&trans4);
	
}

     // ====================== End of saveTransactionTest function =========================== //
 
     // ====================== Implement listSavedTransactionsTest function ======================== //
      
      void listSavedTransactionsTest(void)
{
	// ====== save transaction & listSavedTransactions is validated using the same function ========= //
	
	saveTransactionTest(); 

}
      
     // ====================== End of listSavedTransactionsTest function =========================== //    
      
      
