#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100   //Maximum number os contact allowed

typedef struct {
    char name[50];      //conatact name
    char phone[20];    //contact phone number
    char email[50];    //contact email address
} Contact;

typedef struct {
    Contact contacts[100];   //Array of contacts
    int contactCount;        //Total number of stored contacts
} AddressBook;

void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook, int sortCriteria);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);
int validatename(char *str);
int validatephone(AddressBook *addressBook, char *str);
int validateemail(AddressBook *addressBook, char *str);

#endif
