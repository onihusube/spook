project('spook', 'cpp', default_options : ['warning_level=3', 'werror=true', 'cpp_std=c++17'])

cppc = meson.get_compiler('cpp').get_argument_syntax()

if cppc == 'msvc'
    options = ['/std:c++latest', '/source-charset:utf-8']
elif cppc == 'gcc'
    options = ['-std=c++2a']
else
    std_ver = []
    options = []
endif

include_dir = include_directories('include', 'test\\testheader', 'doctest')

exe = executable('spook_test', 'test/spook_test.cpp', include_directories : include_dir, cpp_args : options)