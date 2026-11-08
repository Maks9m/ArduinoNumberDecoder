// C++
//
#include <LiquidCrystal.h> // підключаємо бібліотеку для роботи з LCD-дисплеєм 16x2

// Зелений світлодіод — відповідь правильна, червоний — неправильна
const int GREEN_LED = 2; // пін зеленого світлодіода
const int RED_LED = 3; // пін червоного світлодіода

const int BUTTON_ZERO = 4; // пін кнопки, яка вводить біт 0
const int BUTTON_ONE = 5; // пін кнопки, яка вводить біт 1

const int REGISTER_SELECT = 11; // пін RS дисплея
const int ENABLE = 10; // пін E дисплея

// піни лінії даних D4, D5, D6, D7 дисплея
const int DB4 = 9;                              
const int DB5 = 8;
const int DB6 = 7;
const int DB7 = 6;

const int CURSSOR_OFFSSET = 8; // зсув курсора на 8 колонок, щоб друкувати біти після напису Binary:

LiquidCrystal lcd(REGISTER_SELECT, ENABLE, DB4, DB5, DB6, DB7); // створюємо об'єкт дисплея в 4-бітному режимі на цих пінах

int target_number; // загадане число, яке треба перевести в двійкову систему
int entered_value = 0; // число, зібране з бітів, які ввів користувач

const int MAX_BITS = 8; // максимальна кількість бітів, які можна ввести (для чисел від 0 до 255)
int bits_entered = 0; // скільки бітів користувач уже ввів

void setup() // виконується один раз після запуску
{
  pinMode(GREEN_LED, OUTPUT); // пін зеленого світлодіода працює як вихід
  pinMode(RED_LED, OUTPUT); // пін червоного світлодіода працює як вихід
  pinMode(BUTTON_ZERO,INPUT); // пін кнопки 0 працює як вхід
  pinMode(BUTTON_ONE,INPUT); // пін кнопки 1 працює як вхід

  randomSeed(analogRead(A0)); // задаємо зерно генератора шумом з неприєднаного піна A0, щоб число щоразу було інше
  target_number = random(0, 1 << MAX_BITS); // загадуємо число від 0 до 255 (вміщується у 8 бітів)

  lcd.begin(16,2); // ініціалізуємо дисплей: 16 колонок, 2 рядки
  lcd.print("Try making:");
  lcd.print(target_number); // показуємо загадане число
  lcd.setCursor(0, 1); // переходимо на початок другого рядка
  lcd.print("Binary:"); // підпис поля, куди виводитимуться введені біти
  lcd.setCursor(CURSSOR_OFFSSET, 1); // ставимо курсор на колонку 8 — звідси друкуватимуться біти
}

int zero_last = LOW; // попередній стан кнопки 0 — потрібен, щоб ловити момент натискання
int one_last = LOW; // попередній стан кнопки 1 — потрібен, щоб ловити момент натискання

void add_bit(int bit) // додає один введений біт (0 або 1)
{
  lcd.print(bit); // показуємо біт на дисплеї в поточній позиції курсора
  entered_value = entered_value*2 + bit; // зсуваємо зібране число на розряд вліво і дописуємо новий біт у кінець
  bits_entered++; // ще один біт введено
}

void loop() // повторюється безкінечно
{
  int zero_now = digitalRead(BUTTON_ZERO); // читаємо поточний стан кнопки 0
  int one_now = digitalRead(BUTTON_ONE); // читаємо поточний стан кнопки 1
  if (bits_entered < MAX_BITS){ // поки введено менше 8 бітів — приймаємо натискання
    if (zero_now == HIGH && zero_last == LOW){ // кнопку 0 щойно натиснули (була відпущена, стала натиснута)
      add_bit(0); // додаємо біт 0
    }
    zero_last = zero_now; // запам'ятовуємо стан кнопки 0 для наступного проходу loop()

    if (one_now == HIGH && one_last == LOW){ // кнопку 1 щойно натиснули (була відпущена, стала натиснута)
      add_bit(1); // додаємо біт 1
    }
    one_last = one_now; // запам'ятовуємо стан кнопки 1 для наступного проходу loop()
  } else { // усі 8 бітів введено — перевіряємо відповідь
    if (target_number == entered_value){ // зібране число збігається із загаданим?
      digitalWrite(GREEN_LED, HIGH); // вмикаємо зелений світлодіод
    } else {
      digitalWrite(RED_LED, HIGH); // вмикаємо червоний світлодіод
    }
  }
}
