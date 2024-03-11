#include <stdio.h>
#include <stdlib.h>
#include "employeeFunction.h"

void main()
{
    while (1)
    {
        int choice = printChoose();
        switch (choice)
        {
        case 1:
        {
            addEmployee();
            break;
        }
        case 2:
        {
            searchEmployee();
            break;
        }
        case 3:
        {
            printAllEmployee();
            break;
        }
        case 4:
        {
            paySalary();
            break;
        }
        case 5:
        {
            exit(0);
            break;
        }
        }
    }

}

