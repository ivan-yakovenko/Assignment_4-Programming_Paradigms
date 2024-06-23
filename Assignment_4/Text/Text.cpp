#include "Text.h"

Text::Text() {
    text = nullptr;
}
Text::Text(char *text) {
    this->text = text;
}
Text::~Text() {
    delete[] text;
}

char *Text::getText() const {
    return text;
}