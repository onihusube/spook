project('spook', 'cpp', default_options : ['warning_level=3', 'werror=true', 'cpp_std=c++2a'])

include_dir = include_directories('include', 'test/testheader', 'doctest')
exe = executable('spook_test', 'test/spook_test.cpp', include_directories : include_dir, cpp_args : ['-std=c++2a', '-Wextra'])