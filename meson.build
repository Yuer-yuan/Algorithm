project('libalg', 'cpp',
  version: '0.1',
  default_options: [
    'cpp_std=c++20',
    'warning_level=3',
    'buildtype=debug',
  ],
)

#=== global options ===
# enable sanitizer when debugging
if (get_option('buildtype') == 'debug')
  message('debug mode, sanitizer enabled')
  add_project_arguments('-fsanitize=address,undefined', language: ['cpp'])
  add_project_link_arguments('-fsanitize=address,undefined', language: ['cpp'])
endif

#=== shared library ===
# sub include directories
subdir('include')
inc_dir = 'include'
# declare dependency
libalg_dep = declare_dependency(include_directories: inc_dir, link_with: libalg)

# inc_dir = 'include/'
# sort_dir = inc_dir + 'sort/'
# search_dir = inc_dir + 'search/'
# graph_dir = inc_dir + 'graph/'
# string_dir = inc_dir + 'string/'
# time_dir = inc_dir + 'time/'
# random_dir = inc_dir + 'random/'
# string_dir = inc_dir + 'string/'
# io_dir = inc_dir + 'IO/'


#=== applications ===
subdir('apps')

#=== tests ===
subdir('tests')

