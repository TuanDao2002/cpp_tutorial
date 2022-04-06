#include <iostream>
#include <fstream>
#include <sstream>

class Student{
    private:
        std::string studentID;
        std::string* name;

    public:
        void mem_request_for_name(){
            name = new (std::nothrow) std::string;
            if (name == NULL) {
                std::cerr << "Cannot allocate for name\n";
            }
        }

        Student(){
            mem_request_for_name();
        }

        Student(std::string studentID, std::string name) {
            mem_request_for_name();
            this->studentID = studentID;
            this->name = new std::string(name);
        }

        Student(const Student& s){ 
            // can access private variables
            this->name = new std::string(*s.name);
            this->studentID = s.studentID;
        }

        Student operator = (const Student& s){ 
            // can access private variables
            this->name = new std::string(*s.name);
            this->studentID = s.studentID;

            return *this;
        }

        void showInfo() {
            std::cout << "Student ID: " << studentID << std::endl
                      << "Name: " << *name << std::endl;
        }

        std::string getName() {
            return *this->name;
        }

        ~Student() {
            delete name;
        }
};

class Course{
    private:
        std::string courseID;
        std::string* name;
        int credit;

    public:
        void mem_request_for_name(){
            name = new (std::nothrow) std::string;
            if (name == NULL) {
                std::cerr << "Cannot allocate for name\n";
            }
        }

        Course(){
            mem_request_for_name();
        }

        Course(std::string courseID, std::string name, int credit) {
            mem_request_for_name();
            this->courseID = courseID;
            this->name = new std::string(name);
            this->credit = credit;
        }

        Course(const Course& c){ 
            // can access private variables
            this->name = new std::string(*c.name);
            this->courseID = c.courseID;
            this->credit = c.credit;
        }

        Course operator = (const Course& c){ 
            // can access private variables
            this->name = new std::string(*c.name);
            this->courseID = c.courseID;
            this->credit = c.credit;

            return *this;
        }

        void showInfo() {
            std::cout << "Course ID: " << courseID << std::endl
                      << "Name: " << *name << std::endl
                      << "Credit: " << credit << std::endl;
        }

        std::string getName() {
            return *this->name;
        }

        ~Course(){
            delete name;
        }
};

class Enrollment{
    private:
        Student student;
        Course course;
        std::string semester;

    public:
        Enrollment(){}

        Enrollment(Student student, Course course, std::string semeser){
            this->student = student;
            this->course = course;
            this->semester = semeser;
        }

        Student getStudent() {
            return this->student;
        }

        Course getCourse() {
            return this->course;
        }

        void showInfo() {
            std::cout << "Enrollment's info: \n";
            student.showInfo();
            std::cout << "\n";
            course.showInfo();
            std::cout << "\n";
            std::cout << "Semester: " << semester << "\n\n";
        }
};

int main(){
    Student s1 = Student("s3877347", "Dao Kha Tuan");
    Course c1 = Course("cosc2482", "SED", 2);
    Enrollment e1 = Enrollment(s1, c1, "2022A");
    e1.showInfo();

    Enrollment* enrollment_arr = new (std::nothrow) Enrollment[5];

    std::ifstream infile("default.csv");
    std::string line;
    std::string temp_sid, temp_student_name, temp_cid, temp_course_name, temp_credit, temp_sem;

    int indx = 0;
    while (std::getline(infile, line)) {
        // use stringstream as local variable to assign attributes for different lines
        std::stringstream ss(line);
			
        std::getline(ss, temp_sid, ',');			
        std::getline(ss, temp_student_name, ',');

        std::getline(ss, temp_cid, ',');
        std::getline(ss, temp_course_name, ',');


        std::getline(ss, temp_credit, ',');
        std::getline(ss, temp_sem, ',');

        Student s = Student(temp_sid, temp_student_name);
        Course c = Course(temp_cid, temp_course_name, stoi(temp_credit));

        enrollment_arr[indx] = Enrollment(s, c, temp_sem);
        indx++;
    }

    std::string course_name;
    std::cout << "Enter a the name of the course: " << std::endl;
    std::getline(std::cin, course_name);

    bool empty = true;
    std::cout << "\nList of enrollments in the course: " << std::endl;
    for (int i = 0; i < 5; i++) {
        if (enrollment_arr[i].getCourse().getName() == course_name) {
            std::cout << "-----------------\n\n";
            enrollment_arr[i].showInfo();
            empty = false;
        }
    }

    if (empty) {
        std::cout << "The course list is empty!!!" << std::endl;
    }

    delete[] enrollment_arr;
    infile.close();
    return 0;
}