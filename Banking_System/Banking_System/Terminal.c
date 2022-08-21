#include "Terminal.h"

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {
	time_t raw;
	time(&raw);
	strftime(termData->transactionDate, sizeof(termData->transactionDate), "%d/%m/%Y", localtime(&raw));
	return Ok;
}

EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData) {
	char cardM[3] = { cardData.cardExpirationDate[0] , cardData.cardExpirationDate[1] },
		cardY[3] = { cardData.cardExpirationDate[3] , cardData.cardExpirationDate[4] },
		terminalM[3] = { termData.transactionDate[3] , termData.transactionDate[4] },
		terminalY[3] = { termData.transactionDate[8] , termData.transactionDate[9] };
	if ((strcmp(terminalY, cardY) > 0) || ((strcmp(terminalY, cardY) == 0) && (strcmp(terminalM, cardM) > 0)))
		return EXPIRED_CARD;
	return Ok;
}

EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData) {
	uint32_t val = 0, temp = 0;
	for (uint32_t i = 0; i < strlen(cardData->primaryAccountNumber); i++) {
		if (i & 1)
			val += (cardData->primaryAccountNumber[i] - '0');
		else {
			temp = (cardData->primaryAccountNumber[i] - '0') * 2;
			while (temp >= 10)
				temp -= 9;
			val += temp;
		}
	}
	if (val % 10 != 0)
		return INVALID_CARD;
	return Ok;
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {
	printf("Enter The Transaction Amount: ");
	float temp=0.0;
	scanf("%f", &temp);
	if (temp <= 0)
		return INVALID_AMOUNT;
	else {
		termData->transAmount = temp;
		return Ok;
	}
}


EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {
	if (termData->transAmount > termData->maxTransAmount)
		return EXCEED_MAX_AMOUNT;
	else
		return Ok;
}


EN_terminalError_t setMaxAmount(ST_terminalData_t* termData) {
	//printf("Enter the max amount: ");
	float temp = 5000.0;
	//scanf("%f", &temp);
	if (temp <= 0)
		return INVALID_MAX_AMOUNT;
	else {
		termData->maxTransAmount = temp;
			return Ok;
	}
}
