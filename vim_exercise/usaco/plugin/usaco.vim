function USACO_C()
		exec "normal! ggi/*\n"
    exec "normal! iUSER: " . g:USACOUser . "\n"
    exec "normal! iLANG: C\n" 
    exec "normal! iTASK: " . expand("%:t:r") . "\n"
    exec "normal! i*/\n"
"    normal kk
endf

function USACO_PY()
		exec "normal! ggi#/usr/bin/python\n"
		exec "normal! i# coding=utf-8\n\n"
    exec "normal! i#USER: " . g:USACOUser . "\n"
    exec "normal! i#LANG: py\n" 
    exec "normal! i#TASK: " . expand("%:t:r") . "\n"
    normal G
"    normal kk
endf

function USACO_CPP()
		exec "normal! ggi/*\n"
		exec "normal! iUSER: " . g:USACOUser . "\n"
		exec "normal! iLANG: C++\n" 
		exec "normal! iTASK: " . expand("%:t:r") . "\n"
		exec "normal! i*/\n"
		endf

function USACO_PAS()
		exec "normal! ggi{\n"
		exec "normal! iUSER: " . g:USACOUser . "\n"
		exec "normal! iLANG: PASCAL\n" 
		exec "normal! iTASK: " . expand("%:t:r") . "\n"
		exec "normal! i}\n"
endf

if !exists("g:USACOUser")
    echo "usaco.vim: Please set 'g:USACOUser' in your vimrc file."
    finish
else
	  au BufNewFile *.c :call USACO_C()
    au BufNewFile *.{cc,cpp} :call USACO_CPP()
    au BufNewFile *.pas :call USACO_PAS()
    au BufNewFile *.py :call USACO_PY()
endif
