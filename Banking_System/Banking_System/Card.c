#include"card.h"


EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {
	printf("Enter The Card Holder Name: ");
	scanf("%s", cardData->cardHolderName);
	if (cardData->cardHolderName != NULL && strlen(cardData->cardHolderName) >= 20 && strlen(cardData->cardHolderName) <= 24) {
		for (uint8_t i = 0; i < strlen(cardData->cardHolderName); i++) {
			if (cardData->cardHolderName[i] >= '0' && cardData->cardHolderName[i] <= '9')
				return WRONG_NAME;
		}
		return OK;
	}
	return WRONG_NAME;
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {
	printf("Enter The Card Expiry Date: ");
	scanf("%s", cardData->cardExpirationDate);
	if (cardData->cardExpirationDate == NULL || strlen(cardData->cardExpirationDate) > 5)
		return WRONG_EXP_DATE;

	if (cardData->cardExpirationDate[2] != '/')
		return WRONG_EXP_DATE;

		for (int i = 0; i < 5; i++) {
			if (i == 2)
				continue;
			else
				if (cardData->cardExpirationDate[i] < '0' || cardData->cardExpirationDate[i]>'9')
					return WRONG_EXP_DATE;
		}

		return OK;
}


EN_cardError_t getCardPAN(ST_cardData_t* cardData) {
	printf("Enter The Card Card Pan: ");
	scanf("%s", cardData->primaryAccountNumber);

	if (strlen(cardData->primaryAccountNumber) < 16 || strlen(cardData->primaryAccountNumber) > 19)
		return WRONG_PAN;

	for (uint8_t i = 0; i < strlen(cardData->primaryAccountNumber); i++) {
		if (cardData->primaryAccountNumber[i] < '0' || cardData->primaryAccountNumber[i]>'9')
			return WRONG_PAN;
		}
	return OK;
}