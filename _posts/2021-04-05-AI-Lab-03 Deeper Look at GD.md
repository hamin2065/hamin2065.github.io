---
layout: post
title:  Deeper Look at GD
subtitle:   
categories:  ai
tags: season-2
---

# 학습 목표
경사하강법(Gradient descent)에 대해 더 자세히 알아본다.

# 핵심 키워드
- 가설 함수(Hypothesis Function)
- 평균 제곱 오차(Mean Squared Error)
- 경사하강법(Gradient descent)

# Hypothesis function 복습

# 사용할 모의 data 확인

H(x) = Wx사용! (No Bias!)
```py
W = torch.zeros(1, requires_grad=True)

hypothesis = x_train * W 
```

`Dummy Data` : Input = Output
|Hours(x)|Points(y)|
|------|---|
|1|1|
|2|2|
|3|3|
```py
x_train = torch.FloatTensor([[1], [2], [3]])
y_train = torch.FloatTensor([[1], [2], [3]])
```
H(x) = x가 정확한 모델이다. 즉, W = 1이 가장 좋은 숫자

모델의 좋고 나쁨을 어떻게 평가할 수 있을까?




# Cost function 이해

Cost Function은 모델의 예측값이 실제 데이터와 얼마나 다른지 나타낸다. 잘 학습된 데이터일수록 낮은 cost값을 가진다.

W = 1일때, cost = 0

: 1에서 멀어질수록 높아진다.

Linear Regression에서 쓰이는 Cost function : MSE


# Gradient descent 이론

cost function값을 최소화하려면 기울기가 음수일때는 W가 더 커져야하고 기울기가 양수이면 W가 작아져야한다.

기울기가 클수록 cost값이 큰 것이므로 


![coding](../../../assets/img/posts/pytorch_Lab03_1.png)

Gradient Descent를 코드로 구현

# Gradient descent 구현
```py
# 데이터 
x_train = torch.FloatTensor([[1], [2], [3]])
y_train = torch.FloatTensor([[1], [2], [3]])

# 모델 초기화
W = torch.zeros(1)

# Learning rate 설정
lr = 0.1

nb_epochs = 10
for epoch in range(nb_epochs + 1):
    
    # H(x) 계산
    hypothesis = x_train * W
    
    # cost gradient 계산
    cost = torch.mean((hypothesis - y_train) ** 2)
    gradient = torch.sum((W * x_train - y_train) * x_train)
    
    print('Epoch {:4d}/{} W: {:.3f}, Cost: {:.6f}'.format(
        epoch, nb_epochs, W.item(), cost.item()
    ))
    
    # cost gradient로 H(x) 개선
    W -= lr * gradient
```
출력결과

>Epoch    0/10 W: 0.000, Cost: 4.666667
>
>Epoch    1/10 W: 1.400, Cost: 0.746666
>
>Epoch    2/10 W: 0.840, Cost: 0.119467
>
>Epoch    3/10 W: 1.064, Cost: 0.019115
>
>Epoch    4/10 W: 0.974, Cost: 0.003058
>
>Epoch    5/10 W: 1.010, Cost: 0.000489
>
>Epoch    6/10 W: 0.996, Cost: 0.000078
>
>Epoch    7/10 W: 1.002, Cost: 0.000013
>
>Epoch    8/10 W: 0.999, Cost: 0.000002
>
>Epoch    9/10 W: 1.000, Cost: 0.000000
>
>Epoch   10/10 W: 1.000, Cost: 0.000000

- Epoch : 데이터로 학습한 횟수
- Epoch값이 증가할 수록 W값은 1에 수렴하고 cost는 줄어든다.







# Gradient descent with torch.optim

```py
# 데이터 
x_train = torch.FloatTensor([[1], [2], [3]])
y_train = torch.FloatTensor([[1], [2], [3]])

# 모델 초기화
W = torch.zeros(1, requires_grad = True)

# optimizer 정의
optimizer = torch.optim.SGD([W], lr=0.15)

nb_epochs = 10
for epoch in range(nb_epochs + 1):
    
    # H(x) 계산
    hypothesis = x_train * W
    
    # cost gradient 계산
    cost = torch.mean((hypothesis - y_train) ** 2)
    
    print('Epoch {:4d}/{} W: {:.3f}, Cost: {:.6f}'.format(
        epoch, nb_epochs, W.item(), cost.item()
    ))

    # cost로 H(x) 개선
    optimizer.zero_grad() # gradient를 0으로 초기화
    cost.backward() # gradient계산
    optimizer.step() # gradient descent
```
출력결과

>Epoch    0/10 W: 0.000, Cost: 4.666667
>
>Epoch    1/10 W: 1.400, Cost: 0.746667
>
>Epoch    2/10 W: 0.840, Cost: 0.119467
>
>Epoch    3/10 W: 1.064, Cost: 0.019115
>
>Epoch    4/10 W: 0.974, Cost: 0.003058
>
>Epoch    5/10 W: 1.010, Cost: 0.000489
>
>Epoch    6/10 W: 0.996, Cost: 0.000078
>
>Epoch    7/10 W: 1.002, Cost: 0.000013
>
>Epoch    8/10 W: 0.999, Cost: 0.000002
>
>Epoch    9/10 W: 1.000, Cost: 0.000000
>
>Epoch   10/10 W: 1.000, Cost: 0.000000