# sub include directories
sort_dir = 'sort/'
search_dir = 'search/'
graph_dir = 'graph/'
string_dir = 'string/'
time_dir = 'time/'
random_dir = 'random/'

# build library
libalg = shared_library('libalg', 
  # time
  time_dir + 'timer.hpp',
  random_dir + 'random.hpp',
  # sort
  sort_dir + 'common.hpp',
  sort_dir + 'selection.hpp',
  sort_dir + 'insertion.hpp',
  sort_dir + 'shell.hpp',
  sort_dir + 'merge.hpp',
  sort_dir + 'quick.hpp',
  sort_dir + 'heap.hpp',
  sort_dir + 'common.hpp',
  # search
  search_dir + 'bst.hpp',
  search_dir + 'llrb.hpp',
  search_dir + 'seperate_chaining.hpp',
  search_dir + 'linear_probing.hpp',
  # graph
  graph_dir + 'graph.hpp',
  graph_dir + 'dfs.hpp',
  graph_dir + 'bfs.hpp',
  graph_dir + 'cc.hpp',
  graph_dir + 'digraph.hpp',
  graph_dir + 'directed_dfs.hpp',
  graph_dir + 'directed_bfs.hpp',
  graph_dir + 'directed_cycle.hpp',
  graph_dir + 'scc.hpp',
)

# declare dependency
# libalg_dep = declare_dependency(include_directories: inc_dir, link_with: libalg)
