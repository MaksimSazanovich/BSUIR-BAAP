//Вариант 1: Расширение класса Animal
//Цель : Создать ещё один производный класс с именем Cat, унаследованный от класса Animal.
//
//Требования :
//    Реализовать конструктор для класса Cat, который инициализирует имя, возраст и дополнительный цвет животного.
//
//    Переопределить метод makeSound() для вывода звука «Мяу!».
//    Реализовать метод displayInfo(), возвращающий цвет кошки.

#include <iostream>
#include <string>

class Animal
{
protected:
    std::string name;
    int age;

public:
    Animal(const std::string& name, int age) : name(name), age(age)
    {
        if (age < 0)
            throw std::invalid_argument("Age cannot be negative");

        std::cout << "Animal created: " << name << ", Age: " << age << std::endl;
    }

    virtual void makeSound()
    {
        std::cout << "Animal sound" << std::endl;
    }

    void displayInfo()
    {
        std::cout << "Name: " << name << ", Age: " << age << std::endl;
    }
};

class Cat : public Animal
{
private:
    std::string color;

public:
    Cat(const std::string& name, int age, const std::string& color)  : Animal(name, age), color(color)
    {
        std::cout << "Cat created: " << name << ", Age: " << age << ", Color: " << color << std::endl;
    }

    void makeSound() override
    {
        std::cout << "Мяу!" << std::endl;
    }

    void displayInfo()
    {
        Animal::displayInfo();
        std::cout << "Color: " << color << std::endl;
    }
    
};

int main()
{
    setlocale(LC_ALL, "Russian");

    Animal animal("Generic animal", 3);
    animal.displayInfo();
    animal.makeSound();

    Cat cat("Murzik", 4, "grey");
    cat.displayInfo();
    cat.makeSound();
}

