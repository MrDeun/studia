/* po uruchomieniu roota w oknie dialogowym mozemy uruchomić makropoleceniem
 .x sciezka_domacro/nazwamakra

wyjscie z programu
.q
*/

#include <cmath>
#include <fstream>
#include <iostream>

using namespace std;

void przyklad_rysowanie() {
  int n = 1000, i;
  float x1[1000];
  ifstream d;
  // tak pod linuxem
  // d.open("dane.txt");
  // pod windows pelna sciezka z podwojnymi slashami

  //     d.open("C:\\Users\\dorota.sobczynska\\Desktop\\dla_doktorantow\\dane\\test.txt");
  d.open("numbers.txt");
  for (i = 0; i < 1000; i = i + 1) {
    d >> x1[i];
    cout << x1[i] << endl;
  }
  d.close();
  // deklarowanie histogramu "jednowymiarowego"  .... liczba klas, przedział
  TH1F *hi1 = new TH1F("hi1", "nazwa histogramu", 10, 0.0, 1.0);
  // wypelnianie histogramu jednowymiarowego
  for (i = 0; i < 1000; i = i + 1) {
    hi1->Fill(x1[i]);
  }

  /*
  // deklarowanie histogramu "dwuwymiarowego"  .... liczba klas, przedział
 najpierw po zmiennej x, potem po zmiennej y TH2F *imd2 = new
 TH2F("imd2","jestem histogramem-2wym ",40,-5.,400.,20,-5,400.);

     // wypelnianie histogramu dwuwymiarowego
  for(i=0;i<3000;i=i+2)
              {
                hi2->Fill(x1[i],x1[i+1]);
              }
  */

  // kolory i style histogramu (mozna bez
  hi1->SetFillColor(2);
  hi1->SetFillStyle(3002);
  // rysowanie histogramu

  hi1->Draw();

  // definicja funkcji do modelowania
  //  f4 wlasna funkcja, w nawisach kwadratowych nieznane parametry, ktorych
  //  szuka program po uruchomieniu fit jesli modelowanie jedna funkcja to jak w
  //  przypadku f4
  // liczby na koncu to zakres dla ktorej funkcje definiujemy

  // TF1 *f4 = new TF1("f4","[0]*x*x+[1])",-15,400);
  //
  //  a tak dopasowujemy funkcje do histogramu

  //TF1 *f4 = new TF1("f4", "[0]", 6, 12.5);
  hi1->Fit("pol0");
  /*
      //f1,f2,f3 jesli modelowanie kawalkami ( ostatnie liczby to zakresy )
 TF1* f1 = new TF1("f1","expo",0,19);
 hi1->Fit(f1,"R+");
 TF1* f2 = new TF1("f2","expo",19,43.5);
 hi1->Fit(f2,"R+");
 TF1* f3 = new TF1("f3","pol9",43.5,400);
 hi1->Fit(f3,"R+");
  */
}
