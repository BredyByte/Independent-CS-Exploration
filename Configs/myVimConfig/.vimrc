"" Disable the generation of backup files
set nobackup
set nowritebackup
set noswapfile

" Set the number of spaces for tab indentation
set tabstop=4
set shiftwidth=4
set expandtab

" Enable syntax highlighting
syntax enable

" Enable line numbering
set number

" Show the current cursor position
set ruler

" Enable autosave
set autowrite

" Enable incremental search
set incsearch

" Ignore case when searching
set ignorecase

" Automatically complete commands
set wildmenu

" Display hidden files
set hidden

" Enable mouse support
set mouse=a

" Disable error bells
set noerrorbells
set visualbell

" Enable highlighting of the current line
set cursorline

" Disable automatic line wrapping
set nowrap

" Enable word autocompletion
set complete+=k

" Theme configuration
colorscheme desert

" PlugIns.
" Install the vim-plug plugin manager
if empty(glob('~/.vim/autoload/plug.vim'))
  silent !curl -fLo ~/.vim/autoload/plug.vim --create-dirs \
        \ https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim
  autocmd VimEnter * PlugInstall --sync | source $MYVIMRC
endif

" Define plugins
call plug#begin('~/.vim/plugged')
" NERDTree - file manager
  Plug 'preservim/nerdtree'
call plug#end()


" if vim argc == 0 - open side bar
autocmd StdinReadPre * let s:std_in=1
autocmd VimEnter * if argc() == 0 && !exists('s:std_in') | NERDTree | endif
" ctrl + b open side bar
map <C-b> :NERDTreeToggle<CR>
" short cut to close vim
nnoremap qq :q<CR>
" short cut to save vim file
inoremap <C-s> <Esc>:w<CR>

