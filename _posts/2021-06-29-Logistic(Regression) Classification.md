---
layout: post
title:  Logistic(Regression) Classification
subtitle:   
categories:  ai
tags: season-1
---

# Classification
 : 분류. 둘 중에 하나를 고르는 것
- Spam Email Detection : Spam or Ham 

    : 스팸메일인지 아닌지 구분해서 스팸메일은 스팸메일함으로 들어가도록한다.
- Facebook Feed : Show or Hide

    : 전에 누른 '좋아요'를 토대로 관심을 가질만한 피드를 보여준다.
- Credit Card Fraudulent Transaction detection : legitimate/fraud

    : 이전 소비생활의 패턴과 비교해서 카드가 도난당한 것인지 알아낸다.

이 때, `0, 1 인코딩`을 사용한다.
(Spam(1) or Ham(0), show(1) or hide(0), legitimate(0) or fraud(1))

그렇다면 이 분류과정을 선형회귀(Linear Regression)을 통해서 해보자!
- - -
# Linear Regression

## Hypothesis

`H(x) = W*x + b` -> 여기서 Y의 값은 0 또는 1이다.

이 때, `H(x)`가 1보다 크거나 0보다 작은 값을 결과로 내놓을 수 있다는 문제점이 생긴다.

따라서 `H(x)`의 값을 0과 1사이의 값으로 압축을 시킬 필요가 있다. 

`H(x)`를 `z`라고 두고 새로운 함수 `g(z)`를 통해서 0과 1사이의 값을 뽑아낼 수 있도록하자

이 때 사용하는 함수는 sigmoid function(logistic function)이다.

![coding](../../../assets/img/posts/sigmoid_function.png)

이 시그모이드 함수를 사용하면 Logistic Hypothesis의 수식은 다음과 같이 된다.

![coding](../../../assets/img/posts/lec5_hypothesis.png)

## Cost Function

![coding](../../../assets/img/posts/lec5_cost_function.png)

`H(x) = W*x + b` 일 때, cost function을 구하면 밥그릇을 뒤집은 모양이 나와서 최솟값을 구할 수 있지만 우리가 새롭게 만든 H(x)로는 둥근 모양이 나오지 않기 때문에 (global minimum을 찾아야하는데 local을 찾으면서 오차가 커진다.) cost function을 새롭게 정의할 필요가 있다.

__New Cost function for logistic__

![coding](../../../assets/img/posts/lec5_logistic_cost_function.png)

위의 경우를 각각 나눠서 보자.

![coding](../../../assets/img/posts/lec5_-logx_function.PNG)

`y = 1`의 경우이다.
- H(x) = 1 으로 값을 알맞게 예측한 경우 cost(1) = 0이다.
- H(x) = 0 으로 값을 틀리게 예측한 경우 cost(0) = ∞ (무한대)

![coding](../../../assets/img/posts/lec5_-log1-x_function.PNG)

`y = 0`의 경우이다.
- H(x) = 1 으로 값을 틀리게 예측한 경우 cost(1) = ∞ (무한대)
- H(x) = 0 으로 값을 알맞게 예측한 경우 cost(0) = 0이다.

코드에서 사용하기 위해 한 줄로 정리한 cost function은 다음과 같다.

__c(H(x), y) = -y * log(H(x)) - (1-y) * log(1-H(x))__

y = 1인 경우 c = -log(H(x))이고,

y = 0인 경우 c = -1 * log(1-H(x))이다.

## Minimize cost - Gradient descent algorithm

마지막으로 구한 cost를 최소화시키는 단계이다.

![coding](../../../assets/img/posts/lec5_gradient_decent_algorithm.png)

__code__
```py
# cost function
cost = tf.reduce_mean(-tf.reduce_sum(Y*tf.log(hypothesis) + (1-Y)*tf.log(1-hypothesis)))

# Minimize
a = tf.Variable(0.1) # Learning rate, alpha
optimizer = tf.train.GradientDescentOptimizer(a)
train = optimizer.minimize(cost)
```