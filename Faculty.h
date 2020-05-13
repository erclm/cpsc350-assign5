#include "NaiveList.h"
#include <iostream>
using namespace std;
class Faculty
{
public:
  int id;
	string name;
	string level;
	string dept;
  NaiveList<int>* adv;

  Faculty();
	~Faculty();

  Faculty(string name, string level, string dept);
	Faculty(string name, string level, string dept, int id);
	Faculty(int id);

  void addAdv(int id);
	void delAdv(int id);

	friend ostream& operator<<(ostream& os, const Faculty& s);
  friend bool operator== (const Faculty &c1, const Faculty &c2);
    friend bool operator!= (const Faculty &c1, const Faculty &c2);
    friend bool operator< (const Faculty &c1, const Faculty &c2);
    friend bool operator> (const Faculty &c1, const Faculty &c2);
    friend bool operator<= (const Faculty &c1, const Faculty &c2);
    friend bool operator>= (const Faculty &c1, const Faculty &c2);
};
