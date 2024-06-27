#pragma once

class Text {
private:
    char* text;
public:
    Text();
    Text(char* text);
    ~Text();
    char* getText() const;
};