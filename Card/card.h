
//
 // Card_Module Header File
 // card.h
 // Tarik Zaki Mohamed (tarik.z.ramadan@gmail.com)
 // Application card_Module Definition (card.h) 
 // Start date DD/MM/YYYY 05-11-2022
 // Testing date DD/MM/YYYY 15-11-2022
 // Finish date DD/MM/YYYY 16-11-2022
 // Copyrights (c) Tarik Zaki Mohamed
 // 
 //



// =========== Header Guards ============ //
#ifndef _CARD_H_
#define _CARD_H_

#include <stdint.h> // using uint8_t

// ============ Use the following typedef as-is: ==================== //


_Bool isStringAlpha(uint8_t* CardHolderName);
_Bool isStringnumeric(uint8_t* cardPAN);
_Bool isCMonthValid(uint8_t* cardExpirationDate);

// ============ this definition is for CardData Structure Type ==================== //
typedef struct ST_cardData_t
{
    uint8_t cardHolderName[25];
    uint8_t primaryAccountNumber[20];
    uint8_t cardExpirationDate[6];
}ST_cardData_t;

// ============ this definition is for Error_State enumerator Type ==================== //
typedef enum EN_cardError_t
{
    CARD_OK, 
    WRONG_NAME, 
    WRONG_EXP_DATE, 
    WRONG_PAN
}EN_cardError_t;

// ============ Use the following functions prototypes as is: ==================== //

EN_cardError_t getCardHolderName(ST_cardData_t *cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData);
EN_cardError_t getCardPAN(ST_cardData_t *cardData);

// ============ Use the following Test functions as is: ==================== //


void getCardHolderNameTest(void);

void getCardExpiryDateTest(void);

void getCardPANTest(void);




#endif 
// ============End of card.h================== //