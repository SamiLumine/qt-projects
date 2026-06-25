# Qt Learning Projects

Personal practice projects to learn the Qt framework, following the KDAB course series.

Starting with **Qt Widgets**, then moving on to **Qt Quick / QML**.

---

## Projects

### Qt Widgets

| # | Project | Description | Concepts |
|---|---------|-------------|----------|
| 01 | [Stopwatch](./stopwatch/) | First steps in Qt — a stopwatch app built while learning the object model, signals & slots, and the event system *(KDAB Part 1)* | QWidget, QTimer, Signals & Slots, Lambdas, Event System, Layouts |
| 02 | [Editor](./editor/) | A minimal text editor built with Qt Designer — open, edit and save text files via a menu bar *(KDAB Part 2)* | Qt Designer, QMainWindow, QPlainTextEdit, QFileDialog, File I/O, Custom Classes |
| 03 | [Contact Manager](./contact-manager/) | A very simple contact list manager — add and delete contacts through modal dialogs with input validation *(KDAB Parts 3 & 4)* | QDialog, QListWidget, QInputMask, QValidator, QPointer, QComboBox, QMessageBox, SizePolicy |
| 04 | [Log Book](./logbook/) | A minimalist personal diary app — write dated entries with a mood, search through them with regex, and persist them to a file *(KDAB Part 5)* | QString, QRegularExpression, QFile, QTextStream, QVariant, QMap, QList (Container Classes) |
| 05 | [Analog Clock](./analog-clock/) | A custom-painted analog clock — draws a live clock face with tick marks, hands entirely in code, no Designer *(KDAB Part 6)* | QPainter, QPen, QBrush, QColor, Coordinate Transformation, QTimer |

---

## Build

Open the project in **Qt Creator**, select the **Release** configuration
(bottom left), then press `Ctrl+B`.

### Windows — Deploy

From a terminal with Qt in the PATH:

```bash
windeployqt .\build\{release-directory}\{file.exe}
```

## Download

→ [Releases](https://github.com/SamiLumine/qt-projects/releases) 

---

## Course

[Introduction to Qt Widgets — KDAB on Qt Academy](https://academy.qt.io)

Also available as a [70-video YouTube playlist](https://www.youtube.com/watch?v=g7yijWiZTmI&list=PL6CJYn40gN6iFcTyItvnE5nOmJR8qk_7o)

| Part | Focus | Videos |
|------|-------|--------|
| [Part 1](https://academy.qt.io/content-details/326726295/2) | Qt Object Model, Signals & Slots, Event System | #1 – #12 |
| [Part 2](https://academy.qt.io/content-details/327186613/2) | Qt Designer, UI ↔ C++ binding, Layouts, Custom Widgets | #13 – #19 |
| [Part 3](https://academy.qt.io/content-details/327304348/2) | Common Widgets, Layout Management (stretch, size hints, size policy), Custom Widgets, Input Validation, Resources | #20 – #28 |
| [Part 4](https://academy.qt.io/content-details/327503906/2) | Modal & Modeless Dialogs, Premade Dialogs, QMainWindow (menus, toolbars, docking widgets) | #29 – #31 |
| [Part 5](https://academy.qt.io/content-details/327503906/2) | QString, QRegularExpression, Container Classes, File Handling, QVariant, Properties + Qt vs STL containers & implicit sharing | #32 – #37 + [extra 1](https://www.youtube.com/watch?v=d3EX9bVFW-E&list=PL6CJYn40gN6jrZFWcB1HK5cJ_nvViBuRu&index=1) [extra 2](https://www.youtube.com/watch?v=sBxE3QraKMw&list=PL6CJYn40gN6jrZFWcB1HK5cJ_nvViBuRu&index=2) |
| [Part 6](https://academy.qt.io/content-details/327503906/2) | Painting Basics, Color Handling, Color Themes & Palettes, Painting Operations, Coordinate Transformation, QFontMetrics, Printing | #38 – #45 |

---

## Stack

- Qt 6
- C++17
- CMake
- Qt Creator