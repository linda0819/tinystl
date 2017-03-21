//#define _SCL_SECURE_NO_WARNINGS
////#include "myvector.h"
////#include "myiterator.h"
//
//
//#include<stdio.h>
//#include<stack>
//#include "llhvector.h"
//#include<string>
//#include<queue>
//#include<iostream>
//#include<functional>
//using namespace std;
//template<class T>
//void print(llh_vector<T> &v)
//{
//	for (llh_vector<T>::iterator it = v.begin(); it < v.end(); it++)
//		cout << *it << " ";
//	cout << endl;
//}
//int main11()
//{
//	llh_vector<int> v1(10, 5);
//	llh_vector<int> v2;
//	llh_vector<int> v3(v1);
//	v1 = v2 = v3;
//	cout << v1;
//	v1.erase(v1.begin(), v1.end());
//	system("pause");
//	return 0;
//}
/*      list      
#include<stdio.h>
#include"llhlist.h"
#include<iostream>
#include<functional>
using namespace std;
int main()
{
	llh_list<int> l1(8,5);
	l1.insertAsLast(1);
	l1.insertAsLast(2);
	l1.insertAsFirst(20);
	l1.insertAsFirst(70);
	l1.insertAsLast(62);
	l1.sort();
	for (int i = 0; i < l1.size(); i++)
	{
		cout << l1[i] << "  ";
	}
	cout << endl;
	l1.reverse();
	for (int i = 0; i < l1.size(); i++)
	{
		cout << l1[i]<<"  ";
	}
	int cou = l1.uniquify();
	cout << cou << endl;
	cout << l1 << endl;

	llh_list<int> l1(8, 5);
	llh_list<int> l2(4, 3);
	cout << l1 << endl;
	cout << l2 << endl;
	l1.swap(l2);
	cout << l1 << endl;
	cout << l2 << endl;
	system("pause");
	return 0;
}

*/



//#include<stdio.h>
//#include "llhmap.h"
//#include<iostream>
//
//using namespace std;
//int main()
//{
//	llh_map<int, int> m1;
//	Pair<int, int> a,b;
//	a.set(5,6);
//	b.set(6,7);
//	m1.Insert(a);
//	m1.Insert(b);
//	m1.print();
//	//m1.Erase(5);
//	//if(NULL==m1.Find(5))
//	//	cout<<"delete success"<<endl;
//	//cout << m1.empty() << endl;
//	//m1.Clear();
//	//cout << m1.empty() << endl;
//	system("pause");
//	return 0;
//}

//
//
//#include<stdio.h>
//#include"llhhashset.h"
//#include<iostream>
//#include<functional>
//using namespace std;
//int main()
//{
//	llh_hashset<int> s1;
//	llh_hashset<int> s2;
//	s1.insert(7);
//	s1.insert(2);
//	s1.print();
//	s2 = s1;
//	s2.print();
//	/*s1.del(2);
//	s1.print();
//	bool flag = s1.find(3);
//	cout << flag << endl;*/
//	system("pause");
//	return 0;
//}

#include<stdio.h>
#include "llhdeque.h"
#include<iostream>
#include<functional>
using namespace std;
int main()
{
	llh_deque<int> l1;
	system("pause");
	return 0;
}