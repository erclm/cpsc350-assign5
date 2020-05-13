#include "Data.h"
using namespace std;

Data::Data()
{
	masterStudent = new BST<Student>();
	masterFaculty = new BST<Faculty>();
	studStack = new GenStack<BST<Student>>(5);
	facStack = new GenStack<BST<Faculty>>(5);
	getFiles();
	studStack->push(*masterStudent);
	facStack->push(*masterFaculty);

}

Data::~Data()
{}

void Data::printS()
{
	masterStudent->printTree();
}

void Data::printF()
{
	masterFaculty->printTree();
}

void Data::findS()
{
	string uinput;
	cout << "Enter Student ID: " <<endl;
	cin >> uinput;
	Student t(stoi(uinput)); // new student
	if (masterStudent->contains(t)){ // checks if that student's id number is in the BST
		cout << masterStudent->search(t) <<endl; //prints all the info about the student if existing id was entered
	}
	else{
    cout << "Student not found." << endl;
  }
}

void Data::findF()
{
	string uinput;
	cout << "Enter Faculty ID: " <<endl;
	cin >> uinput;
	Faculty t(stoi(uinput)); // new faculty
	if (masterFaculty->contains(t)){ // checks if that faculty's id number is in the BST
		cout << masterFaculty->search(t) <<endl; //prints all the info about the faculty if existing id was entered
	}
	else{
    cout << "Faculty not found." << endl;
  }
}

void Data::getAdvisor()
{
	string uinput;
	cout << "Enter Student ID: " <<endl;
	cin >> uinput;
	Student t(stoi(uinput)); //created student
	if (masterStudent->contains(t)){ // compare if student exist
		Student s = masterStudent->search(t); // makes a student w all the info
		cout << masterFaculty->search(s.adv) << endl; //search faculty BST for faculty
	}
	else{
    cout << "Student not found." << endl;
  }
}

void Data::getStuds()
{
	string uinput;
	cout << "Enter Faculty ID: " <<endl;
	cin >> uinput;
	Faculty t(stoi(uinput));  //same concept as above
	if (masterFaculty->contains(t)){
		Faculty f = masterFaculty->search(t);
		for (int i=0; i<f.adv->size; i++){
      int x = f.adv->removeBack();
			cout << masterStudent->search(Student(x)) <<endl;
	    f.adv->insertFront(x);
	   }
	}
	else{
    cout << "Faculty not found." << endl;
  }
}

void Data::addStud()
{
	string name, level, major, adv, gpa;
	cout << "Enter Name: " << endl;
	cin >> name;
	cin.clear();
	cout << "Enter Level: " << endl;
	cin >> level;
	cin.clear();
	cout << "Enter Major: " << endl;
	cin >> major;
	cin.clear();
	cout << "Enter Advisor ID: " << endl;
	cin >> adv;
	cin.clear();
	cout << adv;
  cout << "Enter GPA: " << endl;
  cin >> gpa;
  cin.clear();
	if (masterFaculty->contains(stoi(adv))){ // if the advisor id that the user gave exists, continue
		Student s = Student(name, level, major, stoi(adv), stod(gpa));
		masterStudent->insert(s);
		masterFaculty->search(stoi(adv)).addAdv(s.id);
		studStack->push(*masterStudent);
		facStack->push(*masterFaculty);
	}
	else{
    cout << "Advisor Not Found" << endl;
  }
}

void Data::delStud()
{
	string uinput;
	int adv;
	cout << "Enter Student ID: " <<endl;
	cin >> uinput;
	Student t(stoi(uinput));
	if (masterStudent->contains(t)){
		adv = masterStudent->search(t).adv;
		masterStudent->deleteRec(t);
		masterFaculty->search(adv).delAdv(stoi(uinput));
		studStack->push(*masterStudent);
		facStack->push(*masterFaculty);
	}
	else{
    cout << "Student not found." << endl;
  }
}

void Data::addFac()
{
	string name, level, dept;
	cout << "Enter Name: " << endl;
	cin >> name;
	cout << "Enter Level: " << endl;
	cin >> level;
	cout << "Enter Department: " << endl;
	cin >> dept;
	Faculty f = Faculty(name, level, dept);
	masterFaculty->insert(f);
	studStack->push(*masterStudent);
	facStack->push(*masterFaculty);
}

void Data::delFac()
{
	string uinput,uinput2;
	int adv;
	cout << "Enter Faculty ID: " <<endl;
	cin >> uinput; //get id of faculty we are deleting
	cout << "Enter Faculty ID to transfer students: " <<endl;
	cin >> uinput2;

  //transfers all of these faculty's advisees to a new faculty (bc we are about to get rid of their advisor lol)
	Faculty t(stoi(uinput));

  //creates new faculty just containing the id
	Faculty tr(stoi(uinput2));
	if (masterFaculty->contains(tr) && masterFaculty->contains(t)){
    //if these exist in the faculty BST
		NaiveList<int>* old = masterFaculty->search(t).adv; // there's a list of the advisees of the faculty
    // but we need a new list bc we are changing their faculty person (this defines the old one)
		while(old->getSize()!=0){
			int id = old->removeFront(); //finds the old id
			Student s = Student(id);
			masterStudent->search(s).setAdv(stoi(uinput2)); //changes each of the student's advisor to the new faculty id
			masterFaculty->search(tr).adv->insertFront(id); //adds the stuents to their new advisors list
			// loops through for each student
		}
		masterFaculty->deleteRec(t);
		studStack->push(*masterStudent);
		facStack->push(*masterFaculty);
	}
	else{
    cout << "Faculty not found." << endl;
  }
}

void Data::changeAdv()
{
	string st, adv;
	cout << "Enter Student ID:" << endl;
	cin >> st;
	cout << "Enter Advisor ID: " << endl;
	cin >> adv;

	Student s(stoi(st));
	Faculty t(stoi(adv));

	if (masterStudent->contains(s) && masterFaculty->contains(t)){ // makes sure the user's student and faculty
		// ids exist in their relative BSTS
		masterStudent->search(s).setAdv(stoi(adv)); // finds the student and gives them a new advisor
		masterFaculty->search(t).addAdv(stoi(st)); // vice versa
		masterFaculty->search(masterStudent->search(s).adv).delAdv(stoi(st)); // deletes this student from its former advisor's list
		studStack->push(*masterStudent);
		facStack->push(*masterFaculty);
	}
	else{
    cout << "ID doesn't exist" << endl;
  }
}

void Data::remAdv()
{
	string st, adv;
	cout << "Enter Advisor ID:" << endl;
	cin >> adv;
	cout << "Enter Student ID: " << endl;
	cin >> st;

	Student s(stoi(st));
	Faculty t(stoi(adv));

	if (masterStudent->contains(s) && masterFaculty->contains(t)){
  // makes sure the user's student and faculty
		// ids exist in their relative BSTS
		masterStudent->search(s).setAdv(0); //delets their current advisor
		masterFaculty->search(masterStudent->search(s).adv).delAdv(stoi(st)); // removes the students id fromt he advisees list
		studStack->push(*masterStudent);
		facStack->push(*masterFaculty);
	}
	else{
    cout << "ID doesn't exist" << endl;
  }
}

void Data::rollback()
{
	string count;
	cout << "How many commands would you like to undo?" << endl;
	cin.clear();
	cin.ignore(10000, '\n');
	getline(cin,count);
	cout << "rollbacking "<<stoi(count) << endl;

	for (int i = 0; i < (stoi(count)); ++i){
		//cout << "pen1" << endl;
		BST<Faculty> facCopy = facStack->pop();
		masterFaculty = &facCopy;
		BST<Student> studCopy = studStack->pop();
		masterStudent = &studCopy;
		//cout << "pen2" << endl;
	}
	BST<Faculty> facCopy = facStack->pop();
	masterFaculty = &facCopy;
	BST<Student> studCopy = studStack->pop();
	masterStudent = &studCopy;

}


void Data::getFiles()
{
	string line;
	ifstream s,f;
	//opens txts with given names
	s.open ("studentTable", ifstream::in);
	f.open ("facultyTable", ifstream::in);
	if (s){
		//for each line parse student object values, # stands for null BST pointers
		while(getline(s, line)){
			int count =0;
			string id = "";
			string name= "";
			string level= "";
			string major= "";
			string gpa= "";
			string adv= "";
			if (line!="#"){
				// '/' is delimeter for field values
				for (int i = 0; i < line.size(); i++){
					if (line[i] =='/'){
						count++;
						continue;
					}
					else if (line[i] !='#' && count ==0){
						 name+=line[i];
					}
					else if (line[i] !='#' && count ==1){
						 level+=line[i];
					}
					else if (line[i] !='#' && count ==2){
						 major+=line[i];
					}
					else if (line[i] !='#' && count ==3){
						 adv+=line[i];
					}
					else if (line[i] !='#' && count ==4){
						 gpa+=line[i];
					}
					else if (line[i] !='#' && count ==5){
						 id+=line[i];
					}
				}
				//creates and inserts students to BST
				masterStudent->insert(Student(name, level, major, stoi(adv),stod(gpa), stoi(id)));
			}
		}
	}
	if (f){
		//for each line parse faculty object values, # stands for null BST pointers
		while(getline(f, line)){
			int count =0;
			string id = "";
			string name= "";
			string level= "";
			string dept= "";
			string adv = "";
			if (line!="#"){
				int i;
				for (i = 0; i < line.size(); i++){
					if (line[i] =='/'){
						count++;
						continue;
					}
					else if (line[i]== '-'){
						break;
					}
					else if (line[i] !='#' && count ==0){
						 name+=line[i];
					}
					else if (line[i] !='#' && count ==1){
						 level+=line[i];
					}
					else if (line[i] !='#' && count ==2){
						 dept+=line[i];
					}
					else if (line[i] !='#' && count ==3){
						 id+=line[i];
					}
				}

				Faculty f = Faculty(name, level, dept, stoi(id));
				for (i++; i < line.size(); ++i){
					if (line[i] == '|'){
						f.addAdv(stoi(adv));
						adv = "";
					}
					else{
            adv += line[i];
          }
				}
				masterFaculty->insert(f);
			}
		}
	}
}


void Data::save()
{
	//ouputs BSTs to given txt files
	ofstream s,f;
	s.open("studentTable",std::ofstream::out);
	f.open("facultyTable",std::ofstream::out);
	masterStudent->treeToFile(s);
	masterFaculty->treeToFile(f);
}


void Data::run(string s)
{
	//takes user input for deciding which method to run
	if (s == "1")
		printS();
	else if (s =="2")
		printF();
	else if (s =="3")
		findS();
	else if (s =="4")
		findF();
	else if (s =="5")
		getAdvisor();
	else if (s =="6")
		getStuds();
	else if (s =="7")
		addStud();
	else if (s =="8")
		delStud();
	else if (s =="9")
		addFac();
	else if (s =="10")
		delFac();
	else if (s =="11")
		changeAdv();
	else if (s =="12")
		remAdv();
	else if (s =="13")
		rollback();
	else if (s=="14"){
    std::cout << "exiting" << '\n';
    return;
  }
	else{
		cout << "Try Again!" << endl;
		cout << endl;
		return;
	}
}
