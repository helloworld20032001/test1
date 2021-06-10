#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#define Maxdausach 10000
using namespace std;
// Cau truc danh muc sach: Danh sach lien ket don.
struct Sach{
	char Masach[20];
	int Trangthai; // 0: cho muon dc; 1: da co nguoi muon; 2: sach da thanh ly
	char Vitri[30];
	Sach(){
		Vitri[0]='\0';
	}
};
struct nodeSach{
	Sach sach;
	nodeSach *next;
}; 
typedef struct nodeSach *pDMS;
pDMS First = NULL;
Sach tmpD;
pDMS Dms;


pDMS newnodesach(void){
	pDMS p;
	p = (pDMS)malloc(sizeof(struct Sach));
	return p;
}

pDMS crNodesach(Sach &info){
	pDMS p = new nodeSach;
	p->sach=info;
	p->next=NULL;
	return p;
}

void InsertDms_first(pDMS &first, struct Sach newsach){
	pDMS p;
	p=newnodesach();
	p->sach=newsach;
	p->next=first;
	first=p;
}
void InsertDms_after(pDMS q, struct Sach newsach){
	pDMS p;
	p=newnodesach();	
	p->sach=newsach;
	p->next=q->next;
	q->next=p;
}
void InsertDms_last(pDMS &first, struct Sach &newsach){
	if(First == NULL) InsertDms_first(First,newsach);
	pDMS last;
	for(last = First; last->next != NULL; last = last->next){
		InsertDms_after(last,newsach);
	}
	
}

// Cau truc dau sach: Danh sach tuyen tinh.
struct Dausach{
	char ISBN[15];
	char Tensach[25];
	unsigned int Sotrang;
	char Tacgia[25];
	unsigned int Namxb;
	char Theloai[30];
	nodeSach *dms=NULL;
	int soluong; // so luong sach moi dau sach
	Dausach(){
		ISBN[0]='\0';
		Tensach[0]='\0';
		Tacgia[0]='\0';
		Theloai[0]='\0';
		soluong = 0;
	}
		
};		

struct DS_Dausach{
	int n;
	Dausach *nodes[Maxdausach];	
	DS_Dausach(){
		n=0;
	}
	struct Dausach* Search_ISBN(char tmpISBN[15]){
		for(int i=0; i<n; i++){
			if(strcmp(nodes[i]->ISBN, tmpISBN) == 0){
				return nodes[i];
			}
		}
		return NULL;
	}
}; typedef struct DS_Dausach DSDS;



//=== Them dau sach
// insert last
void Insert(DSDS &dsds, struct Dausach *newnodes){
	  	dsds.nodes[dsds.n]=newnodes;
	  	dsds.n++;
		  /*int j;
		for(j = dsds.n-1; j >= l; j--)
			dsds.nodes[j+1] = dsds.nodes[j];
		dsds.nodes[l] = newnodes;
		dsds.n ++;*/
}

int Search_info(DSDS &dsds, struct Dausach *info){
	for(int i = 0; i<dsds.n; i++){
		if (strcmp(dsds.nodes[i]->ISBN, info->ISBN)==0){                                
			return i;
		}
	}
	return -1;
}

int isFull(DSDS &dsds){
	for(int i=0; i<dsds.n; i++){
		return dsds.n==Maxdausach;
	}
}

void DeleteDs(DSDS &dsds, int pos){
	int j;
	//if(i < 0 || i >= plist.n || plist.n==0) return 0;
	for(j = pos+1;  j< dsds.n ; j++)
		dsds.nodes[j-1] = dsds.nodes[j];
	dsds.n--;

}
void DeleteISBN(DSDS &dsds, char tmpISBN[15]){
	for(int i=0; i<dsds.n; i++){
		if(strcmp(dsds.nodes[i]->ISBN, tmpISBN) == 0){
			DeleteDs(dsds,i);
			break;
		}
	}
}

// Cau truc muon tra: Danh sach lien ket don.
struct DMY{
	int ngay;
	int thang;
	int nam;
};
struct Muontra{
	char Masach[20];
	DMY Ngaymuon[2];
	DMY Ngaytra[2];
	int Trangthai; // 0: dang muon; 1: da tra; 2: lam mat sach(da thanh ly)	
};
struct NodeMuontra{
	Muontra muontra;
	Muontra *next;
};
// Cau truc doc gia: Cay nhi phan tim kiem.
struct Docgia{
	int Mathe;
	char Ho[30];
	char Ten[20];
	int Phai; // Nam, Nu.
	int Trangthai; // 0: Khoa, 1: Hoat dong
};
struct NodeDocgia{
	Docgia docgia;
	NodeMuontra *dsmuon=NULL;
	NodeDocgia *left=NULL;
	NodeDocgia *right=NULL;
};
typedef NodeDocgia ptrDocgia;
	ptrDocgia *DS_Docgia=NULL;





// DOC & GHI FILE //

void ReadDs(ifstream &file, struct Dausach *p){
	file.getline(p->ISBN,sizeof(p->ISBN));
//	file>>p->ISBN;
	file.getline(p->Tensach, sizeof(p->Tensach));
	file>>p->Sotrang;
	file.ignore();
	file.getline(p->Tacgia, sizeof(p->Tacgia));
	file>>p->Namxb;	
	file.ignore();
	file.getline(p->Theloai, sizeof(p->Theloai));	
}

void WriteDs(ofstream &file, struct Dausach *p){
	file<<p->ISBN<<endl;
	file<<p->Tensach<<endl;
	file<<p->Sotrang<<endl;
	file<<p->Tacgia<<endl;
	file<<p->Namxb<<endl;
	file<<p->Theloai<<endl;
}

/*void ReadDms(ifstream &file, struct Danhmucsach *p, struct Dausach* q){
	file>>q->soluong;
	file>>p->Masach;
	file.ignore();
	file.getline(p->Trangthai, sizeof(p->Trangthai));
	file.getline(p->Vitri, sizeof(p->Vitri));
	
}*/

void SaveDs(DSDS &dsds){
	struct Dausach sach;
	ofstream fileDs;
	ofstream logs;
	ofstream fileDms;
	fileDs.open("list_dausach.txt", ios::out);
	fileDms.open("list_dms.txt", ios::out);
	logs.open("Logs.txt", ios::out);
	logs<<dsds.n;
	for(int i=0; i<dsds.n; i++){
		WriteDs(fileDs, dsds.nodes[i]);
		fileDms<<dsds.nodes[i]->soluong<<endl; 
		for(pDMS p = dsds.nodes[i]->dms; p != NULL; p=p->next){
				fileDms<<p->sach.Masach<<endl;
				fileDms<<p->sach.Trangthai<<endl;
				fileDms<<p->sach.Vitri<<endl;
		}
	}
	fileDs.close();
}

void LoadDs(DSDS &dsds){
	struct Dausach sach;
	int m;
	Sach *tmp;
	ifstream fileDs;
	ifstream fileDms;
	ifstream logs;
	fileDs.open("list_dausach.txt", ios::in);
	fileDms.open("list_dms", ios::in);
	logs.open("Logs.txt",ios::in);
	logs>>dsds.n;
	for(int i=0; i<dsds.n; i++){
		dsds.nodes[i] = new Dausach;
		ReadDs(fileDs, dsds.nodes[i]);
		fileDms>>m;
		sach.soluong=m;
		for(int i=0; i<m; i++){
			fileDms>>tmp->Masach;
			fileDms>>tmp->Trangthai;
			fileDms>>tmp->Vitri;
		}
	}
	fileDs.close();
}
















