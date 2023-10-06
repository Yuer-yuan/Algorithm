project('alg', 'cpp',
  version: '0.1',
  default_options: [
    'cpp_std=c++20',
    'warning_level=3',
    'b_sanitize=address'])

# include
inc_dir = 'include/'

# library
sort_dir = 'sort/'
search_dir = 'search/'
graph_dir = 'graph/'
string_dir = 'string/'
time_dir = 'time/'

alg_lib = shared_library('alg', 
  inc_dir + time_dir + 'timer.hpp',
  inc_dir + sort_dir + 'selection.hpp',
  inc_dir + sort_dir + 'insertion.hpp',
  inc_dir + 'BST.hpp')

# tests
test_dir = 'tests/'
gtest_dep = dependency('gtest')

selection_test_exe = executable('selection_test', 
  test_dir + 'selection_test.cpp', 
  include_directories: inc_dir,
  link_with: alg_lib,
  dependencies: gtest_dep)

insertion_test_exe = executable('insertion_test', 
  test_dir + 'insertion_test.cpp', 
  include_directories: inc_dir,
  link_with: alg_lib,
  dependencies: gtest_dep)

BST_test_exe = executable('BST_test', 
  test_dir + 'BST_test.cpp', 
  include_directories: inc_dir,
  link_with: alg_lib,
  dependencies: gtest_dep)

mytest_exe = executable('mytest', 
  test_dir + 'mytest.cpp',
  dependencies: gtest_dep)

test('selection_test', selection_test_exe)
test('insertion_test', insertion_test_exe)
test('BST_test', BST_test_exe)
test('mytest', mytest_exe)


# apps
