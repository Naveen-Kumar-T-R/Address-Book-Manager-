#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include <ctype.h>


int name_valid(char *Name)
{
    while(*Name != '\0')
    {
        if((*Name >= 'a' && *Name <= 'z') || (*Name >= 'A' && *Name <= 'Z') || *Name == ' ' || *Name == '.')
        {
            Name++;
        }
        else
        {
            return 0;
            
        }
      
    }
    return 1;
    
}
int num_valid(char *num)
{
    int count = 0, i;
    for(i = 0; num[i] != '\0'; i++)
    {
        if(num[i] >= '0' && num[i] <= '9')
        {
            count++;
        }
        else
        {
            return 0;
        }
    }
    if(count != 10)
    {
        return 0;
    }
    return 1;

}
int dup(char *dup, AddressBook *addressBook)
{
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if((strcmp(addressBook -> contacts[i] . phone, dup) == 0) || (strcmp(addressBook -> contacts[i] . email, dup) == 0))
        {
            return 0;
        }
    }
    return 1;
}

int email_valid(char *mail, char *c)
{
    int count = 0, index;
    int len = strlen(mail);
    for(int i = 0; mail[i] != '\0'; i++)
    {
        if(i == 0)
        {
            if((mail[i] >= 'a' && mail[i] <= 'z') || (mail[i] >= 'A' && mail[i] <= 'Z') || (mail[i] >= '0' && mail[i] <= '9'))
            {
                continue;
            }
            else
            {
                return 0;
            }
        }
        else if((mail[i] == '.' && mail[i+1] == '.') || (mail[i] == '_' && mail[i+1] == '_') || (mail[i] == '-' && mail[i+1] == '-') || mail[i] == ' ')
        {
            return 0;
        }
        else if((mail[i] >= 'a' && mail[i] <= 'z') || (mail[i] >= 'A' && mail[i] <= 'Z') || (mail[i] >= '0' && mail[i] <= '9'))
        {
            continue;
        }
        else if(mail[i] == '@' && (mail[i + 1] == '.'))
        {
            return 0;
        }
        else if(mail[i] == '@')
        {
            index = i;
            count++;
        }
        
    }

    for(int j = index + 1; j < len - 4; j++)
    {
        if(isdigit(mail[j]))
        {
            return 0;
        }
    }


    if(count != 1)
    {
        return 0;
    }
    char  *cptr = strstr(mail, c);

    if(strcmp(cptr, c) == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
    
}
int search_contact(AddressBook *addressBook, char *search)
{
    int found = 0;
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcasestr(addressBook -> contacts[i] . name, search) != NULL || strstr(addressBook -> contacts[i] . phone, search) != NULL || strstr(addressBook -> contacts[i] . email, search) != NULL)
        {
            printf("Name----->%s\tPhone no.----->%s\tEmail-ID----->%s\n", addressBook -> contacts[i] . name, addressBook -> contacts[i] . phone, addressBook -> contacts[i] . email);   
            
            found = 1;
        }
                    
    }
    if(found == 0)
    {
        return 0;
    }
}

int Search_Contact(AddressBook *addressBook, char *search)
{
    for(int i = 0; i < addressBook -> contactCount; i++)
    {
        if(strcmp(addressBook -> contacts[i] . name, search) == 0 || strcmp(addressBook -> contacts[i] . phone, search) == 0 || strcmp(addressBook -> contacts[i] . email, search) == 0)
        {
            printf("\nContact Found.\n");
            printf("Name----->%s\tPhone no.----->%s\tEmail-ID----->%s\n", addressBook -> contacts[i] . name, addressBook -> contacts[i] . phone, addressBook -> contacts[i] . email);
            return i;
        }
    }
    return -1;
}

void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    char str_temp1[50], str_temp2[50], str_temp3[50];
    int k = 1;
    switch(sortCriteria)
    {
        case 1:
        {
            for(int i = 0; i < addressBook->contactCount-1; i++)
            {
                for(int j = 0; j < addressBook->contactCount -1- i; j++)
                {
                    if(strcmp(addressBook -> contacts[j] . name , addressBook -> contacts[j+1] . name) > 0)
                    {
                        strcpy(str_temp1, addressBook -> contacts[j] . name);
                        strcpy(str_temp2, addressBook -> contacts[j] . phone);
                        strcpy(str_temp3, addressBook -> contacts[j] . email);
                        strcpy(addressBook -> contacts[j] . name, addressBook -> contacts[j+1] . name);
                        strcpy(addressBook -> contacts[j] . phone, addressBook -> contacts[j+1] . phone);
                        strcpy(addressBook -> contacts[j] . email, addressBook -> contacts[j+1] . email);
                        strcpy(addressBook -> contacts[j+1] . name, str_temp1);
                        strcpy(addressBook -> contacts[j+1] . phone, str_temp2);
                        strcpy(addressBook -> contacts[j+1] . email, str_temp3); 
                    }
                }
            }
            for(int i = 0; i < addressBook->contactCount; i++)
            {
                printf("%d. %s\t%s\t%s\n", k, addressBook -> contacts[i] . name, addressBook -> contacts[i] . phone, addressBook -> contacts[i] . email);
                k++;
            }

        }
        break;
        case 2:
        {
            for(int i = 0; i < addressBook->contactCount-1; i++)
            {
                for(int j = 0; j < addressBook->contactCount-1 -i; j++)
                {
                    if(strcmp(addressBook -> contacts[j] . phone, addressBook -> contacts[j+1] . phone) > 0)
                    {
                        strcpy(str_temp1, addressBook -> contacts[j] . name);
                        strcpy(str_temp2, addressBook -> contacts[j] . phone);
                        strcpy(str_temp3, addressBook -> contacts[j] . email);
                        strcpy(addressBook -> contacts[j] . name, addressBook -> contacts[j+1] . name);
                        strcpy(addressBook -> contacts[j] . phone, addressBook -> contacts[j+1] . phone);
                        strcpy(addressBook -> contacts[j] . email, addressBook -> contacts[j+1] . email);
                        strcpy(addressBook -> contacts[j+1] . name, str_temp1);
                        strcpy(addressBook -> contacts[j+1] . phone, str_temp2);
                        strcpy(addressBook -> contacts[j+1] . email, str_temp3); 
                    }
                }
            }
            for(int i = 0; i < addressBook->contactCount; i++)
            {
                printf("%d. %s\t%s\t%s\n", k, addressBook -> contacts[i] . name, addressBook -> contacts[i] . phone, addressBook -> contacts[i] . email);
                k++;
            }

        }
        break;
        case 3:
        {
            for(int i = 0; i < addressBook->contactCount-1; i++)
            {
                for(int j = 0; j < addressBook->contactCount-1 - i; j++)
                {
                    if(strcmp(addressBook -> contacts[j] . email, addressBook -> contacts[j+1] . email) > 0)
                    {
                        strcpy(str_temp1, addressBook -> contacts[j] . name);
                        strcpy(str_temp2, addressBook -> contacts[j] . phone);
                        strcpy(str_temp3, addressBook -> contacts[j] . email);
                        strcpy(addressBook -> contacts[j] . name, addressBook -> contacts[j+1] . name);
                        strcpy(addressBook -> contacts[j] . phone, addressBook -> contacts[j+1] . phone);
                        strcpy(addressBook -> contacts[j] . email, addressBook -> contacts[j+1] . email);
                        strcpy(addressBook -> contacts[j+1] . name, str_temp1);
                        strcpy(addressBook -> contacts[j+1] . phone, str_temp2);
                        strcpy(addressBook -> contacts[j+1] . email, str_temp3);  
                    }
                }
            }
            for(int i = 0; i < addressBook->contactCount; i++)
            {
                printf("%d. %s\t%s\t%s\n", k, addressBook -> contacts[i] . name, addressBook -> contacts[i] . phone, addressBook -> contacts[i] . email);
                k++;
            }
        }
        break;
    }
    
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}
void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    char Name[50], num[20], mail[50], c[5] = ".com";;
    int Res;

    do 
    {
        printf("\nEnter the name: ");
        scanf(" %[^\n]", Name);
        if(name_valid(Name))
        {
            strcpy(addressBook -> contacts[addressBook -> contactCount] . name , Name);
        }
        else
        {
            printf("\nEnter the valid name.\n");
        }
    }while(name_valid(Name) == 0);
    printf("\n");
    
    do 
    {
        do
        {
            printf("Enter the phone no.: ");
            scanf(" %[^\n]", num);
            if(num_valid(num))
            {
                if(dup(num, addressBook))
                {
                    strcpy(addressBook -> contacts[addressBook -> contactCount] . phone, num);
                }
                else
                {
                    printf("\nEnter the correct number.\n");
                }
            }
            else
            {
                printf("\nEnter the valid phone number(0 to 9).\n");
            }
        }while(num_valid(num) == 0);
    }while(dup(num, addressBook) == 0);
    printf("\n");

    do 
    {
        do 
        {
            printf("Enter the email id: ");
            scanf(" %[^\n]", mail);
            if(email_valid(mail, c))
            {
                if(dup(mail, addressBook))
                {
                    strcpy(addressBook -> contacts[addressBook -> contactCount] . email, mail);
                }
                else
                {
                    printf("\nEnter the correct Email-ID.\n");
                }
            }
            else
            {
                printf("\nEnter the valid email id.\n");
            }
        }while(email_valid(mail, c) == 0);

    }while(dup(mail, addressBook) == 0);
    
    addressBook->contactCount++;
}

void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    int search;
    char s_name[20], s_phone[20], s_mail[50];
    do
    {
        printf("\nBy what you are searching: ");
        printf("\n1. Name\n2. Mobile No.\n3. Mail Id\n");
        printf("Enter your choice: ");
        scanf("%d", &search);

        switch(search)
        {
            case 1:
            {
                int n_res;
                do 
                {
                    do 
                    {
                        printf("\nEnter the name to search: ");
                        scanf(" %[^\n]", s_name);
                        if(name_valid(s_name))
                        {
                            n_res = search_contact(addressBook, s_name);
                            if(n_res == 0)
                            {
                                printf("\nContact not found.\n");
                            }
                            else
                            {
                                printf("\nContact Found.\n");
                            }
                        }
                        else
                        {
                            printf("\nEnter the valid Name.\n");
                        }
                    }while(name_valid(s_name) == 0);

                }while(n_res == 0);

            }
            break;
            case 2:
            {
                int s_Res, valid_res;
                do
                {
                    do
                    {
                        printf("\nEnter the phone number to search: ");
                        scanf(" %[^\n]", s_phone);
                        valid_res = num_valid(s_phone);

                        if(valid_res)
                        {
                            s_Res = search_contact(addressBook, s_phone);
                            if(s_Res == 0)
                            {
                                printf("\nContact not found.\n");
                            }
                            else
                            {
                                printf("\nContact Found.\n");
                            }
                            
                        }
                        else
                        {
                            printf("Enter the valid number.\n");
                        }
                    }while(valid_res == 0);

                }while(s_Res == 0);


            }
            break;
            case 3:
            {
                int Ms_Res, Mvalid_res;
                do 
                {
                    do 
                    {
                        printf("\nEnter the email id to search: ");
                        scanf(" %[^\n]", s_mail);
                        char c[5] = ".com";
                        Mvalid_res = email_valid(s_mail, c);
                        // int count = 0;

                        if(Mvalid_res)
                        {
                            Ms_Res = search_contact(addressBook, s_mail);
                            if(Ms_Res == 0)
                            {
                                printf("\nContact not found.\n");
                            }
                            else
                            {
                                printf("\nContact Found.\n");
                            }
                        }
                        else
                        {
                            printf("\nEnter the valid email id.\n");
                        }

                    }while(Mvalid_res == 0);

                }while(Ms_Res == 0);
            }
            break;

            default:
            {
                printf("Invalid input.\n\n");
            }
        }
    }while(search > 3);

    
}

void editContact(AddressBook *addressBook)
{

    int e_choice, found = 0, n_found;
	/* Define the logic for Editcontact */
    do 
    {
        printf("By what you are Searching: \n1. Name\n2. Mobile no.\n3. Email-ID\n");
        printf("Enter your choice: ");
        scanf("%d", &e_choice);
        
        switch(e_choice)
        {
            case 1:
            {
                char e_name[50], new_name[50];
                int evalid_res;
                do 
                {
                    printf("Enter the name to search: ");
                    scanf(" %[^\n]", e_name);
                    evalid_res = name_valid(e_name);
                    if(evalid_res)
                    {
                        int j = Search_Contact(addressBook, e_name);
                        if(j == -1)
                        {
                            printf("\nContact not Found.\n1.Search Again\n2.Exit\n");
                            printf("Enter the choice: ");
                            scanf("%d", &n_found);
                            switch(n_found)
                            {
                                case 1: 
                                {
                                    editContact(addressBook);
                                }
                                break;
                                case 2:
                                {
                                    printf("Your Exited from edit contact.\n");
                                }
                            }


                        }
                        else
                        {
                            do 
                            {    
                                printf("\nEnter the new name: ");
                                scanf(" %[^\n]", new_name);
                                if(name_valid(new_name))
                                {
                                    strcpy(addressBook -> contacts[j].name,new_name);
                                    printf("Yes, Name Edited Successfully.\n");
                                }
                                else
                                {
                                    printf("\nEnter the valid name.\n");
                                }
                            }while(name_valid(new_name) == 0);

                        }

                    }
                    else
                    {
                        printf("Enter the valid name.\n");
                    }
                }while(evalid_res == 0);

            }
            break;
            case 2:
            {
                char e_phone[20], new_phone[20];
                int num_res, new_res, new_Res;
                do
                {
                    printf("Enter the phone number to edit: ");
                    scanf(" %[^\n]", e_phone);
                    num_res = num_valid(e_phone);
                    if(num_res)
                    {
                        int j = Search_Contact(addressBook, e_phone);
                        if(j == -1)
                        {
                            printf("\nContact not Found.\n1.Search Again\n2.Exit\n");
                            printf("Enter the choice: ");
                            scanf("%d", &n_found);
                            switch(n_found)
                            {
                                case 1: 
                                {
                                    editContact(addressBook);
                                }
                                break;
                                case 2:
                                {
                                    printf("Your Exited from edit contact.\n");
                                }
                            }


                        }
                        else
                        {
                            do 
                            {   
                                do
                                { 
                                    printf("\nEnter the new phone numder: ");
                                    scanf(" %[^\n]", new_phone);
                                    new_res = num_valid(new_phone);
                                    if(new_res)
                                    {
                                        new_Res = dup(new_phone, addressBook);
                                        if(new_Res)
                                        {
                                            strcpy(addressBook -> contacts[j].phone,new_phone);
                                            printf("Yes, Successfully edited.\n");
                                        }
                                        else
                                        {
                                            printf("Enter the correct number.\n");
                                        }
                                    }
                                    else
                                    {
                                        printf("\nEnter the valid phone number.\n");
                                    }
                                }while(new_res == 0);
                            }while(new_Res == 0);

                        }
                    }
                    else
                    {
                        printf("Enter the valid phone number.\n");
                    }
                }while(num_res == 0);

            }
            break;
            case 3:
            {
                char e_mail[50], new_mail[50], c[5] = ".com";
                int mail_res, new_res, new_Res;
                do
                {
                    printf("Enter the Email-ID to edit: ");
                    scanf(" %[^\n]", e_mail);
                    mail_res = email_valid(e_mail, c);
                    if(mail_res)
                    {
                        int j = Search_Contact(addressBook, e_mail);
                        if(j == -1)
                        {
                            printf("\nContact not Found.\n1.Search Again\n2.Exit\n");
                            printf("Enter the choice: ");
                            scanf("%d", &n_found);
                            switch(n_found)
                            {
                                case 1: 
                                {
                                    editContact(addressBook);
                                }
                                break;
                                case 2:
                                {
                                    printf("Your Exited from edit contact.\n");
                                }
                            }


                        }
                        else
                        {
                            do 
                            {   
                                do
                                { 
                                    printf("\nEnter the new Email-ID: ");
                                    scanf(" %[^\n]", new_mail);
                                    new_res = email_valid(new_mail, c);
                                    if(new_res)
                                    {
                                        new_Res = dup(new_mail, addressBook);
                                        if(new_Res)
                                        {
                                            strcpy(addressBook -> contacts[j].email, new_mail);
                                            printf("Yes, Successfully edited.\n");
                                        }
                                        else
                                        {
                                            printf("Enter the correct Email-ID.\n");
                                        }
                                    }
                                    else
                                    {
                                        printf("\nEnter the valid Email-ID.\n");
                                    }
                                }while(new_res == 0);
                            }while(new_Res == 0);

                        }
                        
                    }
                    else
                    {
                        printf("Enter the valid Email-ID to edit.\n");
                    }
                }while(mail_res == 0);

            }
            break;

            default:
            {
                printf("Invalid choice\n");
            }
        }
    }while(e_choice > 3);
       
}

void deleteContact(AddressBook *addressBook)
{
    int delete;
	/* Define the logic for deletecontact */
    printf("\nwhat do want to delete: \n1.Name\n2.Mobile number\n3.Email-ID\n");
    printf("Enter the choice: ");
    scanf("%d", &delete);

    switch(delete)
    {
        case 1:
        {
            char d_name[50], ch;
            do
            {
                printf("Enter the name to delete: ");
                scanf(" %[^\n]", d_name);

                if(name_valid(d_name))
                {
                    int i = Search_Contact(addressBook, d_name);
                    if(i == -1)
                    {
                        printf("Contact not Found.\n");
                        deleteContact(addressBook);

                    }
                    else
                    {     
                        printf("Do you want to delete: \n");
                        printf("Enter the choice to delete(y/n): ");
                        scanf(" %c", &ch);
                        switch(ch)
                        {
                            case 'y':
                            case 'Y':
                            {
                                for(int j = i; j < addressBook -> contactCount; j++)
                                {
                                    strcpy(addressBook -> contacts[j] . name, addressBook -> contacts[j+1] . name);
                                    strcpy(addressBook -> contacts[j] . phone, addressBook -> contacts[j+1] . phone);
                                    strcpy(addressBook -> contacts[j] . email, addressBook -> contacts[j+1] . email);
                                    
                                }
                                addressBook->contactCount--;
                                printf("Contact deleted successfully.\n");

                            }
                            break;
                            case 'n':
                            case 'N':
                            {
                                printf("You are exited from delete contact.\n");
                            }
                            break;

                            default:
                            {
                                printf("Invalid input.\n");
                            }
                        }
                        

                    }

                }
                else
                {
                    printf("Enter the valid name to delete.\n");
                }
                
            }while(name_valid(d_name) == 0);


        }
        break;
        case 2:
        {
            char d_phone[50], ch;
            do
            {
                printf("Enter phone number to delete: ");
                scanf(" %[^\n]", d_phone);

                if(num_valid(d_phone))
                {
                    int i = Search_Contact(addressBook, d_phone);
                    if(i == -1)
                    {
                        printf("Contact not Found.\n");
                        deleteContact(addressBook);

                    }
                    else
                    {     
                        printf("Do you want to delete: \n");
                        printf("Enter the choice to delete(y/n): ");
                        scanf(" %c", &ch);
                        switch(ch)
                        {
                            case 'y':
                            case 'Y':
                            {
                                for(int j = i; j < addressBook -> contactCount; j++)
                                {
                                    strcpy(addressBook -> contacts[j] . name, addressBook -> contacts[j+1] . name);
                                    strcpy(addressBook -> contacts[j] . phone, addressBook -> contacts[j+1] . phone);
                                    strcpy(addressBook -> contacts[j] . email, addressBook -> contacts[j+1] . email);
                                    
                                }
                                addressBook->contactCount--;
                                printf("Contact deleted successfully.\n");

                            }
                            break;
                            case 'n':
                            case 'N':
                            {
                                printf("\nYou are exited from delete contact.\n");
                            }
                            break;

                            default:
                            {
                                printf("Invalid input.\n");
                            }
                        }
                        

                    }
                }
                else
                {
                    printf("Enter the valid phone number to delete.\n");
                }
                
            }while(num_valid(d_phone) == 0);


        }
        break;
        case 3:
        {
            char d_mail[50], ch, c[5] = ".com";
            do
            {
                printf("Enter Email-ID to delete: ");
                scanf(" %[^\n]", d_mail);

                if(email_valid(d_mail, c))
                {
                    int i = Search_Contact(addressBook, d_mail);
                    if(i == -1)
                    {
                        printf("Contact not Found.\n");
                        deleteContact(addressBook);

                    }
                    else
                    {     
                        printf("Do you want to delete: \n");
                        printf("Enter the choice to delete(y/n): ");
                        scanf(" %c", &ch);
                        switch(ch)
                        {
                            case 'y':
                            case 'Y':
                            {
                                for(int j = i; j < addressBook -> contactCount; j++)
                                {
                                    strcpy(addressBook -> contacts[j] . name, addressBook -> contacts[j+1] . name);
                                    strcpy(addressBook -> contacts[j] . phone, addressBook -> contacts[j+1] . phone);
                                    strcpy(addressBook -> contacts[j] . email, addressBook -> contacts[j+1] . email);
                                    
                                }
                                addressBook->contactCount--;
                                printf("Contact deleted successfully.\n");

                            }
                            break;
                            case 'n':
                            case 'N':
                            {
                                printf("\nYou are exited from delete contact.\n");
                            }
                            break;

                            default:
                            {
                                printf("Invalid input.\n");
                            }
                        }
                        

                    }
                }
                else
                {
                    printf("Enter the valid Email-ID to delete.\n");
                }
                
            }while(email_valid(d_mail, c) == 0);

        }
        break;

        default:
        {
            printf("Invalid choice.\n");
            deleteContact(addressBook);
        }
    }

   
}