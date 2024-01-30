
#include <iostream>
#include <vector>
#include <ctime>
#pragma warning(disable : 4996)

using namespace std;

enum HesapTuru
{
    GENEL,
    OZEL
};

int kriptoDeger{1};

class Hesap
{
public:
    int hesapNo;
    HesapTuru hesapTuru;
    double bakiye;
    time_t sonGuncelleme;

    Hesap(int no, HesapTuru tur) : hesapNo(no), hesapTuru(tur), bakiye(0), sonGuncelleme(time(0)) {}

    void kriptoParaArttir(double gecenSure)
    {
        time_t simdikiZaman = time(0);
        static int toplamSure = gecenSure;
        // hesap türü genelse yeni bakiye hespalanıyor
        if (hesapTuru == GENEL)
        {
            bakiye += bakiye * gecenSure / 100;
            // 15 günden fazla geçtiyse bakiye düşüyor
            if (toplamSure >= 15)
            {
                bakiye *= 0.95;
            }
        }
        else
        {
            // Rastgele seçilmiş 3 günde %10 düşüş yapılıyor
            if (rand() % 30 < 3)
            {

                bakiye *= 0.9;
            }
            else
            {
                // Günlük artış sağlanıyor
                if (bakiye > 0)
                {
                    bakiye += bakiye * gecenSure / 100;
                }
            }
        }

        sonGuncelleme = simdikiZaman; // Güncellemeyi kaydet
    }

    void al(double girilenTutar)
    {
        double miktar = girilenTutar / kriptoDeger;
        bakiye += miktar;
    }

    void sat(double miktar)
    {
        // bakiye satılcak miktarı karşılıyorsa para çekiliyor
        if (bakiye >= miktar)
        {
            bakiye -= miktar;
        }
        // bakiye miktarı karşılamıyorsa uyarı veriliyor
        else
        {
            cout << "Yetersiz kripto para miktarı!" << endl;
        }
    }

    void bakiyeGoster() const
    {

        cout << "Hesap No: " << hesapNo << "  Kripto Para Miktarı: " << bakiye << " Hesap Türü: " << (hesapTuru == GENEL ? "Genel" : "Özel") << "\n\n";
    }
    void kar()
    {
    }
};

void baslangictarih()
{
    time_t t = time(0);
    tm now = {};

    if (localtime_s(&now, &t) == 0)
    {
        cout << "\nHesap Oluşturma Tarihi (gün/ay/yıl):";
        cout << now.tm_year + 1900 << "/";
        cout << now.tm_mon + 1 << "/";
        cout << now.tm_mday << endl;
    }
}

void simdikitarih(int gunSayisi)
{
    time_t t = time(0);
    tm now = {};

    // Girilen gün kadar tarih arttırılıp,tutuluyor ve kripto bakiyesi arttırılıyor.
    if (localtime_s(&now, &t) == 0)
    {
        static int yıl = now.tm_year + 1900;
        static int ay = now.tm_mon + 1;
        static int gün = now.tm_mday;
        gün += gunSayisi;

        // Gün sayısı 31'den fazlaysa gerekli ay ve gerekirse yıl miktarı arttırılıyor
        if (gün > 31)
        {
            int fazlalıkay = gün / 31;
            gün = gün % 31;
            ay += fazlalıkay;

            int fazlalıkyıl = ay / 12;
            ay = ay % 12;

            yıl += fazlalıkyıl;
        }
        cout << "\nŞu an ki zaman (gün/ay/yıl):";
        cout << yıl << "/";
        cout << ay << "/";
        cout << gün << endl
             << endl;
    }
}

int main()
{
    setlocale(LC_ALL, "Turkish");
    vector<Hesap> hesaplar;

    int secim;
    // kullanıcı karşısına çıkarılacak işlemler kullanıcı çıkana kadar döngüye sokuluyor
    do
    {
        cout << "1. Genel Hesap Aç\n2. Özel Hesap Aç\n3. Para Ekle\n4. Para Çek\n5. Sistem Tarihini Göster veya İleri al\n6. Listele\n7. Çıkış\n\nSeçim: ";
        cin >> secim;
        cout << "\n\n";

        switch (secim)
        {
            // 1 seçilirse genel hesap açılıyor
        case 1:
        {
            int hesapNo;
            double miktar;
            cout << "Hesap No: ";
            cin >> hesapNo;
            cout << "Miktar: ";
            cin >> miktar;
            Hesap yeniHesap(hesapNo, GENEL);
            yeniHesap.al(miktar);
            hesaplar.push_back(yeniHesap);
            yeniHesap.bakiyeGoster();
            cout << "\n\n";
            break;
        }
            // 2 seçilirse özel hesap açılıyor
        case 2:
        {
            int hesapNo;
            double miktar;
            cout << "Hesap No: ";
            cin >> hesapNo;
            cout << "Miktar: ";
            cin >> miktar;

            Hesap yeniHesap(hesapNo, OZEL);
            yeniHesap.al(miktar);
            hesaplar.push_back(yeniHesap);

            yeniHesap.bakiyeGoster();
            cout << "\n\n";
            break;
        }
            // 3 seçilirse para ekleme işlemi yapılıyor
        case 3:
        {
            int hesapNo;
            double miktar;
            cout << "Hesap No: ";
            cin >> hesapNo;
            cout << "Miktar: ";
            cin >> miktar;

            // Her hesap kontrol edilip hesapNo uyuşan hesapta işlem yapılıyor
            for (auto &hesap : hesaplar)
            {
                if (hesap.hesapNo == hesapNo)
                {
                    hesap.al(miktar);
                    hesap.bakiyeGoster();
                    break;
                }
            }
            break;
        }
            // 4 seçilirse satma işlemi yapılıyor
        case 4:
        {
            int hesapNo;
            double miktar;
            cout << "Hesap No: ";
            cin >> hesapNo;
            cout << "Miktar: ";
            cin >> miktar;

            // Her hesap kontrol edilip hesapNo uyuşan hesapta işlem yapılıyor
            for (auto &hesap : hesaplar)
            {
                if (hesap.hesapNo == hesapNo)
                {
                    hesap.sat(miktar);
                    hesap.bakiyeGoster();
                    break;
                }
            }
            break;
        }
            // 5 seçilirse kullanıcı tarihi değiştirebiliyor.
        case 5:
        {
            baslangictarih();
            simdikitarih(0);
            int gunSayisi;
            cout << "\nKac gun ileri gitmek istiyorsunuz?: ";
            cin >> gunSayisi;
            simdikitarih(gunSayisi);

            // hesaplar için bakiyeler düzenleniyor
            for (auto &hesap : hesaplar)
            {

                hesap.kriptoParaArttir(gunSayisi);
            }
            break;
        }
            // 6 seçilirse hesaplar listeleniyor.
        case 6:
        {
            // Eğer hesaplar vektörü boş ise hata veriyor.
            if (hesaplar.empty())
            {
                cout << "Hesap bulunamadı. Lütfen önce bir hesap oluşturun!\n\n";
            }

            // bütün hesaplara erişilip bakiye göster fonksiyonu çağırılıyor
            else
            {
                for (const auto &hesap : hesaplar)
                {
                    hesap.bakiyeGoster();
                }
            }
            break;
        }
            // 7 seçilirse programdan çıkış gerçekleşiyor
        case 7:
        {
            cout << "Çıkış yapılıyor..." << endl;
            break;
        }
        default:
        {
            cout << "Geçersiz seçim!\n\n";
            break;
        }
        }

    } while (secim != 7);

    return 0;
}
