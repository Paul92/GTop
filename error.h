/*
 *
 *      ERROR CODES
 *    1 - bizzare characters in input file
 *    2 - negative value
 *    4 - zero distance
 *    8 - angle >400
 *   16 - not enough arguments
 *   32 - too many arguments
 *   64 - wrong point order (path)
 *   128 - too many/little points
*/


#define ERROR_NUMBER 10

bool checkErrors();
void clearErrorBuff();
