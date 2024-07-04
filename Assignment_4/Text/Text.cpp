#include <iostream>
#include "Text.h"

Text::Text() {
    this->text = nullptr;
}
Text::Text(char *text) {
    this->text = new char[strlen(text)+1];
}

Text::Text(const Text &other) {
    this->text = new char[strlen(other.text) + 1];
}

Text Text::operator=(char element) {
    delete[] text;
    text = new char[2];
    text[0] = element;
    text[1] = '\0';
    return *this;
}

Text::~Text() {
    delete[] text;
}

char *Text::getText() const {
    return text;
}
