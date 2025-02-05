#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <tuple>

struct FullName {
    std::string surname;
    std::string name;
    std::string middlename;

    FullName() = default;
    FullName(const std::string& s, const std::string& n, const std::string& p)
        : surname(s), name(n), middlename(p) {}

    bool operator<(const FullName& other) const {
        return std::tie(surname, name, middlename) < 
               std::tie(other.surname, other.name, other.middlename);
    }

    bool operator==(const FullName& other) const {
        return std::tie(surname, name, middlename) == 
               std::tie(other.surname, other.name, other.middlename);
    }
};

struct GroupNumber {
    int value;
    
    GroupNumber(int v = 0) : value(v) {}
    bool operator<(const GroupNumber& other) const { return value < other.value; }
    bool operator>(const GroupNumber& other) const { return value > other.value; }
    bool operator==(const GroupNumber& other) const { return value == other.value; }
};

struct StudentRecord {
    FullName name;
    GroupNumber group;
    size_t original_line;

    StudentRecord() = default;
    StudentRecord(const FullName& n, GroupNumber g, size_t line)
        : name(n), group(g), original_line(line) {}
};

#endif