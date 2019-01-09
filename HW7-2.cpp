#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
 
int act[100][100];
using namespace std;
 
void calculate_ee(int *ee, int events) {
	for (int i = 0; i < events; i++) {
		for (int j = 0; j < events; j++) {
			if (act[i][j] != 0 && ee[i] + act[i][j] > ee[j]) {
				ee[j] = ee[i] + act[i][j];
			}
		}
	}
}
void calculate_le(int *le, int *ee, int events) {
	int len = events - 1;
	le[len] = ee[len];
	for (int i = len; i >= 0; --i) {
		for (int j = len; j >= 0; --j) {
			if (act[i][j] != 0 && le[j] - act[i][j] < le[i]) {
				le[i] = le[j] - act[i][j];
			}
		}
	}
}
void calculate_e_and_l(int *e, int *l, int *ee, int *le, int events) {
	int k = 0;
	for (int i = 0; i < events; i++) {
		for (int j = 0; j < events; j++) {
			if (act[i][j] != 0) {
				e[k] = ee[i];
				l[k++] = le[j] - act[i][j];
			}
		}
	}
}

int main() {
	
	int bgg;
	int events = 0, activities = 0;
	int n = 0;
	int start,end,key= 0;
	string critical;
	
	cin >> n;
	events = activities = n;
	
	int *ee = new int[events], *le = new int[events];
	int *e = new int[activities], *l = new int[activities];
	
	for(int i=0;i<n;i++)
	{
		cin>>bgg>>start>>end>>key;
		act[start][end]=key;
	}

	for (int i = 0; i < events; ++i) {
		ee[i] = 0;
		le[i] = 99999;
	}
	
	calculate_ee(ee, events);
	calculate_le(le, ee, events);
	calculate_e_and_l(e, l, ee, le, events);
	
	cout << "act.    e    l    slack    critical"<< endl;
	for (int i = 0; i < activities; i++) 
	{
		critical = "No";
		if(l[i]-e[i] == 0)critical = "Yes";
		cout <<"  "<<i+1<<"     "<<e[i]<<"     "<<l[i]<<"     "<<l[i]-e[i]<<"     "<<critical<< endl;
	}
	return 0;
}
