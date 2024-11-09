#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE 
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
class Circle {
public:
    // Конструкторы и деструктор
    Circle(int _x, int _y, double _radius, const char* _color);
    Circle(const Circle& c);
    Circle();
    virtual ~Circle();

    // Методы
    void setCoord(int _x, int _y);
    void setRadius(double _radius);
    void setColor(const char* _color);
    int getX() const;
    int getY() const;
    double getRadius() const;
    double getArea() const;
    void getColor(char* _color) const;
    virtual void print() const;
    static int getCounter();

    // методы для работы с файлами
    void writeToText(ofstream& os) const; //запись информации о круге в текстовый файл
    void readFromText(ifstream& is); //чтение информации о круге из текстового файла
    void writeToBinary(ofstream& os) const; //запись информации о круге в бинарный файл
    void readFromBinary(ifstream& is); //чтение информации о круге из бинарного файла
    // Операторы
    Circle& operator=(const Circle& c);
    Circle operator+(const Circle& c) const;
    Circle& operator++();
    Circle operator++(int);
    operator double() const;

    friend ostream& operator<<(ostream& os, const Circle& c);
    friend istream& operator>>(istream& is, Circle& c);
    friend ofstream& operator<<(ofstream& os, const Circle& c);
    friend ifstream& operator>>(ifstream& is, Circle& c);
    friend Circle operator-(const Circle& c1, const Circle& c2);
    friend Circle operator-(const Circle& c);

protected:
    int x;
    int y;
    double radius;
    char* color;
    static int counter;
    void allocateAndCopyColor(const char* _color);
    friend class CircleList;
};
// функции для работы с вектором объектов Circle
void CirclesToText(const char* filename, const vector<Circle>& circles); //сохранение кругов в текстовый файл
void CirclesFromText(const char* filename, vector<Circle>& circles); //загрузка кругов из текстового файла
void CirclesToBin(const char* filename, const vector<Circle>& circles); //сохранение кругов в бинарный файл
void CirclesFromBin(const char* filename, vector<Circle>& circles); //загрузка кругов из бинарного файла

class Oval: public Circle
{
public:
    Oval(int _x, int _y, double _radius, double _radius1, const char* _color);
    Oval(const Oval& o);
    Oval();
    ~Oval();

    void setRadius1(double _radius);
    double getRadius1() const;
    double getArea() const;
    void print() const;

    Oval& operator=(const Oval& c);
    Oval operator+(const Oval& c) const;
    Oval& operator++();
    Oval operator++(int);

    friend Oval operator-(const Oval& c1, const Oval& c2);
    friend Oval operator-(const Oval& c);

private:
    double radius1;
};

class OutlineCircle: public Circle
{
public:
    OutlineCircle(int _x, int _y, double _radius, const char* _color, const char* _outlinecolor);
    OutlineCircle(const OutlineCircle& oc);
    OutlineCircle();
    ~OutlineCircle();

    void setOutlineColor(const char* _outlinecolor);
    void getOutlineColor(char* _outlinecolor) const;
    void print() const;

    OutlineCircle& operator=(const OutlineCircle& oc);
    OutlineCircle operator+(const OutlineCircle& oc) const;
    OutlineCircle& operator++();
    OutlineCircle operator++(int);

    friend OutlineCircle operator-(const OutlineCircle& oc1, const OutlineCircle& oc2);
    friend OutlineCircle operator-(const OutlineCircle& oc);

private:
    char* outlinecolor;
    void allocateAndCopyOutlineColor(const char* outlinecolor);
};

class CircleContainer
{
public:
    CircleContainer(Circle _obj);

    static int getCounter();

private:
    Circle obj;
    CircleContainer* next;
    friend class CircleList;
    static int counter;
};

int CircleContainer::counter = 0;

class CircleList
{
public:
    CircleList();
    CircleList(Circle obj);
    ~CircleList();

    void add(Circle obj, int n);
    void del(int n);
    void print();
    CircleContainer* search(const char* str);

private:
    CircleContainer* ph;
};