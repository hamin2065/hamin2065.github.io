---
layout: post
title:  Weight Initialization
subtitle:   
categories:  ai
tags: season-2
---

# 학습목표
가중치 초기화(Weight Inititalization)에 대해 알아본다.

# 핵심키워드

- 가중치 초기화(Weight Inititalization)
- Xavier / He inititalization

# Weight Initialization(가중치 초기화)

![coding](/assets/img/posts/Lab-09-2Weightinitialization-04.jpg)
: 가중치 초기화를 적용한 `N모델`이 에러가 더 낮고 훨씬 좋은 성능을 가지고 있는 것을 볼 수 있다. 같은 모델을 훈련시키더라도 가중치가 초기에 어떤 값을 가졌느냐에 따라서 모델의 훈련 결과가 달라지기도 한다. 다시 말해 가중치 초기화만 적절히 해줘도 기울기 소실 문제과 같은 문제를 완화시킬 수 있다.
- - -

# Restricted Boltzmann Machine(RBM)
![coding](/assets/img/posts/Lab-09-2Weightinitialization-06.jpg)
: 위와 같은 모델을 RBM이라고 부르는데 같은 레이어 안에서는 연결이 되지 않고 다른 레이어 사이의 노드끼리는 모두 연결이 되는 것을 의미한다. 

RBM으로 `Pre-training`과 `Fine-tuning`의 기법을 사용해서 Weight를 초기화시킨다. 
![coding](/assets/img/posts/Lab-09-2Weightinitialization-08.jpg)
- (a) : 입력 X가 주어지면 Y가 무엇이 나오는지 계산한다. 이때, w1은 X와 h1간의 weight이다.
- (b) : w1은 고정시킨 상태로 h1과 h2의 RBM을 진행한다.
- (c) : 마지막 layer인 h3과 h2의 RBM을 진핸한다.
- Fine-tuning : RBM으로 학습된 weight들에 일반적으로 사용하는 neural network 학습 방식을 적용시켜서 weight를 업데이트한다.

# Xavier / He initialization
: 복잡한 방식인 RBM을 쓰지 않고 간단한 방식인 Xavier과 He initialization을 쓸 수 있다.
![coding](/assets/img/posts/Lab-09-2Weightinitialization-09.jpg)
![coding](/assets/img/posts/Lab-09-2Weightinitialization-10.jpg)

# Code
![coding](/assets/img/posts/Lab-09-2Weightinitialization-11.jpg)
![coding](/assets/img/posts/Lab-09-2Weightinitialization-12.jpg)
![coding](/assets/img/posts/Lab-09-2Weightinitialization-13.jpg)