#include <string>
using std::string;

class Student
{
protected:
  string firstName;
  string lastName;
  string course;

public:
  Student()
  {
    firstName = '\0';
    lastName = '\0';
    course = '\0';
  }
  Student(const std::string &firstN, const std::string &lastN, const std::string &courseStudent)
  {
    firstName = firstN;
    lastName = lastN;
    course = courseStudent;
  }
  string getFirstName() { return firstName; }
  string getLastName() { return lastName; }
  string getCourse() { return course; }
  virtual double getFinalAverage() const = 0;
  virtual int getFinalExam() const = 0;
  virtual string getFullName() const = 0;
};

class Computer_Science : public Student
{
public:
  Computer_Science(const string &firstName, const string &lastName, const string &course,
                   double programAverage, int test1, int test2, int finalExam)
      : Student(firstName, lastName, course), programAverage(programAverage),
        test1(test1), test2(test2), finalExam(finalExam) {}
  virtual double getFinalAverage() const override
  {
    return 0.3 * programAverage + 0.2 * test1 + 0.2 * test2 + 0.3 * finalExam;
  }
  int getFinalExam() const override
  {
    return finalExam;
  }
  string getFullName() const override
  {
    return firstName + " " + lastName;
  }

private:
  double programAverage;
  int test1;
  int test2;
  int finalExam;
};
class Theater : public Student
{
public:
  Theater(const string &firstName, const string &lastName, const string &course,
          int participation, int midterm, int finalExam)
      : Student(firstName, lastName, course), participation(participation),
        midterm(midterm), finalExam(finalExam) {}
  virtual double getFinalAverage() const override
  {
    return 0.4 * participation + 0.25 * midterm + 0.35 * finalExam;
  }
  virtual int getFinalExam() const override
  {
    return finalExam;
  }
  virtual string getFullName() const override
  {
    return firstName + " " + lastName;
  }

private:
  int participation;
  int midterm;
  int finalExam;
};

class Biology : public Student
{
public:
  Biology(const string &firstName, const string &lastName, const string &course,
          int labGrade, int termTest1, int termTest2, int termTest3, int finalExam)
      : Student(firstName, lastName, course), labGrade(labGrade), termTest1(termTest1),
        termTest2(termTest2), termTest3(termTest3), finalExam(finalExam) {}
  virtual double getFinalAverage() const override
  {
    return ((0.3 * labGrade) + (0.15 * termTest1) + (0.15 * termTest2) + (0.15 * termTest3) + (0.25 * finalExam));
  }
  virtual int getFinalExam() const override
  {
    return finalExam;
  }
  virtual string getFullName() const override
  {
    return firstName + " " + lastName;
  }

private:
  int labGrade;
  int termTest1;
  int termTest2;
  int termTest3;
  int finalExam;
};

class StudentList
{
public:
  StudentList();
  ~StudentList();
  bool ImportFile(const char *fileName);
  bool CreateReportFile(const char *filename) const;
  void ShowList() const;
  void printStudentsByCourse(const string &course, std::ofstream &outputFile) const;
  void displaySummary();
  void printGradeDistribution(std::ofstream &outputFile) const;

private:
  int totalStudents;
  int index;
  int additionalInput;
  Student **students;
};