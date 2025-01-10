/*
 * Login.h
 *
 *  Created on: 18 Sep 2024
 *      Author: ${Ahmed Saeed}
 */

#ifndef LOGIN_H_
#define LOGIN_H_



/*Struct holds the user data*/
typedef struct
{
	char name[7];
	char Password[5];

}tstrUsers;

/*Enum for error may happen*/
typedef enum
{
	Not_found,   						//0
	Exist,	        				  //1
	IncorrectUserorPassword    //2
}tenuLoginStatus;

extern tstrUsers astrUsersData[10];

tenuLoginStatus CheckEquality (const char*string1 ,const char* string2);
tenuLoginStatus UserExistance(const char *UserNameCpy,uint8* pu8UserPosition);
tenuLoginStatus PasswordCheck(char* u16PasswordCpy,uint8 u8UserPositionIndxCpy);
void UserInputReceive(char* acharUserInputCpy,uint8 u8NameSizeCpy);


#endif /* LOGIN_H_ */
