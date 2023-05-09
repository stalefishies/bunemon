#include "common.hpp"

const wchar_t  CLASS_NAME[] = L"Bunemon";
const wchar_t WINDOW_NAME[] = L"Bunemon";

HWND window;
WindowSizes size;

String::String(void):
    length(0), data(NULL) {}

String::String(size_t length, const char *data):
    length(length), data(data) {}

//String::String(size_t length, const char *data) {
//    this->set(length, data);
//}
//
//void String::set(size_t length, const char *data) {
//    std::memset(this->data, 0, 255);
//    this->length = (length > 254 ? 254 : length);
//
//    for (int i = 0; i < this->length; ++i) {
//        if (!data[i]) { break; }
//        this->data[i] = data[i];
//    }
//}

char String::operator [](const int index) { return data[index]; }

bool operator ==(const String& a, const String &b) {
    if (a.length != b.length) { return false; }

    for (int i = 0; i < a.length; ++i) {
        if (a.data[i] != b.data[i]) { return false; }
    } 

    return true;
}

bool operator ==(const String& a, const char *b) {
    for (int i = 0; i < a.length; ++i) {
        if (!b[i] || a.data[i] != b[i]) { return false; }
    } 

    return !b[a.length];
}

bool operator ==(const char   *a, const String& b) { return  (b == a); }
bool operator !=(const String& a, const String &b) { return !(a == b); }
bool operator !=(const String& a, const char   *b) { return !(a == b); }
bool operator !=(const char   *a, const String& b) { return !(b == a); }
