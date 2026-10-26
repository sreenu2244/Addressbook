#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;

void initialize(AddressBook *addressBook);
void loadContact(AddressBook *addressBook);
void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void saveContactsToFile(AddressBook *addressBook);
void saveAndExit(AddressBook *addressBook);
int validate_name(const char *name);
int validate_phone(const char *phone);
int validate_email(const char *email);
int isValidName(const char *name);
int isValidPhone(const char *phone);
int isValidEmail(const char *email);

#endif
