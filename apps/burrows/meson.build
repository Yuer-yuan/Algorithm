project('burrows', 'cpp',
  default_options: [
    'cpp_std=c++20',
    'warning_level=2',
    'buildtype=debug',
  ],
  )

seam_exe = executable('burrows', 
  'burrows_wheeler.cpp',
  'burrows_wheeler.h',
  'circular_suffix_array.h',
  )

hex_dump_exe = executable('hex_dump', 'hex_dump.cpp')
