#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <Windows.h>
#include "List.h"
#include "Node.h"
#include "room.h"
#include "person.h"
#include "booking.h"
#include "payment.h"
#include "Function.h"


using namespace std;
//chỉ thêm khoản tàm 10 dòng
int main() {

	int numberOfperson = 0;

	// Danh sach room
	ifstream ifile("room.txt");
//	if (ifile.is_open()) cout << "thanh cong" << endl;
	List<room> RL;
	string line;
	while (getline(ifile, line)) {
		string v[3];
		int j = 0;
		string x = "";
		for (int i = 0; i < line.length(); i++) {
			if (line[i] == '|') {
				v[j++] = x;
				x = "";
			}
			else {
				x += line[i];
			}
		}
		v[j] = x;
		//	room(int roomId, string roomType, int price) 
		room* r = new room(stoi(v[0]), v[1], stoi(v[2]));
		RL.push(r);
	}
	ifile.close();


		// DAnh sach person
	ifstream ifilee("person.txt", ios::in);
//	if (ifilee.is_open()) cout << "thanh cong" << endl;
	List<person> PL;
	line = "";
	while (getline(ifilee, line)) {
		numberOfperson++;
		string v[7];
		int j = 0;
		string x = "";
		for (int i = 0; i < line.length(); i++) {
			if (line[i] == '|') {
				v[j++] = x;
				x = "";
			}
			else {
				x += line[i];
			}
		}
		v[j] = x;
		customer* p;
		if (stoi(v[3]) == 0) {
			p = new customer(stoi(v[0]), v[1], v[2], stoi(v[3]), v[4], v[5]);
		}
		else {
			p = new customer(stoi(v[0]), v[1], v[2], stoi(v[3]), v[4], v[5], stoi(v[6]));
		}
		PL.push(p);
	}
	ifilee.close();


	ifstream ifileee("booking.txt");
//	if (ifileee.is_open()) cout << "thanh cong" << endl;
	List<booking> BL;
	line = "";
	while (getline(ifileee, line)) {
		string v[9];
		int j = 0;
		string x = "";
		for (int i = 0; i < line.length(); i++) {
			if (line[i] == '|') {
				v[j++] = x;
				x = "";
			}
			else {
				x += line[i];
			}
		}
		v[j] = x;
		payment pm;
		booking* b;
		if (v[4] == "Cash") {
			pm = payment(v[4]);
			time_t t1 = stoi(v[5]);
			time_t t2 = stoi(v[6]);
			b = new booking(stoi(v[0]), v[1], stoi(v[2]), stoi(v[3]), pm, t1, t2);
		}
		else {
			pm = payment(v[4], v[5], v[6]);
			time_t t1 = stoi(v[7]);
			time_t t2 = stoi(v[8]);
			b = new booking(stoi(v[0]), v[1], stoi(v[2]), stoi(v[3]), pm, t1, t2);

		}

		BL.push(b);
	}
	ifileee.close();


	person* p = nullptr;


	//while (1) {

	//	gotoxy(55, 5); cout << "---------CHOOSE THE BANK----------";
	//	gotoxy(35, 9); cout << "________________";
	//	gotoxy(35, 10); cout << "|              |";
	//	gotoxy(35, 11); cout << "|     BIDV     |";
	//	gotoxy(35, 12); cout << "|______________|";

	//	gotoxy(63, 9); cout << "________________";
	//	gotoxy(63, 10); cout << "|              |";
	//	gotoxy(63, 11); cout << "|  VIETTINBANK |";
	//	gotoxy(63, 12); cout << "|______________|";

	//	gotoxy(91, 9); cout << "________________";
	//	gotoxy(91, 10); cout << "|              |";
	//	gotoxy(91, 11); cout << "|    MB BANK   |";
	//	gotoxy(91, 12); cout << "|______________|";

	//	gotoxy(35, 17); cout << "________________";
	//	gotoxy(35, 18); cout << "|              |";
	//	gotoxy(35, 19); cout << "|   AGRIBANK   |";
	//	gotoxy(35, 20); cout << "|______________|";

	//	gotoxy(63, 17); cout << "________________";
	//	gotoxy(63, 18); cout << "|              |";
	//	gotoxy(63, 19); cout << "|  VIETCOMBANK |";
	//	gotoxy(63, 20); cout << "|______________|";

	//	gotoxy(91, 17); cout << "________________";
	//	gotoxy(91, 18); cout << "|              |";
	//	gotoxy(91, 19); cout << "|      ACB     |";
	//	gotoxy(91, 20); cout << "|______________|";

	//	gotoxy(35, 25); cout << "________________";
	//	gotoxy(35, 26); cout << "|              |";
	//	gotoxy(35, 27); cout << "|  TECHCOMBANK |";
	//	gotoxy(35, 28); cout << "|______________|";

	//	gotoxy(63, 25); cout << "________________";
	//	gotoxy(63, 26); cout << "|              |";
	//	gotoxy(63, 27); cout << "|    TP BANK   |";
	//	gotoxy(63, 28); cout << "|______________|";

	//	gotoxy(91, 25); cout << "________________";
	//	gotoxy(91, 26); cout << "|              |";
	//	gotoxy(91, 27); cout << "|   OCEANBANK  |";
	//	gotoxy(91, 28); cout << "|______________|";

	//	gotoxy(120, 32); cout << "__________________";
	//	gotoxy(120, 33); cout << "|                |";
	//	gotoxy(120, 34); cout << "|      EXIT      |";
	//	gotoxy(120, 35); cout << "|________________|";

	//	string choice;
	//	
	//	POINT point = getMouseClickPosition();
	//	gotoxy(1, 33);
	//	cout << point.x << " " << point.y << endl;
	//	string x;
	//	getline(cin, x);
	//	system("cls");

	//}

	///////////////////////////////////////

	bool BREAK = false;
	while (1) {
		while (1) {
			cout << "                                                            MUONG THANH HOTEL                                             " << endl;
			cout << "\n\n\n\n";
			cout << "                 -------------------------------------------                  ------------------------------------------" << endl;
			cout << "                 |                  LOGIN                  |                  |                 REGISTER               |" << endl;
			cout << "                 -------------------------------------------                  ------------------------------------------" << endl;
			gotoxy(55, 15); cout << "-----------------------------";
			gotoxy(55, 16); cout << "|            EXIT           |";
			gotoxy(55, 17); cout << "-----------------------------";
			


			string choice;
			POINT point = getMouseClickPosition();
			if (point.x >= 215 && point.x <= 725 && point.y >= 175 && point.y <= 215) choice = "1";
			else if (point.x >= 950 && point.x <= 1440 && point.y >= 175 && point.y <= 215) choice = "2";
			system("cls");
			if (choice == "1") {
				p = Login(PL);
				if (p) break;
			}
			else if (choice == "2") {
				Register(PL, ++numberOfperson);
				system("cls");
			}
			else if(point.x >= 675 && point.x <= 1015 && point.y >= 400 && point.y <= 550){
				BREAK = true;
				break;
			}
		}

		system("cls");
		if (BREAK == true) break;

		if (p) {
			if (p->getRole() == 0) {
				while (1) {
					gotoxy(55, 2); cout << "_________________________________";
					gotoxy(55, 4); cout << "|_______________________________|";
					gotoxy(55, 3); cout << "|            OPTIONS            |";

					gotoxy(30, 12); cout << "_________________________________";
					gotoxy(30, 14); cout << "|_______________________________|";
					gotoxy(30, 13); cout << "|            BOOKING            |";

					gotoxy(80, 12); cout << "__________________________________";
					gotoxy(80, 14); cout << "|________________________________|";
					gotoxy(80, 13); cout << "|          CANCEL BOOKING        |";


					gotoxy(61, 18); cout << "______________________";
					gotoxy(61, 20); cout << "|____________________|";
					gotoxy(61, 19); cout << "|        EXIT        |";

					POINT point = getMouseClickPosition();
					system("cls");
					if (point.x >= 375 && point.x <= 760 && point.y >= 340 && point.y <= 390) {
						cout << "\n------------------------------------BOOKING ROOM------------------------------------\n\n\n";
						Booking(RL, BL, p);
					}
					else if (point.x >= 975 && point.x <= 1370 && point.y >= 340 && point.y <= 390) {
						cout << "\n------------------------------------CANCELLATION------------------------------------\n\n\n";
						cancellation(BL, p);
					}
					else if (point.x >= 745 && point.x <= 1000 && point.y >= 490 && point.y <= 530) break;
					else continue;

					string x;
					getline(cin, x);
					system("cls");
				}
			}

			else if (p->getRole() == 1) {
				while (1) {
					gotoxy(55, 2); cout << "_________________________________";
					gotoxy(55, 4); cout << "|_______________________________|";
					gotoxy(55, 3); cout << "|            OPTIONS            |";

					gotoxy(30, 8); cout << "__________________________________";
					gotoxy(30, 10); cout << "|________________________________|";
					gotoxy(30, 9); cout << "|            ADD ROOM            |";



					gotoxy(80, 8); cout << "__________________________________";
					gotoxy(80, 10); cout << "|________________________________|";
					gotoxy(80, 9);  cout << "|            EDIT ROOM           |";


					gotoxy(30, 12); cout << "__________________________________";
					gotoxy(30, 14); cout << "|________________________________|";
					gotoxy(30, 13); cout << "|          DELETE ROOM           |";


					gotoxy(80, 12); cout << "__________________________________";
					gotoxy(80, 14); cout << "|________________________________|";
					gotoxy(80, 13); cout << "|     NUMBER OF ROOMS BOOKED     |";

					gotoxy(30, 16); cout << "__________________________________";
					gotoxy(30, 18); cout << "|________________________________|";
					gotoxy(30, 17); cout << "|    NUMBER OF ROOMS AVAILABLE   |";

					gotoxy(80, 16); cout << "__________________________________";
					gotoxy(80, 18); cout << "|________________________________|";
					gotoxy(80, 17); cout << "|             REVENUE            |";


					gotoxy(61, 20); cout << "______________________";
					gotoxy(61, 22); cout << "|____________________|";
					gotoxy(61, 21); cout << "|        EXIT        |";

					POINT point = getMouseClickPosition();


					system("cls");
					if (point.x >= 375 && point.x <= 770 && point.y >= 250 && point.y <= 300) {
						addRoom(RL);
					}
					else if (point.x >= 975 && point.x <= 1370 && point.y >= 250 && point.y <= 300) {
						editRoom(RL);
					}
					else if (point.x >= 375 && point.x <= 770 && point.y >= 345 && point.y <= 395) {
						cout << "\n------------------------------------BOOKED ROOM STATISTICS------------------------------------\n\n\n";

						deleteRoom(RL);
					}
					else if (point.x >= 975 && point.x <= 1370 && point.y >= 345 && point.y <= 395) {

						cout << "\n------------------------------------BOOKED ROOM STATISTICS------------------------------------\n";
						tm t1 = {};
						tm t2 = {};
						cout << "Enter the date(dd mm yyyy)" << endl;
						cout << "From: ";
						cin >> t1.tm_mday >> t1.tm_mon >> t1.tm_year;
						t1.tm_mon -= 1; t1.tm_year -= 1900;
						cout << "To : ";
						cin >> t2.tm_mday >> t2.tm_mon >> t2.tm_year;
						t2.tm_mon -= 1; t2.tm_year -= 1900;
						int count = numberOfRoomBooked(BL, mktime(&t1), mktime(&t2));
						cout << "NUMBER OF BOOKED ROOM: " << count << endl;
						cin.ignore();
					}
					else if (point.x >= 375 && point.x <= 770 && point.y >= 435 && point.y <= 485) {

						cout << "\n-----------------------------AVAILABLE ROOM STATISTICS-----------------------------\n";
						tm t1 = {};
						tm t2 = {};
						cout << "Enter the date (dd mm yyyy)" << endl;
						cout << "From: ";
						cin >> t1.tm_mday >> t1.tm_mon >> t1.tm_year;
						t1.tm_mon -= 1; t1.tm_year -= 1900;
						cout << "To : ";
						cin >> t2.tm_mday >> t2.tm_mon >> t2.tm_year;
						t2.tm_mon -= 1; t2.tm_year -= 1900;
						int count = numberOfRoomAvailable(RL, BL, mktime(&t1), mktime(&t2));
						cout << "NUMBER OF AVAILABLE ROOM: " << count << endl;
						cin.ignore();
					}
					else if (point.x >= 975 && point.x <= 1370 && point.y >= 435 && point.y <= 485) {
						tm t1 = {};
						tm t2 = {};
						cout << "Enter the date (dd mm yyyy)" << endl;
						cout << "From: ";
						cin >> t1.tm_mday >> t1.tm_mon >> t1.tm_year;
						t1.tm_mon -= 1; t1.tm_year -= 1900;
						cout << "To : ";
						cin >> t2.tm_mday >> t2.tm_mon >> t2.tm_year;
						t2.tm_mon -= 1; t2.tm_year -= 1900;
						long long sum = revenueByDay(BL, mktime(&t1), mktime(&t2));
						cout << sum;
						cin.ignore();

					}
					else if (point.x >= 750 && point.x <= 1000 && point.y >= 530 && point.y <= 580) {
						break;
					}
					else continue;
					string x;
					getline(cin, x);
					system("cls");
				}
			}
		}
	}

	ofstream ofile("room.txt", ios::out);

	Node<room>* temp = RL.getHead();
	while (temp) {
		ofile << temp->getValue()->getRoomId() << "|" << temp->getValue()->getRoomType() << "|" << temp->getValue()->getPrice() << endl;
		temp = temp->getNext();
	}
	ofile.close();

	ofstream ofilee("person.txt", ios::out);

	Node<person>* tempp = PL.getHead();
	while (tempp) {
		ofilee << tempp->getValue()->getId() << "|" << tempp->getValue()->getName() << "|" << tempp->getValue()->getPhone() << "|"
			<< tempp->getValue()->getRole() << "|" << tempp->getValue()->getUserName() << "|" << tempp->getValue()->getPassword();
		if (tempp->getValue()->getRole() == 1) {
			ofilee << "|" << tempp->getValue()->getSalary();
		}
		ofilee << endl;
		tempp = tempp->getNext();
	}
	ofilee.close();


	ofstream ofileee("booking.txt", ios::out);

	Node<booking>* xxx = BL.getHead();
	while (xxx) {
		ofileee << xxx->getValue()->getCustomerId() << "|" << xxx->getValue()->getName() << "|" << xxx->getValue()->getRoomId() << "|"
			<< xxx->getValue()->getAmount() << "|" << xxx->getValue()->getPaymentMethod().getType();
		if (xxx->getValue()->getPaymentMethod().getType() == "Banking") {
			ofileee << "|" << xxx->getValue()->getPaymentMethod().getBank() << "|" << xxx->getValue()->getPaymentMethod().getAccountNumber();
		}
		ofileee << "|" << xxx->getValue()->getCheckInDate() << "|" << xxx->getValue()->getCheckOutDate() << endl;
		xxx = xxx->getNext();
	}

	ofileee.close();


	return 0;
}
