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
# include directory
# subdir('include')

#=== tests ===
# test directory
subdir('tests')

