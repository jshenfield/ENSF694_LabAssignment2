/*
 *  lab2exe_A.cpp
 *  ENSF 694 Lab 2 Exercise A
 */

int my_strlen(const char *s);
/*  Duplicates my_strlen from <cstring>, except return type is int.
 *  REQUIRES
 *     s points to the beginning of a string.
 *  PROMISES
 *     Returns the number of chars in the string, not including the
 *     terminating null.
 */

int my_strlen(const char *s){
    int counter = 0; // initialize counters
    int i = 0;
    while(*(s + i) != '\0'){ // while the value at index is not equal to the terminating character
        counter++; // increment counter and i
        i++;
    }

    return counter; // return the number of chars in the C string
}

void my_strncat(char *dest, const char *source, int n);
/*  Duplicates strncat from <cstring>, except return type is void.
 */

void my_strncat(char *dest, const char *source, int n){
    int i = 0;
    while(*(dest + i) != '\0'){ // while the value at index is not equal to the terminating character
        i++;
    }

    int j = 0;
    while(j < n && *(source + j) != '\0'){
        dest[i + j] = source[j]; // Add characters to destination array until terminating character is hit
        j++;
    }
    dest[i + j] = '\0'; // Add terminating character to end
    
}


#include <iostream>
#include <cstring>
using namespace std;

int main(void)
{
    char str1[7] = "banana";
    const char str2[] = "-tacit";
    const char* str3 = "-toe";
    
    /* point 1 */
    char str5[] = "ticket";
    char my_string[100]="";
    int bytes;
    int length;
    
    /* using my_strlen libarary function */
    length = (int) my_strlen(my_string);
    cout << "\nLine 1: my_string length is " << length;
  
    /* using sizeof operator */
    bytes = sizeof (my_string);
    cout << "\nLine 2: my_string size is " << bytes << " bytes.";
   
    /* using strcpy libarary function */
    strcpy(my_string, str1);
    cout << "\nLine 3: my_string contains: " << my_string;
   
    length = (int) my_strlen(my_string);
    cout << "\nLine 4: my_string length is " << length << ".";
   
    my_string[0] = '\0';
    cout << "\nLine 5: my_string contains:\"" << my_string << "\"";
  
    length = (int) my_strlen(my_string);
    cout << "\nLine 6: my_string length is " <<  length << ".";
   
    bytes = sizeof (my_string);
    cout << "\nLine 7: my_string size is still " << bytes << " bytes.";
 
    /* strncat append the first 3 characters of str5 to the end of my_string */
    strncat(my_string, str5, 3);
    cout << "\nLine 8: my_string contains:\"" << my_string << "\"";
  
    length = (int) my_strlen(my_string);
    cout << "\nLine 9: my_string length is " << length << ".";
   
    strncat(my_string, str2,  4);
    cout << "\nLine 10: my_string contains:\"" << my_string << "\"";
    
    /* strncat append ONLY up ot '\0' character from str3 -- not 6 characters */
    strncat(my_string, str3, 6);
    cout << "\nLine 11: my_string contains:\"" << my_string << "\"";
   
    length = (int) my_strlen(my_string);
    cout << "\nLine 12; my_string has " << length << " characters.";

    cout << "\n\nUsing strcmp - C library function: ";
    
    cout << "\n\"ABCD\" is less than \"ABCDE\" ... strcmp returns: " <<
    strcmp("ABCD", "ABCDE");

    cout << "\n\"ABCD\" is less than \"ABND\" ... strcmp returns: " <<
    strcmp("ABCD", "ABND");
    
    cout << "\n\"ABCD\" is equal than \"ABCD\" ... strcmp returns: " <<
    strcmp("ABCD", "ABCD");
 
    cout << "\n\"ABCD\" is less than \"ABCd\" ... strcmp returns: " <<
    strcmp("ABCD", "ABCd");

    cout << "\n\"Orange\" is greater than \"Apple\" ... strcmp returns: " <<
    strcmp("Orange", "Apple") << endl;
    return 0;
}
