---
layout: post
title:  Batch Normalization
subtitle:   
categories:  ai
tags: season-2
---
# 학습목표
Batch Normalization 에 대해 알아본다.

# 핵심키워드
- Batch Normalization
- 경사 소실(Gradient Vanishing) / 폭발(Exploding)


# Batch Vanishing / Exploding
![coding](/assets/img/posts/Lab-09-4BatchNormalization-04.jpg)
- `Gradient Vanishing` : 역전파에서 Gradient가 사라지는 현상 
    - 앞쪽의 레이어가 영향을 주지 못하고 뒤쪽의 레이어에 의해 모델이 결정됨 
- Gradient Exploding : 역전파에서 Gradient가 매우 커지는 현상 
    - 가중치가 크게 바뀌게 되어 모델이 불안정해지거나 NaN으로 사라지는 현상 

- 해결책
    1. Change activation function : 활성 함수를 바꾼다.
        (Ex. sigmoid -> ReLU)
    2. Careful initialization : Xavier / He initialization
    3. Small learning rate
    __4. Batch Normalization__

# Internal Covariate Shift
여기서 Covariate Shift란 Train Set과  Test Set의 차이를 말한다.
즉, `Internal Covariate Shift(내부 공변량 변화)`란 층 별로 입력 데이터 분포가 달라지는 현상을 말하는 것이다.
![coding](/assets/img/posts/Lab-09-4BatchNormalization-06.jpg)

![coding](/assets/img/posts/Lab-09-4BatchNormalization-08.jpg)

# Batch Normalization
배치 정규화(Batch Normalization)는 표현 그대로 한 번에 들어오는 배치 단위로 정규화하는 것을 말한다. 배치 정규화는 각 층에서 활성화 함수를 통과하기 전에 수행된다. 
![coding](/assets/img/posts/Lab-09-4BatchNormalization-09.jpg)
배치 정규화는 입력에 대해 평균을 0으로 만들고, 정규화를 한다. 그리고 정규화 된 데이터에 대해서 스케일과 시프트를 수행한다. 이 때 두 개의 매개변수 γ와 β를 사용하는데, γ는 스케일을 위해 사용하고, β는 시프트를 하는 것에 사용하며 다음 레이어에 일정한 범위의 값들만 전달되게 한다.
- - - 
# Code
![coding](/assets/img/posts/Lab-09-4BatchNormalization-10.jpg)
![coding](/assets/img/posts/Lab-09-4BatchNormalization-11.jpg)
![coding](/assets/img/posts/Lab-09-4BatchNormalization-12.jpg)
![coding](/assets/img/posts/Lab-09-4BatchNormalization-13.jpg)


참고 

https://www.boostcourse.org/ai214/lecture/43762/?isDesc=false
https://wikidocs.net/61271