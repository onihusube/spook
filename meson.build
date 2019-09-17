project('spook', 'cpp', default_options : ['warning_level=3', 'werror=true', 'cpp_std=c++17'], meson_version : '>=0.50.0')

doctest_proj = subproject('doctest')
doctest_dep = doctest_proj.get_variable('doctest_dep')

cppcompiler = meson.get_compiler('cpp').get_argument_syntax()

if cppcompiler == 'msvc'
    options = ['/std:c++latest', '/source-charset:utf-8']
    #VSプロジェクトに編集しうるファイルを追加する
    files = ['test/spook_test.cpp', 'include/spook.hpp', 'test/testheader/cmath_test.hpp', 'test/testheader/bit_test.hpp']
elif cppcompiler == 'gcc'
    options = ['-std=c++2a']
    files = ['test/spook_test.cpp']
else
    options = []
    files = ['test/spook_test.cpp']
endif

include_dir = include_directories('include', 'test/testheader', 'subprojects/doctest')

exe = executable('spook_test', files, include_directories : include_dir, cpp_args : options, dependencies : doctest_dep, install : true)