
# Мефодій 
![Мефодій](https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcSuNYYPUCqBqEUpaVuNUNOnW7FzhU7hPAqcWMpgYYaTWE943RMFMm6QxVE9v6LnMy_6I_8&usqp=CAU)

Мефодій це інтерпритована і динамічно типізована мова програмування основана на українській лексиці. Мова влкючає такі типи даних як цілі числа, дійсні числа, булеві значення, строки, масиви і спеціальний тип нал. Для управління ходом програми використовується умовний оператор, для повторення виконання коду використовуються цикл, а також користувацькі функції. Також є вбудована функція "**вМасиві**" (поки що одна), яка перевіряє наявність елемента в масиві.

### Приклад коду
```
функція підстрока(дані, початок, довжина) {
    конст кінець = (початок + довжина);
    умова (кінець > дані.довжина) {
        друк "Помилка: підстрока виходить за межі строки\n";
        вихід;
    }
    мем результат;
    цикл (мем індекс = початок; індекс < кінець; індекс++) {
        результат += дані[індекс];
    }
    вихід результат;
}
мем тест = підстрока("привіт світ", 0, 6);
друк тест + "\n"; // виведе "привіт"
```

### Особливості
- Програма склається із виразів розділених оператором крапки з комою "**;**" або комою "**,**". Крім виразів можуть використовуватися умовні оператори, цикли і функції.
- Декларація (створення) змінної відокремлена від зверення до неї. Для декларації використовується ключове слово "**мем**" (запозичення від англійського "memorise"), після якого слідує ім'я змінної. 
- Для створення константи використовується ключове слово "**конст**" замість "**мем**".
- Звернення до неіснуючої змінної або спроба змінити значення константи призводять до помилки.
- Спеціальний тип "нал" використовують для змінних які вже створені але ще не мають реального значення. Можна сказати що вони мають тимчасове значення або пусте значення.
- Для виходу із скрипта або функції використовується оператор "**вихід**"
- Для зупинки циклу використовується оператор "**стоп**"
- Спеціальний булевий оператор "**~**" тестує строку на регулярний вираз. Приклад: "привіт" ~ ".\*ві.\*" // істина
- Відстуння підтримка об'єктно орієнтованого програмування

### Оператори 
Підтримують математичні оператори **+**, **-**, **/**, *****, **%** а також булеві оператори **||**, **&&**, **>**, **<**, **<=**, **>=**. Оператор присвоєння **=** і комбіновані **+=** та **-=**. Оператори присвоєння мають найвищий пріорітет, на рівні із обчисленням виразу в дужках "**()**". Потім обчислюють усі математичні операції і в кінці обчислюються булеві операції.

### Змінні
Змінна за замовчуванням має тип "**нал**". Присвоєння змінній значення іншого типу, або змінної іншого типу змінює тип змінної відповідно. Константи не можуть змінювати значення пілся його першого присвоєння. Область видимості змінної обмежена блоком коду в якому вона створена, а також змінна видима із тіла функції, якщо сама функція не ствроє змінну із аналогічним іменем.

### Літеральні константи
Існують такі літеральні константи як "**нал**" - задає змінну типу нал. "**так**" і "**ні**" що відповідають булевим істині та не істині.
```
умова (так) {
    друк "умова є істиною\n";
}
```

### Приведення типів
Для приведення типу ми вказуємо назву потрібного типу перед операндом, який може бути як змінною, так і літеральною константою.
```
мем тест = 123.33; // дійсне число
друк тест; // виведе 123.33
друк (ціле) тест; // виведе 123
```

### Коментарі
Підримуються однострочні коментарі, які починаються із символів "**//**".
```
// це коментар
```

### Вивід тексту
Для виведення значення на консоль використовується диркетива "**друк**". Строки можуть можуть об'єднуватися за допомогою оператора "**+**", який працює як оператор конкатенації коли один із операднів є строкою. 
```
друк "привіт " + "світ!"; // виведе "привіт світ!"
```

### Строки
Строки можуть бути закодовані в одинарнтих або подвійних лапках. Строка в подвійних лапках може містити такі спеціальній символи як символ переведення рядка "**\n**" або символ табуляції "**\t**". 
Строку можна привести до масиву, який буде мати кожну літеру строки елементом масиву. 
Можна звертатися до окремих символів масиву за допомгою операдо індексації "**[]**". Отримання довжини строки виконується звертанням до спеціального поля "довжина".
```
друк "привіт".довжина; // виведе 6
друк "привіт"[0]; // виведе "п"
```

### Масиви
Масив це структура даних, яка може зберіагати нуль або більше елементів різного типу. Масив можна описати за допомогою літералу масиву, який має наступний формат:
```
[0, 1, 2]
```
Масив може мати як числові так і строкові індекси. При незадані індекса елемента, йому буде присвоєний автоматичнй числовий індекс. Наприклад, в попердньому прикладі число "3" зберігається під індексом "2" (індексування починається з нуля).
До першого і другого елементів масиву можна звернутися через спеціальні поля "**перший**" і "**другий**" відповідно. Це дозволяє працювати із масивом із двох елементів як з парою.
```
мем мас = [0, 1, 2];
друк мас.перший;// виведе 0
друк мас.другий;// виведе 1
```
### Функції
Функція ствроюється за допомогою ключового слова "**функція**", за яким слідують параметри в дужках а потім тіло функції. Приклад функції:
```
функція сума(а, б) {
    вихід а + б;
}
```
Виклик функції виконується написанням імені функції, за яким в дужках слідують аргументи функції розділені комою. Значення параметрів за замовчуванням можна вказати після імені параметра після опереатора "=". Аргументи по замовчуванню передаються за значенням (копіюються в стек функції), але можуть бути і передані за посиланям. Для передачі за посиланням, перед параметром функції треба вказати символ "&". 
```
мем тест = 3;
функція сума(а, б = 3) {
    вихід а + б + тест;
}
друк сума(3); // виведе 9
```
### Цикли
Структура циклу починається із ключового слова "**цикл**", після якого слідує один або кілька виразів у дужках, а потім і тіло циклу. Якщо в дужках описано 3 вирази (розділені сиволом крапки з комою ";"), тоді перший вираз описує змінні циклу, другий описує умову виконання тіла циклу, третій виконується після виконання ітерації циклу. Якщо в дужках після першого виразу слідує роздільник "**:**", то цей цикл виконує перебір усіх елементів масиву, який слідує після роздільника. Якщо ж в дужках лише один вираз, то цикл працє до тих пір, поки булеве значення цього виразу обчислюється в "**істину**".
### Підключення файлів
Файли можна підключати один в одний за допомогою директиви "**імпорт**" за яким слідує назва файлу у вигляді літеральної строки.

**файл "функції.txt"**
```
функція додати(ф,а) {
    вихід ф + а;
}
функція відняти(ф,а) {
    вихід ф - а;
}
функція помножити(ф,а) {
    вихід ф * а;
}
```
**файл "програма.txt"**
```
імпорт "функції.txt";
умова (додати(22,22) == 44) {
    друк "виклик функції \"додати\" працює\n";
}

```
## Підготовка до установки
1. Установіть компілятор g++ версії 8.4.0+.
2. Для тестів треба встановити фреймворк Google Test. [Інструкція на GitHub](https://github.com/google/googletest/blob/main/googletest/README.md)

## Установка
1. Клонуйте репозиторій із сирцевим кодом:
`
git clone git@github.com:patronik/mefodij.git
`
2. Перейдіть в папку з кодом.
2. Для побудови інтерпритатора виконайте команду:
`
g++ -g $(find ./src -type f -iregex ".*\.cpp" ! -name "test.cpp") -o build/mefodij
`
3. Для побудови тестів виконайте команду: 
`
g++ -g $(find ./src -type f -iregex ".*\.cpp" ! -name "main.cpp") -lgtest -lpthread -o build/test
`
## Запуск програми
Для запуску програми збережіть її у текстовий файл. Потім виконайте наступну команду:
`./build/mefodij -f "code.txt"`
Також можна виконати код переданий через параметр -r.
`./build/mefodij -r "друк \"привіт світ\";"`
## Тестування
Для запуску юніт тестів виконайте команду:
`./build/test`

## Примітки
Ідея створення полягала у полегшені навчання програмуванню дітей і дорослих, які не володіють англійською мовою в достатній мірі. Форки вітаються. При находжені багів або рекомендацій можна писати на vasyl.voina@gmail.com

