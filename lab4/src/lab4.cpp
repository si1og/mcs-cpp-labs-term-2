#include "circle.hpp"
#include "list.hpp"
#include "point.hpp"
#include <iostream>

int main() {
  List circles;

  circles.push_back(Circle(Point(2, 2), 2.5));
  circles.push_front(Circle(Point(0, 0), 1));
  circles.push_back(Circle(Point(3, 3), 3.5));
  circles.insert(1, Circle(Point(1, 1), 2));

  std::cout << "Список после добавления 4 кругов:\n";
  circles.print(std::cout);

  circles.erase(2);
  std::cout << "\nПосле удаления круга с индексом 2:\n";
  circles.print(std::cout);

  std::cout << "\nРазмер списка: " << circles.size() << "\n";

  Circle &c = circles.at(1);
  std::cout << "Круг с индексом 1: Центр (" << c.get_center().get_x() << ", "
            << c.get_center().get_y() << "), радиус: " << c.get_radius()
            << "\n";

  circles.sort_by_area();
  std::cout << "\nПосле сортировки по площади:\n";
  std::cout << circles;

  circles.write_to_file("circles.txt");
  std::cout << "\nСписок сохранён в circles.txt\n";

  circles.clear();
  std::cout << "\nПосле clear(), размер: " << circles.size() << "\n";

  circles.read_from_file("circles.txt");
  std::cout << "\nСписок после загрузки из файла:\n";
  circles.print(std::cout);

  return 0;
}
