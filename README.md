
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
- Спеціальний тип "**нал**" використовують для змінних які створені, але ще не мають корисного значення. Можна сказати що вони мають тимчасове значення або пусте значення.
- Для виходу із скрипта або функції використовується директива "**вихід**"
- Для зупинки циклу використовується директива "**стоп**"
- Спеціальний булевий оператор "**~**" тестує строку на регулярний вираз. Приклад: 

  `"привіт" ~ ".\*ві.\*" // істина`
- Підтримка об'єктно орієнтованого програмування відсутня 

### Оператори 
Підтримують математичні оператори **+**, **-**, **/**, **\***, **%** а також булеві оператори **||**, **&&**, **>**, **<**, **<=**, **>=**. Оператор присвоєння **=** і комбіновані **+=** та **-=**. Оператори присвоєння мають найвищий пріорітет, на рівні із обчисленням виразу в дужках "**()**". Потім обчислюються математичні операції, булеві (логічні) операції мають найнижчий пріорітет.

### Змінні
Змінна за замовчуванням має тип "**нал**". Присвоєння змінній значення іншого типу, або змінної іншого типу, змінює тип змінної відповідно. Константи не можуть змінювати значення пілся його першого присвоєння. Область видимості змінної обмежена блоком коду в якому вона створена, а також змінна видима в функції, якщо сама функція не створює змінну із таким самим іменем (перекриття).

### Літеральні константи
Існують такі літеральні константи як "**нал**" - створення змінної типу нал. "**так**" і "**ні**" що відповідають булевим істині та не істині.
```
умова (так) {
    друк "умова є істиною\n";
}
```

### Коментарі
Підримуються однострочні коментарі, які починаються із символів "**//**".
```
// це коментар
```

### Вивід тексту
Для виведення значення на консоль використовується диркетива "**друк**". Строки можуть об'єднуватися за допомогою оператора "**+**", який працює як оператор конкатенації коли обоє або один із операднів є строкою. 
```
друк "привіт " + "світ!"; // виведе "привіт світ!"
```

### Приведення типів
Для приведення типу ми вказуємо назву потрібного типу в дужках перед операндом, який може бути як змінною, так і літеральною константою.
```
мем тест = 123.33; // дійсне число
друк тест; // виведе 123.33
друк (ціле) тест; // виведе 123
```

### Строки
Строки можуть бути закодовані в одинарнтих або подвійних лапках. Строки в подвійних лапках можуть містити такі спеціальній символи як символ переведення рядка "**\n**" або символ табуляції "**\t**". 
Строку можна привести до типу масиву, в якому кожен елемент буде зберіагти символ строки. 
Можна звертатися до окремих символів строки за допомгою оператора індексації "**[]**". Отримання довжини строки виконується звертанням до спеціального поля "**довжина**".
```
мем тест = "привіт";
друк тест.довжина; // виведе 6
друк тест[0]; // виведе "п"
```

### Умовний оператор
Умовний оператор керує ходом роботи програми. Він дозволяє виконати один або інший блок коду, в залежності від того чи умова, що перевіряється, є істиною.
Загальна структура умовного оператора:
```
умова (1 > 4) {
  друк "1 > 4 істина\n";
} або умова (1 > 3) {
  друк "1 > 3 істина\n";
} або умова (1 > 2) {
  друк "1 > 2 істина\n";
} або {
  друк "1 менше або рівне 2\n";
}
```
Частини "**або умова (вираз) { ... }**" та "**або { ... }**" є опціональними.

### Масиви
Масив це структура даних, яка може зберігати нуль або більше елементів різного типу. Масив можна описати за допомогою літералу масиву, який має наступний формат:
```
[0, 1, 2]
```
Масив може мати як числові, так і строкові індекси. При незаданні індекса елемента, йому буде присвоєний автоматичнй числовий індекс. Наприклад, в попердньому прикладі число "3" зберігається під індексом "2" (індексування починається з нуля).
До першого і другого елементів масиву можна звернутися через спеціальні поля "**перший**" і "**другий**" відповідно. Це дозволяє працювати із масивом із двох елементів як з парою.
```
мем мас = [0, 1, 2];
друк мас.перший;// виведе 0
друк мас.другий;// виведе 1
```
Асоціативні індекси і їх значання відділяються роздільником "**=>**". При ітерації масиву із числовими індексами і строковими індексами, елементи з числовими індексами йдуть першими.

### Функції
Функція ствроюється за допомогою ключового слова "**функція**", за яким слідують параметри в дужках а потім тіло функції. Значення параметрів за замовчуванням можна вказати після імені параметра використовуючи оператор присвоєння "**=**".

Приклад функцій:
```
функція сума(а, б) {
    вихід а + б;
}
функція сумаДвох(а = 1, б = 1) {
    вихід а + б;
}
друк сумаДвох(0,2); // виведе 2
друк сумаДвох(1,1); // виведе 2
друк сумаДвох(); // виведе 2
```
Виклик функції виконується написанням імені функції, за яким в дужках слідують аргументи функції розділені комою. Аргументи передаються за значенням (копіюються в стек функції), але можуть бути і передані за посиланням. Для передачі за посиланням, перед параметром функції треба вказати символ "**&**". 
```
мем тест = 3;
функція сума(а, б = 3) {
    вихід а + б + тест;
}
друк сума(3); // виведе 9
```
### Цикли
Цикл починається із ключового слова "**цикл**", після якого слідує один або кілька виразів у дужках, а потім і тіло циклу. Якщо в дужках описано 3 вирази (розділені сиволом "**;**"), тоді перший вираз описує змінні циклу, другий описує умову виконання тіла циклу, третій виконується після виконання ітерації циклу. Якщо в дужках після першого виразу слідує роздільник "**:**", то цей цикл виконує перебір усіх елементів масиву, який слідує після роздільника. Якщо ж в дужках лише один вираз, то цикл працє до тих пір, поки булеве (логічне) значення цього виразу обчислюється як "**істина**".
Приклади циклів:
```
// цикл із трьома виразами
мем рядок = "привіт світ!";
цикл (мем і = 0; і < рядок.довжина; і++) {
    друк рядок[і] + "\n";
}

// цикл з однією умовою
мем д = 0;
цикл (так) {
    друк рядок[д] + "\n";
    д++;
    умова (д >= рядок.довжина) {
        стоп;
    }
}

// цикл по перебору масива
цикл (мем символ: (масив) рядок) { 
    // символ буде масивом із 2-ох елементів (пара)
    // в першому - ключ елемента, в другому - значення
    друк символ.другий + "\n";
}
```
### Підключення файлів
Файли можна підключати один в одний за допомогою директиви "**імпорт**", за яким слідує назва файлу у вигляді літеральної строки.

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
1. С++ компілятор g++ версії 8.4.0+ або сумісний.
2. Для тестів треба встановити фреймворк Google Test. [Інструкція на GitHub](https://github.com/google/googletest/blob/main/googletest/README.md)

## Установка
1. Клонуйте репозиторій із сирцевим кодом:

`
git clone git@github.com:patronik/mefodij.git
`

2. Перейдіть в папку з кодом.
3. Для побудови інтерпритатора виконайте команду:

`
g++ -g $(find ./src -type f -iregex ".*\.cpp" ! -name "test.cpp") -o build/mefodij
`

4. Для побудови тестів виконайте команду:

`
g++ -g $(find ./src -type f -iregex ".*\.cpp" ! -name "main.cpp") -lgtest -lpthread -o build/test
`

## Запуск програми
Для запуску програми збережіть її у текстовий файл. Потім виконайте наступну команду:

`./build/mefodij -f "code.txt"`

Також можна виконати код переданий через параметр -r

`./build/mefodij -r "друк \"привіт світ\";"`

## Тестування
Для запуску юніт тестів виконайте команду:

`./build/test`

## Примітки
Ідея створення полягала у полегшені навчання програмуванню дітей і дорослих, які не володіють англійською мовою в достатній мірі. Форки вітаються. При находжені багів або рекомендацій можна писати на vasyl.voina@gmail.com

