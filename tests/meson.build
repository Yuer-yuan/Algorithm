#=== unit tests ===
inc_dir = '../include'
gtest_dep = dependency('gtest')

# sort tests
selection_test_exe = executable('selection_test', 
  'selection_test.cpp', 
  include_directories: inc_dir,
  dependencies: gtest_dep,
)
test('selection_test', selection_test_exe)

insertion_test_exe = executable('insertion_test', 
  'insertion_test.cpp', 
  include_directories: inc_dir,
  dependencies: gtest_dep)
test('insertion_test', insertion_test_exe)

shell_test_exe = executable('shell_test', 
  'shell_test.cpp', 
  include_directories: inc_dir,
  dependencies: gtest_dep)
test('shell_test', shell_test_exe)

merge_test_exe = executable('merge_test', 
  'merge_test.cpp', 
  include_directories: inc_dir,
  dependencies: gtest_dep)
test('merge_test', merge_test_exe)

quick_test_exe = executable('quick_test', 
  'quick_test.cpp', 
  include_directories: inc_dir,
  dependencies: gtest_dep)
test('quick_test', quick_test_exe)

heap_test_exe = executable('heap_test', 
  'heap_test.cpp', 
  include_directories: inc_dir,
  dependencies: gtest_dep)
test('heap_test', heap_test_exe)

# search tests
bst_test_exe = executable('bst_test', 
  'bst_test.cpp', 
  include_directories: inc_dir,
  dependencies: gtest_dep)
test('bst_test', bst_test_exe)

llrb_test_exe = executable('llrb_test', 
  'llrb_test.cpp', 
  include_directories: inc_dir,
  dependencies: gtest_dep
)
test('llrb_test', llrb_test_exe)

seperate_chaining_test_exe = executable('seperate_chaining_test', 
  'seperate_chaining_test.cpp', 
  include_directories: inc_dir,
  dependencies: gtest_dep
)
test('seperate_chaining_test', seperate_chaining_test_exe)

linear_probing_test_exe = executable('linear_probing_test', 
  'linear_probing_test.cpp', 
  include_directories: inc_dir,
  dependencies: gtest_dep
)
test('linear_probing_test', linear_probing_test_exe)

# graph tests
graph_test_exe = executable('graph_test',
  'graph_test.cpp',
  include_directories: inc_dir,
  dependencies: gtest_dep
)
test('graph_test', graph_test_exe)

dfs_test_exe = executable('dfs_test',
  'dfs_test.cpp',
  include_directories: inc_dir,
  dependencies: gtest_dep
)
test('dfs_test', dfs_test_exe)

bfs_test_exe = executable('bfs_test',
  'bfs_test.cpp',
  include_directories: inc_dir,
  dependencies: gtest_dep
)
test('bfs_test', bfs_test_exe)

cc_test_exe = executable('cc_test',
  'cc_test.cpp',
  include_directories: inc_dir,
  dependencies: gtest_dep
)
test('cc_test', cc_test_exe)

digraph_test_exe = executable('digraph_test',
  'digraph_test.cpp',
  include_directories: inc_dir,
  dependencies: gtest_dep
)
test('digraph_test', graph_test_exe)

directed_cycle_test_exe = executable('directed_cycle_test',
  'directed_cycle_test.cpp',
  include_directories: inc_dir,
  dependencies: gtest_dep
)
test('directed_cycle_test', directed_cycle_test_exe)

topological_test_exe = executable('topological_test',
  'topological_test.cpp',
  include_directories: inc_dir,
  dependencies: gtest_dep
)
test('topological_test', topological_test_exe)

# other tests
# mytest_exe = executable('mytest',
#   'mytest.cpp',
#   include_directories: inc_dir,
#   dependencies: gtest_dep
# )
# test('mytest', mytest_exe)
