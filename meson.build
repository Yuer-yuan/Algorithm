project('alg', 'cpp',
  version: '0.1',
  default_options: [
    'cpp_std=c++20',
    'warning_level=3',
    'b_sanitize=address,undefined',
    'buildtype=debug'],
)

# include
inc_dir = 'include/'

# library
sort_dir = inc_dir + 'sort/'
search_dir = inc_dir + 'search/'
graph_dir = inc_dir + 'graph/'
string_dir = inc_dir + 'string/'
time_dir = inc_dir + 'time/'
random_dir = inc_dir + 'random/'

alg_lib = shared_library('alg', 
  time_dir + 'timer.hpp',
  random_dir + 'random.hpp',
  sort_dir + 'common.hpp',
  sort_dir + 'selection.hpp',
  sort_dir + 'insertion.hpp',
  sort_dir + 'shell.hpp',
  sort_dir + 'merge.hpp',
  sort_dir + 'quick.hpp',
  sort_dir + 'heap.hpp',
  sort_dir + 'common.hpp',
  search_dir + 'bst.hpp',
  search_dir + 'llrb.hpp',
  search_dir + 'seperate_chaining.hpp',
  search_dir + 'linear_probing.hpp',
  graph_dir + 'graph.hpp',
  graph_dir + 'dfs.hpp',
)

# tests
test_dir = 'tests/'
gtest_dep = dependency('gtest')

selection_test_exe = executable('selection_test', 
  test_dir + 'selection_test.cpp', 
  include_directories: inc_dir,
  link_with: alg_lib,
  dependencies: gtest_dep,
)
test('selection_test', selection_test_exe)

insertion_test_exe = executable('insertion_test', 
  test_dir + 'insertion_test.cpp', 
  include_directories: inc_dir,
  link_with: alg_lib,
  dependencies: gtest_dep)
test('insertion_test', insertion_test_exe)

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

heap_test_exe = executable('heap_test', 
  test_dir + 'heap_test.cpp', 
  include_directories: inc_dir,
  link_with: alg_lib,
  dependencies: gtest_dep)
test('heap_test', heap_test_exe)

bst_test_exe = executable('bst_test', 
  test_dir + 'bst_test.cpp', 
  include_directories: inc_dir,
  link_with: alg_lib,
  dependencies: gtest_dep)
test('bst_test', bst_test_exe)

llrb_test_exe = executable('llrb_test', 
  test_dir + 'llrb_test.cpp', 
  include_directories: inc_dir,
  link_with: alg_lib,
  dependencies: gtest_dep
)
test('llrb_test', llrb_test_exe)

seperate_chaining_test_exe = executable('seperate_chaining_test', 
  test_dir + 'seperate_chaining_test.cpp', 
  include_directories: inc_dir,
  link_with: alg_lib,
  dependencies: gtest_dep
)
test('seperate_chaining_test', seperate_chaining_test_exe)

linear_probing_test_exe = executable('linear_probing_test', 
  test_dir + 'linear_probing_test.cpp', 
  include_directories: inc_dir,
  link_with: alg_lib,
  dependencies: gtest_dep
)
test('linear_probing_test', linear_probing_test_exe)

graph_test_exe = executable('graph_test',
  test_dir + 'graph_test.cpp',
  include_directories: inc_dir,
  link_with: alg_lib,
  dependencies: gtest_dep
)
test('graph_test', graph_test_exe)

dfs_test_exe = executable('dfs_test',
  test_dir + 'dfs_test.cpp',
  include_directories: inc_dir,
  link_with: alg_lib,
  dependencies: gtest_dep
)
test('dfs_test', dfs_test_exe)
# apps
