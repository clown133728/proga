#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE 
#include <vector> // подключение библиотеки для работы с векторами
#include <iostream> // подключение библиотеки для работы с вводом/выводом
#include <fstream> // подключение библиотеки для работы с файлами
#include "headers.h" 
using namespace std;
Circle::Circle(int _x, int _y, double _radius, const char* _color) {
    counter++;
    x = _x;
    y = _y;
    radius = _radius;
    allocateAndCopyColor(_color);
    cout << "circle constructor" << endl;
}

void Circle::allocateAndCopyColor(const char* _color) {
    color = new char[strlen(_color) + 1];
    strcpy(color, _color);
}

Circle::Circle(const Circle& c) {
    x = c.x;
    y = c.y;
    radius = c.radius;
    allocateAndCopyColor(c.color);
    counter++;
    cout << "circle copy constructor" << endl;
}

Circle& Circle::operator=(const Circle& c) {
    if (this == &c)
        return *this;

    delete[] color;
    x = c.x;
    y = c.y;
    radius = c.radius;
    allocateAndCopyColor(c.color);

    return *this;
}

Circle::Circle() : Circle(0, 0, 1.0, "unknown") {
}

Circle::~Circle() {
    counter--;
    delete[] color;
    cout << "circle dest" << endl;
}

double Circle::getArea() const {
    return 3.14 * radius * radius;
}

int Circle::getX() const {
    return x;
}

int Circle::getY() const {
    return y;
}

double Circle::getRadius() const {
    return radius;
}

void Circle::getColor(char* _color) const {
    strcpy(_color, color);
}

int Circle::getCounter() {
    return counter;
}

void Circle::setCoord(int _x, int _y) {
    x = _x;
    y = _y;
}

void Circle::setRadius(double _radius) {
    radius = _radius;
}

void Circle::setColor(const char* _color) {
    delete[] color;
    allocateAndCopyColor(_color);
}

void Circle::print() const {
    cout << "Coordinates: (" << x << ", " << y << ")" << endl;
    cout << "Radius: " << radius << endl;
    cout << "Color: " << color << endl;
}

Circle Circle::operator+(const Circle& c) const {
    Circle rv(x + c.x, y + c.y, radius + c.radius, color);
    return rv;
}

Circle operator-(const Circle& c) {
    double rad = -c.radius < 0. ? 0. : -c.radius;
    Circle rv(-c.x, -c.y, rad, c.color);
    return rv;
}

Circle operator-(const Circle& c1, const Circle& c2) {
    double rad = c1.radius - c2.radius < 0. ? 0. : c1.radius - c2.radius;
    Circle rv(c1.x - c2.x, c1.y - c2.y, rad, c1.color);
    return rv;
}

Circle& Circle::operator++() {
    radius += 1.;
    return *this;
}

Circle Circle::operator++(int) {
    Circle temp = *this;
    ++(*this);
    return temp;
}

Circle::operator double() const {
    return radius;
}

ostream& operator<<(ostream& os, const Circle& c) {
    os << "Coordinates = (" << c.x << ", " << c.y << "), "
        << "Radius = " << c.radius << ", "
        << "Color = " << c.color; // вывод информации о круге
    return os; // возврат потока вывода
}

istream& operator>>(istream& is, Circle& c) {
    char tempColor[100]; // временный буфер для цвета
    is >> c.x >> c.y >> c.radius >> tempColor; // ввод координат, радиуса и цвета
    c.setColor(tempColor); // установка цвета
    return is;
}

ofstream& operator<<(ofstream& os, const Circle& c) {
    os << c.x << " " << c.y << " " << c.radius << " " << c.color << "\n"; // запись информации о круге в файл
    return os;
}

ifstream& operator>>(ifstream& is, Circle& c) {
    char tempColor[100]; // временный буфер для цвета
    is >> c.x >> c.y >> c.radius >> tempColor; // чтение координат, радиуса и цвета из файла
    c.setColor(tempColor); // установка цвета
    return is;
}

void Circle::writeToText(ofstream& os) const {
    os << x << " " << y << " " << radius << " " << color << "\n"; // запись информации о круге в текстовый файл
}

void Circle::readFromText(ifstream& is) {
    char tempColor[100]; // временный буфер для цвета
    is >> x >> y >> radius >> tempColor; // чтение информации из текстового файла
    setColor(tempColor); // установка цвета
}

void Circle::writeToBinary(ofstream& os) const {
    os.write(reinterpret_cast<const char*>(&x), sizeof(x));// запись координаты x в бинарный файл
    os.write(reinterpret_cast<const char*>(&y), sizeof(y));// запись координаты y в бинарный файл
    os.write(reinterpret_cast<const char*>(&radius), sizeof(radius));// запись радиуса в бинарный файл
    size_t length = strlen(color);//получение длины строки цвета
    os.write(reinterpret_cast<const char*>(&length), sizeof(length));//запись длины строки для цвета
    os.write(color, length);//запис строки цвета
}

void Circle::readFromBinary(ifstream& is) {
    is.read(reinterpret_cast<char*>(&x), sizeof(x));//чтение координаты x из бинарного файла
    is.read(reinterpret_cast<char*>(&y), sizeof(y));//чтение координаты y из бинарного файла
    is.read(reinterpret_cast<char*>(&radius), sizeof(radius));//чтение радиуса из бинарного файла
    size_t length;//длина строки цвета
    is.read(reinterpret_cast<char*>(&length), sizeof(length));//чтение длины строки цвета
    char* buffer = new char[length + 2];//выделение памяти для строки цвета
    is.read(buffer, length);// чтение строки цвета
    buffer[length] = '\0';//добавление нулевого символа в конец строки
    setColor(buffer);//установка цвета
    delete[] buffer;//освобождение памяти
}

void CirclesToText(const char* filename, const vector<Circle>& circles) {
    ofstream os(filename);
    if (!os) { // проверка успешности открытия
        cerr << "Error opening file for writing." << endl;
        return;
    }
    for (const auto& circle : circles) { // перебор всех кругов
        circle.writeToText(os); // запись круга в файл
    }
}

void CirclesFromText(const char* filename, vector<Circle>& circles) {
    ifstream is(filename);
    if (!is) { // проверка успешности открытия
        cerr << "Error opening file for reading." << endl;
        return;
    }
    circles.clear();
    while (!is.eof()) {
        Circle circle; // создание временного объекта круга
        circle.readFromText(is); // чтение информации из файла
        if (is) circles.push_back(circle); // добавление круга в вектор, если чтение успешно
    }
}

void CirclesToBin(const char* filename, const vector<Circle>& circles) {
    ofstream os(filename, ios::binary); // открытие файла в бинарном режиме для записи
    if (!os) { // проверка успешности открытия
        cerr << "Error opening file for writing." << endl;
        return;
    }
    size_t count = circles.size(); // получение количества кругов в векторе
    os.write(reinterpret_cast<const char*>(&count), sizeof(count)); // запись количества кругов
    for (const auto& circle : circles) { // перебор всех кругов
        circle.writeToBinary(os); // запись круга в бинарный файл
    }
}

void CirclesFromBin(const char* filename, vector<Circle>& circles) {
    ifstream is(filename, ios::binary); // открытие файла в бинарном режиме для чтения
    if (!is) {
        cerr << "Error opening file for reading." << endl;
        return;
    }
    size_t count; //количество кргов
    is.read(reinterpret_cast<char*>(&count), sizeof(count)); // чтение количества кругов
    circles.clear();
    for (size_t i = 0; i < count; ++i) { //загрузка всех кругов из файла
        Circle circle; // создание временного объекта круга
        circle.readFromBinary(is); // чтение данных круга из файла
        circles.push_back(circle); // добавление круга в вектор
    }
}
int Circle::counter = 0; // инициализация статической переменной счетчика кругов

//

Oval::Oval(int _x, int _y, double _radius, double _radius1, const char* _color): Circle(_x, _y, _radius, _color)
{
    radius1 = _radius1;
    cout << "oval constructor" << endl;
}

Oval::Oval(): Circle()
{
    radius1 = 0.;
    cout << "oval constructor" << endl;
}

Oval::Oval(const Oval& o): Circle(o)
{
    radius1 = o.radius1;
    cout << "oval copy constructor" << endl;
}

Oval::~Oval()
{
    cout << "oval dest" << endl;
}

void Oval::setRadius1(double _radius1) {
    radius1 = _radius1;
}

double Oval::getRadius1() const {
    return radius1;
}

double Oval::getArea() const
{
    return 3.14 * radius * radius1;
}

void Oval::print() const 
{
    cout << "Coordinates: (" << x << ", " << y << ")" << endl;
    cout << "a: " << radius << endl;
    cout << "b: " << radius1 << endl;
    cout << "Color: " << color << endl;
}

Oval& Oval::operator=(const Oval& o)
{
    if (this == &o)
        return *this;

    delete[] color;
    x = o.x;
    y = o.y;
    radius = o.radius;
    radius1 = o.radius1;
    allocateAndCopyColor(o.color);
    return *this;
}

Oval Oval::operator+(const Oval& o) const
{
    Oval rv(x + o.x, y + o.y, radius + o.radius, radius1 + o.radius1, color);
    return rv;
}

Oval& Oval::operator++() {
    radius += 1.;
    return *this;
}

Oval Oval::operator++(int) {
    Oval temp = *this;
    ++(*this);
    return temp;
}

Oval operator-(const Oval& o)
{
    double rad = -o.radius < 0. ? 0. : -o.radius;
    double rad1 = -o.radius1 < 0. ? 0. : -o.radius1;
    Oval rv(-o.x, -o.y, rad, rad1, o.color);
    return rv;
}

Oval operator-(const Oval& o1, const Oval& o2)
{
    double rad = o1.radius - o2.radius < 0. ? 0. : o1.radius - o2.radius;
    double rad1 = o1.radius1 - o2.radius1 < 0. ? 0. : o1.radius1 - o2.radius1;
    Oval rv(o1.x - o2.x, o1.y - o2.y, rad, rad1, o1.color);
    return rv;
}

//

OutlineCircle::OutlineCircle(int _x, int _y, double _radius, const char* _color, const char* _outlinecolor): Circle(_x, _y, _radius, _color)
{
    allocateAndCopyOutlineColor(_outlinecolor);
    cout << "outlinecircle constructor" << endl;
}

void OutlineCircle::allocateAndCopyOutlineColor(const char* _outlinecolor) {
    outlinecolor = new char[strlen(_outlinecolor) + 1];
    strcpy(outlinecolor, _outlinecolor);
}

OutlineCircle::OutlineCircle(): Circle()
{
    allocateAndCopyOutlineColor("unknown");
    cout << "outlinecircle constructor" << endl;
}

OutlineCircle::OutlineCircle(const OutlineCircle& o): Circle(o)
{
    allocateAndCopyOutlineColor(o.outlinecolor);
    cout << "outlinecircle copy constructor" << endl;
}

OutlineCircle::~OutlineCircle()
{
    delete[] outlinecolor;
    cout << "outlinecircle dest" << endl;
}

void OutlineCircle::getOutlineColor(char* _outlinecolor) const {
    strcpy(_outlinecolor, outlinecolor);
}

void OutlineCircle::setOutlineColor(const char* _outlinecolor) {
    delete[] outlinecolor;
    allocateAndCopyOutlineColor(_outlinecolor);
}

void OutlineCircle::print() const {
    cout << "Coordinates: (" << x << ", " << y << ")" << endl;
    cout << "Radius: " << radius << endl;
    cout << "Color: " << color << endl;
    cout << "OutlineColor: " << outlinecolor << endl;
}

OutlineCircle& OutlineCircle::operator=(const OutlineCircle& oc)
{
    if (this == &oc)
        return *this;

    delete[] color;
    delete[] outlinecolor;
    x = oc.x;
    y = oc.y;
    radius = oc.radius;
    allocateAndCopyColor(oc.color);
    allocateAndCopyOutlineColor(oc.outlinecolor);
    return *this;
}

OutlineCircle OutlineCircle::operator+(const OutlineCircle& oc) const
{
    OutlineCircle rv(x + oc.x, y + oc.y, radius + oc.radius, color, outlinecolor);
    return rv;
}

OutlineCircle& OutlineCircle::operator++() {
    radius += 1.;
    return *this;
}

OutlineCircle OutlineCircle::operator++(int) {
    OutlineCircle temp = *this;
    ++(*this);
    return temp;
}

OutlineCircle operator-(const OutlineCircle& oc)
{
    double rad = -oc.radius < 0. ? 0. : -oc.radius;
    OutlineCircle rv(-oc.x, -oc.y, rad, oc.color, oc.outlinecolor);
    return rv;
}

OutlineCircle operator-(const OutlineCircle& oc1, const OutlineCircle& oc2)
{
    double rad = oc1.radius - oc2.radius < 0. ? 0. : oc1.radius - oc2.radius;
    OutlineCircle rv(oc1.x - oc2.x, oc1.y - oc2.y, rad, oc1.color, oc1.outlinecolor);
    return rv;
}

//


CircleContainer::CircleContainer(Circle _obj)
{
    obj = _obj;
    next = NULL;
    ++counter;
}

int CircleContainer::getCounter()
{
    return counter;
}

CircleList::CircleList()
{
    ph = NULL;
}

CircleList::CircleList(Circle obj)
{
    ph = new CircleContainer(obj);
}

CircleList::~CircleList()
{
    for (CircleContainer* p = ph; p != NULL;)
    {
        CircleContainer* q = p;
        p = p->next;
        delete q;
    }
}

void CircleList::add(Circle obj, int n)
{
    CircleContainer* q = new CircleContainer(obj);
    if (ph == NULL)
    {
        ph = q;
        return;
    }
    if (n == 0)
    {
        q->next = ph;
        ph = q;
        return;
    }
    CircleContainer* p = ph;
    if (n == -1)
    {
        for (int i = 0; p->next != NULL; p = p->next);
        p->next = q;
        return;

    }
    for (int i = 0; i < n; p = p->next);
    q->next = p->next;
    p->next = q;
}

void CircleList::del(int n)
{
    if (ph == NULL) return;
    if (n == 0)
    {
        CircleContainer* q = ph;
        ph = ph->next;
        delete q;
        return;
    }
    if (n == -1) n = CircleContainer::getCounter() - 1;
    CircleContainer* p = ph;
    for (int i = 0; i < n; p = p->next);
    CircleContainer* q = p->next;
    p->next = q->next;
    delete q;
}

void CircleList::print()
{
    for (CircleContainer* p = ph; p != NULL; p = p->next)
    {
        p->obj.print();
    }
}

CircleContainer* CircleList::search(const char* str)
{
    CircleContainer* p;
    for (p = ph; ((p != NULL) && (strcmp(p->obj.color, str) != 0)); p = p->next);
    return p;
}