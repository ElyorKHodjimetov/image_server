# Image Server

**Image Server** — легковесный HTTP-сервер на C++, который принимает PNG/JPEG изображение, обрезает его **по вертикали** (оставляя левую половину) и возвращает обратно в том же формате.

---

## 📋 Содержание

- [Технологии](#-технологии)
- [Требования](#-требования)
- [Установка зависимостей](#-установка-зависимостей)
- [Сборка](#-сборка)
- [Запуск](#-запуск)
- [API](#-api)
- [Структура проекта](#-структура-проекта)


---

## 🛠 Технологии

- **C++17**
- [cpp-httplib](https://github.com/yhirose/cpp-httplib) — встроенный HTTP-сервер без внешних зависимостей
- [OpenCV 4](https://opencv.org/) — библиотека для работы с изображениями
- [CMake](https://cmake.org/) — система сборки
- [vcpkg](https://github.com/microsoft/vcpkg) — менеджер пакетов для C++

---

## 🔍 Требования

- CMake ≥ 3.10
- vcpkg (установлен и интегрирован в CMake)
- Компилятор с поддержкой C++17 (Visual Studio 2022, GCC, Clang и т.д.)

---

## 📦 Установка зависимостей

С помощью vcpkg установите OpenCV:

```sh
vcpkg install opencv4:x64-windows

```

---

## ⚙️ Сборка

1. Клонировка репозитория и переход в папку проекта:
   ```sh
   git clone https://github.com/username/image_server.git
   cd image_server
   ```
2. Создание и переход в папку сборки:
   ```sh
   mkdir build && cd build
   ```
3. Конфигурация CMake с указанием vcpkg toolchain:
   ```sh
   cmake .. -DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake
   ```
4. Сборка в Release-режиме:
   ```sh
   cmake --build . --config Release
   ```

---

## ▶️ Запуск

По умолчанию исполняемый файл `image_server.exe` создаётся в папке `build/bin/Release`:

```sh
cd build/bin/Release
./image_server.exe
```

После запуска сервер слушает по адресу `http://localhost:8080`.

---

## 📡 API

### `GET /ping`
Проверка доступности сервера.

```sh
curl http://localhost:8080/ping
# → pong
```

---

### `POST /process`
Принимает PNG или JPEG изображение в теле запроса и возвращает **левую половину** изображения в том же формате.

- **Content-Type**: `image/png` или `image/jpeg`
- **Тело запроса**: бинарный файл
- **Ответ**: бинарное изображение

**Пример с curl:**
```sh
curl -X POST http://localhost:8080/process \
     -H "Content-Type: image/png" \
     --data-binary @img/input.png \
     -o img/left_output.png
```

---

## 📂 Структура проекта

```
image_server/
├── libs/                 # сторонние заголовочные библиотеки (httplib.h)
├── src/                  # исходники (main.cpp)
├── img/                  # тестовые изображения
├── build/                # артефакты сборки (игнорируется Git)
├── CMakeLists.txt        # настройки сборки
└── README.md             # документация проекта
```

---
