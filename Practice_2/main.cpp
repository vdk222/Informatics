#include <SFML/Graphics.hpp>
#include <functional>
#include <cmath>
#include <string>

// Функция для отрисовки графика
void drawGraph(sf::RenderWindow& window, std::function<float(float)> func,
    float xMin, float xMax, float scaleX, float scaleY, sf::Color color) {
    sf::VertexArray graph(sf::LinesStrip);

    for (float x = xMin; x <= xMax; x += 0.1f) {
        float y = func(x);                 // вычисление значения функции

        float screenX = 400 + x * scaleX;  // преобразование координат в экранные
        float screenY = 300 - y * scaleY;

        graph.append(sf::Vertex(sf::Vector2f(screenX, screenY), color));
    }

    window.draw(graph);
}

std::string Zone(int ZoneNumber) {
    if (ZoneNumber == 0) {
        return "Border"; 
    }
    return std::to_string(ZoneNumber);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Application for displaying graphs");

    sf::CircleShape userPoint(5);          // пользовательская точка, радиус 5 пикселей
    userPoint.setFillColor(sf::Color::Red);
    bool userPointExists = false;

    // 1 _ Загрузка шрифта
    sf::Font font;                                   // шрифт для счёта
    if (!font.loadFromFile("arial.ttf")) {
        return -1;
    }
    // 2 _ Текст для отображения координат: размер 20, позиция (10,10), цвет белый,
    //     переменная coordinatesText
    sf::Text coordinatesText;
    coordinatesText.setFont(font);
    coordinatesText.setCharacterSize(20);
    coordinatesText.setFillColor(sf::Color::White);
    coordinatesText.setPosition(10, 10);
    

    // Оси X и Y
    sf::VertexArray xAxis(sf::Lines, 2);
    xAxis[0].position = sf::Vector2f(50, 300);   xAxis[0].color = sf::Color::White;
    xAxis[1].position = sf::Vector2f(750, 300);  xAxis[1].color = sf::Color::White;
    sf::VertexArray yAxis(sf::Lines, 2);
    yAxis[0].position = sf::Vector2f(400, 50);   yAxis[0].color = sf::Color::White;
    yAxis[1].position = sf::Vector2f(400, 550);  yAxis[1].color = sf::Color::White;



    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    // Преобразование экранных координат в «математические»
                    float mathX = (mousePos.x - 400) / 30.0f;
                    float mathY = -(mousePos.y - 300) / 30.0f;

                    userPoint.setPosition(mousePos.x - userPoint.getRadius(),
                        mousePos.y - userPoint.getRadius());
                    userPointExists = true;

                    // 3 _ логика проверки точки по mathX и mathY! 
                    int ZoneNumber = 0;
                    if ((mathY == (abs(mathX) - mathX)) or (mathY == -(abs(mathX)))) {
                        ZoneNumber = 0;
                    }
                    if (mathY > (abs(mathX) - mathX) and mathY > -(abs(mathX))) {
                        ZoneNumber = 2;
                    }
                    if (mathY < (abs(mathX) - mathX) and mathY < -(abs(mathX))) {
                        ZoneNumber = 1;
                    }
                    if (mathX > 0 and (not(mathY > (abs(mathX) - mathX) and mathY > -(abs(mathX)))) and (not(mathY < (abs(mathX) - mathX) and mathY < -(abs(mathX))))) {
                        ZoneNumber = 4;
                    }
                    if (mathX < 0 and (not(mathY > (abs(mathX) - mathX) and mathY > -(abs(mathX)))) and (not(mathY < (abs(mathX) - mathX) and mathY < -(abs(mathX))))) {
                        ZoneNumber = 3;
                    }

                    coordinatesText.setString("Coordinates: (" + std::to_string(mathX) +
                        ", " + std::to_string(mathY) + ")" + " Zone: " + std::string(Zone(ZoneNumber)));
                }
            }
        }

        


        // 4 _ Очистка экрана

        window.clear();
        window.draw(xAxis);
        window.draw(yAxis);

        // 5 _ графики вашего варианта 
        drawGraph(window, [](float x) { return -abs(x); }, -10, 10, 30, 30, sf::Color::Blue);
        drawGraph(window, [](float x) { return abs(x) - x; }, -10, 10, 30, 30, sf::Color::Red);

        if (userPointExists) {
            window.draw(userPoint);
            window.draw(coordinatesText);
        }

        window.display();
    }

    return 0;
}