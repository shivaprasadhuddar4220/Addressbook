#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

//function to list all contact 
void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    // Sort contacts by name using bubble sort
    for (int i = 0; i < addressBook->contactCount - 1; i++) {
        for (int j = 0; j < addressBook->contactCount - i - 1; j++) {

            // Comparing two contact names
            if (strcmp(addressBook->contacts[j].name,addressBook->contacts[j + 1].name) > 0) 
            {
                // Swaping
                Contact temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j + 1];
                addressBook->contacts[j + 1] = temp;
            }
        }
    }
   
    printf("*******************************************************************************\n");
    printf("                  ---------->YOUR CONTACTS LIST<----------                     \n");
    printf("*******************************************************************************\n");
    printf("S.No\t     NAME   \t\tPHONE NUMBER \t\t     EMAIL\t\n");
    printf("-------------------------------------------------------------------------------\n");
    
    //Printing all contact details
    for(int i=0; i<addressBook->contactCount; i++)
    printf("%-5d|\t %-15s |\t %-15s |\t %-20s |\n",i+1,addressBook -> contacts[i].name,addressBook ->contacts[i].phone,addressBook -> contacts[i].email);
    printf("-------------------------------------------------------------------------------\n");

    
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
     //Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
    /* Define the logic to create a Contacts */
    Contact *c =&addressBook->contacts[addressBook->contactCount]; //point to next empty contact place
    char name[100],phone[20],email[50];
    int phone_no,val_mail;

    //Get and validating name
    do{
        printf("Enter the name : ");
        scanf(" %[^\n]",name);

        
        if(!validatename(name))    //To validate name
        {
            printf("-------------------------------------------------------------------------------\n");
            printf("                               Invalid name\n");
            printf("-------------------------------------------------------------------------------\n");
        }
    }while(!validatename(name));

    //Get and validating phone number
    do
    {
        printf("Enter phone number : ");    
        scanf(" %[^\n]",phone);

        //Validate phone number
        phone_no = validatephone(addressBook, phone);

        if (phone_no == 0)
        {
            printf("-------------------------------------------------------------------------------\n");
            printf("                         Invalid phone number!\n");
            printf("-------------------------------------------------------------------------------\n");
        }
        else if (phone_no == -1)
        {
            printf("-------------------------------------------------------------------------------\n");
            printf("               Phone number already exists. Try another.\n");
            printf("-------------------------------------------------------------------------------\n");
        }

    }while(phone_no !=1);

    //Get and validate email
    do
    {
        printf("Enter email : ");
        scanf(" %[^\n]",email);

        //Validate email
        val_mail= validateemail(addressBook, email);

        if (val_mail == 0)
        {
            printf("-------------------------------------------------------------------------------\n");
            printf("                          Invalid email!\n");
            printf("-------------------------------------------------------------------------------\n");
        }
        else if (val_mail == -1)
        {
            printf("-------------------------------------------------------------------------------\n");
            printf("              eamil already exists. Try another.\n");
            printf("-------------------------------------------------------------------------------\n");
        }

    }while(val_mail != 1);
    
// copying the input data (name ,phone number, email) to the contact list
    strcpy(c ->name,name);     
    strcpy(c ->phone,phone);
    strcpy(c-> email,email);

    addressBook->contactCount++ ; //Increasing contact count

    printf("-------------------------------------------------------------------------------\n");
    printf("                  Contact created Successfully\n");
    printf("-------------------------------------------------------------------------------\n");

    
}

void searchContact(AddressBook *addressBook) 
{
    int choice,flag=0,sl_no=1;
    char name1[50],phone1[50],email1[50],i,sub_phone;

    /* Define the logic for search */
    printf("-------------------------------------------------------------------------------\n");
    printf("Search by\n");
    printf("1.Name\n");
    printf("2.Phone\n");
    printf("3.Email\n");
    printf("-------------------------------------------------------------------------------\n");
    printf("-------------------------------------------------------------------------------\n");
    printf("Enter your choice: ");
    scanf(" %d",&choice);
    switch (choice)
    {
    case 1:
        printf("*******************************************************************************\n");
        printf("                 You choiced the search by name:\n");
        printf("*******************************************************************************\n");
        printf("Enter name : ");
        scanf(" %[^\n]",name1);
        flag=0;
        
        for(int i=0; i<addressBook->contactCount; i++)
        {
            //Case substring search
            char *sub_string=strcasestr(addressBook->contacts[i].name,name1);
            
            if(sub_string != NULL)   //checking condition that return value is not eqaul to null
            {
                printf("*******************************************************************************\n");
                printf("S.No\t     NAME   \t\tPHONE NUMBER \t\t     EMAIL\t\n");
                printf("-------------------------------------------------------------------------------\n");
                printf("%-5d|\t %-15s |\t %-15s |\t %-20s |\n",sl_no,addressBook -> contacts[i].name,addressBook ->contacts[i].phone,addressBook -> contacts[i].email);
                printf("-------------------------------------------------------------------------------\n");
                sl_no++;
                flag=1; 
            }     
        }

        if(flag==0)
        {
            printf("-------------------------------------------------------------------------------\n");
            printf("                     Contact not present\n");
            printf("-------------------------------------------------------------------------------\n");
        }
            printf("*******************************************************************************\n");
        break;


    case 2:
        printf("*******************************************************************************\n");
        printf("             You choiced the search by phone number:\n");
        printf("*******************************************************************************\n");
        printf("Enter the phone number : ");
        scanf(" %[^\n]",phone1);

        flag =0;
        for(int i=0; i<addressBook->contactCount; i++)
        {
            //comparing two phone numbers 
            sub_phone=strcmp(addressBook->contacts[i].phone,phone1);

            if(sub_phone==0)   //checking the function return value is equal to zero or not
            {
                printf("*******************************************************************************\n");
                printf("S.No\t     NAME   \t\tPHONE NUMBER \t\t     EMAIL\t\n");
                printf("-------------------------------------------------------------------------------\n");
                printf("%-5d|\t %-15s |\t %-15s |\t %-20s |\n",sl_no,addressBook -> contacts[i].name,addressBook ->contacts[i].phone,addressBook -> contacts[i].email);
                printf("-------------------------------------------------------------------------------\n");
                sl_no++;
                flag=1;
                break;
            }
        }
        
        if(flag=0)
        {
            printf("-------------------------------------------------------------------------------\n");
            printf("                     Contact not present\n");
            printf("-------------------------------------------------------------------------------\n");
        }
            printf("*******************************************************************************\n");
        break;
        
    case 3:
        printf("*******************************************************************************\n");
        printf("                   You choiced the search by email:\n");
        printf("*******************************************************************************\n");
        printf("Enter the email id : ");
        scanf(" %[^\n]",email1);
        flag=0;
        
        for(int i=0; i<addressBook->contactCount; i++)
        {
            char sub_email=strcmp(addressBook->contacts[i].email,email1);
            if(sub_email  ==  0)   //checking the funciton return value is equal to zero or not
            {   
                //printing contact details
                printf("*******************************************************************************\n");
                printf("S.No\t     NAME   \t\tPHONE NUMBER \t\t     EMAIL\t\n");
                printf("-------------------------------------------------------------------------------\n");
                printf("%-5d|\t %-15s |\t %-15s |\t %-20s |\n",sl_no,addressBook -> contacts[i].name,addressBook ->contacts[i].phone,addressBook -> contacts[i].email); 
                printf("-------------------------------------------------------------------------------\n");
                sl_no++;
                flag=1;
                break;
            }
        }
        
        if(flag==0)
        {
            printf("-------------------------------------------------------------------------------\n");
            printf("                        Contact not present\n");
            printf("-------------------------------------------------------------------------------\n");
        }
            printf("*******************************************************************************\n");
        break;
    
    default:
        printf("*******************************************************************************\n");
        printf("                             Invalid \n");
        printf("*******************************************************************************\n");
        break;
    }
}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    int choice;
    char name1[50], phone1[50], email1[50];
    char ed_name[50], ed_phone[50], ed_email[50];
    
    printf("-------------------------------------------------------------------------------\n");
    printf("Search by\n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("------------------------------------------------------------------------------\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    int arr[100];          
    int count = 0;     

    switch (choice)
    {
    case 1:
    //Searching contact by name
        printf("*******************************************************************************\n");
        printf("                 You choiced the search by name:\n");
        printf("*******************************************************************************\n");
        
        printf("Enter name: ");
        scanf(" %[^\n]", name1);

        //count = 0;

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            //checking is substring is present in the string or not
            char *sub_string = strcasestr(addressBook->contacts[i].name, name1);

            if (sub_string != NULL)
            {
                arr[count] = i;
                count++;
            }
        }
        break;

    case 2:
    //Searching contact by phone number
        printf("*******************************************************************************\n");
        printf("             You choiced the search by phone number:\n");
        printf("*******************************************************************************\n");
        printf("Enter phone number: ");
        scanf(" %[^\n]", phone1);

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            //comparing two phone numbers
            if (strcmp(addressBook->contacts[i].phone, phone1) == 0)
            {
                arr[count] = i;
                count++;
            }
        }
        break;


    case 3:
    //Searching contact by email
        printf("*******************************************************************************\n");
        printf("                   You choiced the search by email:\n");
        printf("*******************************************************************************\n");
        printf("Enter email: ");
        scanf(" %[^\n]", email1);

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            //comparing two emails
            if (strcmp(addressBook->contacts[i].email, email1) == 0)
            {
                arr[count] = i;
                count++;
            }
        }
        break;

    default:
        printf("Invalid choice \n");
        return;
    }

    if (count == 0) 
    {
        printf("-------------------------------------------------------------------------------\n");
        printf("                        Contact not present\n");
        printf("-------------------------------------------------------------------------------\n");
        return;
    }
    int select = 1;

    //printing the contact details
    for(int i=0; i<count; i++)
    {
        printf("*******************************************************************************\n");
        printf("S.No\t     NAME   \t\tPHONE NUMBER \t\t     EMAIL\t\n");
        printf("-------------------------------------------------------------------------------\n");
        printf("%-5d|\t %-15s |\t %-15s |\t %-20s |\n",i+1, addressBook -> contacts[arr[i]].name,
                                                            addressBook ->contacts[arr[i]].phone,
                                                            addressBook -> contacts[arr[i]].email);
        printf("-------------------------------------------------------------------------------\n");
    
    }

    if (count > 1)
    {
        printf("\nMultiple contacts found.\n");
        printf("Which one do you want to edit? (1-%d): ", count);
        scanf("%d", &select);

        //checking that entered select number should be greater than 1 and less than count
        if (select < 1 || select > count)
        {
            printf("Invalid \n");
            return;
        }
    }

    int pos = arr[select - 1];  //geting actual index of the selected contact
    printf("-------------------------------------------------------------------------------\n");
    printf("What do you want to edit?\n");
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf("-------------------------------------------------------------------------------\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    
    switch (choice)
    {
        case 1:
            //Get and validate name
            do
            {
                printf("Enter new name: ");
                scanf(" %[^\n]", ed_name);

                if (!validatename(ed_name))                   //validating name
                    printf("Invalid name! Try again.\n");
            } while (!validatename(ed_name));

            strcpy(addressBook->contacts[pos].name, ed_name); //copying new_name in the place of old name
            break;

        case 2:
        {   
            int res;
            //Get and validate phone number
            do
            {
                printf("Enter new phone: ");
                scanf(" %[^\n]", ed_phone);
                res = validatephone(addressBook, ed_phone);       // \validating phone number

                if (res == 0)
                    printf("Invalid phone number!\n");
                else if (res == -1)
                    printf("Phone number already exists!\n");

            } while (res != 1);
                
            strcpy(addressBook->contacts[pos].phone, ed_phone); //copying new phone number in the place of old phone number
            break;
        }
        case 3:
        {
            int res;
            //Get and validate email
            do
            {
            printf("Enter new email: ");
            scanf(" %[^\n]", ed_email);
            
            res = validateemail(addressBook, ed_email);         //validating email id

            if (res == 0)
                printf("Invalid email format!\n");
            else if (res == -1)
                printf("Email already exists!\n");

            } while (res != 1);
            strcpy(addressBook->contacts[pos].email, ed_email); //copying new email in place of old
            break;
        }
        default:
            printf("Invalid choice \n");
            return;
    }
    printf("*******************************************************************************\n");
    printf("                    Contact updated successfully\n");
    printf("*******************************************************************************\n");
}


void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    int choice;
    char name1[50],phone1[50],email1[50],i,sub_phone;
    int arr[200],count=0;

    /* Define the logic for search */
    printf("-------------------------------------------------------------------------------\n");
    printf("Search by\n");
    printf("1.Name\n");
    printf("2.Phone\n");
    printf("3.Email\n");
    printf("-------------------------------------------------------------------------------\n");
    printf("-------------------------------------------------------------------------------\n");
    printf("Enter your choice: ");
    scanf(" %d",&choice);

    switch (choice)
    {
    case 1:
        printf("*******************************************************************************\n");
        printf("                 You choiced the search by name:\n");
        printf("*******************************************************************************\n");
        printf("Enter name : ");
        scanf(" %[^\n]",name1);

        for(int i=0; i<addressBook->contactCount; i++)
        {
            //comparing provided name with list of contact names   
            char *sub_string=strcasestr(addressBook->contacts[i].name,name1);    
            if(sub_string != NULL)
            {
                arr[count] = i;
                count++;
            }     
        }
        break;

    case 2:
        printf("*******************************************************************************\n");
        printf("             You choiced the search by phone number:\n");
        printf("*******************************************************************************\n");
        printf("Enter the phone number : ");
        scanf(" %[^\n]",phone1);

        for(int i=0; i<addressBook->contactCount; i++)
        {
            //comparing provided phone number with list of contact phone number
            sub_phone=strcmp(addressBook->contacts[i].phone,phone1);
            if(sub_phone==0) 
            {
                arr[count] = i;
                count++;
            }
        }
        break;
        
    case 3:
        printf("*******************************************************************************\n");
        printf("                   You choiced the search by email:\n");
        printf("*******************************************************************************\n");
        printf("Enter the email id : ");
        scanf(" %[^\n]",email1);
        
        for(int i=0; i<addressBook->contactCount; i++)
        {
            //comparing provided email with list of contact email
            char sub_email=strcmp(addressBook->contacts[i].email,email1);
            if(sub_email==0)
            {   
                arr[count] = i;
                count++;
            }
        }
        break;
    
    default:
        printf("*******************************************************************************\n");
        printf("                             Invalid \n");
        printf("*******************************************************************************\n");
        break;
    }

    if(count == 0)
    {
        printf("-------------------------------------------------------------------------------\n");
        printf("                        Contact not present\n");
        printf("-------------------------------------------------------------------------------\n");
        return;
    }

    //printing contact details 
    for(int i=0; i<count; i++)
    {
        printf("*******************************************************************************\n");
        printf("S.No\t     NAME   \t\tPHONE NUMBER \t\t     EMAIL\t\n");
        printf("-------------------------------------------------------------------------------\n");
        printf("%-5d|\t %-15s |\t %-15s |\t %-20s |\n",i+1, addressBook -> contacts[arr[i]].name,
                                                            addressBook ->contacts[arr[i]].phone,
                                                            addressBook -> contacts[arr[i]].email);
        printf("-------------------------------------------------------------------------------\n");
    
    }

    char ch;
    int select;

    //checking count is greater than 1 or not 
    if(count>1)
    {
        printf("which contact do you want to delete (1 - %d)?",count);
        scanf("%d",&select);
    }
    
    printf("-------------------------------------------------------------------------------\n");
    printf("If you want to continue? y/Y : ");
    scanf(" %c",&ch);

    if(ch== 'y' || ch == 'Y')
    {   
        //shifting the contacts after deleting the selected one     
        int pos = arr[select-1];
        for(int i = pos;  i<addressBook->contactCount; i++)
        {
            addressBook->contacts[i] = addressBook->contacts[i+1];
        }
        addressBook->contactCount--;

        printf("*******************************************************************************\n");
        printf("                     Contact deleted successfully. \n");
        printf("*******************************************************************************\n");
    }
    else
    {
        printf("*******************************************************************************\n");
        printf("                     Contact Not Deleted. \n");
        printf("*******************************************************************************\n");

    }

}

int validatename(char *str)
{

    int i=0;
    while(*str)
    {
        //checking name consist of the Uppercase, Lowercase,spacial_characters(space,dot).
        if(!((str[i] >= 'A' && str[i] <= 'Z')||(str[i] >= 'a' && str[i] <='z' ) || str[i] == ' ' || str[i] == '.'))
        {
            return 0;
        }
        str++;
    }
    return 1;
}

int validatephone(AddressBook *addressBook, char *str)
{
    //checking length
    if(strlen(str) != 10)
    {
        return 0;
    }

    //Checking digits only
    for(int i=0; i<10; i++)
    {
        if(str[i] < '0' || str[i] > '9')
            return 0;
    }
    
    // Check if phone already exists
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].phone, str) == 0)
        {
            return -1;   // return value for duplicate
        }
    }

    return 1;    // valid & unique

}


int validateemail(AddressBook *addressBook,char *str)
{
    int Count = 0;
    int len = strlen(str);

    for (int i = 0; i < len; i++)
    {
        if (str[i] == '@')
        {
            Count++;
            continue;
        }

        //checking name consist of the Lowercase,Digits,spacial_characters(underscore,dot).
        if (!((str[i] >= 'a' && str[i]<= 'z') || (str[i] >= '0' && str[i] <= '9') || str[i] == '_' || str[i] == '.'))
        {
            return 0;  
        }
    }

    if (Count != 1)
        return 0;       

    char suffix[] = ".com";             //assigning the suffix 
    int suffix_len = strlen(suffix);    //Finding length of the suffix

    //checking string length is lesser than the suffix_len
    if (len <= suffix_len)
        return 0;

    //checking condition that comparing two strings 
    if (strcmp(str + (len - suffix_len), suffix) != 0)
        return 0;      


    for (int i = 0; i<addressBook->contactCount; i++)
    {
        //checking comparison of emails is present or not in the contact list
        if (strcmp(addressBook->contacts[i].email,str) == 0)
        {
            return -1;  
        }
    }
    return 1; 
}
