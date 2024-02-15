# sub include directories
sort_dir = 'sort/'
search_dir = 'search/'
graph_dir = 'graph/'
string_dir = 'string/'
time_dir = 'time/'
random_dir = 'random/'
string_dir = 'string/'
io_dir = 'IO/'

# build library
libalg = shared_library('libalg', 
  # IO
  io_dir + 'bitstream.hpp',

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

  # string
  string_dir + 'huffman.hpp',
)

