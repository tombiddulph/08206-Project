# Task List


### Connor :
  - Temperature sensor
  - LCD panel
  - Sounder

  
### Tom :
 - Real time clock
 - Input switches
 - I/O ports







To check code in

```sh
$ git a . #if this fails use git add -a -F
$ git status # check the files have been added 
$ git push
```

```sh
$ git branch # check which branch you're woking on
```

To switch branches
```sh
$ git checkout -b <branch name>
```

Branching strategy

  -  Merge the master branch into your branch
  ```sh
  $ git fetch
  $ git rebase origin/master
  ```
  
  See this post for explanation - https://stackoverflow.com/questions/7200614/how-to-merge-remote-master-to-local-branch

 - Merge your branch into master
 
  -  Merge the master branch into your branch
  ```sh
	$ git checkout master
    $ git pull origin master
	$ git merge test
	$ git push origin master
  ```

