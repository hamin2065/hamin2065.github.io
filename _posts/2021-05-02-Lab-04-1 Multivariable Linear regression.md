---
layout: post
title: Lab-04-1 Multivariable Linear regression
color: rgb(242,85,44)
tags: [AI, PyTorch]
---
# 학습목표
다항 선형 회귀(Multivariable Linear regression)에 대해 알아본다.
# 핵심키워드
- 다항 선형 회귀(Multivariable Linear regression)
- 가설 함수(Hypothesis Function)
- 평균 제곱 오차(Mean Squared Error)
- 경사하강법(Gradient descent)

# Simple vs Multivariable
Simple Linear Regression

: 하나의 정보로부터 하나의 결론

: Hypothesis function : H(x) = Wx + b

x 라는 벡터와 W라는 matrix의 곱

Multivariate Linear Regression

: 복수의 정보로 하나의 추측값 계산

: Hypothesis function : H(x) = w1x1 + w2x2 + w3x3 + b 

입력변수가 3개라면 weight도 3개

ex) 쪽지 시험 점수 : 73, 80, 75
    최종 점수 추측 : 152

# Multivariable의 Hypothesis Function
__H(x) = w1x1 + w2x2 + w3x3 + b__

```py
# H(x)계산
hypothesis = x1_train * w1 + x2_train * w2 + x3_train * w3 + b
```
이 때 발생하는 문제점!
if x가 길이 1000의 벡터라면? 식이 너무 길어진다.

해결책! `matmul()`함수 사용
```python
hypothesis = x_train.matmul(W) + b # or .mm or @
```

matmul() 함수는 더 간결하고 x의 길이가 바뀌어도 코드를 바꿀 필요가 없다. 속도도 더 빠르다.


# Multivariable의 Cost Function
cost function:MSE는 simple Linear Regression과 동일
![coding](../../../assets/img/posts/pytorch_Lab02_1.png)

# Gradient Descent with torch.optim

![coding](../../../assets/img/posts/pytorch_Lab03_1.png)

```python
    #optimizer 설정
    optimizer = optim.SGD([W, b], lr=1e-5)

    # optimizer 사용법
    optimizer.zero_grad()
    cost.backward()
    optimizer.step()
    ```

    __Full Code with torch.optim__
    ```python
    x_train = torch.FloatTensor([[73, 80, 75],
                            [93, 88, 93],
                            [89, 91, 90],
                            [96, 98, 100],
                            [73, 66, 70]])
    y_train = torch.FloatTensor([[152], [185], [180], [196], [142]])
                    
    # 모델 초기화
    W = torch.zeros((3, 1), requires_grad=True)
    b = torch.zeros(1, requires_grad=True)

    #optimizer 설정
    optimizer = torch.optim.SGD([W, b], lr=1e-5)

    nb_epochs = 20
    for epoch in range(nb_epochs + 1):
        
        #H(x) 계산
        hypothesis = x_train.matmul(W) + b
        
        #cost 계산
        cost = torch.mean((hypothesis - y_train) ** 2)
        
        # cost로 H(x) 계산
        optimizer.zero_grad()
        cost.backward()
        optimizer.step()
        
        print('Epoch {:4d}/{} hypothesis: {} Cost {:.6f}'.format(epoch, nb_epochs, hypothesis.squeeze().detach(), cost.item()))
```
출력결과

>Epoch    0/20 hypothesis: tensor([0., 0., 0., 0., 0.]) Cost 29661.800781
>
>Epoch    1/20 hypothesis: tensor([67.2578, 80.8397, 79.6523, 86.7394, 61.6605]) Cost 9298.520508
>
>Epoch    2/20 hypothesis: tensor([104.9128, 126.0990, 124.2466, 135.3015,  96.1821]) Cost 2915.712402
>
>Epoch    3/20 hypothesis: tensor([125.9942, 151.4381, 149.2133, 162.4896, 115.5097]) Cost 915.040649
>
>Epoch    4/20 hypothesis: tensor([137.7967, 165.6247, 163.1911, 177.7112, 126.3307]) Cost 287.936157
>
>Epoch    5/20 hypothesis: tensor([144.4044, 173.5674, 171.0168, 186.2332, 132.3891]) Cost 91.371010
>
>Epoch    6/20 hypothesis: tensor([148.1035, 178.0143, 175.3980, 191.0042, 135.7812]) Cost 29.758249
>
>Epoch    7/20 hypothesis: tensor([150.1744, 180.5042, 177.8509, 193.6753, 137.6805]) Cost 10.445281
>
>Epoch    8/20 hypothesis: tensor([151.3336, 181.8983, 179.2240, 195.1707, 138.7440]) Cost 4.391237
>
>Epoch    9/20 hypothesis: tensor([151.9824, 182.6789, 179.9928, 196.0079, 139.3396]) Cost 2.493121
>
>Epoch   10/20 hypothesis: tensor([152.3454, 183.1161, 180.4231, 196.4765, 139.6732]) Cost 1.897688
>
>Epoch   11/20 hypothesis: tensor([152.5485, 183.3609, 180.6640, 196.7389, 139.8602]) Cost 1.710555
>
>Epoch   12/20 hypothesis: tensor([152.6620, 183.4982, 180.7988, 196.8857, 139.9651]) Cost 1.651412
>
>Epoch   13/20 hypothesis: tensor([152.7253, 183.5752, 180.8742, 196.9678, 140.0240]) Cost 1.632369
>
>Epoch   14/20 hypothesis: tensor([152.7606, 183.6184, 180.9164, 197.0138, 140.0571]) Cost 1.625924
>
>Epoch   15/20 hypothesis: tensor([152.7802, 183.6427, 180.9399, 197.0395, 140.0759]) Cost 1.623420
>
>Epoch   16/20 hypothesis: tensor([152.7909, 183.6565, 180.9530, 197.0538, 140.0865]) Cost 1.622141
>
>Epoch   17/20 hypothesis: tensor([152.7968, 183.6643, 180.9603, 197.0618, 140.0927]) Cost 1.621262
>
>Epoch   18/20 hypothesis: tensor([152.7999, 183.6688, 180.9644, 197.0661, 140.0963]) Cost 1.620501
>
>Epoch   19/20 hypothesis: tensor([152.8014, 183.6715, 180.9665, 197.0686, 140.0985]) Cost 1.619764
>
>Epoch   20/20 hypothesis: tensor([152.8020, 183.6731, 180.9677, 197.0699, 140.0999]) Cost 1.619046

-> Cost는 점점 작아지고 H(x)는 y에 가까워진다. Learning rate에 따라서 발산할 수도 있다.

# nn.Module과 F.mse_loss

```py
import torch.nn as nn

class MultivariateLinearRegressionModel(nn.Module):
    def __init__(self):
        super().__init__()
        self.linear = nn.Linear(3, 1)
        
    def forward(self, x):
        return self.linear(x)

hypothesis = model(x_train)
```
- nn.Module을 상속해서 모델을 만든다. 
- nn.Linear(3, 1) -> 입력차원 : 3, 출력차원 : 1
- Hypothesis 계산은 forward()에서 
Gradient 계산은 PyTorch가 알아서 해준다.(backward())

F.mse_loss
```python
import torch.nn.functional as F

#cost계산
cost = F.mse_loss(prediction, y_train)
```
- torch.nn.functional 에서 제공하는 loss function을 사용한다.

- 쉽게 다른 loss와 교체가 가능하다.(l1_loss, smooth_l1_loss등)