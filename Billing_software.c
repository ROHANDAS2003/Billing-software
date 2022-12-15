#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>

char FileName[50];

struct items
{
    char item[20];
    float price;
    int qty;
};

struct order
{
    char customer[50];
    char date[50];
    int numOfItems;
    struct items itm[50];
};


void SaveInvoiceHeader(char name[50], char date[30])
{
    FILE *file;
    file = fopen(FileName, "a");

    fprintf(file, "\t    Company name   ");
    fprintf(file, "\n-----------------------------------------");
    fprintf(file, "\nDate: %s", date);
    fprintf(file, "\nInvoice To: %s", name);
    fprintf(file, "\n");
    fprintf(file, "-----------------------------------------\n");
    fprintf(file, "Items\t\t");
    fprintf(file, "Qty\t\t");
    fprintf(file, "Total\t\t");
    fprintf(file, "\n-----------------------------------------");
    fprintf(file, "\n");

    fclose(file);
}

void SaveInvoiceBody(char item[30], int qty, float price)
{
    FILE *file;
    file = fopen(FileName, "a");

    fprintf(file, "%s\t\t", item);
    fprintf(file, "%d\t\t",qty);
    fprintf(file, "%.2f\t\t",qty*price);
    fprintf(file, "\n");

    fclose(file);
}

void SaveInvoiceFooter(float total, float cgst, float disc)
{
    FILE *file;
    file = fopen(FileName, "a");

    fprintf(file, "\n");

    float discount = total*(disc/100), netTotal = total - discount, cal_cgst = netTotal*(cgst/100), grandTotal = netTotal + (2*cal_cgst);

    fprintf(file, "------------------------------------------\n");
    fprintf(file, "Sub Total\t\t\t%.2f", total);
    fprintf(file, "\nDiscount @%.f%s\t\t\t%.2f", disc, "%", discount);
    fprintf(file, "\n\t\t\t\t----------");
    fprintf(file, "\nNet Total\t\t\t%.2f", netTotal);
    fprintf(file, "\nCGST @%.f%s\t\t\t%.2f", cgst, "%", cal_cgst);
    fprintf(file, "\nSGST @%.f%s\t\t\t%.2f", cgst, "%", cal_cgst);
    fprintf(file, "\n------------------------------------------");
    fprintf(file, "\nGrand Total\t\t\t%.2f",grandTotal);
    fprintf(file, "\n------------------------------------------");

    fclose(file);
}

void GenerateBillHeader(char name[50], char date[30])
{
    printf("\n\n");
    printf("\t    Company name   ");
    printf("\n-----------------------------------------");
    printf("\nDate: %s", date);
    printf("\nInvoice To: %s", name);
    printf("\n");
    printf("-----------------------------------------\n");
    printf("Items\t\t");
    printf("Qty\t\t");
    printf("Total\t\t");
    printf("\n-----------------------------------------");
    printf("\n");
}

void GenarateBillBody(char item[30], int qty, float price)
{
    printf("%s\t\t", item);
    printf("%d\t\t",qty);
    printf("%.2f\t\t",qty*price);
    printf("\n");
}

void GenerateBillFooter(float total, float cgst, float disc)
{
    printf("\n");

    float discount = total*(disc/100), netTotal = total - discount, cal_cgst = netTotal*(cgst/100), grandTotal = netTotal + (2*cal_cgst);

    printf("------------------------------------------\n");
    printf("Sub Total\t\t\t%.2f", total);
    printf("\nDiscount @%.f%s\t\t\t%.2f", disc, "%", discount);
    printf("\n\t\t\t\t----------");
    printf("\nNet Total\t\t\t%.2f", netTotal);
    printf("\nCGST @%.f%s\t\t\t%.2f", cgst, "%", cal_cgst);
    printf("\nSGST @%.f%s\t\t\t%.2f", cgst, "%", cal_cgst);
    printf("\n------------------------------------------");
    printf("\nGrand Total\t\t\t%.2f",grandTotal);
    printf("\n------------------------------------------");

}

bool file_exist(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    bool is_exist = false;
    if (fp != NULL)
    {
        is_exist = true;
        fclose(fp);
    }
    return is_exist;
}

void Create()
{   
    system("CLS");
    printf("\n\t\t======== Delete invoice ========\n\n");
    fflush(stdin);

    struct order ord;
    int n;
    float total, cgst, disc;
    char save;

    printf("Enter the name of customer: ");
    gets(FileName);
    strcpy(ord.customer, FileName);
    strcat(FileName, ".txt");
    strcpy(ord.date, __DATE__);
    fflush(stdin);
    printf("\n\nNumber of items: ");
    scanf("%d", &n);
    ord.numOfItems = n;

    for(int i=0; i<n; i++)
    {
        fflush(stdin);
        printf("\n\n");
        printf("Name of item %d: ", i+1);
        fgets(ord.itm[i].item, 20, stdin);
        // ord.itm[i].item(strlen(ord.itm[i].item)-1)=0;
        printf("Quantity of item: ");
        scanf("%d", &ord.itm[i].qty);
        printf("Price of item: ");
        scanf("%f", &ord.itm[i].price);
        total += ord.itm[i].qty * ord.itm[i].price;
    }

    printf("\nDiscount in %s, if no discount enter 0: ", "%");
    scanf("%f", &disc);
    printf("\nCGST in %s, if no CGST enter 0: ", "%");
    scanf("%f", &cgst);

    GenerateBillHeader(ord.customer, ord.date);
    for(int i=0; i<ord.numOfItems; i++)
    {
        GenarateBillBody(ord.itm[i].item, ord.itm[i].qty, ord.itm[i].price);
    }
    GenerateBillFooter(total, cgst, disc);

    fflush(stdin);
    printf("\n\n Want to save the Invoice [y/n]: ");
    scanf("%c", &save);

    if(save == 'y')
    {
        SaveInvoiceHeader(ord.customer, ord.date);

        for(int i=0; i<ord.numOfItems; i++)
        {
        SaveInvoiceBody(ord.itm[i].item, ord.itm[i].qty, ord.itm[i].price);
        }

        SaveInvoiceFooter(total, cgst, disc);

        printf("\n Invoice succesfully saved.");
    }
    else
    {
        printf("\n Invoice discarded.");
    }

    printf("\n\n Press any key to close Create Window:");
    getch();
}

void Delete()
{
    system("CLS");
    printf("\n\t\t======== Delete invoice ========\n\n");

    char name[50];
    fflush(stdin);
    printf("Enter the name of customer: ");
    gets(name);
    strcat(name, ".txt");

    if (remove(name) == 0)
    {
        printf("\nInvoice: %s has been deleted succesfully.", name);
    }
    else
    {
        printf("\nInvoice: %s doesn't found.", name);
    }

    printf("\n\n Press any key to close Delete Window:");
    getch();
}

void Search()
{
    system("CLS");
    printf("\n\t\t======== Search invoice ========\n\n");

    char name[50];

    fflush(stdin);
    printf("Enter the name of customer: ");
    gets(name);
    strcat(name, ".txt");

    char *filename = name;

    if (file_exist(filename))
    {
        char str[54];
        FILE *file;
        file = fopen(name, "r");

        printf("\n\n");
        while (fgets(str, 54, file) != NULL)
        {
            printf("%s", str);
        }

        fclose(file);
    }
    else
    {
        printf("Invoice: %s doesn't exist.", name);
    }

    printf("\n\n Press any key to close Search Window:");
    getch();
}

int main()
{   
    bool Run = true;
    int opt;

    while (Run)
    {
        system("CLS");
        printf("\n\t\t======== Welcome to Billing software ========\n\n");
        printf("Choose what you wanna do.");
        printf("\n 1. Create invoice.\n 2. Delete invoice. \n 3. Search invoice. \n 4. Exit software.\n\n Your input: ");
        scanf("%d", &opt);

        switch (opt)
        {
        case 1:
            Create();
            break;

        case 2:
            Delete();
            break;

        case 3:
            Search();
            break;

        case 4:
            Run = false;
            break;

        default:
            break;
        }
    }

    return 0;
}