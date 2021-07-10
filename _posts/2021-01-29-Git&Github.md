---
layout: post
title:  "Git & Github"
subtitle:   "깃과 깃허브에 대해 알아보자"
categories:  git&github
tags: Git & Github
---

# Git

 : 분산 버전 관리 시스템 (이때, 버전은 프로그램의 변경 사항을 말한다.)
 
 Git에서는 소스 코드가 변경된 이력을 쉽게 확인할 수 있고 특정 시점에 저장된 버전과 비교하거나 특점 시점으로 되돌아 갈 수 있다.
 
 - 깃을 사용하지 않았을 때 발생할 수 있는 문제들

 ![coding](/assets/img/posts/Git_problem.png)

 1. A는 코드를 구현 완료했지만 B로부터 코드를 공유받지 못해서 프로젝트의 진행이 불가능한 경우

 2. B가 코드를 구현 완료하였지만 A의 코드와 충돌이 일어나서 서로의 코드를 읽어봐야하는 경우 -> 이 과정에서 추가 충돌을 방지하기 위해 C와 D는 A와 B를 기다리는 경우

 3. A, B, C, D는 모든 오류를 고치고 지금까지 코드를 두 번 합칠 때는 문제가 없었지만 세 번째 코드를 합치는 과정에서 에러가 발생, 문제 해결을 위해 이전 코드를 확인하려고 했으나 이전코드들을 과거에 폐기시켜버림

 4. A, B, C, D 모두 코드를 읽어봐야하는 상황이 발생, C가 코드1에 대해서 A에게 질문, 해당 파트는 A가 짠 부분이지만 B와 병합하는 과정에서 수정되어서 둘 다 헷갈림

 -> 이러한 문제를 Git을 통해서 방지를 하고 버전관리를 통해서 작업 일지 기록이나 협업, 백업이 가능해진다.

- - -

# Github 주요 용어 정리

## 1. Repository (저장소)

![coding](/assets/img/posts/Repository.png)

- Local Repository
 : 직접 관리하는 저장소, 내 개인 PC에 저장된다.
- Remote Repository
 : 원격 서버 저장소, 여러 사람과 공유한다.

로컬 저장소에서 작업하던 내용을 원격 저장소에 업로드하고, 원격 저장소에 있는 다른 사람의 코드도 쉽게 불러올 수 있다.

## 2. Commit

![coding](/assets/img/posts/Commit.png)

 : 파일 및 폴더의 추가사항이나 변경사항을 기록하는 것이다.
   Commit은 시간 순으로 저장이 되고 거슬러 올라가면 과거 변경이력와 내용을 확인하는 것이다.

## 3. Stage

![coding](/assets/img/posts/Stage.png)
 
 - Index : 커밋을 통해서 변경사항이 반영되기 전 해당 변경사항들이 저장되는 공간
 - 특정 파일이나 코드를 변경할 때, 해당 이력을 Index에 기록해놓고 이 기록되는 행위를 Stage혹은 Staging이라고 한다.

## 4. Branch

![coding](/assets/img/posts/Branch_1.png)

![coding](/assets/img/posts/Branch_2.png)

 : 여러 개발자가 같은 코드를 공유하며 협업하는 경우 흐름을 나누고 합쳐야 하는데 이때 브랜치는 흐름을 나누는 기점이다.

## 5. CheckOut

 : 현재 위치한 커밋에서 다른 커밋으로 이동하는 것이다.
 이전 시점으로 되돌아가거나 다른 사람의 브랜치로 전환해서 다른 개발자들의 코드 진행상황을 확인할 수 있다.

## 6. Merge

![coding](/assets/img/posts/Merge.png)

 : 여러 사람이 코드를 공유하며 협업을 할 때, 나누었던 흐름을 다시 합치는 것이다.
 - Fast-Forward : 두 개의 브랜치를 자동 병합시키는것 -> 일부 문법에서 충돌(Conflict)이 발생할 수 있다.
 - Non Fast-Forward : 충돌 기록을 보면서 일일히 해당 코드를 수정한 후에 병합하는 것이다.

 -> 성공적인 브랜치 병합을 위해서는 Fast-Forward와 Non Fast-Forward를 같이 하는 것이 좋다.

## 7. Clone

 : 원격 저장소의 특정 프로젝트를 그대로 로컬 저장소로 복제해오는 것이다. 

## 8. Push

 : 원격 저장소로 변경된 파일을 업로드 하는 것이다. 
   push를 하면 원격 저장소에 내 변경 이력이 업로드 되어서 원격 저장소와 로컬 저장소에 동일한 내용이 있게 된다.

## 9. Pull

 : 원격 저장소에 변경된 사항들을 내 로컬 저장소로 pull해서 다른 사람들의 코드를 내 작업창에서 확인할 수 있게한다.


# Flow : 고수준 관리 기법

![coding](/assets/img/posts/Git_Flow.png)

 - 목적에 맞추어 `Feature > Develop > Release > Hotfix > Master`의 5개로 관리한다.
 - 위 순서들은 왼쪽으로 갈수록 포괄적인 가지이며 master branch를 병합할 경우 그 왼쪽에 있는 hotfix등 모든 가지들에 있는 커밋들도 병합하도록 구성하게 된다.

## 메인 브랜치 (Main Branch)

 - Master Branch(메인 배포판) : 실제로 클라이언트에서 이용하는 최종 형태의 메인 브랜치로 추가 생성 및 삭제를 하지 않는다.

 - Develop Branch(메인 개발) : 현재 개발이 진행중인 브랜치이다. master branch와 마찬가지로 추가 생성 및 삭제를 하지 않는다.


## 보조 브랜치 (Supporting Branch)

 - Feature Branch(추가 기능 개발) : 새로운 기능 개발을 위한 브랜치이다. 특정 기능 개발을 할 때, Develop에서 파생이 되고 개발이 완료된 경우 Develop에서 병합이 된다. 가장 많이 추가 및 삭제가 이루어지는 브랜치이다.

 - Release Branch(배포 준비, 오류 확인) : 실제로 프로젝트를 배포하기 위한 브랜치로 Develop에서 파생이 된다. 각종 오류 및 문제사항들을 검토하고 수정하는 일종의 테스트 서버로 수정이 완료되면 Master&Develop으로 병합되어야 한다.

 - Hotfix Branch(긴급 오류 수정) : 배포된 Master Branch의 갑작스런 버그가 발생하였을 때, 급하게 Develop, Feature 단계를 거치지 않고 버그를 수정하는 단계로 수정이 완료되면 Master&Develop으로 병합이 된다.









