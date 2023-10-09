# author: GuoKunchang

project('alg', 'cpp',
  version: '0.1',
  default_options: [
    'cpp_std=c++20',
    'warning_level=everything',
    'werror=true',
    'b_sanitize=address,undefined,thread,memory,leak',
    'buildtype=debug'])

# include
inc_dir = 'include/'

# library
sort_dir = 'sort/'
search_dir = 'search/'
graph_dir = 'graph/'
string_dir = 'string/'
time_dir = 'time/'
random_dir = 'random/'

alg_lib = shared_library('alg', 
  inc_dir + time_dir + 'timer.hpp',
  inc_dir + random_dir + 'random.hpp',
  inc_dir + sort_dir + 'common.hpp',
  inc_dir + sort_dir + 'selection.hpp',
  inc_dir + sort_dir + 'insertion.hpp',
  inc_dir + sort_dir + 'shell.hpp',
  inc_dir + sort_dir + 'merge.hpp',
  inc_dir + sort_dir + 'quick.hpp',
  inc_dir + 'BST.hpp')

# tests
test_dir = 'tests/'
gtest_dep = dependency('gtest')

selection_test_exe = executable('selection_test', 
  test_dir + 'selection_test.cpp', 
  include_directories: inc_dir,
  link_with: alg_lib,
  dependencies: gtest_dep)
test('selection_test', selection_test_exe)

insertion_test_exe = executable('insertion_test', 
  test_dir + 'insertion_test.cpp', 
  include_directories: inc_dir,
  link_with: alg_lib,
  dependencies: gtest_dep)
test('insertion_test', insertion_test_exe)

BST_test_exe = executable('BST_test', 
  test_dir + 'BST_test.cpp', 
  include_directories: inc_dir,
  link_with: alg_lib,
  dependencies: gtest_dep)
test('BST_test', BST_test_exe)

shell_test_exe = executable('shell_test', 
  test_dir + 'shell_test.cpp', 
  include_directories: inc_dir,
  link_with: alg_lib,
  dependencies: gtest_dep)
test('shell_test', shell_test_exe)

merge_test_exe = executable('merge_test', 
  test_dir + 'merge_test.cpp', 
  include_directories: inc_dir,
  link_with: alg_lib,
  dependencies: gtest_dep)
test('merge_test', merge_test_exe)

quick_test_exe = executable('quick_test', 
  test_dir + 'quick_test.cpp', 
  include_directories: inc_dir,
  link_with: alg_lib,
  dependencies: gtest_dep)
test('quick_test', quick_test_exe)

# mytest_exe = executable('mytest', 
#   test_dir + 'mytest.cpp',
#   dependencies: gtest_dep)
# test('mytest', mytest_exe)


# apps
