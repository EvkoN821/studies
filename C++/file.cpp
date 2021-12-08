#include <fstream>;
#include <iostream>;
using namespace std;

int main(){
	ofstream f("f.txt");
	int n,x;
	cin>>n;
	for (int i=0; i<n; i++){
		cin>>x;
		if(i!=n-1) f<<x<<endl;
		else f<<x;
	}
	f.close();
	ifstream h("f.txt");
	ofstream g("g.txt");
	while (!h.eof()){
		h>>x;
		if(x%2==0) g<<x<<endl;
	}
	h.close(); g.close();
	h.open("g.txt");
	while(!h.eof()){
		h>>x;
		if (!h.eof()) cout<<x;
	}
	h.close();
}

/*
int main (){
	ofstream f("f.txt");
	int n,x;
	cin>>n;
	for (int i=0; i<n; i++){
		cin>>x;
		if(i!=n-1) f<<x<<endl;
		else f<<x;
	}
	f.close();
	ifstream h("f.txt");
	while (!h.eof()){
		h>>x;
		//заполнение дерева, списка
	}
	h.close()
}
*/