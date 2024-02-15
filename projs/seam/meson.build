project('seam', 'cpp',
  default_options: [
    'cpp_std=c++20',
    'warning_level=2',
    'buildtype=debug',
  ],
  )

opencv_dep = dependency('opencv4')
seam_exe = executable('seam', 
  'main.cpp',
  'carver.h',
  dependencies: opencv_dep)
