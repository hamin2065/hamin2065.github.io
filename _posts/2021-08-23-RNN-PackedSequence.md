---
layout: post
title:  "[RNN] PackedSequence"
subtitle:   
categories:  ai
tags: season-2
---

# 길이가 다른 Sequential data
Text : The quick brown jumps over the lazy dog -> 단어의 개수가 정해지지 않은 텍스트 데이터

오디오 : 시간과 샘플링 데이터에 따라서 오디오 데이터의 길이가 달라진다.

vs

이미지 -> 크기가 정해져있는 데이터

- - -

# 묶는 방법

![packed-sequence-example](/assets/img/posts/packed-sequence-example.png)
## Padding Method
![packed-sequence-example-padding](/assets/img/posts/packed-sequence-example-padding.png)
제일 긴 문자열에 맞춰서 `<pad>`로 채워넣으면 된다. 모양이 깔끔해지기 때문에 컴퓨터에서 처리하기 쉬워지지만 계산하지 않아도 되는 부분까지 계산해야하는 단점이 있다.
## Packing Method
![packed-sequence-example-packing](/assets/img/posts/packed-sequence-example-packing.png)
packing method는 `<pad>`를 쓰지 않고 sequence 길이에 대한 정보를 저장한다. 이 방법을 파이토치에서 쓰기 위해서는 길이 내림 차순으로 정렬이 되어야한다.
```text
SHORT CIRCUIT
HELLO WORLD
CALCULATION
MIDNIGHT
PATH
```
이를 `Packed Sequence`라고 부른다. `padding method`에 비해서 `pad`토큰을 쓰지 않아도 되고, 좀 더 효율적으로 계산할 수 있다는 장점이 있다. 

하지만 내림차순으로 정렬을 해주어야한다는 단점이나, 구현시 `Padding Method`보다 조금 더 복잡하다는 단점이 있다.

- - -

# Pytorch Library Function

![pytorch-library-function](/assets/img/posts/pytorch-library-function.png)