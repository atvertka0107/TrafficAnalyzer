# infotecs test-task
В проекте включает в себя: программу написаную на C++ и программу использующую Python. Первая программа(application_1) на C+, предназначенна для анализа сетефого трафика и класификации пакетов к конкретному потоку. Вторая программа(application_2) выполняет постобработку выходного файла. Её суть заключается в анализе входящего и исходящего трафика для каждого IP-адреса. Ниже приведён список зависимостей необходимых для сборки программы на C++, а также будет размещена инструкция по сборке.

## application_1(C++) 

### Зависимости
- CMake (>= 3.10)
- libpcap 

### Установка зависимостей
- **Debuan/Ubuntu**
```bash
sudo apt update
sudo apt install libpcap-dev
```

### Инструкция по сборке application_1
```
cd application_1
mkdir build
cd build
cmake ..
make
# to run programm use this command:
./application_1 <input_file.pcap> <output_file.csv>
```

## application_2(Python)
В данной программе используются стандартные библиотеки, поэтому не нужно дополнительно устанавливать никаких зависимостей.

### Запуск программы
```
cd application_2
python3 application_2.py <input_file.csv> <output_file.csv>
```