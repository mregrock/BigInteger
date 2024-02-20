# Библиотека по реализации длинной арифметики

Бибилотека на с++ для реализации длинного целых и дробных чисел.

# Сборка
Для лучшей перформативности используйте тип сборки Release.
Для тестирования используется открытый репозиторий GoogleTests

Примерный вид сборки проекта
```bash
git clone --recurse-submodules https://github.com/mregrock/BigInteger.git
cd BigInteger
mkdir cmake-build-release
cd cmake-build-release
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```
Установка библиотеки тестирования
```bash
cd tests
cd extern
cd googletest
git clone https://github.com/google/googletest.git googletest
```




# Тестирование
```bash
./tests/tests
```

# Вычисление числа Пи

По умолчанию Precision = 100
```bash
./pi_calculate [PRECISION]
```





