// Vdk.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cmath>
#include <algorithm>
int main()
{
    setlocale(LC_CTYPE, "rus");                   
    std::string name;
    float x;
    float y;
    std::cout << "Введите x: ";
    std::cin >> x;
    std::cout << "Введите y: ";
    std::cin >> y;
    float R = x * std::tan(3.14159265358979 / 2);
    float S = sqrt(pow(x, 2) + pow(y, 2)) / pow(2, log2(x));
    std::cout << "R = " << R << std::endl; 
    std::cout << "S = " << S << std::endl;
    float C = std::max(R, S);
    std::cout << "C = " << C << std::endl;
    system("pause");
}


