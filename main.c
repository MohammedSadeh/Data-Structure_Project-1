/*
Name : Mohammed Jamil Saada
ID : 1221972
Section NO. : 1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct district;
struct town;
struct list;

//typedef make it easy to declare variables.
typedef struct district* ptrd;
typedef struct town* ptrt;
typedef struct district* district;
typedef struct town* town;
typedef struct list* List;
typedef struct list* ptrl;

//to build Linked List of Districts that contains another L:inked List of Towns
struct district{
    char* district_name;
    town t;

    ptrd next;
    ptrd prev;
};

//to build Linked List of towns
struct town{
    char* town_name;
    int population;
    ptrt next;
    ptrt prev;
};

struct list{
    char* d_name;
    char* t_name;
    int pop;
    ptrl next;
    ptrl prev;
};

//functions prototype
district createDistrict();
town createTown();
void display_menu();
district loadInputFile();
void printSortedInfo(district);
int calculateDistrictPop(district);
void insertDistrict(district,char*);
void insertTown(town,char*,int);
void printAsInputFile();
int sizeOfString(char*);
int maxSize(district);
void radixSortDis(district);
void deleteAllDistricts(district);
void mergeAllDistricts(district, district[]);
void radixSortTown(town);
int getMaxPop(town);
int getMaxLenght(int);
void deleteAllTowns(town);
void mergeAllTowns(town,town[]);
void addNewDis(district);
void addNewTown(district);
district searchDis(district,char*);
void deleteTown(district);
town searchTown(town,char*);
void deleteDis(district);
int calculatePalestinePop(district);
town maxTownPop(district);
town minTownPop(district);
void printPop_Max_Min(district);
void printDistricts(district);
void changeTownPop(district);
void saveToOutputFile(district);
void insertList(List,char*,char*,int);
List loadFileToList();
district listToDistricts(List);
char* trim(char*);
List createList();
void townSorting(district);

int main()
{
    district D;
    int m;
    printf("Please enter the number of operation that you want\n");
    display_menu();
    scanf("%d",&m);
    if(m!=1){
        while(m!=1){
            printf("\nYou can't chose any operation before load the information!\n\n");
            printf("Please enter the number of operation that you want\n");
            display_menu();
            scanf("%d",&m);
        }
    }
    while(m!=14){
        switch(m){
            case 1 :
                printf("\n");
                D = loadInputFile();
                break;
            case 2 :
                printf("\n");
                printAsInputFile();
                break;
            case 3 :
                printf("\n");
                radixSortDis(D);
                break;
            case 4 :
                printf("\n");
                townSorting(D);
                break;
            case 5 :
                printf("\n");
                printSortedInfo(D);
                break;
            case 6 :
                printf("\n");
                addNewDis(D);
                break;
            case 7 :
                printf("\n");
                addNewTown(D);
                break;
            case 8 :
                printf("\n");
                deleteTown(D);
                break;
            case 9 :
                printf("\n");
                deleteDis(D);
                break;
            case 10 :
                printf("\n");
                printPop_Max_Min(D);
                break;
            case 11 :
                printf("\n");
                printDistricts(D);
                break;
            case 12 :
                printf("\n");
                changeTownPop(D);
                break;
            case 13 :
                printf("\n");
                saveToOutputFile(D);
                break;
            default :
                printf("\n");
                printf("Invalid operation number, please try again...\n");
        }
        printf("\nPlease enter the number of operation that you want\n");
        display_menu();
        scanf("%d",&m);
    }

    printf("Exit from the program...\nThank you for using this program...\n");
    return 0;
}

// function to create Linked List of Districts
district createDistrict(){                                    //Done
    district D = (district)malloc(sizeof(struct district));
    if(D==NULL){
        printf("District List can not be defined");
        return NULL;
        }
    else {
        D->next = NULL;
        D->prev = NULL;
        return D;
        }
}

// function to create Linked List of towns
town createTown(){                                        //Done
    town T = (town)malloc(sizeof(struct town));
    if(T==NULL){
        printf("Town List can not be defined");
        return NULL;
        }
    else {
        T->next = NULL;
        T->prev = NULL;
        return T;
        }
}

//function to create Linked List of the input file to (list)         //Done
List createList(){
    List L = (List)malloc(sizeof(struct list));
    if(L==NULL){
        printf("The List can not be defined");
        return NULL;
    }
    else {
        L->next = NULL;
        L->prev = NULL;
        return L;
    }
}

//function to add new nose to list
void insertList(List L,char* d,char* j,int p){              //Done
    ptrl h = (ptrl)malloc(sizeof(struct district));
    if(L==NULL)
        printf("out of memory space\n");
    else{
        ptrl t;
        for(t=L; t->next!=NULL; t=t->next);
        h->next = t->next;
        h->prev = t;
        t->next = h;
        h->d_name = d;
        h->t_name = j;
        h->pop = p;
    }
 }

// function that print (display) the menu
void display_menu(){                                   //Done
    printf("Menu :\n");
    printf("1- Load the input file (Palestine districts and their town with population).\n");
    printf("2- Print the loaded information before sorting (as in the input file format).\n");
    printf("3- Sort the districts alphabetically using Radix sort.\n");
    printf("4- Sort the towns for each district based on population in ascending order.\n");
    printf("5- Print the sorted information.\n");
    printf("6- Add a new district to the list sorted districts (and sort the list).\n");
    printf("7- Add a new town to certain district.\n");
    printf("8- Delete a town from a specific district.\n");
    printf("9- Delete a complete district.\n");
    printf("10- Calculate the population of Palestine, the max and min town population.\n");
    printf("11- Print the districts and their total population (without towns details).\n");
    printf("12- Change the population of a town.\n");
    printf("13- Save to output file.\n");
    printf("14- Exit.\n");

}

// function to load the input File and return a linked List contain the information        //Done
List loadFileToList(){
    List L = createList();
    if(L==NULL)
        printf("The List is not exist");
    else{
        FILE* input = fopen("districts.txt","r");
        if(input==NULL)
            printf("The file can't be opened..\n");
        else{
            char myString[50];
            char* s = fgets(myString,50,input);
            while(s!=NULL){
                    char* c1 = strtok(s,"|");     //strtok function to split the string by delimiter |
                    char* c2 = strtok(NULL,"|");
                    char* c3 = strtok(NULL,"|");
                    insertList(L,strdup(c1),strdup(c2),atoi(c3));  //strdup function copy the string to new allocate memory(duplicate it)
                    s = fgets(myString,50,input);                  //atoi is a function that take a string and return its value as integer
            }
                fclose(input);
        }
    }
    return L;
}

//function to arrange information in the Linked List of Districts
district listToDistricts(List L){                    //Done
    district D = createDistrict();
    ptrl l = L->next;
    while(l!=NULL){
        char* c1 = strdup(trim(l->d_name));
        char* c2 = strdup(trim(l->t_name));
        if(searchDis(D,c1)==NULL){
            insertDistrict(D,c1);
            insertTown(searchDis(D,c1)->t,c2,l->pop);
        }
        else{
            if(searchTown(searchDis(D,c1)->t,c2)==NULL)
                insertTown(searchDis(D,c1)->t,c2,l->pop);
        }
    l = l->next;
    }
        return D;

}

/*function to read data from file and save them in linked list (List)
then arrange the data in linked list of districts, each node in districts has linked list of towns */
district loadInputFile(){           // Done
    List L = loadFileToList();
    printf("Input File loaded successfully..\n");
    return listToDistricts(L);
}


// function to print the Sorted information
void printSortedInfo(district D){
    radixSortDis(D);
    townSorting(D);
    ptrd p = D->next;
    while (p!=NULL){
        int x = calculateDistrictPop(p);
        ptrt c = p->t->next;
        printf("%s District, Population = %d\n",p->district_name,x);
        while (c!=NULL){
            printf("%s, %d\n",strdup(c->town_name),c->population);
            c = c->next;
        }
        p = p->next;
    }

}
//function to calculate total population of each district
 int calculateDistrictPop(district p){           //Done
    ptrt c = p->t->next;
    int x = 0;
    while (c!=NULL){
        x+=c->population;
        c = c->next;
    }
    return x;
 }

 //function to add new node to linked list of districts
 void insertDistrict(district D,char* dis_name){   // Done
     ptrd h = (ptrd)malloc(sizeof(struct district));
    if(D!=NULL){
        ptrd t;
        for(t=D; t->next!=NULL; t=t->next);
        h->next = t->next;
        h->prev = t;
        t->next = h;
        h->district_name = dis_name;
        h->t = createTown();
    }
 }

//function to add a new node to linked list of town
 void insertTown(town T, char* c, int p){         //Done
     ptrt h = (ptrt)malloc(sizeof(struct town));
     if(T!=NULL){
        ptrt t;
        for(t=T; t->next!=NULL; t=t->next);
        h->next = t->next;
        h->prev = t;
        t->next = h;
        h->town_name = c;
        h->population = p;
     }
 }
//function to print data exactly as the input file
 void printAsInputFile(){
        List L = loadFileToList();
        ptrl l = L->next;
        while(l!=NULL){
            printf("%s|%s| %d\n",l->d_name,l->t_name,l->pop);
            l = l->next;
        }
 }

 //function to calculate the size of string
 int sizeOfString(char* a){
    int size = 0;
    int i = 0;
    while(a[i] != '\0'){
        size++;
        i++;
    }
    return size;
}

//function to calculate max size of strings (district names) in linked list of district
int maxSize(district D){
    ptrd p = D->next;
    int max = sizeOfString(p->district_name);
    p = p->next;
    while(p != NULL){
        if(sizeOfString(p->district_name) > max)
            max = sizeOfString(p->district_name);
        p = p->next;
    }
    return max;
}

//radix sort for string alphabetically
void radixSortDis(district D){                             //Done
    district a[27]; // first element a[0] for space, a[1] ... a[26] from aA-zZ
    for(int  i=0; i<27; i++)
        a[i] = createDistrict();  // make array of linked list
    int b = maxSize(D);
    int c = b-1;
    while(c>=0){
        while(D->next != NULL){
            ptrd d = D->next;
            if(sizeOfString(d->district_name)-1<c){  //if size of string is less than the index add it to index 0
                ptrd f;                              // considered it space
                for(f = a[0]; f->next!=NULL; f = f->next);
                f ->next = d;
                d->prev = f;
                D->next = d->next;
                if(d->next!=NULL){
                    d->next->prev = D;
                    d->next = NULL;
                }
            }
            else if(d->district_name[c]>='a' && d->district_name[c]<='z'){ //to determine the the index that the string should insert to
                    int x = d->district_name[c] - 'a' + 1;
                    ptrd f;
                    for(f = a[x]; f->next!=NULL; f = f->next);
                    f ->next = d;
                    d->prev = f;
                    D->next = d->next;
                    if(d->next!=NULL){
                        d->next->prev = D;
                        d->next = NULL;
                    }
            }

                else if(d->district_name[c]>='A' && d->district_name[c]<='Z'){ //to determine the the index that the string should insert to
                    int x = d->district_name[c] - 'A' + 1;
                    ptrd f;
                    for(f = a[x]; f->next!=NULL; f = f->next);
                    f ->next = d;
                    d->prev = f;
                    D->next = d->next;
                    if(d->next!=NULL){
                        d->next->prev = D;
                        d->next = NULL;
                    }
                }
                else{                           //if the character in this index special or space for example (considered it is space)
                    ptrd f;
                    for(f = a[0]; f->next!=NULL; f = f->next);
                    f ->next = d;
                    d->prev = f;
                    D->next = d->next;
                    if(d->next!=NULL){
                        d->next->prev = D;
                        d->next = NULL;
                    }
            }

        }
        mergeAllDistricts(D,a);  //move all district nodes from the array to original linked list and empty all linked list in the array
        c--;
    }
    printf("The districts sorted alphabetically using Radix Sort Successfully..\n");
}

//function to delete all districts in the linked list
void deleteAllDistricts(district d){      //Done
    if(d!=NULL){
        ptrd p = d->next;
        while(p!=NULL){
                district temp = p;
                p->prev->next = p->next;
                p->next->prev = p->prev;
                p = p->next;
                free(temp);
        }
    }
}

//function to merge districts and move them  from array of linked list with size 27 to unique linked list in order from index 0 to 26
void mergeAllDistricts(district D, district a[27]){      //Done
    for(int i=0; i<27; i++){
        ptrd temp = a[i]->next;
        if(temp!=NULL){
            ptrd d;
            for(d=D; d->next!=NULL; d=d->next);
            d->next = temp;
            temp->prev = d;
            a[i]->next = NULL;
        }
        else
            continue;
    }
}

//function to sort town with radix sort
void radixSortTown(town T){      //Done
    if(T->next!=NULL){
        town b[10];                 //declare array of linked list with size 10
        for(int i=0; i<10; i++)
            b[i] = createTown();    //initialize each index as a head of town linked list
        int x = getMaxPop(T);
        int y = getMaxLength(x);
        int c,d;
        int div =1;
            for(int i=0; i<y; i++){
                while(T->next != NULL){
                    ptrt a = T->next;
                    c = a->population/div;
                    d = c%10;                 //to find the digit of specific index
                    ptrt f;
                    for(f = b[d]; f->next != NULL; f = f->next);
                    f->next = a;              // add the number to suitable index of linked list
                    a->prev = f;
                    T->next = a->next;
                    if(a->next!=NULL){
                        a->next->prev = T;
                        a->next = NULL;
                    }
            }
            mergeAllTowns(T,b);  //to move all nodes from the array to original linked list and so all the linked list in the array be empty
            div *= 10;
            }
    }
}

//function to delete all nodes in town linked list
void deleteAllTowns(town a){  // Done
     if(a!=NULL){
        ptrt p = a->next;
        while(p!=NULL){
                ptrt temp = p;
                p->prev->next = p->next;
                if(p->next!=NULL)
                    p->next->prev = p->prev;
                p = p->next;
                free(temp);
        }
    }
}

//function to (merge) move all nodes form array of linked list to unique linked list in order from index 0 to 10
void mergeAllTowns(town a, town b[10]){ // Done
    for(int i=0; i<10; i++){
        ptrt temp = b[i]->next;
        if(temp!=NULL){
            ptrt d;
            for(d=a; d->next!=NULL; d=d->next);
            d->next = temp;
            temp->prev = d;
            b[i]->next = NULL;
        }
        else
            continue;
    }
}

//function to find maximum population in linked list of town
int getMaxPop(town t){         // Done
    ptrt a = t ->next;
    int max = a->population;
    a = a->next;
    while(a!=NULL){
        if(a->population > max)
            max = a->population;
        a = a->next;
    }
    return max;
}

//function to find number of digits in the maximum population
int getMaxLength(int a){   // Done
    int count = 0;
    while(a%10 != 0 || a/10 != 0){
        a/=10;
        count++;
    }
    return count;
}

//function that take linked list of districts and sort towns in each districts by calling the radix sort function
void townSorting(district D){ //Done
    if(D!=NULL){
        ptrd d = D->next;
        while(d!=NULL){
            radixSortTown(d->t);
            d = d->next;
        }
    printf("Towns Sorted using Radix Sort Successfully..\n");
    }
}

//function to add district, asking the user about it's name
 void addNewDis(district D){    // Done
    radixSortDis(D);
    char ch[20];
    printf("Please Enter the District name..\n");
    getchar();
    scanf("%[^\n]%*c",ch);
    int x = (searchDis(D,ch)==NULL); //check if the district is already exist
    if(x){
        insertDistrict(D,strdup(ch));
        radixSortDis(D);
        printf("%s district added successfully..\n",ch);
    }
    else
        printf("%s District is already exists..\n",ch);
}

//function to add town to district, but asking the user about its details
void addNewTown(district D){     // Done
    char d_name[20],t_name[20];
    int p = 0;
    printf("please enter the District that town belongs to ..\n");
    getchar();
    scanf("%[^\n]%*c",d_name);
    ptrd d = searchDis(D,d_name);
    if(d==NULL)
        printf("%s district is not found, add it first ..\n",d_name);
    else{
        printf("Please enter the town name..\n");
        scanf("%[^\n]%*c",t_name);
        if(searchTown(d->t,t_name)==NULL){
            printf("Please enter %s town population..\n",t_name);
            scanf("%d",&p);
            insertTown(d->t,strdup(t_name),p);
            radixSortTown(d->t);
            printf("%s town added successfully..\n",t_name);
        }
        else
            printf("%s town is already exist..\n",t_name);
    }
}

//function to search on district in linked list by its name
district searchDis(district D, char* d_name){   // Done
    if(D!=NULL){
        ptrd d = D->next;
        while(d!=NULL){
            if(strcasecmp(d->district_name,d_name) == 0){
                return d;
                break;
            }
            d = d->next;
        }
    }
    else
        return NULL;
}

//function to delete town, but asking the user about its name
void deleteTown(district D){
    char d_name[20],t_name[20];
    printf("Please enter the name of district that you want to delete a town from it..\n");
    getchar();
    scanf("%[^\n]%*c",d_name);
    ptrd d = searchDis(D,d_name);
    if(d==NULL)
        printf("%s district is not found..\n",d_name);
    else{
        printf("Please enter the name of town that you want to delete..\n");
        scanf("%[^\n]%*c",t_name);
        ptrt s = searchTown(d->t,t_name);
        if(s==NULL)
            printf("%s town is not found..\n",t_name);
        else{
            ptrt temp = s;
            s->prev->next = s->next;
            if(s->next != NULL)
                s->next->prev = s->prev;
            free(temp);
            printf("%s town deleted successfully..\n",t_name);
        }

    }
}

//function to search on town in linked list by its name
town searchTown(town t,char* t_name){
    if(t!=NULL){
        ptrt d = t->next;
        while(d!=NULL){
            if(strcasecmp(d->town_name,t_name) == 0){
                return d;
                break;
            }
            d = d->next;
        }
    }
    else
        return NULL;
}

//function to delete district from linked list, but delete all towns in it before deleting it
void deleteDis(district D){
    char d_name[20];
    printf("Please enter the name of district that you want to delete..\n");
    getchar();
    scanf("%[^\n]%*c",d_name);
    ptrd d = searchDis(D,d_name);
    if(d==NULL)
        printf("%s district is not found..\n",d_name);
    else {
        ptrd temp = d;
        deleteAllTowns(d->t);
        d->prev->next = d->next;
        if(d->next!=NULL)
            d->next->prev = d->prev;
        free(temp);
        printf("%s district deleted successfully..\n",d_name);
    }
}

//function to calculate the total population of Palestine
int calculatePalestinePop(district D){
    int pop = 0;
    if(D==NULL)
        printf("The Districts List is Not Found..\n");
    else {
        ptrd d = D->next;
        while(d!=NULL){
            pop += calculateDistrictPop(d);
            d = d->next;
        }
    }
    return pop;
}

//function to find the town with maximum population from whole the districts
town maxTownPop(district D){
    if(D==NULL){
        printf("The Districts List is Not Found..\n");
        return NULL;
    }
    else {
        ptrd d = D->next;
        town max = d->t->next;
        while(d!=NULL){
            for(ptrt p = d->t->next; p!=NULL; p = p->next){
                if(p->population > max->population)
                    max = p;
            }
            d = d->next;
        }
        return max;
    }
}

//function to find the town with minimum population from whole the districts
town minTownPop(district D){
    if(D==NULL){
        printf("The Districts List is Not Found..\n");
        return NULL;
    }
    else {
        ptrd d = D->next;
        town min = d->t->next;
        while(d!=NULL){
            for(ptrt p = d->t->next; p!=NULL; p = p->next){
                if(p->population < min->population)
                    min = p;
            }
            d = d->next;
        }
        return min;
    }
}

//function to print total population of Palestine,the town with maximum population and the town with minimum population
void printPop_Max_Min(district D){
    printf("Population of Palestine = %d\n",calculatePalestinePop(D));
    printf("Max town population : %s ,%d\n",maxTownPop(D)->town_name,maxTownPop(D)->population);
    printf("Min town population : %s ,%d\n",minTownPop(D)->town_name,minTownPop(D)->population);
}

//function to print districts and its population without towns details
void printDistricts(district S){
    if(S==NULL)
        printf("The Districts List is Not Found..\n");
    else{
        ptrd d = S->next;
        while(d!=NULL){
            printf("%s district, total Population = %d\n",d->district_name,calculateDistrictPop(d));
            d = d->next;
        }
    }
}

//function to change the population of specific town, after asking the user about the details
void changeTownPop(district D){
    if(D==NULL)
        printf("The District List is Not Found..\n");
    else{
        char d_name[20], t_name[20];
        int x;
        printf("Please enter the District that have the town you want to change it's population..\n");
        getchar();
        scanf("%[^\n]%*C",d_name);
        ptrd p = searchDis(D,d_name);
        if(p==NULL)
            printf("%s district is not found..\n",d_name);
        else {
            printf("Please enter the town you want to change it's population..\n");
            scanf("%[^\n]%*c",t_name);
            ptrt t = searchTown(p->t,t_name);
            if(t==NULL)
                printf("%s town is not found..\n",t_name);
            else {
                printf("Please enter the new population of %s\n",t_name);
                scanf("%d",&x);
                t->population = x;
                printf("%s town population changed successfully..\n", t_name);
            }
        }
    }
}


//function to trim strings (delete the spaces from the beginning and the end of string if exist
char* trim(char* c){                    //Done
int start = 0, end = sizeOfString(c)-1;
while(isspace(c[start]))
    start++;                //the start will stop on the first character after the spaces in the beginning if any
while((end>=start)&& isspace(c[end]))
    end--;                  //the end will stop on the last character before the spaces in the end if any
c[end+1]='\0';              // to stop the string
memmove(c,c+start,end-start+2); //function that move the string from c (source)[second argument] / c+start means that the moving will be from the
return strdup(c);               //index (start) to the destination c (the first argument), the size of the string that will be move is (end - start + 1)
                                // and an additional index to '\0' to stop the string
}


//function that will save the data to file
void saveToOutputFile(district D){
    FILE* output = fopen("sorted_districts.txt","w");
    if(output==NULL)
        printf("The File is not exist..\n");
    else{
        ptrd p = D->next;
        while (p!=NULL){
            int x = calculateDistrictPop(p);
            ptrt c = p->t->next;
            fprintf(output,"%s District, Population = %d\n",p->district_name,x);
            while (c!=NULL){
                fprintf(output,"%s, %d\n",c->town_name,c->population);
                c = c->next;
            }
            p = p->next;
        }
    printf("Data Saved to File successfully..\n");
    fclose(output);
    }
}


