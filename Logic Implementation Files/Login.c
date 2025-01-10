#include "STD_Types.h"
#include "Login.h"
#include "USART.h"
#include <util/delay.h>


/*Array of struct of the provided users */
tstrUsers astrUsersData[10]=
{
		{
				"user01",
				"1111"
		},
		{
				"user02",
				"2222"
		},
		{
				"user03",
				"3333"
		},
		{
				"user04",
				"4444"
		},
		{
				"user05",
				"5555"
		},
		{
				"user06",
				"6666"
		},
		{
				"user07",
				"7777"
		},
		{
				"user08",
				"8888"
		},
		{
				"user09",
				"9999"
		},
		{
				"user10",
				"1010"
		}

};

/*String comparing Function to check enter user name and the stored names in the data base */
tenuLoginStatus CheckEquality (const char*string1 , const char* string2)
{
	uint8 flag = Exist;

	while ((*string1 != '\0') || (*string2 != '\0'))
	{
		if (*string1 == *string2)
		{
			string1++;
			string2++;
		}
		else
		{
			flag = Not_found; // used as doesn't match
			break;
		}
	}

	return flag;
}

/*Checking the entered User name existing or not Function*/
/*It will return pu8 holds the position of the user if it exists */
tenuLoginStatus UserExistance(const char *UserNameCpy, uint8* pu8UserPosition)
{
	tenuLoginStatus enuStatusLoc = Not_found;

	uint8 u8IteratorLoc = 0;
	*pu8UserPosition = 0;

	for (u8IteratorLoc = 0 ; u8IteratorLoc < 10 ; u8IteratorLoc++)
	{
		/*Comparing using the comparing implemented function */

		if (CheckEquality(UserNameCpy, astrUsersData[u8IteratorLoc].name) == Exist)
		{
			enuStatusLoc = Exist;
			//return the position of the user to use it in the check of the password to be for the same user

			break;
		}
	}

	*pu8UserPosition = u8IteratorLoc;

	return enuStatusLoc;
}

/*Password check function*/
tenuLoginStatus PasswordCheck(char* u16PasswordCpy, uint8 u8UserPositionIndxCpy)
{
	tenuLoginStatus enuStatusLoc = IncorrectUserorPassword;
	/*Using the returned user num from the comparing function*/
	if (CheckEquality(astrUsersData[u8UserPositionIndxCpy].Password, u16PasswordCpy) == Exist)
	{
		enuStatusLoc = Exist;
	}

	return enuStatusLoc;

}

void UserInputReceive(char* acharUserInputCpy, uint8 u8NameSizeCpy)
{
	uint8 u8CntrLoc = 0;
	uint8 DummyVarLoc;

	while(u8CntrLoc < u8NameSizeCpy)
	{

		DummyVarLoc = (uint8)USART_u16RecvDataSync();
		//To only receive the valid data and ignore the other
		if (((DummyVarLoc >= '0') && (DummyVarLoc <= '9')) || ((DummyVarLoc >= 'A') && (DummyVarLoc <= 'Z'))|| ((DummyVarLoc >= 'a') && (DummyVarLoc <= 'z')))
		{
			acharUserInputCpy[u8CntrLoc] = DummyVarLoc;
			u8CntrLoc++;
		}

	}
}


