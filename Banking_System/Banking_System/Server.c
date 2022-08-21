#include "Server.h"
extern ST_accountsDB_t AccDB[255] = { {500,"1234567899876543210"},{10000,"1234567899876543211"},{50000,"1234567899876543212"} };
extern ST_transaction_t TransDB[255] = { 0 };
uint16_t transactionNumbers = 0;
uint16_t accountNumber = 3;

EN_transState_t recieveTransactionData(ST_transaction_t* transData) {
	if (isValidAccount(&transData->cardHolderData) != tOK) return DECLINED_STOLEN_CARD;
	if (isAmountAvailable(&transData->cardHolderData, &transData->terminalData) != tOK)
		return DECLINED_INSUFFECIENT_FUND;
	else {
		for (int i = 0; i < accountNumber; i++)
			if (strcmp(transData->cardHolderData.primaryAccountNumber, AccDB[i].primaryAccountNumber) == 0)
				AccDB[i].balance = AccDB[i].balance - transData->terminalData.transAmount;
	}
		return APPROVED; 
}	

EN_serverError_t isValidAccount(ST_cardData_t* cardData) {
	for (int i = 0; i < accountNumber; i++)
		if (strcmp(cardData->primaryAccountNumber, AccDB[i].primaryAccountNumber)==0)
			return tOK;
	return DECLINED_STOLEN_CARD;
}

EN_serverError_t isAmountAvailable(ST_cardData_t* cardData,ST_terminalData_t* termData) {
	for (int i = 0; i < accountNumber; i++)
		if (strcmp(cardData->primaryAccountNumber, AccDB[i].primaryAccountNumber) == 0)
			if (AccDB[i].balance < termData->transAmount)
				return LOW_BALANCE;
	return tOK;


}

EN_serverError_t saveTransaction(ST_transaction_t* transData) {
	if (transactionNumbers == 255)return SAVING_FAILED;
	else {
		TransDB[transactionNumbers].cardHolderData = transData->cardHolderData;
		TransDB[transactionNumbers].terminalData = transData->terminalData;
		TransDB[transactionNumbers].transactionSequenceNumber = transactionNumbers+59534;
		TransDB[transactionNumbers].transState = recieveTransactionData(transData) == 0 ? APPROVED : recieveTransactionData(transData);
		transactionNumbers++;
		return tOK;
	}
}

EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData){ 
	for (int i = 0; i < transactionNumbers; i++)
{
	if (TransDB[i].transactionSequenceNumber == transactionSequenceNumber) {
		transData = &TransDB[i];
		return tOK;
	}
}
return TRANSACTION_NOT_FOUND;
}