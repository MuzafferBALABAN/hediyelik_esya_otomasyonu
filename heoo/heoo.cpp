#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <locale.h>
//AD SOYAD:MUZAFFER BALABAN NO:2412721029 KONU:HEDİYELİK EŞYA OTOMASYONU
using namespace std;

struct HediyelikEya {
    char ad[80];
    char kategori[50];
    float fiyat;
    int miktar;
};

void urunEkle();
void urunListele();
void urunGuncelle();
void urunSil();
void urunAra();

int main() {
    setlocale(LC_ALL, "Turkish");
    char secim;
    do {
        system("cls");
        cout << "|------- Hediyelik Eşya Otomasyonu -------|" << endl;
        cout << "| 1 - Ürün Ekle                          |" << endl;
        cout << "| 2 - Ürün Listele                       |" << endl;
        cout << "| 3 - Ürün Güncelle                      |" << endl;
        cout << "| 4 - Ürün Sil                           |" << endl;
        cout << "| 5 - Ürün Ara                           |" << endl;
        cout << "| Çıkmak için 'q' tuşuna basın.          |" << endl;
        cout << "|----------------------------------------|" << endl;
        cin >> secim;

        switch (secim) {
        case '1': urunEkle(); break;
        case '2': urunListele(); break;
        case '3': urunGuncelle(); break;
        case '4': urunSil(); break;
        case '5': urunAra(); break;
        case 'q': break;
        default: cout << "Geçersiz seçenek!" << endl;
        }

        cout << "Ana menüye dönmek için 'a', çıkmak için 'q' basın: ";
        cin >> secim;
    } while (secim != 'q');

    return 0;
}

void urunEkle() {
    HediyelikEya urun;
    ofstream yaz("urunler.dat", ios::binary | ios::app);

    char secim;
    do {
        cout << "Ürün Adı: ";
        cin >> urun.ad;
        cout << "Ürün Kategorisi: ";
        cin >> urun.kategori;
        cout << "Ürün Fiyatı: ";
        cin >> urun.fiyat;
        cout << "Ürün Miktarı: ";
        cin >> urun.miktar;

        yaz.write((char*)&urun, sizeof(urun));
        cout << "Başka ürün eklemek ister misiniz? (E/H): ";
        cin >> secim;
    } while (secim == 'e' || secim == 'E');

    yaz.close();
}

void urunListele() {
    ifstream oku("urunler.dat", ios::binary);

    if (!oku) {
        cout << "Veritabanı bulunamadı!" << endl;
        return;
    }

    HediyelikEya urun;
    int i = 1;
    while (oku.read((char*)&urun, sizeof(urun))) {
        cout << i++ << ". Ürün Adı: " << urun.ad << ", Kategori: " << urun.kategori
            << ", Fiyat: " << urun.fiyat << " TL, Miktar: " << urun.miktar << endl;
    }

    oku.close();
}

void urunGuncelle() {
    ifstream oku("urunler.dat", ios::binary);
    ofstream gecici("gecici.dat", ios::binary);

    if (!oku) {
        cout << "Veritabanı bulunamadı!" << endl;
        return;
    }

    char urunAd[80];
    cout << "Güncellemek istediğiniz ürünün adını girin: ";
    cin >> urunAd;

    HediyelikEya urun;
    bool bulundu = false;

    while (oku.read((char*)&urun, sizeof(urun))) {
        if (strcmp(urun.ad, urunAd) == 0) {
            bulundu = true;
            cout << "Ürün Bulundu!" << endl;
            cout << "Yeni Fiyatı: ";
            cin >> urun.fiyat;
            cout << "Yeni Miktarı: ";
            cin >> urun.miktar;
            cout << "Ürün güncellendi!" << endl;
        }
        gecici.write((char*)&urun, sizeof(urun));
    }

    oku.close();
    gecici.close();

    if (bulundu) {
        remove("urunler.dat");
        rename("gecici.dat", "urunler.dat");
    }
    else {
        remove("gecici.dat");
        cout << "Ürün bulunamadı!" << endl;
    }
}

void urunSil() {
    ifstream oku("urunler.dat", ios::binary);
    ofstream gecici("gecici.dat", ios::binary);

    if (!oku) {
        cout << "Veritabanı bulunamadı!" << endl;
        return;
    }

    char urunAd[80];
    cout << "Silmek istediğiniz ürünün adını girin: ";
    cin >> urunAd;

    HediyelikEya urun;
    bool bulundu = false;

    while (oku.read((char*)&urun, sizeof(urun))) {
        if (strcmp(urun.ad, urunAd) != 0) {
            gecici.write((char*)&urun, sizeof(urun));
        }
        else {
            bulundu = true;
            cout << "Ürün Silindi!" << endl;
        }
    }

    oku.close();
    gecici.close();

    if (bulundu) {
        remove("urunler.dat");
        rename("gecici.dat", "urunler.dat");
    }
    else {
        remove("gecici.dat");
        cout << "Ürün bulunamadı!" << endl;
    }
}

void urunAra() {
    ifstream oku("urunler.dat", ios::binary);

    if (!oku) {
        cout << "Veritabanı bulunamadı!" << endl;
        return;
    }

    char urunAd[80];
    cout << "Aramak istediğiniz ürün adını girin: ";
    cin >> urunAd;

    HediyelikEya urun;
    bool bulundu = false;

    while (oku.read((char*)&urun, sizeof(urun))) {
        if (strcmp(urun.ad, urunAd) == 0) {
            bulundu = true;
            cout << "Ürün Bulundu!" << endl;
            cout << "Ürün Adı: " << urun.ad << ", Kategori: " << urun.kategori
                << ", Fiyat: " << urun.fiyat << " TL, Miktar: " << urun.miktar << endl;
        }
    }

    if (!bulundu) {
        cout << "Ürün bulunamadı!" << endl;
    }

    oku.close();
}
