#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <clocale>
#include <Windows.h>

using namespace std;

//Функция для шифровывания данных
void shifrovanie(char *first, int a, int b) {
    srand(b);   // Инициализация секретного ключа
    unsigned short Gamma;   // Гамма
    unsigned short Block1, Block2; // Блоки, которые будут использованы в качестве буфера обмена
    int c;  // c - Количество блоков памяти
    c = a / 1; //  Количество блоков памяти по 1 байт
    Block1 = 0;
    Block2 = 0;
    for (int i = 1; i <= c; i++) {
        Gamma = rand();// Генерируем гамму с помощью рандома
        memcpy(&Block1, first + (i - 1),
               1);    //  Копирование блока исходных данных размером 1 байт из исходной строки в буферный блок данных
        Block2 = Block1 ^
                 Gamma; // Наложение гаммы на буферный блок данных, используя операцию поразрядного исключающего "ИЛИ"
        Block1 = Block2 &
                 128; // Наложение маски, чтобы выделить отдельные биты и сохранить их в отдельном буферном блоке
        Block1 >>= 7; // Выполнениеоперации поразрядного сдвига на 7 бит вправо
        Block2 <<= 1; // Выполнение операции поразрядного сдвига на 1 бита влево
        Block2 |= Block1; // Использование операции поразрядного "ИЛИ", получение поразрядно сдвинутого на 1 бит влево исходного блока с наложенной гаммой
        memcpy(first + (i - 1), &Block2, 1); // Копирование результата из буфера в блок с зашифрованными данными
    }


}



//Функция для расшифровывания данных

void deshifrovanie(char *late, int a, int b) {

    srand(b); // Инициализация секретного ключа
    unsigned short Gamma;   // Гамма
    int c; // c - Количество блоков памяти
    unsigned short Block1, Block2;  // Блоки, которые будут использованы в качестве буфера обмена
    c = a / 1; //  Количество блоков памяти по 1 байт
    Block1 = 0;
    Block2 = 0;
    for (int i = 1; i <= c; i++) {
        Gamma = rand();// Генерация гаммы с помощью рандома
        memcpy(&Block1, late + (i - 1),
               1); // Копирование блока зашифрованных данных размером 1 байт из исходной строки в буферный блок данных
        Block2 =
                Block1 & 1;  // Наложение маски, чтобы выделить отдельные биты и сохранить их в отдельном буферном блоке
        Block2 <<= 7; // Выполнение операции поразрядного сдвига на 7 бит влево
        Block1 >>= 1; // Выполнение операции поразрядного сдвига на 1 бита вправо
        Block1 |= Block2; // Использование операции поразрядного "ИЛИ", получение поразрядно сдвинутого на 1 бит вправо исходного блока зашифрованных данных
        Block2 = Block1 ^
                 Gamma; // Наложение гаммы, используя операцию поразрядного исключающего "ИЛИ", и получаем блок исходных данных
        memcpy(late + (i - 1), &Block2, 1); // Копирование результата из буфера в блок с расшифрованными данными

    }

}


int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string mode, name_file, s;
    int a;
    int Key, Key1;   // Key, Key1 - Секретный ключ
    ofstream file; // Файл с шифром
    ifstream file1;
    cout << "Enter mode(e for encryption/d for decryption) " << endl;
    cin >> mode;//Команда
    cout << "Enter name to the file: " << endl;
    cin >> name_file;//Имя файла
    if (mode == "e") {
        string str;
        cout << "Enter the data you want to encrypt: " << endl;
        cin >> str;//Исходная строка
        char *Original;
        Original = new char[str.length() + 1];
        strcpy(Original, str.c_str());
        a = strlen(Original); // Длина строки
        cout << "Enter the key:" << endl;
        cin >> Key; // Ввод секретного ключа
        shifrovanie(Original, a, Key);//Зашифровка исходных данных
        file.open(name_file, ios::binary);//Открытие файла
        string s(Original, a);//Перевод в строку для записи в файл
        file << s;
        file.close();
    } else if (mode == "d") {
        cout << "Enter the key:" << endl;
        cin >> Key1; // Ввод секретного ключа
        file1.open(name_file, ios::binary);//открытие файла
        if (!file1) {//Проверка на существование файла
            cout << "File not found" << endl;
            file1.close();
            return 0;
        }
        string str;
        file1 >> str;//Чтение из файла
        cin.get();
        char *Encrypt = new char[str.length() + 1];
        strcpy(Encrypt, str.c_str());
        a = strlen(Encrypt); // Длина строки
        deshifrovanie(Encrypt, a, Key1); // Расшифровывание зашифрованных данных
        cout << "Decrypted data:" << Encrypt << endl;//Вывод расшифрованных данных

    }
    return 0;
}
