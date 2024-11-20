#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <fstream>
//#include <vector>
#include "headers.h"

using namespace std;
// void mainer() {
//     cout << "Viberite deistvie:" << endl;
//     cout << "1)R?" << endl;
//     cout << "2)X?" << endl;
//     cout << "3)Y?" << endl;
//     cout << "4)Cvet?" << endl;
//     cout << "5)S cryga?" << endl;
//     cout << "6)ystanovka Coordinat" << endl;
//     cout << "7)ystanovka Radiusa" << endl;
//     cout << "8)ystanovka cveta" << endl;
//     cout << "9)Inform o krugax" << endl;
//     cout << "10)Vichitanie unarnoe" << endl;
//     cout << "11)Preobrazovanie v double" << endl;
//     cout << "12)Prefix" << endl;
//     cout << "13)Posfix" << endl;
//     cout << "14)Sohranenie v tekstovyi fail" << endl;
//     cout << "15)Zagruzka iz tekstovogo faila" << endl;
//     cout << "16)Sohranenie v binarnyi fail" << endl;
//     cout << "17)Zagruzka iz binarnogo faila" << endl;
//     cout << "18)Vyvod vsekh krugov" << endl;
//     cout << "19)Dobavit novyi krug s klaviatury v tekstovyi fail" << endl;
//     cout << "0)exit" << endl;
// }

void test1()
{
    cout << "sozdanie objektov v steke" << endl;
    Circle c(2, 4, 5.0, "blue");
    cout << endl;
    Oval o(1, 1, 3., 6., "orange");
    cout << endl;
    OutlineCircle oc(3, 4, 7., "white", "purple");
    cout << endl;
    c.print();
    cout << endl;
    o.print();
    cout << endl;
    oc.print();
    cout << endl << endl;
    cout << "prisvaivanie c objektov oval i outlinecircle v steke" << endl;
    c = o;
    c.print();
    cout << endl;
    c = oc;
    c.print();
    cout << endl << endl;
}

void test2()
{
    cout << endl << endl;
    cout << "sozdanie objektov v kuche" << endl;
    Circle* c = new Circle(2, 4, 5.0, "blue");
    cout << endl;
    Oval* o = new Oval(1, 1, 3., 6., "orange");
    cout << endl;
    OutlineCircle* oc = new OutlineCircle(3, 4, 7., "white", "purple");
    cout << endl;
    c->print();
    cout << endl;
    o->print();
    cout << endl;
    oc->print();
    cout << endl << endl;
    delete c;
    delete o;
    delete oc;
    cout << endl << endl;
    cout << "prisvaivanie c objektov oval i outlinecircle v kuche" << endl;
    c = new Oval(1, 1, 3., 6., "orange");
    c->print();
    cout << endl;
    delete c;
    c = new OutlineCircle(3, 4, 7., "white", "purple");
    c->print();
    cout << endl << endl;
    delete c;
}

int main() {
//    vector<Circle> circles;

 //   char* str = new char[15];
 //   strcpy(str, "blue");
    //test1();
    //test2();
    CircleList* cl = new CircleList;
    cl->add(new Circle(1, 3, 2.5, "black"), -1);
    cl->add(new Circle(2, 4, 1.3, "yellow"), -1);
    cl->add(new Oval(0, 0, 1.8, .5, "blue"), -1);
    //cl->del(2);
    int a = cl->search("yellow");
    (*cl)[a].print();
    //cl->print();
    delete cl;




 //   Circle b(3, 1, 2.0, "RED");
 //   Circle c = a + b;
    //circles.push_back(a);
    //circles.push_back(b);
    //circles.push_back(c);
    // int choice;
    // bool exit = false;

    // while (!exit) {
    //     mainer();
    //     cin >> choice;
    //     switch (choice) {
    //     case 1: {
    //         cout << "R=" << c.getRadius() << endl;
    //         break;
    //     }
    //     case 2: {
    //         cout << "X=" << c.getX() << endl;
    //         break;
    //     }
    //     case 3: {
    //         cout << "Y=" << c.getY() << endl;
    //         break;
    //     }
    //     case 4: {
    //         char clr[15];
    //         c.getColor(clr);
    //         cout << "Cvet:" << clr << endl;
    //         break;
    //     }
    //     case 5: {
    //         cout << "S=" << c.getArea() << endl;
    //         break;
    //     }
    //     case 6: {
    //         int newX, newY;
    //         cout << "vvedite X: ";
    //         cin >> newX;
    //         cout << "vvedite Y: ";
    //         cin >> newY;
    //         c.setCoord(newX, newY);
    //         break;
    //     }
    //     case 7: {
    //         double newRadius;
    //         cout << "vvedite radius: ";
    //         cin >> newRadius;
    //         c.setRadius(newRadius);
    //         break;
    //     }
    //     case 8: {
    //         char newColor[15];
    //         cout << "vvedite cvet: ";
    //         cin >> newColor;
    //         c.setColor(newColor);
    //         break;
    //     }
    //     case 9: {
    //         c.print();
    //         break;
    //     }
    //     case 0: {
    //         exit = true;
    //         break;
    //     }
    //     case 10: {
    //         cout << "Resultat vichitania:" << endl;
    //         c = -a;
    //         c.print();
    //         break;
    //     }
    //     case 11: {
    //         cout << (double)c << endl;
    //         break;
    //     }
    //     case 12: {
    //         cout << "Prefix: " << endl;
    //         (++c).print();
    //         break;
    //     }
    //     case 13: {
    //         cout << "Postfix: " << endl;
    //         (c++).print();
    //         break;
    //     }
    //     case 14: {
    //         CirclesToText("circles.txt", circles);
    //         cout << "Krugi sohraneni v fail\n";
    //         break;
    //     }
    //     case 15: {
    //         CirclesFromText("circles.txt", circles);
    //         cout << "Krugi zagrusheni iz faila \n";
    //         break;
    //     }
    //     case 16: {
    //         CirclesToBin("circles.dat", circles);
    //         cout << "Krugi sohraneni v binarni fail\n";
    //         break;
    //     }
    //     case 17: {
    //         CirclesFromBin("circles.dat", circles);
    //         cout << "Krugi zagrusheni iz binarnogo faila\n";
    //         break;
    //     }
    //     case 18: {
    //         cout << "Krugi seichas:\n";
    //         for (const auto& circle : circles) {
    //             circle.print();
    //             cout << "Area: " << circle.getArea() << "\n";
    //         }
    //         break;
    //     }
    //     case 19: {
    //         // Добавление нового круга с клавиатуры и немедленное сохранение в текстовый файл
    //         int x, y;
    //         double radius;
    //         char color[100];

    //         cout << "Vvdedite X: ";
    //         cin >> x;
    //         cout << "Vvrdite Y: ";
    //         cin >> y;
    //         cout << "Vvedite R: ";
    //         cin >> radius;
    //         cout << "Vvdedite cvet: ";
    //         cin >> color;
    //         Circle newCircle(x, y, radius, color);
    //         circles.push_back(newCircle);
    //         // Сохранение сразу после добавления
    //         CirclesToText("circles.txt", circles);
    //         cout << "Dobavlen novi krug v fail\n";
    //         break;
    //     }
    //     default: {
    //         cout << "Nepravilni vvod\n";
    //         break;
    //     }
    //     }
    // }
    return 0;
}
