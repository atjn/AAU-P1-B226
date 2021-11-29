/**
 * Flushes the input buffer.
 * This is useful when taking input from the user with `scanf`,
 * because unreadable input might be left in the buffer, causing an infinite loop.
 * @param void
 * @return void
 */
void flushInput();


/**
 * Capitalises the first character of a string.
 * @param char* String of which first character will be uppercase.
 * @return void
 */
void capitaliseFirst(char*);

/**
 * Takes the letters in a char array and makes them all lower case.
 * @param char* String of which all characters will be lowercase.
 * @return void
 */
void toLowerCase(char*);
