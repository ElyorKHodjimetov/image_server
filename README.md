# Image HTTP Server

📷 HTTP-сервер на C++, который принимает PNG/JPEG изображение, обрезает его **по вертикали** (оставляя левую часть) и возвращает обратно в том же формате.

## 🛠 Технологии

- C++17
- [httplib.h](https://github.com/yhirose/cpp-httplib) — встроенный HTTP-сервер
- [OpenCV 4](https://opencv.org/) — для обработки изображений
- CMake — для сборки
- [vcpkg](https://github.com/microsoft/vcpkg) — менеджер библиотек

## 🚀 Как запустить

### Зависимости

- CMake >= 3.10
- vcpkg (установлен и интегрирован)
- Visual Studio 2022 (или другой C++ компилятор)

### Установка зависимостей

```sh
vcpkg install opencv4:x64-windows
```

### Сборка проекта

```sh
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=D:/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build . --config Release
```

### Запуск

```sh
cd build/bin/Release
./image_server.exe
```

Сервер будет слушать `http://localhost:8080`.

## 📡 API

### `GET /ping`

Проверка живости сервера:

```sh
curl http://localhost:8080/ping
# → pong
```

### `POST /process`

Принимает PNG или JPEG изображение. Возвращает **левую половину** изображения в том же формате.

**Пример:**

```sh
curl -X POST http://localhost:8080/process      -H "Content-Type: image/png"      --data-binary "@image.png"      --output left.png
```

## 📂 Структура

```
image_server/
├── libs/          ← httplib.h
├── src/           ← исходники (main.cpp)
├── img/           ← тестовые картинки
├── build/         ← папка сборки (в .gitignore)
├── CMakeLists.txt
└── README.md
```


