#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool Exist = false;

//Variables
int LectID;
char Name[50];
int SerialNum;
int Date;
int Choice = 0;
int DPWMchoice; //For Mainmenu2
int SortChoice; //For MainMenu3
int Choice2; //For Searching
int DPcount = 0;
int WMcount = 0;
int Choice3;
int DPreturn;
int WMreturn;

//struct of Linked List
struct node {
	int LectID;
	char Name[50];
	int SerialNum;
	int Date;
	struct node* next;
}*DPnode, * WMnode, * list, * prev, * temp, * tmpdisplay, * list2, * prev2, * temp2, * temp3, * temp4, * ReturnDP, * ReturnWM;

//Create Linked List
void createlist() {
	list = NULL;
}

//Create Linked List2
void createlist2() {
	list2 = NULL;
}

//MainMenu
void Mainmenu() {
	printf("\n**************************************************\n");
	printf("**                 Main Menu                    **\n");
	printf("**************************************************\n");
	printf("**  1. Check Out Process                        **\n");
	printf("**  2. Check In Process                         **\n");
	printf("**  3. Search For A Loan Record                 **\n");
	printf("**  4. View Outstanding Unit Loan Reports       **\n");
	printf("**  5. Historical Unit Loan Reports             **\n");
	printf("**  6. Exit                                     **\n");
	printf("**************************************************\n");
	printf("Please Enter Your Choice(Only Number 1 To 6 Can Be Accepted): \n");
	scanf("%d", &Choice);
}

//MainMenu 2 (Digital Pads or Wireless Microphone)
void DPorWM() {
	printf("\n*********************************\n");
	printf("**       Items Available       **\n");
	printf("*********************************\n");
	printf("**  1. Digital Pads            **\n");
	printf("**  2. Wireless Microphones    **\n");
	printf("*********************************\n");
	printf("Please Enter Your Choice: \n");
	scanf("%d", &DPWMchoice);
}

//MainMenu 3 (Sort By LectID or Date)
void Sortby() {
	printf("\n****************************************\n");
	printf("**           Sorting Method           **\n");
	printf("****************************************\n");
	printf("**  1. Sort By Lecturer's ID          **\n");
	printf("**  2. Sort By Date                   **\n");
	printf("****************************************\n");
	printf("Please Enter Your Choice: \n");
	scanf("%d", &SortChoice);
}

// DIGITAL PADS //
// Check If The LectID Is Recorded In The System B4 (Checkout) DP
void CheckItemDPi(int LectID) { //checkout item
	Exist = true;
	temp = list;
	if (temp != NULL) {
		while (temp != NULL) {
			if (temp->LectID == LectID) {
				Exist = false;
				break;
			}temp = temp->next;
		}
	}
}

// Check If The SerialNum Is Recorded In The System B4(Checkout) DP
void CheckItemDPs(int SerialNum) { //checkout item
	Exist = true;
	temp = list;
	if (temp != NULL) {
		while (temp != NULL) {
			if (temp->SerialNum == SerialNum) {
				Exist = false;
				break;
			}temp = temp->next;
		}
	}
}

// Check If The LectID Is Recorded In The System B4 (Checkin) DP
void CheckItemDP2i(int LectID) { //checkout item 
	Exist = false;
	temp = list;
	if (temp != NULL) {
		while (temp != NULL) {
			if (temp->LectID == LectID) {
				Exist = true;
				break;
			}temp = temp->next;
		}
	}
}

//Checkout Digital Pads (Insert Lecturer Into The Loan List)
void CheckoutDP() {
	DPnode = (struct node*)malloc(sizeof(struct node));
	printf("Enter Lecturer's ID: \n");
	scanf("%d", &DPnode->LectID);
	CheckItemDPi(DPnode->LectID);
	if (Exist) {
		printf("Enter Name Of Lecturer: \n");
		scanf("%s", DPnode->Name);
		printf("Enter The Serial Number For The Unit: \n");
		scanf("%d", &DPnode->SerialNum);
		CheckItemDPs(DPnode->SerialNum);
		if (Exist) {
			printf("Enter Today's Date (YYYY-MM-DD): \n");
			scanf("%d", &DPnode->Date);
			DPnode->next = NULL;
			if (list == NULL)
				list = DPnode;
			else if (DPnode->LectID < list->LectID) {
				DPnode->next = list;
				list = DPnode;
			}
			else {
				temp = list;
				while (temp != NULL) {
					if (DPnode->LectID > temp->LectID) {
						prev = temp;
					}
					temp = temp->next;
				}
				DPnode->next = prev->next;
				prev->next = DPnode;
			}DPcount++;
		}
		else {
			printf("\n*********************\n");
			printf("**  Item Invalid.  **\n");
			printf("*********************\n");
		}
	}
	else {
		printf("\n*********************\n");
		printf("**  User Invalid.  **\n");
		printf("*********************\n");
	}
}

//Checkin Item Digital Pads (Delete Lecturer From The Loan List)
void CheckinDP() {
	if (list == NULL) {
		printf("\n*******************************\n");
		printf("**     The List Is Empty     **\n");
		printf("*******************************\n");
	}
	else {
		printf("Please Enter Lecturer's ID: \n");
		scanf("%d", &LectID);
		CheckItemDP2i(LectID);
		if (Exist) {
			if (LectID == list->LectID) {
				temp = list;
				list = list->next;
			}
			else {
				temp = list;
				while (temp->LectID != LectID) {
					prev = temp;
					temp = temp->next;
				}prev->next = prev->next->next;
			}temp->next = NULL;
			DPcount--;

			temp->next = NULL;

			//Historical Reports
			if (ReturnDP == NULL) {
				ReturnDP = temp;
			}
			else {
				prev = ReturnDP;
				while (prev->next != NULL) {
					prev = prev->next;
				}prev->next = temp;
			}DPreturn++;
		}
		else {
			printf("\n***********************\n");
			printf("**  User Not Found.  **\n");
			printf("***********************\n");
		}
	}
}

//Display DP Loan List
void displayDP(char SNorLID[50], int b) {
	if (list == NULL) {
		printf("\n*******************************\n");
		printf("**     The List Is Empty     **\n");
		printf("*******************************\n");
	}
	else
	{
		tmpdisplay = list;
		while (tmpdisplay != NULL)
		{
			if (strcmp(SNorLID, "SerialNum") == 0) {
				if (tmpdisplay->SerialNum == b) {
					printf("\n*****************************************\n");
					printf("**     Loan Record Of Digital Pads     **\n");
					printf("*****************************************\n");
					printf("Lecturer's ID: %d\n", tmpdisplay->LectID);
					printf("Name Of Lecturer: %s\n", tmpdisplay->Name);
					printf("Serial Number For The Unit: %d\n", tmpdisplay->SerialNum);
					printf("Date Borrowed (YYYY-MM-DD): %d\n\n", tmpdisplay->Date);
				}
			}
			else if (strcmp(SNorLID, "LectID") == 0) {
				if (tmpdisplay->LectID == b) {
					printf("Lecturer's ID: %d\n", tmpdisplay->LectID);
					printf("Name Of Lecturer: %s\n", tmpdisplay->Name);
					printf("Serial Number For The Unit: %d\n", tmpdisplay->SerialNum);
					printf("Date Borrowed (YYYY-MM-DD): %d\n\n", tmpdisplay->Date);
				}
			}tmpdisplay = tmpdisplay->next;
		}
	}
}

//Search For DP Loan Records
void searchDP() {
	printf("\n**************************\n");
	printf("**     Display option   **\n");
	printf("**************************\n");
	printf("**  1.Lecture ID        **\n");
	printf("**  2.Serial Number     **\n");
	printf("**************************\n");
	printf("Please Enter Your Choice: \n");
	scanf("%d", &Choice2);

	if (Choice2 == 1)
	{
		printf("Please enter the Lecture ID: ");
		scanf("%d", &LectID);
		displayDP("LectID", LectID);
	}
	else if (Choice2 == 2)
	{
		printf("Please enter the Serial Number: ");
		scanf("%d", &SerialNum);
		displayDP("SerialNum", SerialNum);
	}
	else if (Choice2 != 1 && Choice2 != 2) {
		printf("Invalid Choice, Returning To Main Menu...\n");
	}
}

//Display DP Loan REPORTS by ID
void DPReportsL() {
	if (list == NULL) {
		printf("\n*******************************\n");
		printf("**     The List Is Empty     **\n");
		printf("*******************************\n");
	}
	else
	{
		int k, j;
		for (int i = DPcount - 2; i >= 0; i--) {
			temp = list;
			temp4 = temp->next;
			for (j = 0; j <= i; j++) {
				if (temp->LectID > temp4->LectID)
				{
					k = temp->LectID;
					temp->LectID = temp4->LectID;
					temp4->LectID = k;
				}
				temp = temp4;
				temp4 = temp4->next;
			}
		}
		tmpdisplay = list;
		printf("\n******************************************\n");
		printf("**     Loan Reports Of Digital Pads     **\n");
		printf("******************************************\n");
		while (tmpdisplay != NULL) {
			for (int i = 1; i < DPcount + 1; i++) {
				printf("%d. ", i);
				printf("Lecturer's ID: %d\t\t", tmpdisplay->LectID);
				printf("Name Of Lecturer: %s\t\t", tmpdisplay->Name);
				printf("Serial Number For The Unit: %d\t\t", tmpdisplay->SerialNum);
				printf("Date Borrowed (YYYY-MM-DD): %d\t\t\n", tmpdisplay->Date);
				tmpdisplay = tmpdisplay->next;
			}
		}
	}
}

//Display DP Loan REPORTS by Date
void DPReportsD() {
	if (list == NULL) {
		printf("\n*******************************\n");
		printf("**     The List Is Empty     **\n");
		printf("*******************************\n");
	}
	else
	{
		int k, k1, k3, j;
		char k2[50];
		for (int i = DPcount - 2; i >= 0; i--) {
			temp = list;
			temp4 = temp->next;
			for (j = 0; j <= i; j++) {
				if (temp->Date > temp4->Date)
				{
					k = temp->Date;
					k1 = temp->LectID;
					strcpy(k2, temp->Name);
					k3 = temp->SerialNum;

					temp->Date = temp4->Date;
					temp->LectID = temp4->LectID;
					strcpy(temp->Name, temp4->Name);
					temp->SerialNum = temp4->SerialNum;

					temp4->Date = k;
					temp4->LectID = k1;
					strcpy(temp4->Name, k2);
					temp4->SerialNum = k3;
				}
				temp = temp4;
				temp4 = temp4->next;
			}
		}
		tmpdisplay = list;
		printf("\n******************************************\n");
		printf("**     Loan Reports Of Digital Pads     **\n");
		printf("******************************************\n");
		while (tmpdisplay != NULL) {
			for (int i = 1; i < DPcount + 1; i++) {
				printf("%d. ", i);
				printf("Lecturer's ID: %d\t\t", tmpdisplay->LectID);
				printf("Name Of Lecturer: %s\t\t", tmpdisplay->Name);
				printf("Serial Number For The Unit: %d\t\t", tmpdisplay->SerialNum);
				printf("Date Borrowed (YYYY-MM-DD): %d\t\t\n", tmpdisplay->Date);
				tmpdisplay = tmpdisplay->next;
			}
		}
	}
}

//DP Historical REPORTS
void historicalDP() {
	if (ReturnDP == NULL) {
		printf("\n*******************************\n");
		printf("**     The List Is Empty     **\n");
		printf("*******************************\n");
	}
	else {
		tmpdisplay = ReturnDP;
		printf("\n**********************************************\n");
		printf("**     Historical Reports Of Digital Pads   **\n");
		printf("**********************************************\n");
		int index = 1;
		while (tmpdisplay != NULL) {
			printf("%d. ", index);
			printf("Lecturer's ID: %d\t\t", tmpdisplay->LectID);
			printf("Name Of Lecturer: %s\t\t", tmpdisplay->Name);
			printf("Serial Number For The Unit: %d\t\t", tmpdisplay->SerialNum);
			printf("Date Borrowed (YYYY-MM-DD): %d\t\t\n", tmpdisplay->Date);
			tmpdisplay = tmpdisplay->next;
			index++;
		}
	}
}

// WIRELESS MICROPHONE //
//Check If The LectID Is Recorded In The System B4 (Checkout) WM
void CheckItemWMi(int LectID) { //checkout item
	Exist = true;
	temp2 = list2;
	if (temp2 != NULL) {
		while (temp2 != NULL) {
			if (temp2->LectID == LectID) {
				Exist = false;
				break;
			}temp2 = temp2->next;
		}
	}
}

//Check If The SerialNum Is Recorded In The System B4 (Checkout) WM
void CheckItemWMs(int SerialNum) { //checkout item
	Exist = true;
	temp2 = list2;
	if (temp2 != NULL) {
		while (temp2 != NULL) {
			if (temp2->SerialNum == SerialNum) {
				Exist = false;
				break;
			}temp2 = temp2->next;
		}
	}
}

//Check If The LectID Is Recorded In The System B4 (Checkin) WM
void CheckItemWM2i(int LectID) { //checkout item
	Exist = false;
	temp2 = list2;
	if (temp2 != NULL) {
		while (temp2 != NULL) {
			if (temp2->LectID == LectID) {
				Exist = true;
				break;
			}temp2 = temp2->next;
		}
	}
}

//Checkout Wireless Microphone (Insert Lecturer Into The Loan List)
void CheckoutWM() {
	WMnode = (struct node*)malloc(sizeof(struct node));
	printf("Enter Lecturer's ID: \n");
	scanf("%d", &WMnode->LectID);
	CheckItemWMi(WMnode->LectID);
	if (Exist) {
		printf("Enter Name Of Lecturer: \n");
		scanf("%s", WMnode->Name);
		printf("Enter The Serial Number For The Unit: \n");
		scanf("%d", &WMnode->SerialNum);
		CheckItemWMs(WMnode->SerialNum);
		if (Exist) {
			printf("Enter Today's Date (YYYY-MM-DD): \n");
			scanf("%d", &WMnode->Date);
			WMnode->next = NULL;
			if (list2 == NULL)
				list2 = WMnode;
			else if (WMnode->LectID < list2->LectID) {
				WMnode->next = list2;
				list2 = WMnode;
			}
			else {
				temp2 = list2;
				while (temp2 != NULL) {
					if (WMnode->LectID > temp2->LectID) {
						prev = temp2;
					}
					temp2 = temp2->next;
				}
				WMnode->next = prev->next;
				prev->next = WMnode;
			}WMcount++;
		}
		else {
			printf("\n***********************\n");
			printf("**  Item Not Found.  **\n");
			printf("***********************\n");
		}
	}
	else {
		printf("\n*********************\n");
		printf("**  User Invalid.  **\n");
		printf("*********************\n");
	}
}

//Checkin Item Digital Pads (Delete Lecturer From The Loan List)
void CheckinWM() {
	if (list2 == NULL) {
		printf("\n*******************************\n");
		printf("**     The List Is Empty     **\n");
		printf("*******************************\n");
	}
	else {
		printf("Please Enter Lecturer's ID: \n");
		scanf("%d", &LectID);
		CheckItemWM2i(LectID);
		if (Exist) {
			if (LectID == list2->LectID) {
				temp2 = list2;
				list2 = list2->next;
			}
			else {
				temp2 = list2;
				while (temp2->LectID != LectID) {
					prev2 = temp2;
					temp2 = temp2->next;
				}prev2->next = prev2->next->next;
			}temp2->next = NULL;
			WMcount--;

			temp2->next = NULL;

			//Historical Reports
			if (ReturnWM == NULL) {
				ReturnWM = temp2;
			}
			else {
				prev2 = ReturnWM;
				while (prev2->next != NULL) {
					prev2 = prev2->next;
				}prev2->next = temp2;
			}DPreturn++;
		}
		else {
			printf("\n***********************\n");
			printf("**  User Not Found.  **\n");
			printf("***********************\n");
		}
	}
}

//Display WM Loan List
void displayWM(char SNorLID[50], int b) {
	if (list2 == NULL) {
		printf("\n*******************************\n");
		printf("**     The List Is Empty     **\n");
		printf("*******************************\n");
	}
	else
	{
		tmpdisplay = list2;
		while (tmpdisplay != NULL) {
			if (strcmp(SNorLID, "SerialNum") == 0) {
				if (tmpdisplay->SerialNum == b) {
					printf("\n***********************************************\n");
					printf("**     Loan Record Of Wireless Microphone    **\n");
					printf("***********************************************\n");
					printf("Lecturer's ID: %d\n", tmpdisplay->LectID);
					printf("Name Of Lecturer: %s\n", tmpdisplay->Name);
					printf("Serial Number For The Unit: %d\n", tmpdisplay->SerialNum);
					printf("Date Borrowed (YYYY-MM-DD): %d\n\n", tmpdisplay->Date);
				}
			}
			else if (strcmp(SNorLID, "LectID") == 0) {
				if (tmpdisplay->LectID == b) {
					printf("Lecturer's ID: %d\n", tmpdisplay->LectID);
					printf("Name Of Lecturer: %s\n", tmpdisplay->Name);
					printf("Serial Number For The Unit: %d\n", tmpdisplay->SerialNum);
					printf("Date Borrowed (YYYY-MM-DD): %d\n\n", tmpdisplay->Date);
				}
			}tmpdisplay = tmpdisplay->next;
		}
	}
}

//Search For WM Loan Records
void searchWM() {
	printf("\n**************************\n");
	printf("**     Display option   **\n");
	printf("**************************\n");
	printf("**  1.Lecture ID        **\n");
	printf("**  2.Serial Number     **\n");
	printf("**************************\n");
	printf("Please Enter Your Choice: \n");
	scanf("%d", &Choice2);

	if (Choice2 == 1)
	{
		printf("Please enter the Lecture ID: ");
		scanf("%d", &LectID);
		displayWM("LectID", LectID);
	}
	else if (Choice2 == 2)
	{
		printf("Please enter the Serial Number: ");
		scanf("%d", &SerialNum);
		displayWM("SerialNum", SerialNum);
	}
	else if (Choice2 != 1 && Choice2 != 2) {
		printf("Invalid Choice, Returning To Main Menu...\n");
	}
}

//Display WM Loan REPORTS by ID
void WMReportsL() {
	if (list2 == NULL) {
		printf("\n*******************************\n");
		printf("**     The List Is Empty     **\n");
		printf("*******************************\n");
	}
	else
	{
		int k, j;
		for (int i = WMcount - 2; i >= 0; i--) {
			temp2 = list2;
			temp3 = temp2->next;
			for (j = 0; j <= i; j++) {
				if (temp2->LectID > temp3->LectID)
				{
					k = temp2->LectID;
					temp2->LectID = temp3->LectID;
					temp3->LectID = k;
				}
				temp2 = temp3;
				temp3 = temp3->next;
			}
		}
		tmpdisplay = list2;
		printf("\n**************************************************\n");
		printf("**     Loan Reports Of Wireless Mircrophone     **\n");
		printf("**************************************************\n");
		while (tmpdisplay != NULL) {
			for (int j = 1; j < WMcount + 1; j++) {
				printf("%d. ", j);
				printf("Lecturer's ID: %d\t\t", tmpdisplay->LectID);
				printf("Name Of Lecturer: %s\t\t", tmpdisplay->Name);
				printf("Serial Number For The Unit: %d\t\t", tmpdisplay->SerialNum);
				printf("Date Borrowed (YYYY-MM-DD): %d\t\t\n", tmpdisplay->Date);
				tmpdisplay = tmpdisplay->next;
			}
		}
	}
}

//Display WM Loan REPORTS by Date
void WMReportsD() {
	if (list2 == NULL) {
		printf("\n*******************************\n");
		printf("**     The List Is Empty     **\n");
		printf("*******************************\n");
	}
	else
	{
		int k, k1, k3, j;
		char k2[50];
		for (int i = WMcount - 2; i >= 0; i--) {
			temp2 = list2;
			temp3 = temp2->next;
			for (j = 0; j <= i; j++) {
				if (temp2->Date > temp3->Date)
				{
					k = temp2->Date;
					k1 = temp2->LectID;
					strcpy(k2, temp2->Name);
					k3 = temp2->SerialNum;

					temp2->Date = temp3->Date;
					temp2->LectID = temp3->LectID;
					strcpy(temp2->Name, temp3->Name);
					temp2->SerialNum = temp3->SerialNum;

					temp3->Date = k;
					temp3->LectID = k1;
					strcpy(temp3->Name, k2);
					temp3->SerialNum = k3;
				}
				temp2 = temp3;
				temp3 = temp3->next;
			}
		}
		tmpdisplay = list2;
		printf("\n*************************************************\n");
		printf("**     Loan Reports Of Wireless Microphone     **\n");
		printf("*************************************************\n");
		while (tmpdisplay != NULL) {
			for (int i = 1; i < WMcount + 1; i++) {
				printf("%d. ", i);
				printf("Lecturer's ID: %d\t\t", tmpdisplay->LectID);
				printf("Name Of Lecturer: %s\t\t", tmpdisplay->Name);
				printf("Serial Number For The Unit: %d\t\t", tmpdisplay->SerialNum);
				printf("Date Borrowed (YYYY-MM-DD): %d\t\t\n", tmpdisplay->Date);
				tmpdisplay = tmpdisplay->next;
			}
		}
	}
}

//WM Historical REPORTS
void historicalWM() {
	if (ReturnWM == NULL) {
		printf("\n*******************************\n");
		printf("**     The List Is Empty     **\n");
		printf("*******************************\n");
	}
	else {
		tmpdisplay = ReturnWM;
		printf("\n*****************************************************\n");
		printf("**     Historical Reports Of Wireless Microphone   **\n");
		printf("*****************************************************\n");
		int index = 1;
		while (tmpdisplay != NULL) {
			printf("%d. ", index);
			printf("Lecturer's ID: %d\t\t", tmpdisplay->LectID);
			printf("Name Of Lecturer: %s\t\t", tmpdisplay->Name);
			printf("Serial Number For The Unit: %d\t\t", tmpdisplay->SerialNum);
			printf("Date Borrowed (YYYY-MM-DD): %d\t\t\n", tmpdisplay->Date);
			tmpdisplay = tmpdisplay->next;
			index++;
		}
	}
}

//Main Function
void main() {
	createlist();
	createlist2();
	printf("============================================================================\n");
	printf("||                                                                        ||\n");
	printf("||        APU Digital Pads & Wireless Microphones Borrowing system        ||\n");
	printf("||                                                                        ||\n");
	printf("============================================================================\n");
	while (Choice != 6) {
		Mainmenu();
		if (Choice == 1) { // (Check out item)
			DPorWM();
			if (DPWMchoice == 1) { //DP
				if (DPcount <= 19) {
					CheckoutDP();
				}
				else if (DPcount > 19) {
					printf("The Items Are Fully Loaned, Try Again Later.\n");
				}
			}
			if (DPWMchoice == 2) { //WM
				if (WMcount <= 19) {
					CheckoutWM();
				}
				else if (WMcount > 19) {
					printf("The Items Are Fully Loaned, Try Again Later.\n");
				}
			}
			else if (DPWMchoice != 1 && DPWMchoice != 2) {
				printf("Invalid Choice, Returning To Main Menu...\n");
			}
		}
		else if (Choice == 2) {// (Check in item)
			DPorWM();
			if (DPWMchoice == 1) { //DP
				CheckinDP();
			}
			else if (DPWMchoice == 2) { //WM
				CheckinWM();
			}
			else if (DPWMchoice != 1 && DPWMchoice != 2) {
				printf("Invalid Choice, Returning To Main Menu...\n");
			}
		}
		else if (Choice == 3) {// (Display Loan record based on LectID or SerialNum)
			DPorWM();
			if (DPWMchoice == 1) { //DP
				searchDP();
			}
			else if (DPWMchoice == 2) { //WM
				searchWM();
			}
			else if (DPWMchoice != 1 && DPWMchoice != 2) {
				printf("Invalid Choice, Returning To Main Menu...\n");
			}
		}
		else if (Choice == 4) {// (Display Loan Reports Order by LectID or Date)
			DPorWM();
			if (DPWMchoice == 1) { //DP
				//LectID or LoanDate
				Sortby();
				if (SortChoice == 1) {
					DPReportsL();
				}
				else if (SortChoice == 2) {
					DPReportsD();
				}
				else
					printf("Invalid Choice, Returning To Main Menu...\n");
			}
			else if (DPWMchoice == 2) { //WM
				//LectID or LoanDate
				Sortby();
				if (SortChoice == 1) {
					WMReportsL();
				}
				else if (SortChoice == 2) {
					WMReportsD();
				}
				else
					printf("Invalid Choice, Returning To Main Menu...\n");
			}
			else if (DPWMchoice != 1 && DPWMchoice != 2) {
				printf("Invalid Choice, Returning To Main Menu...\n");
			}
		}
		else if (Choice == 5) {// (Historical unit)
			DPorWM();
			if (DPWMchoice == 1) { //DP
				historicalDP();
			}
			else if (DPWMchoice == 2) { //WM
				historicalWM();
			}
			else if (DPWMchoice != 1 && DPWMchoice != 2) {
				printf("Invalid Choice, Returning To Main Menu...\n");
			}
		}
		else if (Choice == 6) { // (Exit)
			printf("\n************************************************\n");
			printf("**                                            **\n");
			printf("**  System Shutting Down...Have A Good Day !  **\n");
			printf("**                                            **\n");
			printf("************************************************\n");
		}
		else { // (Invalid Choice)
			printf("Invalid Choice, Please Choose Again !\n");
		}
	}
}
