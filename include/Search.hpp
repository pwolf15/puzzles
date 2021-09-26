#pragma once

#include <functional>
#include <string>
#include <vector>

int bsearch(int t, const std::vector<int>& A);

struct Student
{
  std::string name;
  double grade_point_average;
};

const static std::function<bool(const Student&, const Student&)> CompGPA =
    [](const Student& a, const Student& b)
{
  if (a.grade_point_average != b.grade_point_average)
  {
    return a.grade_point_average > b.grade_point_average;
  }
  return a.name < b.name;
};

bool SearchStudent(
  const std::vector<Student>& students, const Student& target,
  const std::function<bool(const Student&, const Student&)>& comp_GPA);

int bsearch_iter(std::vector<int>::iterator begin, std::vector<int>::iterator end, int k);

int SearchFirstOfK(std::vector<int>& A, int k);