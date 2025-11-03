#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits> 
using namespace std;
class Student {
private:
    string surname;
    bool needsDormitory;
    int workExperience;
    bool workedAsTeacher;
    string graduatedFrom;
    string languageStudied;

public:
    // Конструкторы
    Student();
    Student(const string& surname, bool needsDorm, int experience,
        bool workedTeacher, const string& graduated, const string& language);
    Student(const Student& other);

    
    string getSurname() const { return surname; }
    bool getNeedsDormitory() const { return needsDormitory; }
    int getWorkExperience() const { return workExperience; }
    bool getWorkedAsTeacher() const { return workedAsTeacher; }
    string getGraduatedFrom() const { return graduatedFrom; }
    string getLanguageStudied() const { return languageStudied; }

    void setSurname(const string& s) { surname = s; }
    void setNeedsDormitory(bool needs) { needsDormitory = needs; }
    void setWorkExperience(int exp) { workExperience = exp; }
    void setWorkedAsTeacher(bool worked) { workedAsTeacher = worked; }
    void setGraduatedFrom(const string& grad) { graduatedFrom = grad; }
    void setLanguageStudied(const string& lang) { languageStudied = lang; }

    
    bool hasTeachingExperience(int minYears = 2) const;
    bool graduatedFromPedagogicalCollege() const;
    void displayInfo() const;

    //перегруженные операции
    Student& operator=(const Student& other);
    friend ostream& operator<<(ostream& os, const Student& student);
    friend istream& operator>>(istream& is, Student& student);

    //операции сравнения
    bool operator==(const Student& other) const;
    bool operator!=(const Student& other) const;
    bool operator>(const Student& other) const;

    //арифметические операции
    Student operator+(int years);
    Student operator+(const string& newLanguage);
};

// Реализация конструкторов
Student::Student() : surname(""), needsDormitory(false), workExperience(0),
workedAsTeacher(false), graduatedFrom(""), languageStudied("") {
}

Student::Student(const string& surname, bool needsDorm, int experience,
    bool workedTeacher, const string& graduated, const string& language)
    : surname(surname), needsDormitory(needsDorm), workExperience(experience),
    workedAsTeacher(workedTeacher), graduatedFrom(graduated), languageStudied(language) {
}

Student::Student(const Student& other)
    : surname(other.surname), needsDormitory(other.needsDormitory),
    workExperience(other.workExperience), workedAsTeacher(other.workedAsTeacher),
    graduatedFrom(other.graduatedFrom), languageStudied(other.languageStudied) {
}

// Реализация методов
bool Student::hasTeachingExperience(int minYears) const {
    return workedAsTeacher && workExperience >= minYears;
}

bool Student::graduatedFromPedagogicalCollege() const {
    return graduatedFrom == "педучилище" || graduatedFrom == "педагогический колледж";
}

void Student::displayInfo() const {
    cout << "Фамилия: " << surname << "\n";
    cout << "Нуждается в общежитии: " << (needsDormitory ? "Да" : "Нет") << "\n";
    cout << "Стаж работы: " << workExperience << " лет\n";
    cout << "Работал учителем: " << (workedAsTeacher ? "Да" : "Нет") << "\n";
    cout << "Окончил: " << graduatedFrom << "\n";
    cout << "Изучаемый язык: " << languageStudied << "\n";
}

// Реализация перегруженных операций
Student& Student::operator=(const Student& other) {
    if (this != &other) {
        surname = other.surname;
        needsDormitory = other.needsDormitory;
        workExperience = other.workExperience;
        workedAsTeacher = other.workedAsTeacher;
        graduatedFrom = other.graduatedFrom;
        languageStudied = other.languageStudied;
    }
    return *this;
}

ostream& operator<<(ostream& os, const Student& student) {
    os << student.surname << " (" << student.languageStudied << ") - "
        << student.workExperience << " лет стажа";
    return os;
}

// Реализация оператора ввода
istream& operator>>(istream& is, Student& student) {
    cout << "Введите данные студента:\n";

    cout << "Фамилия: ";
    is >> student.surname;

    cout << "Нуждается в общежитии (1 - да, 0 - нет): ";
    int dorm;
    is >> dorm;
    student.needsDormitory = (dorm == 1);

    cout << "Стаж работы (лет): ";
    is >> student.workExperience;

    cout << "Работал учителем (1 - да, 0 - нет): ";
    int teacher;
    is >> teacher;
    student.workedAsTeacher = (teacher == 1);

    is.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Что окончил: ";
    getline(is, student.graduatedFrom);

    cout << "Какой язык изучал: ";
    getline(is, student.languageStudied);

    return is;
}

bool Student::operator==(const Student& other) const {
    return surname == other.surname && workExperience == other.workExperience;
}

bool Student::operator!=(const Student& other) const {
    return !(*this == other);
}

bool Student::operator>(const Student& other) const {
    return workExperience > other.workExperience;
}

Student Student::operator+(int years) {
    Student temp = *this;
    temp.workExperience += years;
    return temp;
}

Student Student::operator+(const string& newLanguage) {
    Student temp = *this;
    if (!temp.languageStudied.empty()) {
        temp.languageStudied += ", " + newLanguage;
    }
    else {
        temp.languageStudied = newLanguage;
    }
    return temp;
}

class StudentGroup {
private:
    vector<Student> students;

public:
    // Конструкторы
    StudentGroup() = default;
    StudentGroup(const vector<Student>& studentsList);

    // Методы для работы с коллекцией
    void addStudent(const Student& student);
    void removeStudent(const string& surname);

    // Требуемые методы по заданию
    int countNeedingDormitory() const;
    vector<Student> getTeachersWithExperience(int minYears = 2) const;
    vector<Student> getPedagogicalCollegeGraduates() const;
    vector<string> getLanguageGroups() const;
    vector<Student> getStudentsByLanguage(const string& language) const;

    // Перегрузка операции индексации
    Student& operator[](size_t index);
    const Student& operator[](size_t index) const;

    // Другие полезные методы
    size_t size() const { return students.size(); }
    void displayAll() const;
};

// Реализация методов StudentGroup
StudentGroup::StudentGroup(const vector<Student>& studentsList)
    : students(studentsList) {
}

void StudentGroup::addStudent(const Student& student) {
    students.push_back(student);
}

void StudentGroup::removeStudent(const string& surname) {
    students.erase(
        remove_if(students.begin(), students.end(),
            [&surname](const Student& s) { return s.getSurname() == surname; }),
        students.end()
    );
}

int StudentGroup::countNeedingDormitory() const {
    int count = 0;
    for (const auto& student : students) {
        if (student.getNeedsDormitory()) {
            count++;
        }
    }
    return count;
}

vector<Student> StudentGroup::getTeachersWithExperience(int minYears) const {
    vector<Student> result;
    for (const auto& student : students) {
        if (student.hasTeachingExperience(minYears)) {
            result.push_back(student);
        }
    }
    return result;
}

vector<Student> StudentGroup::getPedagogicalCollegeGraduates() const {
    vector<Student> result;
    for (const auto& student : students) {
        if (student.graduatedFromPedagogicalCollege()) {
            result.push_back(student);
        }
    }
    return result;
}

vector<string> StudentGroup::getLanguageGroups() const {
    vector<string> languages;
    for (const auto& student : students) {
        string lang = student.getLanguageStudied();
        if (find(languages.begin(), languages.end(), lang) == languages.end()) {
            languages.push_back(lang);
        }
    }
    return languages;
}

vector<Student> StudentGroup::getStudentsByLanguage(const string& language) const {
    vector<Student> result;
    for (const auto& student : students) {
        if (student.getLanguageStudied() == language) {
            result.push_back(student);
        }
    }
    return result;
}

// Перегрузка операции индексации
Student& StudentGroup::operator[](size_t index) {
    if (index >= students.size()) {
        throw out_of_range("Индекс выходит за границы коллекции");
    }
    return students[index];
}

const Student& StudentGroup::operator[](size_t index) const {
    if (index >= students.size()) {
        throw out_of_range("Индекс выходит за границы коллекции");
    }
    return students[index];
}

void StudentGroup::displayAll() const {
    for (size_t i = 0; i < students.size(); ++i) {
        cout << i + 1 << ". " << students[i] << "\n";
    }
}

void demonstrateOperations() {
    cout << "=== ДЕМОНСТРАЦИЯ ПЕРЕГРУЖЕННЫХ ОПЕРАЦИЙ ===\n\n";

    // Создание студентов
    Student s1("Иванов", true, 3, true, "педучилище", "английский");
    Student s2("Петров", false, 1, false, "школа", "немецкий");
    Student s3("Сидорова", true, 5, true, "педучилище", "французский");

    cout << "1. Операция вывода (<<):\n";
    cout << "s1: " << s1 << "\n";
    cout << "s2: " << s2 << "\n";
    cout << "s3: " << s3 << "\n\n";

    cout << "2. Операция присвоения (=):\n";
    Student s4 = s1;
    cout << "s4 (копия s1): " << s4 << "\n\n";

    cout << "3. Операции сравнения:\n";
    cout << "s1 == s4: " << (s1 == s4) << "\n";
    cout << "s1 != s2: " << (s1 != s2) << "\n";
    cout << "s3 > s1 (по стажу): " << (s3 > s1) << "\n\n";

    cout << "4. Арифметические операции:\n";
    Student s5 = s2 + 2; // увеличение стажа
    cout << "s2 + 2 лет стажа: " << s5 << "\n";

    Student s6 = s1 + "испанский"; // добавление языка
    cout << "s1 + 'испанский': " << s6 << "\n\n";
}

void demonstrateInputOutputOperations() {
    cout << "=== ДЕМОНСТРАЦИЯ ОПЕРАТОРОВ ВВОДА/ВЫВОДА ===\n\n";

    Student newStudent;
    cout << "Создание нового студента:\n";
    cin >> newStudent;  //ерегруженный оператор >>

    cout << "\nВведенный студент:\n";
    cout << newStudent << "\n\n";  //перегруженный оператор <<
}

void interactiveDemo() {
    cout << "=== ИНТЕРАКТИВНОЕ ДОБАВЛЕНИЕ СТУДЕНТОВ ===\n\n";

    // УДАЛИТЬ эту группу и использовать ту, что в main
    // StudentGroup group;  ← УБРАТЬ ЭТУ СТРОКУ

    // Вместо этого передаем группу из main как параметр
}

// ИЗМЕНИТЬ функцию, чтобы она принимала группу как параметр
void interactiveDemo(StudentGroup& group) {
    cout << "=== ИНТЕРАКТИВНОЕ ДОБАВЛЕНИЕ СТУДЕНТОВ ===\n\n";

    cout << "Текущий список студентов:\n";
    group.displayAll();
    cout << "\n";

    // пользователь добавляет нового студента
    char choice;
    do {
        cout << "Хотите добавить нового студента? (y/n): ";
        cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            Student newStudent;
            cin >> newStudent;

            group.addStudent(newStudent);
            cout << "Студент добавлен!\n\n";
        }
    } while (choice == 'y' || choice == 'Y');

    cout << "\nИтоговый список студентов:\n";
    group.displayAll();
}

int main() {
    demonstrateOperations();
    demonstrateInputOutputOperations();

    // СОЗДАЕМ ОДНУ группу
    StudentGroup group;

    // СНАЧАЛА добавляем базовых студентов
    group.addStudent(Student("Иванов", true, 3, true, "педучилище", "английский"));
    group.addStudent(Student("Петров", false, 1, false, "школа", "немецкий"));
    group.addStudent(Student("Сидорова", true, 5, true, "педучилище", "французский"));
    group.addStudent(Student("Козлова", true, 2, true, "техникум", "английский"));
    group.addStudent(Student("Смирнов", false, 0, false, "педучилище", "немецкий"));

    // ПЕРЕДАЕМ существующую группу в interactiveDemo
    interactiveDemo(group);

    cout << "=== ИНФОРМАЦИЯ О ГРУППЕ СТУДЕНТОВ ===\n\n";

    cout << "Все студенты:\n";
    group.displayAll();  // Теперь покажет ВСЕХ студентов
    cout << "\n";

    // Остальной код остается без изменений...
    cout << "1. Нуждающихся в общежитии: "
        << group.countNeedingDormitory() << " человек\n\n";

    cout << "2. Студенты с опытом работы учителем (2+ лет):\n";
    auto teachers = group.getTeachersWithExperience();
    for (const auto& teacher : teachers) {
        cout << "   - " << teacher << "\n";
    }
    cout << "\n";

    cout << "3. Окончившие педучилище:\n";
    auto pedGraduates = group.getPedagogicalCollegeGraduates();
    for (const auto& graduate : pedGraduates) {
        cout << "   - " << graduate << "\n";
    }
    cout << "\n";

    cout << "4. Языковые группы:\n";
    auto languages = group.getLanguageGroups();
    for (const auto& language : languages) {
        cout << "   " << language << " язык:\n";
        auto langStudents = group.getStudentsByLanguage(language);
        for (const auto& student : langStudents) {
            cout << "     - " << student.getSurname() << "\n";
        }
    }
    cout << "\n";

    // Демонстрация перегрузки индексации
    cout << "5. Демонстрация перегрузки индексации:\n";
    cout << "   group[0]: " << group[0] << "\n";
    cout << "   group[2]: " << group[2] << "\n";

    group[1] = group[1] + 1; // увеличение стажа
    cout << "   После group[1] = group[1] + 1: " << group[1] << "\n";

    return 0;
}
