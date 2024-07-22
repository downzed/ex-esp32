# ESP32 Experiments

This repository contains my experiments with the ESP32 microcontroller, utilizing the ESP-IDF framework and the C programming language. 

## Project Description

This project is a collection of various experiments and code snippets that I have worked on with the ESP32. The purpose of these experiments is to explore and understand the capabilities of the ESP32, as well as to get hands-on experience with the ESP-IDF framework and C programming.

## No Contributions

Please note that this repository is for personal use and experimentation. Contributions are not being accepted at this time.

## Repository Structure

The repository is structured as follows:
```
ex-esp32/
├── blink-it/
│ ├── main/
│ │ ├── blink-it.c
│ │ └── ...
│ └── CMakeLists.txt
├── oled-test/
│ ├── main/
│ │ ├── oled-test.c
│ │ └── ...
│ ├── components/
│ │ ├── ssd1306.c
│ │ ├── ssd1306.h
│ │ └── ...
│ └── CMakeLists.txt
└── README.md
```



- **blink-it/**: Contains a simple blinking LED example.
- **oled-test/**: Contains experiments related to OLED/LCD 0.96 display functionality on the ESP32 + external component.
- **README.md**: This file, providing an overview of the repository.

## Getting Started

To get started with these experiments, you will need the following:

1. An ESP32 development board
2. ESP-IDF framework installed on your system
3. A development environment set up for C programming

### Prerequisites

- Ensure you have the [ESP-IDF framework](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html) installed.
- Set up your development environment according to the ESP-IDF documentation.

### Building and Flashing

Each experiment can be built and flashed to the ESP32 using the following commands:

1. **Navigate to the experiment directory.** for example, `blink-it/`.

    ```bash
    cd blink-it
    ```

2. **Configure the project for your ESP32 board.**

    ```bash
    idf.py set-target esp32
    ```

3. **Check the Pin Number**: Before building and flashing, ensure you have the correct pin number associated with the LED. In the `blink` example, the LED pin is defined as follows:

    ```c
    #define BLINK_LED 5
    ```

4. **Build the project**.

    ```bash
    idf.py build
    ```

5. **Flash the project to the ESP32.**

    ```bash
    idf.py -p [PORT] flash
    ```

    Replace `[PORT]` with the serial port connected to your ESP32.

6. **Monitor the output.**

    ```bash
    idf.py -p [PORT] monitor
    ```
    
7. **Combined Flash & Monitor.**

    ```bash
    idf.py -p [PORT] flash monitor
    ``` 

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

## Acknowledgements

- [Espressif Systems](https://www.espressif.com/) for providing the ESP32 and the ESP-IDF framework.
- The open-source community for various libraries and tools.

