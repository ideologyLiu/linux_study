

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMPLOYEES 100

struct Employee {
  char name[50];
  int age;
  float salary;
};

struct Employee employees[MAX_EMPLOYEES];
int num_employees = 0;

void add_employee() {
  if (num_employees >= MAX_EMPLOYEES) {
    printf("Error: Maximum number of employees reached.\n");
    return;
  }

  struct Employee new_employee;
  printf("Enter name: ");
  scanf("%s", new_employee.name);
  printf("Enter age: ");
  scanf("%d", &new_employee.age);
  printf("Enter salary: ");
  scanf("%f", &new_employee.salary);

  employees[num_employees] = new_employee;
  num_employees++;

  printf("Employee added successfully.\n");
}

void print_employees() {
  if (num_employees == 0) {
    printf("No employees found.\n");
    return;
  }

  printf("Name\tAge\tSalary\n");
  for (int i = 0; i < num_employees; i++) {
    printf("%s\t%d\t%f\n", employees[i].name, employees[i].age, employees[i].salary);
  }
}

void search_employee(char* name) {
  int found = 1;
  for (int i = 0; i < num_employees; i++) {
    if (strcmp(employees[i].name, name) == 0) {
      printf("Name\tAge\tSalary\n");
      printf("%s\t%d\t%f\n", employees[i].name, employees[i].age, employees[i].salary);
      found = 0;
      break;
    }
  }

  if (found) {
    printf("Employee \"%s\" not found.\n", name);
  }
}

int main() {
  int choice;
  char name[50];

  while (1) {
    printf("1. Add employee\n");
    printf("2. Print all employees\n");
    printf("3. Search employee by name\n");
    printf("4. Exit\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch (choice) {
      case 1:
        add_employee();
        break;
      case 2:
        print_employees();
        break;
      case 3:
        printf("Enter name to search: ");
        scanf("%s", name);
        search_employee(name);
        break;
      case 4:
        printf("Goodbye.\n");
        exit(0);
      default:
        printf("Invalid choice.\n");
    }
  }

  return 0;
}
