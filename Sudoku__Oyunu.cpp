#include <iostream>

using namespace std;

void yazdir(char tahta[9][9]);
bool kontrol(char tahta[9][9]);
bool ekleme(int x, int y, int sayi, char sozde_tahta[9][9]);
bool son_ekleme(char tahta[9][9] , char sozde_tahta[9][9],bool sonuc_sutun, bool sonuc_satir , bool sonuc_blok);
void giris(int & x,int & y,int & sayi);
bool Blok_Kontrol(char sozde_tahta[9][9] , int x , int y);

// iki adet tahta yapýmýz var . sözde_tahta yapýsý sayesinde tahtaya ekleme yapýlýr ve bu ekleme 
// doðru mu diye kontrol edilir. Eðer doðruysa sözde_tahta dizisi tahta dizisine kopyalanarak ekleme 
// gerçekleþtirilir. Doðru deðilse kopyalama iþlemi gerçekleþtirilmez ve ekleme yapýlmaz.


void yazdir(char tahta[9][9]){
	for (int i = 0; i < 9; i++) {
			if(i%3 == 0 && i != 0){
				cout<<"-------------------"<<endl;
			}
        for (int j = 0; j < 9; j++) {
        	if(j%3 == 0 && j != 0){
				cout<<"|";
			}
            cout << tahta[i][j] << " ";   
        }
        cout << endl;
	}
}


bool sutun_kontrol(char sozde_tahta[9][9]){ // sütun kontrolü saðlanýr
	
	int syc=0;
	int i,j,k;
	
	for(k=0;k<9;k++){
		for(i=0;i<8;i++){
			for(j=i+1;j<9;j++){
				
				if(sozde_tahta[i][k] != '.' &&
					sozde_tahta[i][k] == sozde_tahta[j][k]){
					
					return false;	//çakýþma oldu
				}
			}
		}
	}
	
	return true; // çakýþma olmadý
}


bool satir_kontrol(char sozde_tahta[9][9]){  // satýr kontolü saðlanýr
	
	int syc=0;
	int i,j,k;
	
	for(k=0;k<9;k++){
		for(i=0;i<8;i++){
			for(j=i+1;j<9;j++){
				
				if(sozde_tahta[k][i] != '.' &&
					sozde_tahta[k][i] == sozde_tahta[k][j]){
					
					return false;	//çakýþma oldu
				}
			}
		}
	}
	
	return true; // çakýþma olmadý
}


//3x3 lük bloklarda da 1-9 arasýndaki sayilardan ayný sayý olmasýný kontrol eder..
// baþlangýç sýnýr deðerlerine görre bloklar tespit edilir ve kontrolleri saðlanýr


bool Blok_Kontrol(char sozde_tahta[9][9] , int x , int y){    // 3x3 lük bloklarýn kontrolü
	
	int blok_satir_baslangici = (x/3) * 3;
	int blok_sutun_baslangici = (y/3) * 3;
	
	int sayi = sozde_tahta[x][y];
	
	for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
			int satir =blok_satir_baslangici + i ;
			int sutun =blok_sutun_baslangici + j ;
			
			if(satir == x && sutun == y)	continue; // eðer ayný konumsa atlar
			
			if(sozde_tahta[satir][sutun] == sayi){
				return false; // çakýþma var
			}
		}
	}
	return true;
}




// döngünün saðlanmasý için giris almayý fonksiyona verdim

void giris(int &x, int &y, int &sayi) {
    cout << "1-9 arasi satir, sutun ve sayi giriniz .. ";
    cin >> x >> y >> sayi;
    
    // Kullanýcý 1-9 girer, biz 0-8'e çevirmek için 1 çýkarýyoruz
    x -= 1;
    y -= 1;
}




// eklenmek istenen sayýnýn kontrol edilmek için sozde_tahta ya eklenmesi yapýlýr
//  ve kontrol edilmek üsere "kontrol" fonksiyonlarýna gönderilir

bool ekleme(int x,int y, int sayi,char sozde_tahta[9][9],char tahta[9][9] ){ 
	
	if(tahta[x][y] != '.' ){
		cout<<"sabit terim . Bu noktaya giris yapilamaz..";
		return false;
	}

	
	sozde_tahta[x][y] =sayi + '0';
	
	bool sonuc_sutun = sutun_kontrol(sozde_tahta);
	bool sonuc_satir = satir_kontrol(sozde_tahta);
	bool sonuc_blok = Blok_Kontrol(sozde_tahta,x,y);
	
	bool son_sonuc=son_ekleme(tahta,sozde_tahta,sonuc_sutun,sonuc_satir,sonuc_blok);
	
	
	return son_sonuc;
}


// sozde_tahtaya eklenen sayýnýn kontrolü ve doðruysa kopyalama iþlemi bu fonksiyonda yapýlýr

bool son_ekleme(char tahta[9][9] , char sozde_tahta[9][9],bool sonuc_sutun , bool sonuc_satir, bool sonuc_blok){
	
	if(sonuc_sutun == true && sonuc_satir == true && sonuc_blok== true){
		
		for(int i=0;i<9;i++){
			for(int j=0;j<9;j++){
				tahta[i][j]=sozde_tahta[i][j];
			}		               		
		}
		
		cout<<"Ekleme yapildi.."<<endl;
		return true;
	}
	else{
		return false;
	}
}


// oyunun bitme durumunun kontrolü bool ile saðlandý

bool oyun_Bitti_mi(char tahta[9][9]){
	for(int i =0 ; i < 9 ; i++ ){
		for(int j = 0 ; j < 9 ;j ++ ){
			if(tahta[i][j] == '.'){
				return false;
			}
		}
	}
	
	return true;
}



int main() {
	
	bool sonuc;
	char sozde_tahta[9][9];
	int x,y,sayi;
	
	  char tahta[9][9] = {
        {'5','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}
		};
		
		
	
	//kopyalama iþlemi -> tahta sozde_tahta ya kopyalanýr
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			sozde_tahta[i][j]=tahta[i][j];
		}	               		
	}
	
	
while (true) {
	
    yazdir(tahta);         
    giris(x, y, sayi);     
    bool basarili = ekleme(x, y, sayi, sozde_tahta, tahta); // Ekleme denemesi
    
    if (!basarili) {
        cout << "Gecersiz hamle. Lutfen tekrar deneyin.\n";
    }

    // Buraya istenirse "oyun bitti mi?" kontrolü de eklenebilir ( eklendi) ..
    bool oyun_bitti_mii = oyun_Bitti_mi(tahta);
   
   	if(oyun_bitti_mii){
   		cout<<"oyun bitti. Tebrikler";
		   break;	
	}
}

}
	


