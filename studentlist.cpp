#include "studentlist.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
void displayMenu();
std::string concatenateStrings(const std::string &str1, const std::string &str2);
int main()
{
    char fName[21];
    char lName[21];
    StudentList s;

    displayMenu();
    char choice = '\0';
    int population;
    const char *inputFile;

    while (toupper(choice) != 'Q')
    {
        cin >> choice;
        if (toupper(choice) == 'I')
        {
            string filePath;
            cout << "Enter the name of the filename: ";
            cin.ignore();
            getline(cin, filePath);
            while (filePath.size() > 30 || filePath.size() < 0)
            {
                cout << "Invalid file name size, please re-enter: ";
                getline(cin, filePath);
            }
            inputFile = filePath.c_str();
            s.ImportFile(inputFile);
            displayMenu();
        }
        if (toupper(choice) == 'S')
        {
            s.ShowList();
            displayMenu();
        }
        if (toupper(choice) == 'E')
        {
            string outputName;
            cout << "Please enter a name for your output File \n";
            cin >> outputName;
            s.CreateReportFile(outputName.c_str());
            displayMenu();
        }
        if (toupper(choice) == 'M')
        {
            displayMenu();
        }
        if (toupper(choice) == 'Q')
        {
        }
    }
}

StudentList::StudentList()
{
    index = 0;
    totalStudents = 0;
    additionalInput = 0;
    students = nullptr;
}

bool StudentList::ImportFile(const char *fileName)
{
    std::ifstream in1;
    in1.open(fileName);
    if (!in1)
    {
        cout << "Sorry, invalid filename entered.\n";
        return false;
    }
    else
    {
        int population;
        string fName;
        string lName;
        string major;
        string major_extend;
        in1 >> population;

        if (additionalInput > 0)
        {
            int oldStudents = totalStudents; // 2
            totalStudents += population;     // 6
            Student **moreStudents = new Student *[totalStudents];
            for (int i = 0; i < oldStudents; i++)
            {
                moreStudents[i] = students[i];
            }

            students = moreStudents;

            for (int i = oldStudents; i < totalStudents; i++)
            {
                in1.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(in1, lName, ',');
                in1 >> std::ws;
                std::getline(in1, fName);
                in1 >> major;
                if (major == "Biology")
                {
                    int labGrade, termTest1, termTest2, termTest3, finalExam;
                    in1 >> labGrade >> termTest1 >> termTest2 >> termTest3 >> finalExam;

                    students[i] = new Biology(fName, lName, major, labGrade, termTest1, termTest2, termTest3, finalExam);
                }
                else if (major == "Theater")
                {
                    int participation, midterm, finalExam;
                    in1 >> participation >> midterm >> finalExam;

                    students[i] = new Theater(fName, lName, major, participation, midterm, finalExam);
                }
                else if (major == "Computer")
                {
                    in1 >> major_extend;

                    double programAverage;
                    int pr1, pr2, pr3, pr4, pr5, pr6, test1, test2, finalExam;
                    in1 >> pr1 >> pr2 >> pr3 >> pr4 >> pr5 >> pr6;
                    programAverage = ((pr1 + pr2 + pr3 + pr4 + pr5 + pr6) / 6);
                    in1 >> test1 >> test2 >> finalExam;

                    students[i] = new Computer_Science(fName, lName, major, programAverage, test1, test2, finalExam);
                }
            }

            return true;
        }
        else
        {
            totalStudents += population;
            ++additionalInput;
            students = new Student *[totalStudents];

            for (int i = 0; i < totalStudents; i++)
            {
                in1.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(in1, lName, ',');
                in1 >> std::ws;
                std::getline(in1, fName);
                in1 >> major;
                if (major == "Biology")
                {
                    int labGrade, termTest1, termTest2, termTest3, finalExam;
                    in1 >> labGrade >> termTest1 >> termTest2 >> termTest3 >> finalExam;

                    students[i] = new Biology(fName, lName, major, labGrade, termTest1, termTest2, termTest3, finalExam);
                }
                else if (major == "Theater")
                {
                    int participation, midterm, finalExam;
                    in1 >> participation >> midterm >> finalExam;

                    students[i] = new Theater(fName, lName, major, participation, midterm, finalExam);
                }
                else if (major == "Computer")
                {
                    in1 >> major_extend;
                    double programAverage;
                    int pr1, pr2, pr3, pr4, pr5, pr6, test1, test2, finalExam;
                    in1 >> pr1 >> pr2 >> pr3 >> pr4 >> pr5 >> pr6;
                    programAverage = ((pr1 + pr2 + pr3 + pr4 + pr5 + pr6) / 6);
                    in1 >> test1 >> test2 >> finalExam;

                    students[i] = new Computer_Science(fName, lName, major, programAverage, test1, test2, finalExam);
                }
            }
        }
        in1.close();
        return true;
    }
}

void StudentList::ShowList() const
{
    cout << std::left << std::setw(30) << "Last" << std::setw(30) << "First"
         << "Course\n\n";
    cout << std::left;
    for (int i = 0; i < totalStudents; i++)
    {
        cout << std::setw(30) << students[i]->getLastName() << std::setw(30)
             << students[i]->getFirstName() << students[i]->getCourse() << "\n\n";
    }
}

bool StudentList::CreateReportFile(const char *filename) const
{
    std::ofstream outputFile(filename);
    if (!outputFile)
    {
        cout << "Error creating file: " << filename << std::endl;
        return false;
    }
    outputFile << "Student Grade Summary\n---------------------\n\n";
    outputFile << "BIOLOGY CLASS"
               << "\n\n";
    outputFile << std::left << std::setw(40) << "Student" << std::setw(7) << "Final" << std::setw(8) << "Final" << std::setw(8) << "Letter" << std::endl;
    outputFile << std::left << std::setw(40) << "Name" << std::setw(7) << "Exam" << std::setw(8) << "Avg" << std::setw(8) << "Grade" << std::endl;
    outputFile << "----------------------------------------------------------------------\n";
    printStudentsByCourse("Biology", outputFile);
    outputFile << "\n";
    outputFile << "THEATER CLASS"
               << "\n\n";
    outputFile << std::left << std::setw(40) << "Student" << std::setw(7) << "Final" << std::setw(8) << "Final" << std::setw(8) << "Letter" << std::endl;
    outputFile << std::left << std::setw(40) << "Name" << std::setw(7) << "Exam" << std::setw(8) << "Avg" << std::setw(8) << "Grade" << std::endl;
    outputFile << "----------------------------------------------------------------------\n";
    printStudentsByCourse("Theater", outputFile);
    outputFile << "\n";
    outputFile << "COMPSCI CLASS"
               << "\n\n";
    outputFile << std::left << std::setw(40) << "Student" << std::setw(7) << "Final" << std::setw(8) << "Final" << std::setw(8) << "Letter" << std::endl;
    outputFile << std::left << std::setw(40) << "Name" << std::setw(7) << "Exam" << std::setw(8) << "Avg" << std::setw(8) << "Grade" << std::endl;
    outputFile << "----------------------------------------------------------------------\n";
    printStudentsByCourse("Computer", outputFile);

    printGradeDistribution(outputFile);

    outputFile.close();
    return true;
}
char getLetterGrade(double average)
{
    if (average >= 90)
    {
        return 'A';
    }
    else if (average >= 80)
    {
        return 'B';
    }
    else if (average >= 70)
    {
        return 'C';
    }
    else if (average >= 60)
    {
        return 'D';
    }
    else
    {
        return 'F';
    }
}
void StudentList::printStudentsByCourse(const string &course, std::ofstream &outputFile) const
{

    for (int i = 0; i < totalStudents; ++i)
    {
        if (students[i]->getCourse() == course)
        {
            outputFile << std::left << std::setw(40) << students[i]->getFullName();
            outputFile << std::setw(7) << students[i]->getFinalExam();
            outputFile << std::setw(8) << std::fixed << std::setprecision(2) << students[i]->getFinalAverage();
            outputFile << std::setw(8) << getLetterGrade(students[i]->getFinalAverage()) << std::endl;
        }
    }
    outputFile << std::endl;
}

void StudentList::printGradeDistribution(std::ofstream &outputFile) const
{
    int numAs = 0, numBs = 0, numCs = 0, numDs = 0, numFs = 0;

    for (int i = 0; i < totalStudents; i++)
    {
        double average = students[i]->getFinalAverage();
        if (average >= 90)
        {
            numAs++;
        }
        else if (average >= 80)
        {
            numBs++;
        }
        else if (average >= 70)
        {
            numCs++;
        }
        else if (average >= 60)
        {
            numDs++;
        }
        else
        {
            numFs++;
        }
    }

    outputFile << "Grade Distribution" << std::endl;
    outputFile << "A: " << numAs << std::endl;
    outputFile << "B: " << numBs << std::endl;
    outputFile << "C: " << numCs << std::endl;
    outputFile << "D: " << numDs << std::endl;
    outputFile << "F: " << numFs << std::endl;
}
std::string concatenateStrings(const std::string &str1, const std::string &str2)
{
    std::string result = str1 + str2;
    return result;
}

StudentList::~StudentList() { delete[] students; }

void displayMenu()
{
    cout << "\n\n\t *** Student List menu *** \t\t\n"
         << "\nI\t Import students from a file"
         << "\nS\t Show student list (brief)\n"
         << "E\t Export a grade report (to file)"
         << "\nM\t Show this menu \nQ\t Quit Program\n";
}
