/*
PHYS30762 Assignment 2

Program to compute mean, standard deviation and standard
error of the a set of courses. Data is read from file

Author: Labeebah Islaam 10453447
Date: 18/02/2022
*/

#include<iostream>
#include<iomanip>
#include<fstream>
#include<vector>
#include<string>
#include<regex>
#include<sstream>
#include<cmath>

// "\courselist.txt"

struct course {
    float mark{};
    int code{};
    std::string title;
};

bool check_true_false() {
    // Return true for 'y', false for 'n', otherwise reprompt for input
    std::string input;
    bool input_ok = false;
    bool repeat{};

    std::getline(std::cin, input);

    while (input_ok == false) {
        if (std::regex_match(input, std::regex("^(y|Y|yes)$")) == true) {
            repeat = true;
            input_ok = true;
        }
        else if (std::regex_match(input, std::regex("^(n|N|no)$")) == true) {
            repeat = false;
            input_ok = true;
        }
        else {
            std::cout << "Invalid input. Answer with 'y' or 'n':";
            std::getline(std::cin, input);
        }
    }
    return repeat;
}

std::string copy_file(std::string file_name) {
    std::ifstream original_file(file_name);
    std::ofstream copy_file(file_name.substr(0, file_name.size() - 4) + "_new.txt");

    copy_file << original_file.rdbuf();
    std::cout << "File copied successfully" << std::endl;
    return file_name.substr(0, file_name.size() - 4) + "_new.txt";
}

float mean(std::vector<float> numbers) {
    float sum = 0; // Only one decimal place in course marks
    for (int i = 0; i < numbers.size(); i++) {
        sum += numbers[i];
    }
    return sum / numbers.size();
}

double standard_dev(std::vector<float> numbers) {
    double sum = 0;
    for (int i = 0; i < numbers.size(); i++) {
        sum += pow(double(numbers[i] - mean(numbers)), 2);
    }
    return sqrt((1. / (numbers.size() - 1.)) * sum);
}

std::vector<course> get_course_data(std::vector<std::string> file_data,
    std::string subject = "PHYS") {
    // Print courses and save marks, course codes and titles in their correct format
    std::vector<course> course_data;
    float course_mark;
    int course_code;
    std::string course_title;

    for (auto iterate = std::begin(file_data); iterate != std::end(file_data); iterate++) {
        std::istringstream ss(*iterate);

        ss >> course_mark >> course_code;
        std::getline(ss, course_title); // Read until EOL, store in course_title

        // Print e.g "PHYS 30762 Object-Oriented Programming in C++"
        std::cout << std::fixed << std::setprecision(1);
        std::cout << course_mark << " " << subject << " " << course_code;
        std::cout << " " << course_title << std::endl;
        course_data.push_back({ course_mark, course_code, course_title });
    }
    return course_data;
}

std::vector<float> get_course_marks(std::vector<course> courses) {
    // Retrieve marks from vector of course struct
    std::vector<float> marks;
    for (int i = 0; i < courses.size(); i++) {
        marks.push_back(courses[i].mark);
    }
    return marks;
}

void print_average_marks(std::vector<float> course_marks) {
    std::cout << "The average mark is " << std::fixed << std::setprecision(1) << mean(course_marks); // 1 decimal
    std::cout << " +/- " << standard_dev(course_marks) / sqrt(course_marks.size());
    std::cout << ", with standard deviation " << standard_dev(course_marks) << std::endl;
}

bool compare_marks(course course_1, course course_2) {
    if (course_1.code < course_2.code) {
        return true;
    } 
    else{
        return false;
    }
}

bool compare_titles(course course_1, course course_2) {
    if (course_1.title < course_2.title) { // Requires input to be in title case already
        return true;
    }
    else {
        return false;
    }
}

std::vector<course> sort_list(std::vector<course> course_list, std::string subject = "PHYS") {
    // Give user option to sort list by course code or by title
    std::cout << "Sort by ascending course code? (y/n): ";
    if (check_true_false() == true) {
       std::sort(course_list.begin(), course_list.end(), compare_marks);
       for (int i = 0; i < course_list.size(); i++) {
           std::cout << std::fixed << std::setprecision(1);
           std::cout << course_list[i].mark << " " << subject << " " << course_list[i].code;
           std::cout << " " << course_list[i].title << std::endl;
       }
    }

    else {
        std::cout << "Sort by title? (y/n): ";
        if (check_true_false() == true) {
            std::sort(course_list.begin(), course_list.end(), compare_titles);
            for (int i = 0; i < course_list.size(); i++) {
                std::cout << std::fixed << std::setprecision(1);
                std::cout << course_list[i].mark << " " << subject << " " << course_list[i].code;
                std::cout << " " << course_list[i].title << std::endl;
            }
        }
    }
    return course_list;
}


int main()
{
    std::fstream input_file;
    std::string file_name = "C:\\Users\\Student\\Downloads\\courselist.txt", temp_input;
    std::string modified_file_name;
    std::vector<std::string> file_data;
    std::vector<course> file_courses;
    std::vector<course> searched_courses;
    std::vector<float> file_marks; // List of numerical marks to calculate with
    std::vector<float> searched_courses_marks;
    std::string subject = "PHYS";
    bool repeat = true;
    char year{};

    std::cout << "Enter the name of the file, e.g 'data.txt': ";
    std::cin >> file_name;
    input_file.open(file_name);
    while (!input_file.good()) {
        std::cerr << "File could not be found. Re-enter file name, or paste file path: ";
        std::cin >> file_name;
        input_file.open(file_name);
    }

    while (std::getline(input_file, temp_input)) {
        file_data.push_back(temp_input);
    }
    input_file.close();

    file_courses = get_course_data(file_data);
    file_marks = get_course_marks(file_courses);
    std::cout << "\nThere are " << file_data.size() << " courses in this file." << std::endl;
    print_average_marks(file_marks);

    std::cout << "\nCreate a copy of the file to modify? (y/n): ";
    if (check_true_false() == true) {
        modified_file_name = copy_file(file_name);
    }
    else {
        std::cout << "File not copied.";
        modified_file_name = file_name;
    }

    std::cout << "\nEnter a new course? (y/n): ";
    if (check_true_false() == true) {
        while (!repeat == false) {
            std::cout << "Please enter course details in the format 'course mark', 'course code,";
            std::cout << "'course title', separated by spaces: ";

            while (std::getline(std::cin, temp_input)) {
                std::istringstream ss(temp_input);
                course input_course;

                if (ss >> input_course.mark >> input_course.code >> input_course.title) {
                    if (input_course.mark <= 100.0) {
                        input_file.open(modified_file_name, std::ios_base::app); // Appending to file
                        input_file << "\n" << ss.str();
                        input_file.close();
                        file_data.emplace_back(ss.str());
                        file_courses.push_back({ input_course.mark, input_course.code, 
                            input_course.title });
                        file_marks.push_back(input_course.mark);

                        std::cout << "Course added to " << modified_file_name << std::endl;
                        print_average_marks(file_marks);
                        std::cout << "Add another course? (y/n): ";
                        repeat = check_true_false();
                        break;
                    }
                }
                else {
                    std::cout << "Input was not in the required format. Try again? (y/n): ";
                    repeat = check_true_false();
                    break;
                }
            }
        }
    }

    file_courses = sort_list(file_courses);

    std::cout << "\nSearch courses by year? (y/n): ";
    if (check_true_false() == true) {
        std::cout << "Enter year 1, 2, 3 or 4: ";
        std::cin >> year;

        for (int i = 0; i < file_courses.size(); i++) {
            if (std::to_string(file_courses[i].code)[0] == year) {
                searched_courses.push_back(file_courses[i]);
                std::cout << std::fixed << std::setprecision(1);
                std::cout << file_courses[i].mark << " " << subject << " " << file_courses[i].code;
                std::cout << " " << file_courses[i].title << std::endl;
            }
        }
        std::cout << "\nThere are " << searched_courses.size() << " courses in this year. ";
        searched_courses_marks = get_course_marks(searched_courses);
        print_average_marks(searched_courses_marks);

    }

    return 0;
}
