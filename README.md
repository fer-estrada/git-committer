# git committer (WIP)

small CLI tool written in C to automate common git operations. more features to be added

## installation
### prerequisites
 * git
 * C compiler of your choice

### installing

first clone this repo down using your preferred method, then cd into it

then just run
```
mkdir build
make
sudo make install
```
and you're done

## usage

you need to be in a directory that already has a git repository set up, then just type the command
```
git_commit
```

## notes

 * the git repository already needs to be initialized and have its remote configured
 * you also need to already have the proper credentials set up for pushing, the program won't ask for your git user.email and user.name

## contributing

free to do whatever you want

## license

MIT
