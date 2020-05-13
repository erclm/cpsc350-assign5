#include <iostream>
using namespace std;

class Student
{
public:
  int id;
  string name;
  string level;
  string major;
  double gpa;
  int adv;

	Student(string name, string level, string major, int adv, double gpa);
	Student(string name, string level, string major, int adv, double gpa, int id);
	Student(int id);
	Student();
	~Student();
	void setAdv(int i);

	friend ostream& operator<<(ostream& os, const Student& s);
  friend bool operator== (const Student &c1, const Student &c2);
    friend bool operator!= (const Student &c1, const Student &c2);
    friend bool operator< (const Student &c1, const Student &c2);
    friend bool operator> (const Student &c1, const Student &c2);
    friend bool operator<= (const Student &c1, const Student &c2);
    friend bool operator>= (const Student &c1, const Student &c2);
};
