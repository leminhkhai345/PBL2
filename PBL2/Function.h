#include <iostream>
#include "List.h"
#include "Node.h"
#include "room.h"
#include "person.h"
#include "booking.h"
#include "payment.h"
#include "customer.h"
#include <fstream>
#include <string>
#include <ctime>
#include <Windows.h>
#include <conio.h>  
using namespace std;


void gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


POINT getMouseClickPosition() {
	POINT point;  

	while (true) {
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
			GetCursorPos(&point);  
			while (GetAsyncKeyState(VK_LBUTTON) & 0x8000);
			return point;
		}
	}
}

person* Login(List<person>& pl) {
	string username, password;
	while (true) {
		gotoxy(72, 5);
		cout << "LOGIN";
		gotoxy(45, 10);
		cout << "          _________________________________________";
		gotoxy(45, 12);
		cout << "          |_______________________________________|";
		gotoxy(45, 11);
		cout << "username ";
		gotoxy(95, 11);
		cout << "|";
		gotoxy(55, 11);
		cout << "|    ";


		gotoxy(45, 13);
		cout << "          _________________________________________";
		gotoxy(45, 15);
		cout << "          |_______________________________________|";
		gotoxy(45, 14);
		cout << "password ";
		gotoxy(95, 14);
		cout << "|";
		gotoxy(55, 14);
		cout << "|    ";

		gotoxy(67, 18);
		cout << "_________________";
		gotoxy(67, 19); cout << "|     LOGIN     |";
		gotoxy(67, 20); cout << "|_______________|";

		gotoxy(110, 23); cout << "________________________";
		gotoxy(110, 24); cout << "|                      |";
		gotoxy(110, 25); cout << "|         EXIT         |";
		gotoxy(110, 26); cout << "|______________________|";

		POINT point = getMouseClickPosition();
		if (point.x >= 1335 && point.x <= 1610 && point.y >= 600 && point.y <= 665) {
			return nullptr;
		}

		gotoxy(58, 11);
		getline(cin, username);
		gotoxy(58, 14);
		password = "";
		char ch;
		while (true) {
			ch = _getch();
			if (ch == '\r') { // Enter key
				break;
			}
			else if (ch == '\b') { // Backspace key
				if (!password.empty()) {
					cout << "\b \b";
					password.pop_back();
				}
			}
			else {
				cout << '*';
				password += ch;
			}
		}
		cout << endl;

		Node<person>* temp = pl.getHead();
		while (temp) {
			if (temp->getValue()->getUserName() == username && temp->getValue()->getPassword() == password) {
				return temp->getValue();
			}
			temp = temp->getNext();
		}
		system("cls");
		gotoxy(55, 16);
		cout << "Username or password is not correct!" << endl;
	}
}



void Register(List<person>& pl, int autoId) {  // DANG KY
	gotoxy(50, 2); cout << "-------------------  REGISTER  -------------------";

	gotoxy(100, 25); cout << "___________________";
	gotoxy(100, 26); cout << "|                 |";
	gotoxy(100, 27); cout << "|       EXIT      |";
	gotoxy(100, 28); cout << "|_________________|";

	gotoxy(35, 5); cout << "__________________________________________________";
	gotoxy(35, 6); cout << "|";
	gotoxy(35, 7); cout << "|";
	gotoxy(35, 8); cout << "|________________________________________________|";
	gotoxy(84, 6); cout << "|";
	gotoxy(84, 7); cout << "|";
	gotoxy(20, 7); cout << "NAME";

	gotoxy(35, 10); cout << "__________________________________________________";
	gotoxy(35, 11); cout << "|";
	gotoxy(35, 12); cout << "|";
	gotoxy(35, 13); cout << "|________________________________________________|";
	gotoxy(84, 11); cout << "|";
	gotoxy(84, 12); cout << "|";
	gotoxy(20, 12); cout << "PHONE";

	gotoxy(35, 15); cout << "__________________________________________________";
	gotoxy(35, 16); cout << "|";
	gotoxy(35, 17); cout << "|";
	gotoxy(35, 18); cout << "|________________________________________________|";
	gotoxy(84, 16); cout << "|";
	gotoxy(84, 17); cout << "|";
	gotoxy(20, 17); cout << "USERNAME";

	gotoxy(35, 20); cout << "__________________________________________________";
	gotoxy(35, 21); cout << "|";
	gotoxy(35, 22); cout << "|";
	gotoxy(35, 23); cout << "|________________________________________________|";
	gotoxy(84, 21); cout << "|";
	gotoxy(84, 22); cout << "|";
	gotoxy(20, 22); cout << "PASSWORD";

	gotoxy(35, 25); cout << "__________________________________________________";
	gotoxy(35, 26); cout << "|";
	gotoxy(35, 27); cout << "|";
	gotoxy(35, 28); cout << "|________________________________________________|";
	gotoxy(84, 26); cout << "|";
	gotoxy(84, 27); cout << "|";
	gotoxy(16, 27); cout << "CONFIRM PASSWORD";


	string name, phone, username, password = "", passwordAgain = "";
	POINT P1 = getMouseClickPosition();
	if (P1.x >= 1215 && P1.x <= 1430 && P1.y >= 640 && P1.y <= 700) {
		return;
	}
	gotoxy(40, 7);
	getline(cin, name);
	gotoxy(40, 12);
	getline(cin, phone);
	while (1) {
		bool check = true;
		for (int i = 0; i < 10; i++) {
			if (phone[i] > '9' || phone[i] < '0') {
				check = false;
				gotoxy(32, 14);
				cout << "Phone must be number from 0 to 9!! Enter phone number again";
				gotoxy(40, 12);
				getline(cin, phone);
				break;
			}
		}
		if (check == true) break;
	}
	gotoxy(40, 17);
	getline(cin, username);
	while (1) {
		Node<person>* temp = pl.getHead();
		while (temp) {
			if (temp->getValue()->getUserName() == username) {
				gotoxy(32, 19);
				cout << "Username already uese! Please enter username again: ";
				gotoxy(40, 17);
				getline(cin, username);
				break;
			}
			temp = temp->getNext();
		}
		if (temp == nullptr) break;
	}
	gotoxy(40, 22);
	char ch;
	while (true) {
		ch = _getch();
		if (ch == '\r') { // Enter key
			break;
		}
		else if (ch == '\b') { // Backspace key
			if (!password.empty()) {
				cout << "\b \b";
				password.pop_back();
			}
		}
		else {
			cout << '*';
			password += ch;
		}
	}
	while (1) {
		Node<person>* temp = pl.getHead();
		while (temp) {
			if (temp->getValue()->getPassword() == password) {
				gotoxy(32, 24);
				cout << "Password already uese! Please enter password again: ";
				break;
			}
			temp = temp->getNext();
		}
		if (password == "") {
			gotoxy(32, 24);
			cout << "Invalid password!! Please enter password again: ";
			char ch;
			gotoxy(40, 22);
			while (true) {
				ch = _getch();
				if (ch == '\r') { // Enter key
					break;
				}
				else if (ch == '\b') { // Backspace key
					if (!password.empty()) {
						cout << "\b \b";
						password.pop_back();
					}
				}
				else {
					cout << '*';
					password += ch;
				}
			}
			continue;
		}
		if (temp == nullptr) break;
		else {
			char ch;
			gotoxy(40, 22);
			while (true) {
				ch = _getch();
				if (ch == '\r') { // Enter key
					break;
				}
				else if (ch == '\b') { // Backspace key
					if (!password.empty()) {
						cout << "\b \b";
						password.pop_back();
					}
				}
				else {
					cout << '*';
					password += ch;
				}
			}
		}
	}
	while (1) {
		gotoxy(40, 27);
		char ch;
		passwordAgain = "";
		while (true) {
			ch = _getch();
			if (ch == '\r') { // Enter key
				break;
			}
			else if (ch == '\b') { // Backspace key
				if (!passwordAgain.empty()) {
					cout << "\b \b";
					passwordAgain.pop_back();
				}
			}
			else {
				cout << '*';
				passwordAgain += ch;
			}
		}
		if (password == passwordAgain) break;
		else {
			gotoxy(32, 29); cout << "Password doesn't match. Please enter again!";
		}
	}
	customer* p = new customer(autoId, name, phone,0, username, password);
	pl.push(p);
	gotoxy(50, 32); cout << "Successful!";
	cin.ignore();
}

int Booking(List<room>& rl, List<booking>& bl, person* p) {
	int day[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	time_t now = time(nullptr);
	tm t1 = {};
	tm t2 = {};
	time_t tt1, tt2;
	bool check = true;
	while (1) {
		check = true;
		gotoxy(5, 10); cout << "CHECK-IN DATE";
		gotoxy(5, 15); cout << "CHECK-OUT DATE";
		gotoxy(30, 9); cout << "-----------";
		gotoxy(25, 10); cout << "DAY  |";
		gotoxy(30, 11); cout << "-----------";
		gotoxy(40, 10); cout << "|";

		gotoxy(57, 9); cout << "-----------";
		gotoxy(50, 10); cout << "MONTH  |";
		gotoxy(57, 11); cout << "-----------";
		gotoxy(67, 10); cout << "|";


		gotoxy(83, 9); cout << "-----------";
		gotoxy(77, 10); cout << "YEAR  |";
		gotoxy(83, 11); cout << "-----------";
		gotoxy(93, 10); cout << "|";



		gotoxy(30, 14); cout << "-----------";
		gotoxy(25, 15); cout << "DAY  |";
		gotoxy(30, 16); cout << "-----------";
		gotoxy(40, 15); cout << "|";

		gotoxy(57, 14); cout << "-----------";
		gotoxy(50, 15); cout << "MONTH  |";
		gotoxy(57, 16); cout << "-----------";
		gotoxy(67, 15); cout << "|";


		gotoxy(83, 14); cout << "-----------";
		gotoxy(77, 15); cout << "YEAR  |";
		gotoxy(83, 16); cout << "-----------";
		gotoxy(93, 15); cout << "|";

		gotoxy(100, 20); cout << "_________________";
		gotoxy(100, 21); cout << "|               |";
		gotoxy(100, 22); cout << "|      EXIT     |";
		gotoxy(100, 23); cout << "|_______________|";

		POINT P1 = getMouseClickPosition();

		if (P1.x >= 1215 && P1.x <= 1410 && P1.y >= 520 && P1.y <= 600) {
			return -1;
		}

		gotoxy(35, 10);
		cin >> t1.tm_mday;
		gotoxy(62, 10);
		cin >> t1.tm_mon;
		gotoxy(87, 10);
		cin >> t1.tm_year;

		gotoxy(35, 15);
		cin >> t2.tm_mday;
		gotoxy(62, 15);
		cin >> t2.tm_mon;
		gotoxy(87, 15);
		cin >> t2.tm_year;
		if (t1.tm_mon > 12 || t1.tm_mon < 1 || t2.tm_mon > 12 || t2.tm_mon < 1) check = false;
		t2.tm_year -= 1900; t2.tm_mon -= 1;
		t1.tm_year -= 1900; t1.tm_mon -= 1;
		tt1 = mktime(&t1);
		tt2 = mktime(&t2);
		if (tt2 <= tt1 || tt1 <= now) {
			check = false;
		}
		if (check == true) {
			break;
		}
		system("cls");
		gotoxy(30, 20);
		cout << "Ivalid day. Try again: ";
	}

	while (1) {
		system("cls");
		gotoxy(50, 2); cout << "-----------------  BOOKING ROOM  ----------------";
		int k = 7;
		gotoxy(20, k++);
		cout << "-----------------------------------------------------------------------------------" << endl;
		gotoxy(20, k++);
		cout << "|    ROOM ID    |          ROOM TYPE          |          PRICE FOR 1 DAY          |" << endl;
		gotoxy(20, k++);
		cout << "-----------------------------------------------------------------------------------" << endl;
		Node<room>* temp1 = rl.getHead();
		while (temp1) {
			Node<booking>* temp3 = bl.getHead();
			while (temp3) {
				if (temp1->getValue()->getRoomId() == temp3->getValue()->getRoomId()) {
					if (!(temp3->getValue()->getCheckOutDate() < tt1 || temp3->getValue()->getCheckInDate() > tt2)) {
						break;
					}
				}
				temp3 = temp3->getNext();
			}
			if (temp3 == nullptr) {
				gotoxy(20, k++);
				temp1->getValue()->displayDetail();
			}
			temp1 = temp1->getNext();
		}
		gotoxy(20, k++);
		cout << "-----------------------------------------------------------------------------------" << endl;
		k += 3;

		gotoxy(36, k++); cout << "_________________________________";
		gotoxy(36, k++); cout << "|                               |";
		gotoxy(36, k); cout << "|";
		int tmp1 = k;
		gotoxy(68, k++); cout << "|";
		gotoxy(36, k++); cout << "|_______________________________|";
		gotoxy(26, tmp1); cout << "ROOM ID";
		gotoxy(50, tmp1);

		int id;
		cin >> id;
		Node<room>* temp2 = rl.getHead();
		while (temp2) {
			if (temp2->getValue()->getRoomId() == id) break;
			temp2 = temp2->getNext();
		}
		if (temp2 != nullptr) {
			system("cls");
			payment pm;
			gotoxy(50, 5); cout << "-------------------------------------------------";
			gotoxy(50, 6); cout << "|      Room id      |";
			gotoxy(50, 7); cout << "-------------------------------------------------";
			gotoxy(50, 8); cout << "|     Room type     |";
			gotoxy(50, 9); cout << "-------------------------------------------------";
			gotoxy(50, 10); cout << "|      Amount       |";
			gotoxy(50, 11); cout << "-------------------------------------------------";
			gotoxy(98, 6); cout << "|";
			gotoxy(98, 8); cout << "|";
			gotoxy(98, 10); cout << "|";
			gotoxy(84, 6); cout << temp2->getValue()->getRoomId();
			gotoxy(82, 8); cout << temp2->getValue()->getRoomType();
			gotoxy(82, 10); cout << temp2->getValue()->getPrice() * (tt2 - tt1) / (24 * 3600);
			cin.ignore();
			string s;
			getline(cin, s);
			bool NGAT = false;
			while (1) {
				system("cls");
				gotoxy(50, 5); cout << "-------------------------------------------";
				gotoxy(50, 6); cout << "|              PAYMENT METHOD             |";
				gotoxy(50, 7); cout << "-------------------------------------------";

				gotoxy(40, 12); cout << "_____________________";
				gotoxy(40, 13); cout << "|                   |";
				gotoxy(40, 14); cout << "|        CASH       |";
				gotoxy(40, 15); cout << "|___________________|";

				gotoxy(80, 12); cout << "_____________________";
				gotoxy(80, 13); cout << "|                   |";
				gotoxy(80, 14); cout << "|      BANKING      |";
				gotoxy(80, 15); cout << "|___________________|";

				gotoxy(110, 20); cout << "_________________";
				gotoxy(110, 21); cout << "|               |";
				gotoxy(110, 22); cout << "|      EXIT     |";
				gotoxy(110, 23); cout << "|_______________|";


				POINT point = getMouseClickPosition();
				if (point.x >= 395 && point.x <= 730 && point.y >= 340 && point.y <= 410) {
					pm = payment("Cash");
					break;
				}
				else if (point.x >= 1335 && point.x <= 1530 && point.y >= 530 && point.y <= 600) {
					return -1;
				}
				else if (point.x >= 970 && point.x <= 1215 && point.y >= 340 && point.y <= 410) {
					system("cls");
					string bank, accountNumber;
					cout << "choose the bank:" << endl;
					while (1) {
						gotoxy(55, 5); cout << "---------CHOOSE THE BANK----------";
						gotoxy(35, 9); cout << "________________";
						gotoxy(35, 10); cout << "|              |";
						gotoxy(35, 11); cout << "|     BIDV     |";
						gotoxy(35, 12); cout << "|______________|";

						gotoxy(63, 9); cout << "________________";
						gotoxy(63, 10); cout << "|              |";
						gotoxy(63, 11); cout << "|  VIETTINBANK |";
						gotoxy(63, 12); cout << "|______________|";

						gotoxy(91, 9); cout << "________________";
						gotoxy(91, 10); cout << "|              |";
						gotoxy(91, 11); cout << "|    MB BANK   |";
						gotoxy(91, 12); cout << "|______________|";

						gotoxy(35, 17); cout << "________________";
						gotoxy(35, 18); cout << "|              |";
						gotoxy(35, 19); cout << "|   AGRIBANK   |";
						gotoxy(35, 20); cout << "|______________|";

						gotoxy(63, 17); cout << "________________";
						gotoxy(63, 18); cout << "|              |";
						gotoxy(63, 19); cout << "|  VIETCOMBANK |";
						gotoxy(63, 20); cout << "|______________|";

						gotoxy(91, 17); cout << "________________";
						gotoxy(91, 18); cout << "|              |";
						gotoxy(91, 19); cout << "|      ACB     |";
						gotoxy(91, 20); cout << "|______________|";

						gotoxy(35, 25); cout << "________________";
						gotoxy(35, 26); cout << "|              |";
						gotoxy(35, 27); cout << "|  TECHCOMBANK |";
						gotoxy(35, 28); cout << "|______________|";

						gotoxy(63, 25); cout << "________________";
						gotoxy(63, 26); cout << "|              |";
						gotoxy(63, 27); cout << "|    TP BANK   |";
						gotoxy(63, 28); cout << "|______________|";

						gotoxy(91, 25); cout << "________________";
						gotoxy(91, 26); cout << "|              |";
						gotoxy(91, 27); cout << "|   OCEANBANK  |";
						gotoxy(91, 28); cout << "|______________|";

						gotoxy(120, 32); cout << "__________________";
						gotoxy(120, 33); cout << "|                |";
						gotoxy(120, 34); cout << "|      EXIT      |";
						gotoxy(120, 35); cout << "|________________|";

						POINT getbank = getMouseClickPosition();
						if (getbank.x >= 435 && getbank.x <= 615 && getbank.y >= 270 && getbank.y <= 345) {
							bank = "BIDV";
							break;
						}
						else if (getbank.x >= 770 && getbank.x <= 950 && getbank.y >= 270 && getbank.y <= 345) {
							bank = "VIETTINBANK";
							break;
						}
						else if (getbank.x >= 1100 && getbank.x <= 1290 && getbank.y >= 270 && getbank.y <= 345) {
							bank = "MB BANK";
							break;
						}
						else if (getbank.x >= 435 && getbank.x <= 615 && getbank.y >= 455 && getbank.y <= 530) {
							bank = "AGRIBANK";
							break;
						}
						else if (getbank.x >= 770 && getbank.x <= 950 && getbank.y >= 455 && getbank.y <= 530) {
							bank = "VIETCOMBANK";
							break;
						}
						else if (getbank.x >= 1100 && getbank.x <= 1290 && getbank.y >= 455 && getbank.y <= 530) {
							bank = "ACB";
							break;
						}
						else if (getbank.x >= 435 && getbank.x <= 615 && getbank.y >= 640 && getbank.y <= 710) {
							bank = "TECHCOMBANK";
							break;
						}
						else if (getbank.x >= 770 && getbank.x <= 950 && getbank.y >= 640 && getbank.y <= 710) {
							bank = "TP BANK";
							break;
						}
						else if (getbank.x >= 1100 && getbank.x <= 1290 && getbank.y >= 640 && getbank.y <= 710) {
							bank = "TP BANK";
							break;
						}
						else if (getbank.x >= 1455 && getbank.x <= 1655 && getbank.y >= 800 && getbank.y <= 870) {
							NGAT = true;
							break;
						}
					}
					if (NGAT == true) continue;
					system("cls");

					while (1) {
						gotoxy(42, 17); cout << "ACCOUNT NUMBER";
						gotoxy(60, 15); cout << "_______________________________";
						gotoxy(60, 16); cout << "|                             |";
						gotoxy(60, 17); cout << "|";
						gotoxy(60, 18); cout << "|_____________________________|";
						gotoxy(90, 17); cout << "|";
						gotoxy(65, 17);
						getline(cin, accountNumber);
						bool check = true;
						for (char x : accountNumber) {
							if (x < '0' || x > '9') {
								check = false;
								break;
							}
						}
						if (check == true) {
							break;
						}
						system("cls");
						cout << "accountNumber invalid! Try again: ";
					}
					pm = payment("Banking", bank, accountNumber);
					break;
				}
				else {
					cout << "Ivalid choice! Enter your choice again: " << endl;
				}
			}
			booking* x = new booking(p->getId(), p->getName(), temp2->getValue()->getRoomId(), temp2->getValue()->getPrice() * (tt2 - tt1) / (24 * 3600), pm, tt1, tt2);
			bl.push(x);
			gotoxy(60, 20);
			cout << "Booking successfully." << endl;
			cin.ignore();
			break;
		}
		gotoxy(30, k++); cout << "Invalid room id! Please enter room id again!";
		cin.ignore();
		cin.ignore();
	}
	return 1;
}


void cancellation(List<booking>& bl, person *c) {
	Node<booking>* temp = bl.getHead();
	time_t now = time(nullptr);

	cout << "\n                                            ----------------------------  CANCELLATION  ----------------------------";
	gotoxy(20, 4); cout << "All room you can cacel :" << endl;
	int k = 7;
	gotoxy(20, k++);
	cout << "-----------------------------------------------------------------------------------------------------------------" << endl;
	gotoxy(20, k++);
	cout << "|    room id    |           Name          |        Amount      |      check-in date      |     check-out date   |" << endl;
	gotoxy(20, k++);
	cout << "-----------------------------------------------------------------------------------------------------------------" << endl;
	while (temp) {
		if (temp->getValue()->getCustomerId() == c->getId() && temp->getValue()->getCheckInDate() > now) {
			gotoxy(20, k++);
			temp->getValue()->display();
		}
		temp = temp->getNext();
	}
	gotoxy(20, k++);
	cout << "-----------------------------------------------------------------------------------------------------------------\n" << endl;

	k += 3;
	int temp1;
	gotoxy(40, k++); cout << "_____________________________________";
	gotoxy(40, k++); cout << "|                                   |";
	temp1 = k;
	gotoxy(40, k++); cout << "|";
	gotoxy(76, temp1); cout << "|";
	gotoxy(40, k++); cout << "|___________________________________|";
	gotoxy(20, temp1); cout << "ROOM ID";

	k += 3;
	int temp2;
	gotoxy(20, k++); cout << "CHECK-IN DATE";
	k += 2;
	gotoxy(30, k); cout << "_________________";
	gotoxy(60, k); cout << "_________________";
	gotoxy(90, k); cout << "_________________";
	k++;
	gotoxy(30, k); cout << "|"; 
	gotoxy(46, k); cout << "|";
	gotoxy(60, k); cout << "|";
	gotoxy(76, k); cout << "|";
	gotoxy(90, k); cout << "|";
	gotoxy(106, k); cout << "|";
	k++;
	temp2 = k;
	gotoxy(25, k); cout << "DAY";
	gotoxy(30, k); cout << "|";
	gotoxy(46, k); cout << "|";
	gotoxy(53, k); cout << "MONTH";
	gotoxy(60, k); cout << "|";
	gotoxy(76, k); cout << "|";
	gotoxy(84, k); cout << "YEAR";
	gotoxy(90, k); cout << "|";
	gotoxy(106, k); cout << "|";
	k++;
	gotoxy(30, k); cout << "|_______________|";
	gotoxy(60, k); cout << "|_______________|";
	gotoxy(90, k); cout << "|_______________|";
	gotoxy(135, 1); cout << "_______________";
	gotoxy(135, 2); cout << "|             |";
	gotoxy(135, 3); cout << "|     EXIT    |";
	gotoxy(135, 4); cout << "|_____________|";

	POINT point = getMouseClickPosition();
	if (point.x >= 1635 && point.x <= 1800 && point.y >= 90 && point.y <= 160) {
		return;
	}

	gotoxy(58, temp1);
	int roomid;
	cin >> roomid;
	tm timechekin = {};
	gotoxy(38, temp2);
	cin >> timechekin.tm_mday;
	gotoxy(68, temp2);
	cin >> timechekin.tm_mon;
	gotoxy(96, temp2);
	cin >> timechekin.tm_year;
	timechekin.tm_mon--; timechekin.tm_year -= 1900;
	time_t time_tchekin = mktime(&timechekin);
	temp = bl.getHead();
	while (temp) {
		if (temp->getValue()->getRoomId() == roomid && time_tchekin == temp->getValue()->getCheckInDate()) {
			bl.pop(temp);
			gotoxy(62, k + 4);
			cout << "Successful!!";
			cin.ignore();
			break;
		}
		temp = temp->getNext();
	}
	if (temp == nullptr) {
		gotoxy(64, k+4);
		cout << "Invalid!!!" << endl;
		cin.ignore();
	}
	cin.ignore();
}



void addRoom(List<room>& rl) {
	int id, price;
	string roomtype;

	while (1) {

		gotoxy(50, 2); cout << "-------------------- ADD ROOM --------------------";
		gotoxy(0, 7);
		cout << "-----------------------------------------------------------------------------------" << endl;
		cout << "|    ROOM ID    |          ROOM TYPE          |          PRICE FOR 1 DAY          |" << endl;
		cout << "-----------------------------------------------------------------------------------" << endl;
		Node<room>* r = rl.getHead();
		while (r) {
			r->getValue()->displayDetail();
			r = r->getNext();
		}
		cout << "-----------------------------------------------------------------------------------";

		gotoxy(90, 12); cout << "ROOM ID";
		gotoxy(100, 10); cout << "___________________________";
		gotoxy(100, 11); cout << "|                         |";
		gotoxy(100, 12); cout << "|";
		gotoxy(126, 12); cout << "|";
		gotoxy(100, 13); cout << "|_________________________|";

		gotoxy(90, 18); cout << "ROOM TYPE";
		gotoxy(100, 16); cout << "___________________________";
		gotoxy(100, 17); cout << "|                         |";
		gotoxy(100, 18); cout << "|";
		gotoxy(126, 18); cout << "|";
		gotoxy(100, 19); cout << "|_________________________|";

		gotoxy(90, 24); cout << "PRICE";
		gotoxy(100, 22); cout << "___________________________";
		gotoxy(100, 23); cout << "|                         |";
		gotoxy(100, 24); cout << "|";
		gotoxy(126, 24); cout << "|";
		gotoxy(100, 25); cout << "|_________________________|";

		gotoxy(100, 30); cout << "___________________________";
		gotoxy(100, 31); cout << "|                         |";
		gotoxy(100, 32); cout << "|          EXIT           |";
		gotoxy(100, 33); cout << "|_________________________|";

		POINT point = getMouseClickPosition();
		if (point.x >= 1215 && point.x <= 1530 && point.y >= 750 && point.y <= 825) {
			return;
		}

		gotoxy(112, 12);
		cin >> id;
		Node<room>* temp = rl.getHead();
		bool check = true;
		while (temp) {
			if (id == temp->getValue()->getRoomId()) {
				check = false;
				break;
			}
			temp = temp->getNext();
		}
		if (check == true) break;
		else {
			system("cls");
			gotoxy(90, 14);
			cout << "The id already exist! Please enter another id." << endl;
		}
	}
	
	cin.ignore();
	gotoxy(110, 18); getline(cin, roomtype);
	gotoxy(110, 24); cin >> price;
	room* r = new room(id, roomtype, price);
	rl.push(r);
	gotoxy(109, 27);
	cout << "Successful!" << endl;
	cin.ignore();
	cin.ignore();
}

void editRoom(List<room>& rl) {
	while (1) {
		gotoxy(50, 2); cout << "-------------------- EDIT ROOM --------------------";
		gotoxy(0, 7);
		cout << "-----------------------------------------------------------------------------------" << endl;
		cout << "|    ROOM ID    |          ROOM TYPE          |          PRICE FOR 1 DAY          |" << endl;
		cout << "-----------------------------------------------------------------------------------" << endl;
		Node<room>* r = rl.getHead();
		while (r) {
			r->getValue()->displayDetail();
			r = r->getNext();
		}
		cout << "-----------------------------------------------------------------------------------";

		gotoxy(90, 12); cout << "ROOM ID";
		gotoxy(110, 10); cout << "___________________________";
		gotoxy(110, 11); cout << "|                         |";
		gotoxy(110, 12); cout << "|";
		gotoxy(136, 12); cout << "|";
		gotoxy(110, 13); cout << "|_________________________|";

		gotoxy(90, 18); cout << "NEW ROOM TYPE";
		gotoxy(110, 16); cout << "___________________________";
		gotoxy(110, 17); cout << "|                         |";
		gotoxy(110, 18); cout << "|";
		gotoxy(136, 18); cout << "|";
		gotoxy(110, 19); cout << "|_________________________|";

		gotoxy(90, 24); cout << "NEW PRICE";
		gotoxy(110, 22); cout << "___________________________";
		gotoxy(110, 23); cout << "|                         |";
		gotoxy(110, 24); cout << "|";
		gotoxy(136, 24); cout << "|";
		gotoxy(110, 25); cout << "|_________________________|";

		gotoxy(110, 30); cout << "___________________________";
		gotoxy(110, 31); cout << "|                         |";
		gotoxy(110, 32); cout << "|          EXIT           |";
		gotoxy(110, 33); cout << "|_________________________|";

		POINT point = getMouseClickPosition();
		if (point.x >= 1335 && point.x <= 1645 && point.y >= 750 && point.y <= 825) {
			return;
		}

		gotoxy(122, 12);
		int roomId;
		cin >> roomId;
		cin.ignore();
		Node<room>* temp = rl.getHead();
		bool check = false;
		while (temp) {
			if (temp->getValue()->getRoomId() == roomId) {
				gotoxy(120, 18);
				string roomtype; 
				getline(cin, roomtype);
				string price;
				gotoxy(120, 24);
				getline(cin, price);
				if (price != "") temp->getValue()->setPrice(stoi(price));
				if(roomtype != "")temp->getValue()->setRoomtype(roomtype);
				check = true;
				break;
			}
			if (check == true) break;
			temp = temp->getNext();
		}
		if (temp == nullptr) {
			gotoxy(104, 14);
			cout << "Invalid room id!!! Please enter room id again." << endl;
			string x;
			getline(cin, x);
			system("cls");
		}
		else {
			gotoxy(119, 27);
			cout << "Successfull!!" << endl;
			cin.ignore();
			break;
		}
	}
}

void deleteRoom(List<room>& rl) {
	while (1) {
		gotoxy(50, 2); cout << "-------------------- DELETE ROOM --------------------";
		gotoxy(0, 7);
		cout << "-----------------------------------------------------------------------------------" << endl;
		cout << "|    ROOM ID    |          ROOM TYPE          |          PRICE FOR 1 DAY          |" << endl;
		cout << "-----------------------------------------------------------------------------------" << endl;
		Node<room>* r = rl.getHead();
		while (r) {
			r->getValue()->displayDetail();
			r = r->getNext();
		}
		cout << "----------------------------------------------------------------------------------" << endl;

		gotoxy(90, 12); cout << "ROOM ID";
		gotoxy(110, 10); cout << "___________________________";
		gotoxy(110, 11); cout << "|                         |";
		gotoxy(110, 12); cout << "|";
		gotoxy(136, 12); cout << "|";
		gotoxy(110, 13); cout << "|_________________________|";

		gotoxy(110, 25); cout << "___________________________";
		gotoxy(110, 26); cout << "|                         |";
		gotoxy(110, 27); cout << "|           EXIT          |";
		gotoxy(110, 28); cout << "|_________________________|";

		POINT point = getMouseClickPosition();
		if (point.x >= 1335 && point.x <= 1645 && point.y >= 640 && point.y <= 710) {
			return;
		}

		gotoxy(122, 12);
		int roomid;
		cin >> roomid;
		cin.ignore();
		Node<room>* temp = rl.getHead();
		while (temp) {
			if (temp->getValue()->getRoomId() == roomid) {
				rl.pop(temp);
				gotoxy(119, 15);
				cout << "Successful!" << endl;
				cin.ignore();
				return;
			}
			temp = temp->getNext();
		}
		if (temp == nullptr) {
			gotoxy(109, 15);
			cout << "Room with id " << roomid << " does not exist!" << endl;
		}
		string x;
		getline(cin, x);
		system("cls");
	}
}


int numberOfRoomBooked(List<booking>& bl) {


	cout << "\n                                         -----------------  BOOKED ROOM STATISTICS  -----------------\n";
	tm t1 = {};
	tm t2 = {};
	gotoxy(15, 5); cout << "ENTER THE CHECK-IN DATE:";

	gotoxy(15, 10); cout << "FROM";
	gotoxy(15, 16); cout << "TO";
	gotoxy(30, 8); cout << "____________";
	gotoxy(30, 9); cout << "|          |";
	gotoxy(25, 10); cout << "DAY  |";
	gotoxy(30, 11); cout << "|__________|";
	gotoxy(41, 10); cout << "|";

	gotoxy(57, 8); cout << "____________";
	gotoxy(57, 9); cout << "|          |";
	gotoxy(50, 10); cout << "MONTH  |";
	gotoxy(57, 11); cout << "|__________|";
	gotoxy(68, 10); cout << "|";


	gotoxy(83, 8); cout << "____________";
	gotoxy(83, 9); cout << "|          |";
	gotoxy(77, 10); cout << "YEAR  |";
	gotoxy(83, 11); cout << "|__________|";
	gotoxy(94, 10); cout << "|";



	gotoxy(30, 14); cout << "____________";
	gotoxy(30, 15); cout << "|          |";
	gotoxy(25, 16); cout << "DAY  |";
	gotoxy(30, 17); cout << "|__________|";
	gotoxy(41, 16); cout << "|";

	gotoxy(57, 14); cout << "____________";
	gotoxy(57, 15); cout << "|          |";
	gotoxy(50, 16); cout << "MONTH  |";
	gotoxy(57, 17); cout << "|__________|";
	gotoxy(68, 16); cout << "|";


	gotoxy(83, 14); cout << "____________";
	gotoxy(83, 15); cout << "|          |";
	gotoxy(77, 16); cout << "YEAR  |";
	gotoxy(83, 17); cout << "|__________|";
	gotoxy(94, 16); cout << "|";


	gotoxy(110, 25); cout << "___________________________";
	gotoxy(110, 26); cout << "|                         |";
	gotoxy(110, 27); cout << "|           EXIT          |";
	gotoxy(110, 28); cout << "|_________________________|";

	POINT point = getMouseClickPosition();
	if (point.x >= 1335 && point.x <= 1645 && point.y >= 640 && point.y <= 710) {
		return -1;
	}

	gotoxy(35, 10); cin >> t1.tm_mday;
	gotoxy(62, 10); cin >> t1.tm_mon;
	gotoxy(87, 10);  cin >> t1.tm_year;
	t1.tm_mon -= 1; t1.tm_year -= 1900;

	gotoxy(35, 16); cin >> t2.tm_mday;
	gotoxy(62, 16); cin >> t2.tm_mon;
	gotoxy(87, 16); cin >> t2.tm_year;
	t2.tm_mon -= 1; t2.tm_year -= 1900;

	time_t checkInDate = mktime(&t1), checkOutDate = mktime(&t2);

	system("cls");
	gotoxy(50, 2); cout << "-------------------- BOOKED ROOM --------------------";
	int count = 0;
	Node<booking>* temp = bl.getHead();
	int k = 7;
	gotoxy(20, k++);
	cout << "-----------------------------------------------------------------------------------------------------------------" << endl;
	gotoxy(20, k++);
	cout << "|    room id    |      Name of booker     |       Amount       |      check-in date      |    check-out date    |" << endl;
	gotoxy(20, k++);
	cout << "-----------------------------------------------------------------------------------------------------------------" << endl;
	while (temp) {
		if (temp->getValue()->getCheckInDate() >= checkInDate && temp->getValue()->getCheckInDate() <= checkOutDate)
		{	
			gotoxy(20, k++);
			temp->getValue()->display();
			count++;
		}
		temp = temp->getNext();
	}
	gotoxy(20, k++);
	cout << "-----------------------------------------------------------------------------------------------------------------" << endl;
	return count;
}

int numberOfRoom(List<room>& rl) {
	int count = 0;
	Node<room>* temp = rl.getHead();
	while (temp) {
		count++;
		temp = temp->getNext();
	}
	return count;
}

int numberOfRoomAvailable(List<room>& rl, List<booking>& bl) {

	cout << "\n                                              ---------------  AVAILABLE ROOM STATISTICS  ---------------\n";
	tm t1 = {};
	tm t2 = {};

	gotoxy(15, 5); cout << "ENTER THE CHECK-IN DATE:";

	gotoxy(15, 10); cout << "FROM";
	gotoxy(15, 16); cout << "TO";
	gotoxy(30, 8); cout << "____________";
	gotoxy(30, 9); cout << "|          |";
	gotoxy(25, 10); cout << "DAY  |";
	gotoxy(30, 11); cout << "|__________|";
	gotoxy(41, 10); cout << "|";

	gotoxy(57, 8); cout << "____________";
	gotoxy(57, 9); cout << "|          |";
	gotoxy(50, 10); cout << "MONTH  |";
	gotoxy(57, 11); cout << "|__________|";
	gotoxy(68, 10); cout << "|";

	gotoxy(83, 8); cout << "____________";
	gotoxy(83, 9); cout << "|          |";
	gotoxy(77, 10); cout << "YEAR  |";
	gotoxy(83, 11); cout << "|__________|";
	gotoxy(94, 10); cout << "|";

	gotoxy(30, 14); cout << "____________";
	gotoxy(30, 15); cout << "|          |";
	gotoxy(25, 16); cout << "DAY  |";
	gotoxy(30, 17); cout << "|__________|";
	gotoxy(41, 16); cout << "|";

	gotoxy(57, 14); cout << "____________";
	gotoxy(57, 15); cout << "|          |";
	gotoxy(50, 16); cout << "MONTH  |";
	gotoxy(57, 17); cout << "|__________|";
	gotoxy(68, 16); cout << "|";


	gotoxy(83, 14); cout << "____________";
	gotoxy(83, 15); cout << "|          |";
	gotoxy(77, 16); cout << "YEAR  |";
	gotoxy(83, 17); cout << "|__________|";
	gotoxy(94, 16); cout << "|";

	gotoxy(110, 25); cout << "___________________________";
	gotoxy(110, 26); cout << "|                         |";
	gotoxy(110, 27); cout << "|           EXIT          |";
	gotoxy(110, 28); cout << "|_________________________|";

	POINT point = getMouseClickPosition();
	if (point.x >= 1335 && point.x <= 1645 && point.y >= 640 && point.y <= 710) {
		return -1;
	}

	gotoxy(35, 10); cin >> t1.tm_mday;
	gotoxy(62, 10); cin >> t1.tm_mon;
	gotoxy(87, 10);  cin >> t1.tm_year;
	t1.tm_mon -= 1; t1.tm_year -= 1900;

	gotoxy(35, 16); cin >> t2.tm_mday;
	gotoxy(62, 16); cin >> t2.tm_mon;
	gotoxy(87, 16); cin >> t2.tm_year;

	t2.tm_mon -= 1; t2.tm_year -= 1900;

	time_t checkInDate = mktime(&t1), checkOutDate = mktime(&t2);

	system("cls");
	int count = 0;
	gotoxy(50, 2); cout << "-------------------- VAILABLE ROOM --------------------";
	int k = 7;
	gotoxy(20, k++);
	cout << "-----------------------------------------------------------------------------------" << endl;
	gotoxy(20, k++);
	cout << "|    ROOM ID    |          ROOM TYPE          |          PRICE FOR 1 DAY          |" << endl;
	gotoxy(20, k++);
	cout << "-----------------------------------------------------------------------------------" << endl;
	int arr[1000] = { 0 };
	Node<booking>* temp = bl.getHead();
	while (temp) {
		if ((temp->getValue()->getCheckInDate() <= checkInDate && temp->getValue()->getCheckOutDate() >= checkInDate)
			|| (temp->getValue()->getCheckInDate() <= checkOutDate && temp->getValue()->getCheckOutDate() >= checkOutDate))
		{
			arr[temp->getValue()->getRoomId()] = 1;
		}
		temp = temp->getNext();
	}
	Node<room>* tmp = rl.getHead();
	while (tmp) {
		if (arr[tmp->getValue()->getRoomId()] == 0) {
			gotoxy(20, k++);
			tmp->getValue()->displayDetail();
			count++;
		}
		tmp = tmp->getNext();
	}
	gotoxy(20, k++);
	cout << "-----------------------------------------------------------------------------------" << endl;

 	return count;
}

long long revenueByDay(List<booking>& bl) {

	tm t1 = {};
	tm t2 = {};
	gotoxy(15, 5); cout << "ENTER STATISTICAL DATE:";

	gotoxy(15, 10); cout << "FROM";
	gotoxy(15, 16); cout << "TO";
	gotoxy(30, 8); cout << "____________";
	gotoxy(30, 9); cout << "|          |";
	gotoxy(25, 10); cout << "DAY  |";
	gotoxy(30, 11); cout << "|__________|";
	gotoxy(41, 10); cout << "|";

	gotoxy(57, 8); cout << "____________";
	gotoxy(57, 9); cout << "|          |";
	gotoxy(50, 10); cout << "MONTH  |";
	gotoxy(57, 11); cout << "|__________|";
	gotoxy(68, 10); cout << "|";

	gotoxy(83, 8); cout << "____________";
	gotoxy(83, 9); cout << "|          |";
	gotoxy(77, 10); cout << "YEAR  |";
	gotoxy(83, 11); cout << "|__________|";
	gotoxy(94, 10); cout << "|";



	gotoxy(30, 14); cout << "____________";
	gotoxy(30, 15); cout << "|          |";
	gotoxy(25, 16); cout << "DAY  |";
	gotoxy(30, 17); cout << "|__________|";
	gotoxy(41, 16); cout << "|";

	gotoxy(57, 14); cout << "____________";
	gotoxy(57, 15); cout << "|          |";
	gotoxy(50, 16); cout << "MONTH  |";
	gotoxy(57, 17); cout << "|__________|";
	gotoxy(68, 16); cout << "|";


	gotoxy(83, 14); cout << "____________";
	gotoxy(83, 15); cout << "|          |";
	gotoxy(77, 16); cout << "YEAR  |";
	gotoxy(83, 17); cout << "|__________|";
	gotoxy(94, 16); cout << "|";

	gotoxy(110, 25); cout << "___________________________";
	gotoxy(110, 26); cout << "|                         |";
	gotoxy(110, 27); cout << "|           EXIT          |";
	gotoxy(110, 28); cout << "|_________________________|";

	POINT point = getMouseClickPosition();
	if (point.x >= 1335 && point.x <= 1645 && point.y >= 640 && point.y <= 710) {
		return -1;
	}

	gotoxy(35, 10); cin >> t1.tm_mday;
	gotoxy(62, 10); cin >> t1.tm_mon;
	gotoxy(87, 10);  cin >> t1.tm_year;
	t1.tm_mon -= 1; t1.tm_year -= 1900;

	gotoxy(35, 16); cin >> t2.tm_mday;
	gotoxy(62, 16); cin >> t2.tm_mon;
	gotoxy(87, 16); cin >> t2.tm_year;

	t2.tm_mon -= 1; t2.tm_year -= 1900;

	time_t checkInDate1 = mktime(&t1), checkInDate2 = mktime(&t2);

	system("cls");
	gotoxy(45, 2); cout << "---------------------  REVENUE  STATISTICS  ---------------------";
	long long sum = 0;
	Node<booking>* temp = bl.getHead();
	int k = 7;
	gotoxy(20, k++);
	cout << "-----------------------------------------------------------------------------------------------------------------" << endl;
	gotoxy(20, k++);
	cout << "|    room id    |           Name          |        Amount      |      check-in date      |     check-out date   |" << endl;
	gotoxy(20, k++);
	cout << "-----------------------------------------------------------------------------------------------------------------" << endl;
	while (temp) {
		if (temp->getValue()->getCheckInDate() >= checkInDate1 && temp->getValue()->getCheckInDate() <= checkInDate2) {
			gotoxy(20, k++);
			temp->getValue()->display();
			sum += temp->getValue()->getAmount();
		}
		temp = temp->getNext();
	}
	gotoxy(20, k++);
	cout << "-----------------------------------------------------------------------------------------------------------------" << endl;
	gotoxy(20, k + 2); cout << "REVENUE : " << sum << " VND";
	return sum;
}
