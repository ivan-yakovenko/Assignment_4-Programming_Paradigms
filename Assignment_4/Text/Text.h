#pragma once

class Text {
private:
    char* text;
public:
    Text();
    Text(char* text);
    Text(const Text& other);
    Text operator=(char element);
    ~Text();
    char* getText() const;
};