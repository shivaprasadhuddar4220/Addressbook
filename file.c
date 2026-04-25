#include <stdio.h>
#include "file.h"


void saveContactsToFile(AddressBook *addressBook) 
{
    //logic to Save contact to file
    FILE *fp;
    if((fp=fopen("contact.csv","w"))==NULL)
    {
        fprintf(stderr,"file can't open\n");
        return;
    }

    for(int i=0;i<addressBook->contactCount;i++)
    
    {
        fprintf(fp,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }

}


void loadContactsFromFile(AddressBook *addressBook) 
{   
    //Logic to load contacts from file
    FILE *fp;
    if((fp=fopen("contact.csv","r"))==NULL){
        fprintf(stderr,"file not found");
        return;
    }
    addressBook->contactCount = 0;

    while((fscanf(fp,"%[^,],%[^,],%[^\n] ",addressBook->contacts[addressBook->contactCount].name,
                                           addressBook->contacts[addressBook->contactCount].phone,
                                           addressBook->contacts[addressBook->contactCount].email))==3)
    
    {
        addressBook->contactCount++;
    }

    fclose(fp);
}