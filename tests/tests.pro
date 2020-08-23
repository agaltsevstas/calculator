TARGET = tests
TEMPLATE = app
CONFIG += c++17
CONFIG -= app_bundle
CONFIG -= qt

DESTDIR = $$PWD/../bin/

#Отключить "теневую сборку" в криейторе!
CONFIG(release, debug|release)
{
message(Project $$TARGET (Release))

OBJECTS_DIR = build/
MOC_DIR = build/
RCC_DIR = build/
UI_DIR = build/
}

CONFIG(debug, debug|release)
{
message(Project $$TARGET (Debug))

OBJECTS_DIR = build/
MOC_DIR = build/
RCC_DIR = build/
UI_DIR = build/
DEFINES += DEBUG_BUILD
}

INCLUDEPATH += ../include/
HEADERS += \
    ../include/calculator.h \

SOURCES += \
    ../src/calculator.cpp \
    calculator_test.cpp

# Boost and common
LIBS += -L/usr/lib/x86_64-linux-gnu \
        -lboost_unit_test_framework
