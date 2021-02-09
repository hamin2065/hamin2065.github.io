---
layout: post
title: Version Control (Hufs Missing Semester)
color: rgb(242,85,44)
tags: [Git, Github, Branch, Checkout]
---

# 버전관리?

1. 버전 관리가 무엇일까
버전 관리(Version Control) : 파일 변화를 시간에 따라 기록하고 나중에 특정 시점의 버전을 꺼내올 수 있는 시스템
버전 관리 시스템의 종류
 - Git
 - Subversion
 - Mercurial 등



2. 사용하는 이유
    : 작업을 하다가 파일을 잃거나 잘못 고쳤을 때 쉽게 복구가 가능하다. 또 기록된 버전마다 어느 부분이 변경되었는지 추적할 수 있고, 협업을 할 때에 누가 언제 만들어낸 것인지 쉽게 확인이 가능하다.

3. 버전 관리 종류

- 로컬 버전 관리(디렉토리로 파일을 복사하는 방법) : 개인의 개발 환경 내에서 사용이 가능하다. 작업한 파일을 삭제하거나 잘못 복사하면 돌이킬 수 없다는 단점이 있다. 
- 중앙집중식 버전 관리 : 파일 관리를 중앙 서버에서 하게 되고 개발자들은 파일을 관리하고 있는 중앙 서버에서 파일들을 내려받아서 사용하는 방법이다. 파일 관리를 모두 중앙 서버에서 하기 때문에 중앙 서버에 문제가 생기면 협업이 제대로 안된다는 단점이 발생한다.
- 분산 버전 관리 : 로컬과 서버에 저장소가 모두 존재한다. 서버에 있는 저장소를 똑같이 로컬에 복제해서 사용하게 되기 때문에 서버에 문제가 생기더라도 로컬 저장소를 이용해서 작업을 진행할 수 있다. 


4. git

: 오픈 소스로 관리되는 분산 버전 관리 시스템이다.


빠른 속도, 단순한 구조, 동시 다발적으로 개발, 완벽한 분산으로 서버측의 저장소와 개발자들의 환경에 저장소가 존재해서 저장소 한 곳에서 복제를 하면 다시 작업이 가능하다. 성능이 우수해서 대형 프로젝트에서도 사용 가능하다.

- - -

# git 입문

## git 저장소 만들기
git이 파일을 관리하기 위해서 저장소에 파일을 추가하고 커밋하는 과정을 거쳐야 한다.
- Windows 기준 생성 폴더 위치
C:\Users\ (유저이름)\hufs-missing-semester
```
md ~/hufs-missing-semester
cd ~/hufs-missing-semester
git init
```
1. `hufs-missing-semester`폴더에 `first.txt`라는 파일을 생성
2. `git add first.txt`의 명령을 통해 생성한 `first.txt`파일을 저장소에 추가
3. `git status` : 명령을 통해서 추가한 파일을 확인한다.
4. `git commit -m "(원하는 메시지)"` : 원하는 메시지를 입력 후 커밋을 한다.
5. `git log` : 커밋 로그를 조회한다.
 
## Github
: 온라인 git 저장소이다.

- 다른 사람에게 공개되는 public과 지정한 사람에게만 공개되는 private 저장소를 생성할 수 있다. 
- Organization기능이 지원되기 때문에 여러 사람들과 한 공간에서 프로젝트를 진행할 수 있다.



# Github과 로컬 저장소를 연결

## Github에 커밋 push 하기

1. `github`->`repository`-> `new`버튼을 누르고 `my first repository`라는 이름의 저장소를 만든다.
2.  만든 저장소의 url을 복사한다.
3.  `git remote add origin (복사한 url)` : origin 이름으로 로컬 저장소를 github 저장소에 연결한다.
4.  `git push origin main` : 깃헙의 저장소에 푸시를 한다.
5. 유저 네임과 비밀번호를 입력한다. (비밀번호는 보안유지를 위해 화면에 출력되지 않는다.)
6. github repository에 내용이 올라간 것을 확인한다.

> - 4번 과정에서 에러가 뜨는 경우
> ```
> error: src refspec main does not match any
> error: failed to push some refs to '(깃헙 저장소 url)'
> ```
> 해당 에러는 깃허브에서 pull 없이 push할 경우 기존 내용을 삭제하거나 하는 문제가 생길 수 있기 때문에 이런 문제를 피하고자 에러 메시지를 발생시키는  것이다. 
> 
> 해결방법 : 
>
> 1. `git init`
> 2. `git add .`
> 3. `git commit -m "(commit message)"`
> 4. `git config user.name "(User name)"`
> 5. `git config user.email "(User email)"`
> 6. `git remote add origin "(github repository url)"`
> 7. `git push -u origin master`


## 원격저장소에서 새로운 내용 가져오기

1. github repository에서 `create new file`을 누르고 `new_file.txt`라는 파일을 생성한 후 내용을 작성하고 `commit new file`을 눌러 새로운 파일을 만든다. (이 파일은 깃헙 저장소에서 생성되었기 때문에 로컬 저장소에는 반영되지 않았다.)
2. `git pull` : remote 저장소 내용을 가져온다.
3. `git log` : new_file.txt가 로컬 저장소에 반영되었는지 확인한다.

## 다른 프로젝트 가져오기
1. 자신이 원하는 디렉토리로 이동한다.
2. `git clone (가져오고자 하는 github repository url)` : 커맨드를 입력하면 경로에 프로젝트의 이름으로 폴더가 생기고 내부에 프로젝트 정보들이 생긴다.

- - -

# git 브랜치 사용

## 여러 명이서 작업한다면?
- 서로 다른 두 명의 개발자가 같은 이름의 다른 파일을 작업하는 경우에 깃헙 저장소에 푸시를 하면 충돌이 발생한다.
- 나눠서 작업하는 경우 예전 파일에 문제가 생겨서 복구를 할 때에 그 중간에 추가한 파일들의 작업이 날라가는 문제가 발생한다.

## Branch와 Checkout

1. `git branch develop` : develop이라는 브랜치 생성
 -> git이 가리키는 위치(HEAD)에서 branch가 생성된다.
2. `git checkout develop` : checkout을 통해 브랜치간의 전환이 일어나게 한다.  -> HEAD(현재 git이 가리키는 위치)가 develop으로 전환된다.
3. `git log` : HEAD가 develop으로 전환되는 것을 확인한다.

## 다른 브랜치로 코드 합치기
1. hufs-missing-semester 폴더에 file2.txt를 추가한다.
2. `git add file2.txt`
3. `git commit -m "(commit message)"`
4. `git push origin develop`
5. 깃헙에 들어가서 `pull request`를 누르고 `new pull request`를 눌러준다.
6. Comparing changes에서 `base:main <- compare:develop`이 되게 설정해준다.(base : 어느 브랜치에 합칠지, compare : 어느 브랜치를)
7. `create pull request` 버튼을 눌러준다.
8. pull request에 대해서 제목과 내용을 작성하고 다시 `create pull request`를 누른다.
9. `Merge pull request`를 눌러 main브랜치로 합쳐준다.

