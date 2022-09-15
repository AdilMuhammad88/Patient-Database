#include <stdio.h>
#include <ctype.h>  // for tolower
#include <string.h>
#include <stdlib.h>

#define SIZE 42
#define fieldLength 250

struct db_type {
   char name[fieldLength];
   int age;
   int height;   // cm
   float bmi;
   char status[fieldLength];
};

char prompt_menu(void);
void enterNew(struct db_type * pArr[]);  
void init_list(struct db_type * pArr[]); 
void displayDB(struct db_type * pArr[]);   
void sortDB(struct db_type * pArr[]);
void updateRecord(struct db_type * pArr[]); 
void removeRecord(struct db_type * pArr[]);
void clearDB(struct db_type * pArr[]);

int main(int argc, char *argv[]) {
    
    struct db_type * db_pArr[SIZE];  // main db storage

    init_list(db_pArr);  // set to NULL
    
    char choice;
    for(; ;){
      choice = prompt_menu();
      switch (choice)
      {
         case 'n': enterNew(db_pArr); break;
         case 'd': displayDB(db_pArr); break;
        
         case 's': sortDB(db_pArr); break;
	   
         case 'c': clearDB(db_pArr); break;  
        
         case 'u': updateRecord(db_pArr); break;
         case 'r': removeRecord(db_pArr);break;
         
         case 'q': exit(1); // terminate the whole program
       }
	
     }
     return 0;
}

char prompt_menu(void){
  char s[80];
  while(1){
    printf("\n-----------------------------------------------------------------\n");
    printf("|    %-20s","(N)ew record");
    printf("%-20s","(R)emove record");
    printf("(U)pdate record\t|\n");
    printf("|    %-20s","(S)ort database");
    printf("%-20s","(C)lear database");
    printf("(D)isplay database\t|\n");
  
    printf("|    %-20s","(Q)uit");
    printf("*Case Insensitive*\t\t\t|\n");
    printf("-----------------------------------------------------------------\n");
    printf("choose one: ");
  
    fgets(s,50, stdin); // \n added
    //scanf("%s", s);  
    if (strlen(s) == 2 && strchr("edlsuqrcwnvpr", tolower(*s))) 
       return tolower(*s); // s[0], return the first character of s  
    //else
    printf("not a valid input!\n");
	 
 }
}

void init_list(struct db_type * pArr[]){
  int t;
  for (t = 0; t < SIZE; t++) pArr[t]= NULL;
}

/* delete all the records in the database */
void clearDB(struct db_type * pArr[]){
   char yn[3];
   printf("are you sure to clear database? (y) or (n)? "); 
   fgets(yn, 3, stdin);
   
   // complete the function by calling init_list();
   if (strcmp("y\n", yn) == 0) init_list(pArr);
}

/* input items into the database */
/* hint: need malloc */
void enterNew(struct db_type * pArr[SIZE]) {  
   int i, weight;

   struct db_type *member = malloc (sizeof (struct db_type));
   printf("name: "); scanf("%[^\n]s", member -> name); getchar();
   printf ("age: "); scanf("%d", &member -> age); getchar();
   printf ("height (cm): "); scanf("%d", &member -> height); getchar();
   printf ("weight (kg): "); scanf("%d", &weight); getchar();
   member -> bmi = (weight * 1.0) / member->height / member->height * 10000;

   if (member -> bmi < 18.5) {
      strcpy (member -> status, "Underweight");
   }
   else if (member -> bmi >= 18.5 && member -> bmi <= 24.999) {
      strcpy (member -> status, "Normal");
   }
   else if (member -> bmi >= 25 && member -> bmi <= 29.999) {
      strcpy (member -> status, "Overweight");
   }
   else if (member -> bmi >= 30 && member -> bmi <= 34.999) {
      strcpy (member -> status, "Obese I");
   }
   else if (member -> bmi >= 35 && member -> bmi <= 39.999) {
      strcpy (member -> status, "Obese II");
   }
   else {
      strcpy (member->status, "Obese III");
   }
   
   for (i = 0; i < SIZE; i++) {
      if (pArr[i] == NULL) {
         pArr[i] = member;
         break;
      }
   }
}

/* remove an existing item from the database */
void removeRecord (struct db_type * pArr[]) {
  int t, u, pos, recFound = 0;
  int length = SIZE - 1;

  char name[30];
  printf("enter full name to remove: ");
  scanf("%[^\n]s", name); getchar();
    
  for (t = 0; t < SIZE; t++) {
    if (pArr[t] != NULL && strcmp(pArr[t] -> name, name) == 0) {
      printf("record [%s] removed successfully.", name);
      pos = t; recFound = 1; 
      break;
    }
  }
  
  if (recFound == 0) printf("record not found");

  if (recFound == 1) {
      for (u = pos; u < length; u++) pArr[u] = pArr[u + 1];
  }
}

/* display all the records in the database. Generate output with the same formaing as the sample output 
 use \t to align well
*/
void displayDB(struct db_type * pArr[]) {
  printf("===============================\n");
  
  int t;

  for (t = 0; t < SIZE; t++) {
    if (pArr[t] != NULL) {
      printf("name:\t%s\nage:\t%d\nheight:\t%d\nBMI:\t%.1f\nstatus:\t%s\n\n", 
             pArr[t] -> name, pArr[t] -> age, pArr[t] -> height, pArr[t] -> bmi, pArr[t] -> status);
    }

    else{
      break;
    }
  }

  printf("========== %d records ==========\n", t);
}

 /* modify an existing item */
void updateRecord (struct db_type * pArr[]) {
   char name[fieldLength]; int weight, t;
   printf("enter full name to search: "); 
   scanf("%[^\n]s", name); getchar();
   
   for (t = 0; t < SIZE; t++) {
        if (pArr [t] == NULL) {
           continue;
        }

        if (strcmp (pArr [t]->name, name) == 0) {
            printf ("record found, enter new weight (kg): "); scanf("%d", &weight); getchar();
            pArr[t] -> bmi = ((weight * 1.0) / pArr[t] -> height) / pArr[t] -> height * 10000;

            if (pArr[t] -> bmi < 18.5) {
               strcat(pArr[t] -> status, " -> Underweight");
            }
            else if (pArr[t] -> bmi >= 18.5 && pArr[t] -> bmi <= 24.999) {
               strcat(pArr[t] -> status, " -> Normal");
            }
            else if (pArr[t] -> bmi >= 25 && pArr[t] -> bmi <= 29.999) {
               strcat(pArr[t] -> status, " -> Overweight");
            }
            else if (pArr[t] -> bmi >= 30 && pArr[t] -> bmi <= 34.999) {
               strcat(pArr[t] -> status, " -> Obese I");
            }
            else if (pArr[t] -> bmi >= 35 && pArr[t] -> bmi <= 39.999) {
               strcat(pArr[t] -> status, " -> Obese II");
            }
            else {
               strcat(pArr[t] -> status, " -> Obese III");
            }
            
            printf ("Record [%s] updated successfully.\n", name); return;
        }
    }
    printf ("record not found!\n");
}
 
// sort the record, either by name or BMI, prompt use for choice
void sortDB(struct db_type * pArr[]) {
  char sortRec[SIZE];
  printf("sort by name (n) or bmi (b)? ");

  scanf("%s", sortRec); getchar();

  if (strcmp("n", sortRec) == 0) {
    int t, u;

    for (t = 0; t < SIZE; t++) {
      if (pArr[t] != NULL) {
        for (u = t + 1; u < SIZE; u++) {
          if (pArr[u] != NULL) {
            if (strcmp(pArr[t] -> name , pArr[u] -> name) > 0) {
              struct db_type *temp = malloc(sizeof(struct db_type));

              *temp = *pArr[t];
              *pArr[t] = *pArr[u];
              *pArr[u] = *temp;
            }
          }
        }
      }
    }
  }

  if (strcmp("b", sortRec) == 0) {
    int t, u;

    for (t = 0; t < SIZE; t++) {
      if (pArr[t] != NULL) {
        for (u = t + 1; u < SIZE; u++) {
          if (pArr[u] != NULL) {
            if (pArr[t] -> bmi > pArr[u] -> bmi) {
              struct db_type *temp = malloc(sizeof(struct db_type));

              *temp = *pArr[t];
              *pArr[t] = *pArr[u];
              *pArr[u] = *temp;
            }
          }
        }
      }
    }
  }
}

