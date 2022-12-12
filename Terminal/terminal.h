
//
 // Terminal_Module Header File
 // terminal.h
 // Tarik Zaki Mohamed (tarik.z.ramadan@gmail.com)
 // Application Terminal_Module Definition (terminal.h) 
 // Start date DD/MM/YYYY 05-11-2022
 // Testing date DD/MM/YYYY 15-11-2022
 // Finish date DD/MM/YYYY 16-11-2022
 // Copyrights (c) Tarik Zaki Mohamed
 // 
 //




// ===========Header Guards============ //
#ifndef Terminal_H
#define Terminal_H

// ============ Use the following typedef as-is: ==================== //

 _Bool isTMonthValid(uint8_t* transactionDate);

// ============ this definition is for TerminalData Structure Type ==================== //


typedef struct ST_terminalData_t
{
float transAmount;
float maxTransAmount;
uint8_t transactionDate[11];
}ST_terminalData_t;

// ============ this definition is for Error_State enumerator Type ==================== //

typedef enum EN_terminalError_t
{
TERMINAL_OK,
WRONG_DATE,
EXPIRED_CARD,
INVALID_CARD,
INVALID_AMOUNT,
EXCEED_MAX_AMOUNT,
INVALID_MAX_AMOUNT
}EN_terminalError_t ;

// ============ Use the following functions prototypes as is: ==================== //

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData);
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData);
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData);
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData);
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount);

// ============ Use the following functions prototypes as is Optional: ==================== // 

EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData); 


// ============ Use the following Test functions as is: ==================== //

void getTransactionDateTest(void);
void isCardExpiredTest(void); 
void getTransactionAmountTest(void);
void isBelowMaxAmountTest(void);
void setMaxAmountTest(void);
void isValidCardPANTest(void);

#endif

// ============End of terminal.h================== //