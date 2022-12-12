
//
 // Server_Module Header File
 // server.h
 // Tarik Zaki Mohamed (tarik.z.ramadan@gmail.com)
 // Application Server_Module Definition (server.h) 
 // Start date DD/MM/YYYY 05-11-2022
 // Testing date DD/MM/YYYY 15-11-2022
 // Finish date DD/MM/YYYY 16-11-2022
 // Copyrights (c) Tarik Zaki Mohamed
 // 
 //
 


 // ===========Header Guards============ //
#ifndef _SERVER_H_
#define _SERVER_H_

#include <stdint.h> // using uint8_t
// ============ Use the following typedef as-is: ==================== //

// ============ this definition is for EN_transState_t enumerator Type ==================== //

typedef enum EN_transState_t
{
     APPROVED,
	 DECLINED_INSUFFECIENT_FUND,
	 DECLINED_STOLEN_CARD,
	 FRAUD_CARD,
	 INTERNAL_SERVER_ERROR
}EN_transState_t;

// ============ this definition is for ST_transaction_t transaction Data Structure Type ==================== //

	typedef struct ST_transaction_t
{
     ST_cardData_t cardHolderData;
     ST_terminalData_t terminalData;
	 EN_transState_t transState;
     uint32_t transactionSequanceNumber;
}ST_transaction_t;

// ============ this definition is for EN_serverError_t enumerator Type ==================== //

typedef enum EN_serverError_t 
{
     SERVER_OK,
	 SAVING_FAILED,
	 TRANSACTION_NOT_FOUND,
	 ACCOUNT_NOT_FOUND,
	 LOW_BALANCE,
	 BLOCKED_ACCOUNT
}EN_serverError_t ;

// ============ this definition is for EN_accountState_t enumerator Type ==================== //

typedef enum EN_accountState_t
{
     RUNNING,
     BLOCKED
}EN_accountState_t;

// ============ this definition is for ST_accountsDB_t accounts Data Structure Type ==================== //

typedef struct ST_accountsDB_t
{
     float balance;
     EN_accountState_t state;
     uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;

// ============ Use the following functions prototypes as is: ==================== //

EN_transState_t recieveTransactionData(ST_transaction_t *transData);
EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence);
EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence);
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountRefrence);
EN_serverError_t saveTransaction(ST_transaction_t *transData);


_Bool isStringEqual(uint8_t* src, uint8_t* des);
uint8_t len(uint8_t* str);

// ============ Use the following Test functions as is: ==================== //

void listSavedTransactions(void);

// ============ test functions ==================== //
void recieveTransactionDataTest(void);

void isValidAccountTest(void);

void isBlockedAccountTest(void);

void isAmountAvailableTest(void);

void saveTransactionTest(void);

void listSavedTransactionsTest(void);



#endif 
// ============End of server.h================== //

 