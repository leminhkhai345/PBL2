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

		gotoxy(58, 11);
		getline(cin, username);
		gotoxy(58, 14);
		password = "";
		char ch;
		while (true) {
			//if (GetAsyncKeyState(VK_LBUTTON)) {
			//	break;
			//	// Lấy tọa độ hiện tại của con trỏ chuột
			//	POINT point;
			//	GetCursorPos(&point);
			//	if (point.x >= 820 && point.x <= 1000 && point.y >= 480 && point.y <= 525) break;
			//}

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

//person* Login(List<person>& pl) {
//	string username, password;
//	bool check = false;
//	while (1) {
//		cout << "username: ";
//		getline(cin, username);
//		cout << "password: ";
//		char ch;
//		while (true) {
//			password = "";
//			ch = _getch();  
//
//			if (ch == '\r') { 
//				break;
//			}
//			else if (ch == '\b' && !password.empty()) {  
//				std::cout << "\b \b";
//				password.pop_back();
//			}
//			else if (ch != '\b') {  
//				std::cout << '*';
//				password += ch;
//			}
//		}
//		
//		Node<person>* temp = pl.getHead();
//		while (temp) {
//			if (temp->getValue()->getUserName() == username && temp->getValue()->getPassword() == password) {
//				cout << "Login successfully! " << endl;
//				return temp->getValue();
//			}
//			temp = temp->getNext();
//		}
//		system("cls");
//		cout << "user name or password is not correct!" << endl;
//	}
//}

void Register(List<person>& pl, int autoId) {  // DANG KY
	string name, phone, username, password;
	cout << "Enter your name: ";
	getline(cin, name);
	cout << "Enter your phone: ";
	getline(cin, phone);
	while (1) {
		bool check = true;
		for (int i = 0; i < 10; i++) {
			if (phone[i] > '9' || phone[i] < '0') {
				check = false;
				cout << "Phone must be number from 0 to 9!!" << endl;
				cout << "Enter phone number again: ";
				getline(cin, phone);
				break;
			}
		}
		if (check == true) break;
	}
	cout << "uername: ";
	getline(cin, username);
	while (1) {
		Node<person>* temp = pl.getHead();
		while (temp) {
			if (temp->getValue()->getUserName() == username) {
				cout << "Username already uese! Please enter username again: ";
				getline(cin, username);
				break;
			}
			temp = temp->getNext();
		}
		if (temp == nullptr) break;
	}
	cout << "Password: ";
	getline(cin, password);
	while (1) {
		Node<person>* temp = pl.getHead();
		while (temp) {
			if (temp->getValue()->getPassword() == password) {
				cout << "Password already uese! Please enter password again: ";
				break;
			}
			temp = temp->getNext();
		}
		if (password == "") {
			cout << "Invalid password!! Please enter password again: ";
			getline(cin, password);
			continue;
		}
		if (temp == nullptr) break;
		else {
			getline(cin, password);
		}
	}
	customer* p = new customer(autoId, name, phone,0, username, password);
	pl.push(p);
	cout << "Register successful!!" << endl;
	string pau;
	getline(cin, pau);
}

void Booking(List<room>& rl, List<booking>& bl, person* p) {
	int day[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	time_t now = time(nullptr);
	tm nowtime;
	localtime_s(&nowtime, &now);
	tm t1 = {};
	tm t2 = {};
	time_t tt1, tt2;
	while (1) {
		bool check = true;
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
		t2.tm_year -= 1900; t2.tm_mon -= 1;
		t1.tm_year -= 1900; t1.tm_mon -= 1;
		tt1 = mktime(&t1);
		tt2 = mktime(&t2);
		if (tt2 <= tt1) {
			check = false;
		}
		if (t1.tm_mday > day[t1.tm_mon]) check = false;
		if (t1.tm_year < nowtime.tm_year) check = false;
		if (t1.tm_year == nowtime.tm_year && t1.tm_mon < nowtime.tm_mon ) check = false;
		if (t1.tm_year == nowtime.tm_year && t1.tm_mon == nowtime.tm_mon && t1.tm_mday < nowtime.tm_mday) check = false;
		if (check == true) {
			break;
		}
		if (t1.tm_mon > 12 || t1.tm_mon < 1 || t2.tm_mon > 12 || t2.tm_mon < 1) check = false;
		system("cls");
		gotoxy(30, 20);
		cout << "Ivalid day. Try again: ";
	}


	
	system("cls");
	cout << "-----------------------------------------------------------------------------------" << endl;
	cout << "|    ROOM ID    |          ROOM TYPE          |          PRICE FOR 1 DAY          |" << endl;
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
			temp1->getValue()->displayDetail();
		}
		temp1 = temp1->getNext();
	}
	cout << "-----------------------------------------------------------------------------------" << endl;
	cout << "Enter the room id: ";
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
			POINT point = getMouseClickPosition();
			if (point.x >= 395 && point.x <= 730 && point.y >= 340 && point.y <= 410) {
				pm = payment("Cash");
				break;
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
				
				cout << "enter accountNumber: ";
				while (1) {
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
					cout << "accountNumber invalid! Try again: ";
				}
				pm = payment("Banking", bank, accountNumber);
				break;
			}
			else {
				cout << "Ivalid choice! Enter your choice again: " << endl;
			}
		}
		booking* x = new booking(p->getId(), p->getName(), temp2->getValue()->getRoomId(), temp2->getValue()->getPrice() * (tt2 - tt1)/(24 * 3600), pm, tt1, tt2);
		bl.push(x);
		gotoxy(60, 20);
		cout << "Booking successfully." << endl;
		string xx;
		getline(cin, xx);
	}
	
}


void cancellation(List<booking>& bl, person *c) {
	Node<booking>* temp = bl.getHead();
		cout << "All room you can cancel :" << endl;
		cout << "------------------------------------------------------------------------------------------------" << endl;
		cout << "|    room id    |       Name of booker      |      check-in date      |     check-out date     |" << endl;
		cout << "------------------------------------------------------------------------------------------------" << endl;
	while (temp) {
		if (temp->getValue()->getCustomerId() == c->getId()) {
			temp->getValue()->display();
		}
		temp = temp->getNext();
	}
	cout << "------------------------------------------------------------------------------------------------" << endl;


	cout << "Enter room id your want to cancel: ";
	int roomid;
	cin >> roomid;
	cout << "Enter date check-in(dd mm yyyy): ";
	tm timechekin = {};
	cin >> timechekin.tm_mday >> timechekin.tm_mon >> timechekin.tm_year;
	timechekin.tm_mon--; timechekin.tm_year -= 1900;
	time_t time_tchekin = mktime(&timechekin);
	temp = bl.getHead();
	while (temp) {
		if (temp->getValue()->getRoomId() == roomid && time_tchekin == temp->getValue()->getCheckInDate()) {
			bl.pop(temp);
			cout << "Cancel successfully!!";
			break;
		}
		temp = temp->getNext();
	}
	if (temp == nullptr) {
		cout << "Invalid!!!" << endl;
	}
	cin.ignore();
}


void scheduleBooing(List<booking>& bl, int roomid) {
	Node<booking>* temp = bl.getHead();
	while (temp) {
		if (temp->getValue()->getRoomId() == roomid) {
			time_t t = temp->getValue()->getCheckInDate();
			tm tt;
			localtime_s(&tt, &t);
			cout << "check-in date: ";
			cout << tt.tm_mday << "/" << tt.tm_mon << "/" << tt.tm_year << endl;
			cout << "cehck-out date: ";
			time_t t2 = temp->getValue()->getCheckOutDate();
			tm to;
			localtime_s(&to, &t2);
			cout << to.tm_mday << "/" << to.tm_mon << "/" << to.tm_year << endl;
		}
		temp = temp->getNext();
		string x;
		getline(cin, x);
	}
}

void addRoom(List<room>& rl) {
	int id, price;
	string roomtype;
	while (1) {
		cout << "-----------------------------------------------------------------------------------" << endl;
		cout << "|    ROOM ID    |          ROOM TYPE          |          PRICE FOR 1 DAY          |" << endl;
		cout << "-----------------------------------------------------------------------------------" << endl;
		Node<room>* r = rl.getHead();
		while (r) {
			r->getValue()->displayDetail();
			r = r->getNext();
		}
		cout << "----------------------------------------------------------------------------------";
		cout << "\nEnter room id: "; cin >> id;
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
			cout << "The id already exist! Please enter another id." << endl;
		}
	}
	cin.ignore();
	cout << "Enter room type: "; getline(cin, roomtype);
	cout << "Price for 1 day: "; cin >> price;
	room* r = new room(id, roomtype, price);
	rl.push(r);
	cout << "Successful!" << endl;
	string x;
	getline(cin, x);
}

void editRoom(List<room>& rl) {
	while (1) {
		cout << "-----------------------------------------------------------------------------------" << endl;
		cout << "|    ROOM ID    |          ROOM TYPE          |          PRICE FOR 1 DAY          |" << endl;
		cout << "-----------------------------------------------------------------------------------" << endl;
		Node<room>* r = rl.getHead();
		while (r) {
			r->getValue()->displayDetail();
			r = r->getNext();
		}
		cout << "-----------------------------------------------------------------------------------";
		int roomId;
		cout << "\nRoom id you want to edit: ";
		cin >> roomId;
		cin.ignore();
		Node<room>* temp = rl.getHead();
		bool check = false;
		while (temp) {
			if (temp->getValue()->getRoomId() == roomId) {
				string price;
				cout << "Enter new price (enter if you don't want to change) : "; 
				getline(cin, price);
				if(price != "") temp->getValue()->setPrice(stoi(price));
				cout << "Enter new roomtype (enter if you don't want to change) : ";
				string roomtype; 
				getline(cin, roomtype);
				if(roomtype != "")temp->getValue()->setRoomtype(roomtype);
				check = true;
				break;
			}
			if (check == true) break;
			temp = temp->getNext();
		}
		if (temp == nullptr) {
			cout << "Invalid room id!!! Please enter room id again." << endl;
			string x;
			getline(cin, x);
			system("cls");
		}
		else {
			cout << "Successfull!!" << endl;
			break;
		}
	}
}

void deleteRoom(List<room>& rl) {
	while (1) {
		cout << "-----------------------------------------------------------------------------------" << endl;
		cout << "|    ROOM ID    |          ROOM TYPE          |          PRICE FOR 1 DAY          |" << endl;
		cout << "-----------------------------------------------------------------------------------" << endl;
		Node<room>* r = rl.getHead();
		while (r) {
			r->getValue()->displayDetail();
			r = r->getNext();
		}
		cout << "----------------------------------------------------------------------------------" << endl;
		int roomid;
		cout << "Enter the room id your want to delete: ";
		cin >> roomid;
		cin.ignore();
		Node<room>* temp = rl.getHead();
		while (temp) {
			if (temp->getValue()->getRoomId() == roomid) {
				rl.pop(temp);
				cout << "Room has been deleted!" << endl;
				return;
			}
			temp = temp->getNext();
		}
		if (temp == nullptr) {
			cout << "Room with id " << roomid << " does not exist!" << endl;
		}
		string x;
		getline(cin, x);
		system("cls");
	}
}


int numberOfRoomBooked(List<booking>& bl, time_t checkInDate, time_t checkOutDate) {
	int count = 0;
	Node<booking>* temp = bl.getHead();
	cout << "-----------------------------------------------------------------------------------------------------------------" << endl;
	cout << "|    room id    |      Name of booker     |       Amount       |      check-in date      |    check-out date    |" << endl;
	cout << "-----------------------------------------------------------------------------------------------------------------" << endl;
	while (temp) {
		if (temp->getValue()->getCheckInDate() >= checkInDate && temp->getValue()->getCheckInDate() <= checkOutDate)
		{	
			temp->getValue()->display();
			count++;
		}
		temp = temp->getNext();
	}
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

int numberOfRoomAvailable(List<room>& rl, List<booking>& bl,time_t checkInDate, time_t checkOutDate) {
	int count = 0;

	cout << "-----------------------------------------------------------------------------------" << endl;
	cout << "|    ROOM ID    |          ROOM TYPE          |          PRICE FOR 1 DAY          |" << endl;
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
			tmp->getValue()->displayDetail();
			count++;
		}
		tmp = tmp->getNext();
	}

	cout << "-----------------------------------------------------------------------------------" << endl;

 	return count;
}

long long revenueByDay(List<booking>& bl, time_t checkInDate1, time_t checkInDate2) {
	long long sum = 0;
	Node<booking>* temp = bl.getHead();
	while (temp) {
		if (temp->getValue()->getCheckInDate() >= checkInDate1 && temp->getValue()->getCheckInDate() <= checkInDate2) {
			temp->getValue()->display();
			sum += temp->getValue()->getAmount();
		}
		temp = temp->getNext();
	}
	return sum;
}

