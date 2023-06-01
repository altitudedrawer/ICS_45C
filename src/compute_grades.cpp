#include <compare>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>

#include "compute_grades.hpp"

void Student::validate() const {
    
    for (int num : quiz) {
        if (num < 0 || num > 100) throw std::domain_error("Error: invalid percentage " + std::to_string(num));
    }
    for (int num : hw) {
        if (num < 0 || num > 100) throw std::domain_error("Error: invalid percentage " + std::to_string(num));
    }
    if (final_score < 0 || final_score > 100) throw std::domain_error("Error: invalid percentage " + std::to_string(final_score));
}

void Student::compute_grade() {

    compute_quiz_avg();
    compute_hw_avg();
    compute_course_score();
    if (course_score >= 97 && course_score <= 100) {
        course_grade = "A+";
    } else if (course_score >= 93 && course_score <= 96) {
        course_grade = "A";
    } else if (course_score >= 90 && course_score <= 92) {
        course_grade = "A-";
    } else if (course_score >= 87 && course_score <= 89) {
        course_grade = "B+";
    } else if (course_score >= 83 && course_score <= 86) {
        course_grade = "B";
    } else if (course_score >= 80 && course_score <= 82) {
        course_grade = "B-";
    } else if (course_score >= 77 && course_score <= 79) {
        course_grade = "C+";
    } else if (course_score >= 73 && course_score <= 76) {
        course_grade = "C";
    } else if (course_score >= 70 && course_score <= 72) {
        course_grade = "C-";
    } else if (course_score >= 67 && course_score <= 69) {
        course_grade = "D+";
    } else if (course_score >= 63 && course_score <= 66) {
        course_grade = "D";
    } else if (course_score >= 60 && course_score <= 62) {
        course_grade = "D-";
    } else {
        course_grade = "F";
    }
}

std::strong_ordering Student::operator<=>(const Student& other) const {

    auto last_name_comparison = last_name <=> other.last_name;
    if (last_name_comparison != 0) return last_name_comparison;
    return first_name <=> other.first_name;
}

bool Student::operator==(const Student& other) const {

    return (quiz == other.quiz) && (hw == other.hw) && (final_score == other.final_score);
}

std::istream& operator>>(std::istream& in, Student& s) {

    // TODO implement this you lazy ass motherfucker

    std::string label;
    std::string line;
    while (std::getline(in, line)) {
        std::istringstream iss(line);
        iss >> label;
        if (label == "Name") {
            iss >> s.first_name;
            if (iss) s.last_name = "";
            std::string word;
            bool first = true;
            while (iss >> word) {
                if (!first) {
                    s.last_name += " ";
                }
                else {
                    first = false;
                }
                s.last_name += word;
            }
        }
        if (label == "Final") {
            iss >> s.final_score;
        }
        if (label == "Quiz") {
            int num;
            while (iss >> num) {
                s.quiz.push_back(num);
            }
        }
        if (label == "HW") {
            int num;
            while (iss >> num) {
                s.hw.push_back(num);
            }
        }
    }
    if (s.quiz.empty()) s.quiz_avg = 0.0;
    if (s.hw.empty()) s.hw_avg = 0.0;
    return in;
}

std::ostream& operator<<(std::ostream& out, const Student& s) {

    out << std::setw(8) << std::left << "Name: " << s.first_name << " " << s.last_name << "\n";
    out << std::setw(8) << std::left << "HW Ave: " << s.hw_avg << "\n";
    out << std::setw(8) << std::left << "QZ Ave: " << s.quiz_avg << "\n";
    out << std::setw(8) << std::left << "Final: " << s.final_score << "\n";
    out << std::setw(8) << std::left << "Total: " << s.course_score << "\n";
    out << std::setw(8) << std::left << "Grade: " << s.course_grade << "\n";
    return out;
}

void Student::compute_quiz_avg() {

    if (quiz.empty()) {
        quiz_avg = 0.0;
    }
    else if (quiz.size() == 1) {
        quiz_avg = quiz.front();
    }
    else {
        int min = *std::min_element(quiz.begin(), quiz.end());
        int sum = std::accumulate(quiz.begin(), quiz.end(), 0, [min](int acc, int num) {
            return acc + (num == min ? 0 : num);
        });
        int count = quiz.size() - 1;
        quiz_avg = static_cast<double>(sum) / count;
    }
}

void Student::compute_hw_avg() {

    if (hw.empty()) {
        hw_avg = 0.0;
    }
    else if (hw.size() == 1) {
        hw_avg = hw.front();
    }
    else {
        int sum = std::accumulate(hw.begin(), hw.end(), 0);
        hw_avg = static_cast<double>(sum) / hw.size();
    }
}

void Student::compute_course_score() {
    
    course_score = static_cast<int>(std::round(0.4 * quiz_avg + 0.3 * hw_avg + 0.3 * final_score));
}

// TODO implement the Gradebook class below

void Gradebook::compute_grades() {

    std::for_each(students.begin(), students.end(), [](Student& student) {student.compute_grade();});
}

void Gradebook::sort() {

    std::sort(students.begin(), students.end());
}

void Gradebook::validate() const{

    std::for_each(students.begin(), students.end(), [](const Student& student) {student.validate();});
}

std::istream& operator>>(std::istream& in, Gradebook& b) {
    
    std::copy(std::istream_iterator<Student>(in), std::istream_iterator<Student>(), std::back_inserter(b.students));
    return in;
}

std::ostream& operator<<(std::ostream& out, const Gradebook& b) {
    
    std::copy(b.students.begin(), b.students.end(), std::ostream_iterator<Student>(out, "\n"));
    return out;
}
