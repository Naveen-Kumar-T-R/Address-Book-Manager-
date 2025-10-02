#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) 
{
    FILE *fptr = fopen("contacts.csv", "w");
    //fprintf(fptr, "#%d\n", addressBook-> contactCount);
    for(int i = 0; i < addressBook-> contactCount; i++)
    {
        fprintf(fptr, "%s,%s,%s\n", addressBook -> contacts[i] . name, addressBook -> contacts[i] . phone, addressBook -> contacts[i] . email);
    }
    fclose(fptr);
}

void loadContactsFromFile(AddressBook *addressBook) 
{
    addressBook->contactCount = 0;
    FILE *fptr = fopen("contacts.csv", "r");
    int n;
    if(fptr == NULL)
    {
        printf("file is empty");
        return;
    }
    //fscanf(fptr,"#%d\n", &addressBook-> contactCount);


    for(int i = 0; i < 100; i++)
    {
        
        int res=fscanf(fptr, "%[^,],%[^,],%s\n", addressBook -> contacts[i] . name, addressBook -> contacts[i] . phone, addressBook -> contacts[i] . email);
        if(res==3)
        {
            addressBook->contactCount++;
        }
        else
        {
            break;
        }
    }
    fclose(fptr);
    
}
