#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"

//-------Initialize address book-------
void initialize(AddressBook *addressBook) {
    if (addressBook == NULL) {
        printf("Invalid address book.\n");
        return;
    }

    addressBook->contactCount = 0;
    loadContact(addressBook);
}

//------------name------------------

int validate_name(const char *name) {
    if (name == NULL || name[0] == '\0') {
        printf("Name cannot be empty.\n");
        return 0;
    }

    for (int i = 0; name[i] != '\0'; i++) {
        if (!isalpha((unsigned char)name[i]) && name[i] != ' ') {
            return 0;
        }
    }

    return 1;
}

int validate_phone(const char *phone) {
    if (phone == NULL || strlen(phone) != 10) {
        printf("Phone number must be exactly 10 digits.\n");
        return 0;
    }

    for (int i = 0; i < 10; i++) {
        if (!isdigit((unsigned char)phone[i])) {
            return 0;
        }
    }

    return 1;
}

int validate_email(const char *email) {
    if (email == NULL) {
        printf("Email cannot be empty.\n");
        return 0;
    }

    const char *at = strchr(email, '@');
    const char *dot = strrchr(email, '.');

    return (at != NULL && dot != NULL && at < dot && strcmp(dot, ".com") == 0);
}

int isValidName(const char *name) {
    return validate_name(name);
}

int isValidPhone(const char *phone) {
    return validate_phone(phone);
}

int isValidEmail(const char *email) {
    return validate_email(email);
}

void loadContact(AddressBook *addressBook) {
    if (addressBook == NULL) {
        printf("Invalid address book.\n");
        return;
    }

    addressBook->contactCount = 0;
    FILE *file = fopen("contacts.txt", "r");
    if (file == NULL) {
        printf("Error opening contacts file.\n");
        return;
    }

    char line[200];
    while (addressBook->contactCount < MAX_CONTACTS &&
           fgets(line, sizeof(line), file) != NULL) {
        int i = addressBook->contactCount;
        if (sscanf(line, "%49[^,],%19[^,],%49[^\n]",
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email) != 3) {
            break;
        }

        addressBook->contactCount++;
    }

    fclose(file);
}

//-------Create contact (1)-------

void createContact(AddressBook *addressBook) {
    if (addressBook == NULL) {
        printf("Invalid address book.\n");
        return;
    }

    if (addressBook->contactCount >= MAX_CONTACTS) {
        printf("Address book is full!\n");
        return;
    }

    Contact newContact = {0};

    printf("Enter name: ");
    scanf(" %49[^\n]", newContact.name);
    if (strlen(newContact.name) == 0) {
        printf("Name cannot be empty.\n");
        return;
    }
    if (!validate_name(newContact.name)) {
        printf("Invalid name. Please use only alphabetic characters.\n");
        return;
    }

    printf("Enter phone (10 digits): ");
    scanf(" %19[^\n]", newContact.phone);
    if (!validate_phone(newContact.phone)) {
        printf("Invalid phone number. Please enter exactly 10 digits.\n");
        return;
    }

    printf("Enter email: ");
    scanf(" %49[^\n]", newContact.email);
    if (!validate_email(newContact.email)) {
        printf("Invalid email. It should contain '@' and end with '.com'.\n");
        return;
    }

    addressBook->contacts[addressBook->contactCount] = newContact;
    addressBook->contactCount++;
    printf("Contact added!\n");
}

//-------Search contact (2)-------

void searchContact(AddressBook *addressBook) {
    if (addressBook == NULL) {
        printf("Invalid address book.\n");
        return;
    }

    char name[50];
    printf("Enter name to search: ");
    scanf(" %49[^\n]", name);

    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].name, name) == 0) {
            printf("Contact found: %s, %s, %s\n",
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email);
            return;
        }
    }

    printf("Contact not found.\n");
}
//-------Edit contact (3)-------

void editContact(AddressBook *addressBook) {
    if (addressBook == NULL) {
        printf("Invalid address book.\n");
        return;
    }

    char name[50];
    printf("Enter name to edit: ");
    scanf(" %49[^\n]", name);

    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].name, name) == 0) {
            printf("Editing contact: %s\n", name);

            printf("Enter new phone (10 digits): ");
            scanf(" %19[^\n]", addressBook->contacts[i].phone);
            if (!validate_phone(addressBook->contacts[i].phone)) {
                printf("Invalid phone number. It should be 10 digits.\n");
                return;
            }

            printf("Enter new email: ");
            scanf(" %49[^\n]", addressBook->contacts[i].email);
            if (!validate_email(addressBook->contacts[i].email)) {
                printf("Invalid email. It should contain '@' and end with '.com'.\n");
                return;
            }

            printf("Contact updated!\n");
            return;
        }
    }

    printf("Contact not found.\n");
}
//-------Delete contact (4)-------

void deleteContact(AddressBook *addressBook) {
    if (addressBook == NULL) {
        printf("Invalid address book.\n");
        return;
    }

    char name[50];
    printf("Enter name to delete: ");
    scanf(" %49[^\n]", name);

    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].name, name) == 0) {
            addressBook->contacts[i] = addressBook->contacts[addressBook->contactCount - 1];
            addressBook->contactCount--;
            printf("Contact deleted!\n");
            return;
        }
    }

    printf("Contact not found.\n");
}

//-------List all contacts (5)-------

void listContacts(AddressBook *addressBook) {
    if (addressBook == NULL) {
        printf("Invalid address book.\n");
        return;
    }

    if (addressBook->contactCount == 0) {
        printf("No contacts available.\n");
        return;
    }

    for (int i = 0; i < addressBook->contactCount; i++) {
        printf("Contact %d: %s, %s, %s\n",
               i + 1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }
}

void saveContactsToFile(AddressBook *addressBook) {
    if (addressBook == NULL) {

        return;
    }

    FILE *file = fopen("contacts.txt", "w");
    if (file == NULL) {
        printf("Error saving contacts.\n");
        return;
    }

    for (int i = 0; i < addressBook->contactCount; i++) {
        fprintf(file, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    fclose(file);
}


//-------Exit and save contacts (6)-------

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook);
    printf("Contacts saved. Exiting...\n");
}
