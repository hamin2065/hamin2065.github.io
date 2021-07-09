---
layout: post
title:  Linear Regression
subtitle:   
categories:  ai
tags: season-2
---

# 학습목표
선형회귀(Linear Regression)에 대해 알아본다.

# 핵심키워드
- 선형회귀(Linear Regression)
- 평균 제곱 오차(Mean Squared Error)
- 경사하강법(Gradient descent)

- - -

# Data definition

ex) 공부한 시간의 상관관계가 있는가?

__Training dataset__ : 모델을 학습시키기 위한 데이터셋

__Test dataset__ : 시험해볼 데이터셋

입력받는 데이터의 형태는 torch.tensor의 형태를 띤다.



# Hypothesis

모델을 구현한다.

y = Wx + b

여기서 `W`는 weight이고 `b`는 Bias이다.


```py
x_train = torch.FloatTensor([[1], [2], [3]])
y_train = torch.FloatTensor([[2], [4], [6]])

# Weight와 Bias를 0으로 초기화 -> 항상 출력 0을 예측
W = torch.zeros(1, requires_grad=True)
b = torch.zeros(1, requires_grad=True) 

hypothesis = x_train * W + b
```

- `requires_grad = True`는 학습할 것이라고 명시하는 것

# Compute loss

학습을 하려면 얼마나 정답과 가까운지 알아야한다.-> 이 값을 cost또는 loss라고 한다.

linear Regression에서는 `Mean Squared Error(MSE)`라는 함수로 loss를 계산한다.



![coding](../../../assets/img/posts/pytorch_Lab02_1.png)

위의 식을 코드 한 줄로 계산할 수 있다.
```py
cost = torch.mean((hypothesis - y_train) ** 2 ) # MSE
```



# Gradient descent

torch.optim 라이브러리를 사용한다.
- [W, b]는 학습할 tensor들
- 1r = 0.01은 learning rate이다.

- zero_grad()로 gradient 초기화
- backward()로 gradient 계산
- step으로 개선

```py
optimizer = torch.optim.SGD([W, b], lr=0.01)

optimizer.zero_grad()
cost.backward()
optimizer.step()
```
- - -
`Full Training Code`
```py
# 데이터 정의
x_train = torch.FloatTensor([[1], [2], [3]])
y_train = torch.FloatTensor([[2], [4], [6]])

# Hypothesis 초기화
W = torch.zeros(1, requires_grad=True)
b = torch.zeros(1, requires_grad=True) 

# Optimizer 정의
optimizer = torch.optim.SGD([W, b], lr=0.01)

# 반복!
# 1. Hypothesis 예측
# 2. Cost 계산
# 3. Optimizer로 학습
nb_epochs = 1000
for epoch in range(1, nb_epochs + 1):
    hypothesis = x_train * W + b
    cost = torch.mean((hypothesis - y_train) ** 2)
    
    optimizer.zero_grad()
    cost.backward()
    optimizer.step()
```
W, b가 하나의 최적의 숫자로 수렴하게 된다.
