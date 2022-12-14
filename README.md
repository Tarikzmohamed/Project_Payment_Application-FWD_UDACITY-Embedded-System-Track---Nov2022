# Project_Payment_Application-FWD_UDACITY-Embedded-System-Track---Nov2022
this is the first project in the Embedded Systems Professional Track nanodegree for FWD_UDACITY Embedded System Track - Nov2022 


Project: Payment Application
Project Introduction
Payment systems are now available everywhere and everyone interacts with these systems every day.
There are different types of transactions you can make, SALE, REFUND, Pre-Authorization, and VOID.
•	SALE: means to buy something and its price will be deducted from your bank account.
•	REFUND: this means that you will return something and wants your money back to your bank account.
•	Pre-Authorization: means holding an amount of money from your account, e.g Hotel reservation.
•	VOID: this means canceling the transaction, e.g if the seller entered the wrong amount.
You are required to implement the SALE transaction only by simulating the card, terminal(ATM), and the server.
Project Requirements
1.	Development environment preparation
2.	Implement the card module
3.	Implement the terminal module
4.	Implement the server module
5.	Implement the application
6.	Testing the application


Project: Payment Application
Project Instructions

Application Flowchart


 
The project can be distributed over 6 main tasks:

Development environment preparation
1.	Create modules folders 
2.	Create .c and .h file for each module 
3.	Add header file guard 
4.	Create the main.c file 
Implement the card module
1.	Fill in card.h file with functions' prototypes and typedefs 
2.	Implement getCardHolderName function 
3.	Implement getCardExpiryDate function 
4.	Implement getCardPAN function 
Implement the terminal module
1.	Fill in terminal.h file with functions' prototypes and typedefs 
2.	Implement getTransactionDate function 
3.	Implement isCardExpried function 
4.	Implement gatTransactionAmount function 
5.	Implement isBelowMaxAmount function 
6.	Implement setMaxAmount function
Implement the server module
1.	Fill in server.h file with functions' prototypes and typedefs 
2.	Implement server-side accounts' database 
3.	Implement server-side transactions' database 
4.	Implement recieveTransactionData function 
5.	Implement isValidAccount function 
6.	Implement isAmountAvailable function 
7.	Implement saveTransaction function 
Implement the application
1.	Fill in application.h file with functions' prototypes 
2.	Implement appStart function
Testing the application
1.	Transaction approved user story 
2.	Exceed the maximum amount user story 
3.	Insufficient fund user story 
4.	Expired card user story 
5.	Invalid card user story
