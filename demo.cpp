#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
typedef struct NuocUong {
	char tenSanPham[30];
	char maSP[30];
	int giaTien; 
} NU;
void nhapMon(NU *input);
void nhapMons(NU *input, int &n);
void nhapNhanVien(char tenNhanVien[], char maNV[], NU *input, int &n);
void inMenu(NU *output, int n);
void xapSepTheoGiaTien(NU *source, int n);
void inHoaDon(int cho_ngoi, NU *source, char tenNhanVien[]);
void order(NU *source, int n,char tenNhanVien[], int &cho_ngoi);
void danhsach(NU *menu, int n, char tenNhanVien[], int cho_ngoi);
int main(){
	NU *menu;
	int n;
	menu = (NU *)calloc(n,sizeof(NU));
	if(menu == NULL){
        printf("\nError");
        exit(0);
    }
	char tenNhanVien[30];
	char maNV[30];
	int doanhThu;
	int cho_ngoi;
	nhapNhanVien(tenNhanVien,maNV,menu,n);
	danhsach(menu,n,tenNhanVien,cho_ngoi);
	free(menu);
	return 0;
}
void danhsach(NU *menu, int n, char tenNhanVien[], int cho_ngoi){
	char luachon;
	do{
		printf("\n--------------------------MENU-----------------------\n");
		printf("1. Xem menu hom nay.\n");
		printf("2. Xắp xếp giá tiền (từ lớn đến bé).\n");
		printf("3. Order món.\n");
		printf("Thoat bang phim ESC.\n");
		printf("your choice: ");
		luachon = getch();
		switch(luachon){
			case 49:
			{
				inMenu(menu,n);
				break;
			}
			case 50:
			{
				xapSepTheoGiaTien(menu,n);
				inMenu(menu,n);
				break;
			}
			case 51:
			{
				order(menu,n,tenNhanVien,cho_ngoi);
				break;
			}
			default:
			{
				printf("\nLua chọn của bạn không có.");
			}
		}
	} while (luachon != 27);
}
void nhapNhanVien(char tenNhanVien[], char maNV[], NU *input, int &n){
	fflush(stdin);
	printf("ten cua nhan vien quan ly: ");
	gets(tenNhanVien);
	printf("Ma nhan vien: ");
	gets(maNV);
	printf("-----------------Menu Hom Nay------------------");
	nhapMons(input,n);
	fflush(stdin);
}
void nhapMon(NU *input){
	fflush(stdin);
	printf("ma san pham: ");
	gets(input->maSP);
	printf("ten san pham: ");
	gets(input->tenSanPham);
	printf("gia tien: ");
	scanf("%d", &input->giaTien);
	fflush(stdin);
}
void nhapMons(NU *input, int &n){
	printf("\nNhap so luong mon hom nay: ");
	scanf("%d", &n);
	input = (NU*)realloc(input, n*sizeof(NU));
	for(int i=0; i<n; i++){
		printf("\nsan pham %d:\n", i+1);
		nhapMon((input+i));
	}
}
void inMenu(NU *output, int n){
	printf("\n------------------------Thuc don------------------------\n");
    printf("STT||ID\t\t||Ten\t\t||Gia");
	for(int i = 0; i<n; i++){
		printf("\n00%d||%s\t\t||%s\t\t||%d", i+1,(output+i)->maSP,(output+i)->tenSanPham,(output+i)->giaTien);
	}
}	
void xapSepTheoGiaTien(NU *source, int n){
	NU temp;
	for(int i = 0; i<n-1; i++){
		for(int j = i+1; j<n; j++){
			if((source+i)->giaTien > (source+j)->giaTien){
				temp = *(source+i);
				*(source+i) = *(source+j);
				*(source+j) = temp;
			}
		}
	}
}
void order(NU *source, int n,char tenNhanVien[], int &cho_ngoi){
	char id[30];
	printf("\nBạn chọn muốn gì (nhập mã) ?");
	gets(id);
	for(int i = 0; i<n; i++){
		if(strcmp(id,source->maSP) == 0){
			printf("\nVi trí ngồi của bạn.");
			scanf("%d", &cho_ngoi);
			inHoaDon(cho_ngoi, source, tenNhanVien);
	} else {
		printf("\nMón bạn order không có.");
		}
	}
}
void inHoaDon(int cho_ngoi, NU *source, char tenNhanVien[]){
	printf("\n--------------BILL-------------");
	printf("\n1)Chỗ ngồi:  %d", cho_ngoi);
	printf("\n2)Gía tiền: %d", source->giaTien);
	printf("\n3)nhân viên phụ trách: %s", tenNhanVien);
	printf("\n-------------------------------");
}