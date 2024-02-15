inc_dir = '../include/'

#=== applications

bits_dump_exe = executable('bits_dump', 'bits_dump.cpp')

huffman_exe = executable('huffman', 'huffman.cpp',
  include_directories: inc_dir)

in_exe = executable('in',
  'in.cpp',
  include_directories: inc_dir,
  dependencies: libalg_dep)

out_exe = executable('out',
  'out.cpp',
  include_directories: inc_dir,
  dependencies: libalg_dep)


