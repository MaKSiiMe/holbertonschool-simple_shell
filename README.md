:map <F2> i<Esc>:let w=winwidth(0)<CR>:let l=strlen(getline('.'))<CR>:let s=(w-l)/2<CR>:exe "normal " . s . "i "<CR>
