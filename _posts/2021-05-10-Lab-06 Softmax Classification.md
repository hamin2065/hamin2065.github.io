---
layout: post
title: Lab-06 Softmax Classification
color: rgb(242,85,44)
tags: [AI, PyTorch]
---

# 학습목표
소프트맥스 분류(Softmax Classification)에 대해 알아본다.

# 핵심키워드
- 소프트맥스(Softmax)
- 크로스 엔트로피(Cross Entropy)
- - - 

![coding](../../../assets/img/posts/Lab-06SoftmaxClassification-01.jpg)

![coding](../../../assets/img/posts/Lab-06SoftmaxClassification-02.jpg)

![coding](../../../assets/img/posts/Lab-06SoftmaxClassification-03.jpg)

![coding](../../../assets/img/posts/Lab-06SoftmaxClassification-04.jpg)
- - -
# Softmax 함수
 : 확률의 총합이 1이 되도록 각 클래스에 확률을 할당하는 함수로, 분류해야 하는 정답지(클래스)의 총 개수를 k라고 할 때 k차원의 벡터를 입력받아 각 클래스에 대한 확률을 추정한다.
![coding](../../../assets/img/posts/Lab-06SoftmaxClassification-05.jpg)


- - -
# Cross Entropy 
: 2개의 확률분포가 주어졌을 때, 그 확률분포가 얼마나 비슷할지 나타낼 수 있는 수치

![coding](../../../assets/img/posts/Lab-06SoftmaxClassification-06.jpg)

Cross Entropy를 최소화하면 Q2는 Q1으로, Q1은 P로 점점 근사하게 될 것이다.(Cross Entropy를 최소화하는 것이 중요하다.)

![coding](../../../assets/img/posts/Lab-06SoftmaxClassification-07.jpg)

![coding](../../../assets/img/posts/Lab-06SoftmaxClassification-08.jpg)

- 원-핫 인코딩(One-hot encoding) : 선택해야 하는 선택지의 개수만큼의 차원을 가지면서, 각 선택지의 인덱스에 해당하는 원소에는 1, 나머지 원소는 0의 값을 가지도록 하는 표현 방법
- 원-핫 벡터(one-hot vector) : 원-핫 인코딩으로 표현된 벡터

- `y.unsqueeze(1)` : |y| = (3,) -> |y| = (3 × 1)
- `_` : In-place Operation (덮어쓰기 연산)


![coding](../../../assets/img/posts/Lab-06SoftmaxClassification-09.jpg)

__F.softmax() + torch.log() = F.log_softmax()__

![coding](../../../assets/img/posts/Lab-06SoftmaxClassification-10.jpg)

__F.log_softmax() + F.nll_loss() = F.cross_entropy()__

![coding](../../../assets/img/posts/Lab-06SoftmaxClassification-11.jpg)

- - -
![coding](../../../assets/img/posts/Lab-06SoftmaxClassification-12.jpg)

![coding](../../../assets/img/posts/Lab-06SoftmaxClassification-13.jpg)

![coding](../../../assets/img/posts/Lab-06SoftmaxClassification-14.jpg)

![coding](../../../assets/img/posts/Lab-06SoftmaxClassification-15.jpg)

![coding](../../../assets/img/posts/Lab-06SoftmaxClassification-16.jpg)

