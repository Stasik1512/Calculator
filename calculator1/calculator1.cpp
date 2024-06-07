#include <iostream>
#include <stack>
using namespace std;

struct Leksema // описывает любое число или операцию
{
    char type;
    double value;
};

bool Maths(stack <Leksema>& Stack_number, stack <Leksema>& Stack_oper) // расчеты
{
    Leksema item;
    double a, b, c;
    a = Stack_number.top().value; //берем верхний элемент
    Stack_number.pop(); //удаляем верхний элемент
    switch (Stack_oper.top().type) // top возвращает элемент; type возвращает тип/знак
    {
    case '+':
        b = Stack_number.top().value; //берем верхний элемент
        Stack_number.pop();  //удаление вверх элем.числа
        c = a + b;
        item.type = '0';
        item.value = c;
        Stack_number.push(item);  // положили обратно
        Stack_oper.pop();  // удалене вверх элем операции
        break;
    case '-':
        b = Stack_number.top().value;
        Stack_number.pop();
        c = b - a;
        item.type = '0';
        item.value = c;
        Stack_number.push(item);
        Stack_oper.pop();
        break;
    case '*':
        b = Stack_number.top().value;
        Stack_number.pop();
        c = a * b;
        item.type = '0';
        item.value = c;
        Stack_number.push(item);
        Stack_oper.pop();
        break;
    case '/':
        b = Stack_number.top().value;
        if (b == 0 || a == 0)
        {
            cout << "Делить на 0 нельзя!\n";
            return false;
        }
        else
        {
            Stack_number.pop();
            c = (b / a);
            item.type = '0';
            item.value = c;// положили обратно
            Stack_number.push(item);
            Stack_oper.pop();// удаление вверх элем операции
            break;
        }
    }
    return true;


}
//15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))

int GetSing(char symbol) // расставляет приоритет знаков
{
    if (symbol == '+' || symbol == '-')
        return 1;
    if (symbol == '*' || symbol == '/')
        return 2;
    else return 0; // скобка
}

int main()
{
    setlocale(LC_ALL, "RUS");

    cout << "Привет, это Калькулятор выражений"<< endl << "Введите выражение, которое надо посчитать" << endl;
    char symbol;
    double value;
    bool Flag = 1; // если встречаем минус перед числом
    stack <Leksema> Stack_number;

    stack <Leksema> Stack_oper;
    Leksema item;// инициализируем элемент который получили

    while (true)
    {

        symbol = cin.peek();//смотрим на символ 

        if (symbol == '\n') break;
        if (symbol == ' ')
        {
            cin.ignore();
            continue;
        }
        if (symbol >= '0' && symbol <= '9' || symbol == '-' && Flag == 1) // определяем число, кладем в стэк
        {
            cin >> value;
            item.type = '0'; // тип
            item.value = value;//значение
            Stack_number.push(item); // отправляем на вершину стэка
            Flag = 0;
            continue;
        }



        if (symbol == '+' || symbol == '-' && Flag == 0 || symbol == '*' || symbol == '/') // опред приоритет
        {
            if (Stack_oper.size() == 0) // если стэк пуст
            {
                item.type = symbol;
                item.value = 0;
                Stack_oper.push(item); // отправляем знак на врешину стэка
                cin.ignore(); // после того как занесли в стэк переходим к след
                continue;
            }
            if (Stack_oper.size() != 0 && GetSing(symbol) > GetSing(Stack_oper.top().type))// если стэк не пуст, но приоритет текущей опер выше верхней операции                                                                   
            {
                item.type = symbol;
                item.value = 0;
                Stack_oper.push(item);
                cin.ignore();
                continue;
            }
            if (Stack_oper.size() != 0 && GetSing(symbol) <= GetSing(Stack_oper.top().type)) // если стек не пуст, но приоритет текущей опре ниже или равен верхней операции
            {
                if (Maths(Stack_number, Stack_oper) == false)
                {
                    return 0;
                }
                continue;
            }
            
        }
        if (symbol == '(')
        {
            item.type = symbol;
            item.value = 0;
            Stack_oper.push(item); // отправляем скобку на вершину стэка
            cin.ignore(); // после того как занесли в стэк переходим к след
            continue;
        }
        if (symbol == ')')
        {
            while (Stack_oper.top().type != '(') // пока верхний элемент не скобка открытия
            {
                if (Maths(Stack_number, Stack_oper) == false)
                {
                    return 0;
                }
                else continue;
                
            }
            Stack_oper.pop();

            cin.ignore(); // переход, тк скобка не постоянная
            continue;
        }
        else
            {
                cout << "Не корректный ввод!" << endl;
                return 0;
            }
    }
    while (Stack_oper.size() != 0) // пока стэк не станет пустым                                                                                                                            
    {

        if (Maths(Stack_number, Stack_oper) == false)
        {
            return 0;
        }
        else
        {
            continue;
        }

    }
    cout << "Ответ: " << Stack_number.top().value << endl;
    return 0;
}

