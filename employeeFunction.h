#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct employee
{
    char name[25], address[20];
    int id, age, salary;
    int salaryPay;
} employees;

employees allEmployee[100];
int employeeCounter = 0;int printChoose()
{
    int choose;
    printf("\n1.)Add Employee\n2.)Search Employee\n3.)Print All Employee\n4.)Pay Salary\n5.)Exit\nChoose:");
    scanf("%d", &choose);
    system("cls");
    return choose;
}

void printEmployee(int index)
{
    printf("\n-----------------------------------------------------------\n");
    printf("Id: %d\nName: %s\nAge: %d\nAddress: %s\nSalary: %d\n",
           allEmployee[index].id, allEmployee[index].name, allEmployee[index].age,
           allEmployee[index].address, allEmployee[index].salary);
    printf("-----------------------------------------------------------\n");
}

void printAllEmployee()
{
    if (employeeCounter == 0)
    {
        printf("Add Employee First\n");
    }
    else
    {
        for (int i = 0; i < employeeCounter; i++)
        {
            printEmployee(i);
        }
    }
}

void addEmployee()
{
    FILE *add = fopen("employeeRec.dat", "a");
    FILE *empCount = fopen("empCount.data", "a");


    printf("Enter employee Id:");
    scanf("%d", &allEmployee[employeeCounter].id);

    printf("Enter employee Name:");
    scanf("%s", allEmployee[employeeCounter].name);

    printf("Enter employee Age:");
    scanf("%d", &allEmployee[employeeCounter].age);

    printf("Enter employee Address:");
    scanf("%s", allEmployee[employeeCounter].address);

    printf("Enter employee Salary:");
    scanf("%d", &allEmployee[employeeCounter].salary);

    printf("Pay Salary?:-");
    scanf("%d", &allEmployee[employeeCounter].salaryPay);
    employeeCounter++;
    system("cls");

    // Add employee to file
    // fprintf(add,"Id\t   Name\t\t\t\t\t    Age\t\tAddress\t\t\t\tSalary\n");

    fprintf(add, "%d\t %s\t\t\t\t\t%d\t\t%s\t\t\t\t%d\t\t%d\t\t%d\n", allEmployee[employeeCounter - 1].id,
            allEmployee[employeeCounter - 1].name, allEmployee[employeeCounter - 1].age,
            allEmployee[employeeCounter - 1].address, allEmployee[employeeCounter - 1].salary,
            allEmployee[employeeCounter -1].salaryPay,allEmployee[employeeCounter -1].salary - allEmployee[employeeCounter -1].salaryPay);

    fprintf(empCount, "%d\n", employeeCounter);

    fclose(add);
    fclose(empCount);
}
void paySalary() {
    FILE *file = fopen("employeeRec.dat", "r");
    FILE *tempFile = fopen("temp.txt", "w");


    int targetId, amountToPay;
    printf("Enter the employee ID to pay salary: ");
    scanf("%d", &targetId);

    char line[100];

    while (fgets(line, sizeof(line), file)) {
        int id, salaryAmt, salaryPaid, dueSalary,age;
        char name[25], address[20];
        sscanf(line, "%d%s%d%s%d%d%d\n", &id, name,&age, address, &salaryAmt, &salaryPaid, &dueSalary);

        if (id == targetId) {
            printf("Enter the amount of salary to pay: ");
            scanf("%d", &amountToPay);

            salaryPaid += amountToPay;
            dueSalary = salaryAmt - salaryPaid;

            fprintf(tempFile, "%d\t %s\t\t\t\t\t%d\t\t%s\t\t\t\t%d\t\t%d\t\t%d\n", id, name,age, address, salaryAmt, salaryPaid, dueSalary);
        } else {
            fputs(line, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove("employeeRec.dat");
    rename("temp.txt", "employeeRec.dat");
}

// Search Employee By their Name...
void searchEmployee() {
    FILE *file = fopen("employeeRec.dat", "r");

    int found = 0;
    char searchingName[100];
    printf("Enter Employee Name to search: ");
    scanf("%s", searchingName);

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        int id, age, salaryAmt, salaryPaid, dueSalary;
        char name[25], address[20];

        sscanf(line, "%d %s %d %s %d %d %d", &id, name, &age, address, &salaryAmt, &salaryPaid, &dueSalary);

        if (strcmp(searchingName, name) == 0) {
            printf("\n-----------------------------------------------------------\n");
            printf("Id: %d\nName: %s\nAge: %d\nAddress: %s\nSalaryAmt: %d\nSalaryPaid: %d\nSalaryDue: %d\n", id, name, age, address, salaryAmt,salaryPaid,dueSalary);
            printf("-----------------------------------------------------------\n");
            found = 1;
            break;
        }
    }

    fclose(file);

    if (found == 0) {
        printf("\nEmployee with name '%s' not found!!\n", searchingName);
    }
}
