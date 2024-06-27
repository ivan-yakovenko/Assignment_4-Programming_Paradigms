#include <iostream>
#include "Text.h"

Text::Text() {
    this->text = nullptr;
}
Text::Text(char *text) {
    this->text = new char[strlen(text)+1];
    strcpy(this->text, text);
}
Text::~Text() {
    delete[] text;
}

char *Text::getText() const {
    return text;
}