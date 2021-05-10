---
layout: post
title: Lab-05 Logistic Regression
color: rgb(242,85,44)
tags: [AI, PyTorch]
---

# 학습목표
로지스틱 회귀(Logistic Regression)에 대해 알아본다.

# 핵심키워드
- 로지스틱 회귀(Logistic Regression)
- 가설(Hypothesis)
- 손실함수(Cost Function)
- 평가(Evaluation)

- - -
# Logistic Regression

이진 분류(Binary Classification) : 추론값과 정답값이 2개로, 하나는 참이고 두번째는 거짓이다. 참은 1이고 거짓은 0값이다.

이진 분류를 풀기 위한 대표적인 알고리즘으로 로지스틱 회귀(Logistic Regression)가 있다.

__실습__

```python
import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim
```
```py
# For reproducibility
torch.manual_seed(1)
```
출력결과

> <torch._C.Generator at 0x22ddd0c2370>
```py
x_data = [[1, 2], [2, 3], [3, 1], [4, 3], [5, 3], [6, 2]] # |x_data| = (6, 2)
y_data = [[0], [0], [0], [1], [1], [1]] # |y_data| = (6, )
```
```py
x_train = torch.FloatTensor(x_data)
y_train = torch.FloatTensor(y_data)
```
```py
print(x_train.shape)
print(y_train.shape)
```
출력결과

>torch.Size([6, 2])
>
>torch.Size([6, 1])

x_train을 받아서 y_train의 결과가 나오도록 로지스틱 모델을 훈련하는 것이 목표이다.
```py
print('e^1 equals : ',torch.exp(torch.FloatTensor([1])))
```
결과
>e^1 equals :  tensor([2.7183])

> `torch.exp()` : 지수함수와 비슷한 함수

```py
W = torch.zeros((2, 1), requires_grad = True)
b = torch.zeros(1, requires_grad = True)
```
```py
hypothesis = 1 / (1 + torch.exp(-(x_train.matmul(W) + b)))
```
```py
print(hypothesis)
print(hypothesis.shape)
```
출력결과
> tensor([[0.5000],
>
>    [0.5000],
>
>    [0.5000],
>
>    [0.5000],
>
>    [0.5000],
>
>    [0.5000]], grad_fn=\<MulBackward0>)
>
>torch.Size([6, 1])
- - -
__sigmoid 함수를 사용하는 경우__

```py
# sigmoid 함수 사용
print('1/(1+e^{-1}) equals: ',torch.sigmoid(torch.FloatTensor([1])))
```
출력결과
>1/(1+e^{-1}) equals:  tensor([0.7311])

```py
hypothesis = torch.sigmoid(x_train.matmul(W) + b)
```
```py
print(hypothesis)
print(hypothesis.shape)
```
출력결과
> tensor([[0.5000],
>
>    [0.5000],
>
>    [0.5000],
>
>    [0.5000],
>
>    [0.5000],
>
>    [0.5000]], grad_fn=\<MulBackward0>)
>
>torch.Size([6, 1])

- - -

하나의 원소가 있을 때, 손실 계산
```py
-(y_train[0] * torch.log(hypothesis[0]) + 
     (1 - y_train[0]) * torch.log(1 - hypothesis[0]))
```
출력결과
>tensor([0.6931], grad_fn=\<NegBackward>)

`y_train[0]` : 스칼라

`hypothesis[0]` : 스칼라, logP(x = 1;W)

`1 - hypothesis[0]` : log P(x = 0;W) = 1 - logP(x = 1;W)
- - - 
전체에 대해서 손실 계산
```py
losses = -(y_train * torch.log(hypothesis) + 
             (1 - y_train) * torch.log(1 - hypothesis))
print(losses)
```
출력결과
>tensor([[0.6931],
>
>    [0.6931],
>
>    [0.6931],
>
>    [0.6931],
>
>    [0.6931],
>
>    [0.6931]], grad_fn=\<NegBackward>)
- - -
`.mean()` : 각각의 손실에 대해서 평균값을 계산해준다.

```py
cost = losses.mean()
print(cost)
```
출력결과
> tensor(0.6931, grad_fn=<MeanBackward0>)

- - - 
`binary_cross_entropy` 함수 사용
```py
F.binary_cross_entropy(hypothesis, y_train)
```
출력결과 
> tensor(0.6931, grad_fn=<BinaryCrossEntropyBackward>)

위에서 복잡하게 쓴 식을 한 줄의 코드로 구현이 가능해진다.
- - -
__Full Code__
```py
# 모델 초기화
W = torch.zeros((2, 1), requires_grad = True)
b = torch.zeros(1, requires_grad = True)

#optimizer 설정
optimizer = optim.SGD([W, b], lr = 1)

nb_epochs = 1000
for epoch in range(nb_epochs + 1):
    
    # Cost 계산
    hypothesis = 1 / (1 + torch.exp(-(x_train.matmul(W) + b)))
    cost = F.binary_cross_entropy(hypothesis, y_train)
    
    #cost로 H(x) 개선
    optimizer.zero_grad()
    cost.backward()
    optimizer.step()
    
    #100번마다 로그 출력
    if epoch % 100 == 0:
        print('Epoch {:4d}/{} Cost : {:.6f}'.format(epoch, nb_epochs, cost.item()))
```

>출력결과
>Epoch    0/1000 Cost : 0.693147
>
>Epoch  100/1000 Cost : 0.134722
>
>Epoch  200/1000 Cost : 0.080643
>
>Epoch  300/1000 Cost : 0.057900
>
>Epoch  400/1000 Cost : 0.045300
>
>Epoch  500/1000 Cost : 0.037261
>
>Epoch  600/1000 Cost : 0.031673
>
>Epoch  700/1000 Cost : 0.027556
>
>Epoch  800/1000 Cost : 0.024394
>
>Epoch  900/1000 Cost : 0.021888
>
>Epoch 1000/1000 Cost : 0.019852
- - - 
__Evaluation__
```py
hypothesis = torch.sigmoid(x_train.matmul(W) + b)
print(hypothesis[:5])
```
출력결과 
>tensor([[2.7648e-04],
>
>    [3.1608e-02],
>
>    [3.8977e-02],
>
>    [9.5622e-01],
>    
>    [9.9823e-01]], grad_fn=<SliceBackward>)


위의 hypothesis를 토대로 결과값을 예측한다.
```py
prediction = hypothesis >= torch.FloatTensor([0.5])
print(prediction[:5])
```
출력결과
>tensor([[False],
>
>    [False],
>
>    [False],
>
>    [ True],
>    
>    [ True]])


예측 값이 맞는지 y_train과 비교
```py
print(prediction[:5])
print(y_train[:5])      
```
출력결과
>tensor([[False],
>
>    [False],
>
>    [False],
>
>    [ True],
>
>    [ True]])
>
>tensor([[0.],
>
>    [0.],
>
>    [0.],
>
>    [1.],
>
>    [1.]])

```py
correct_prediction = prediction.float() == y_train
print(correct_prediction[:5])
``` 
출력결과
>tensor([[True],
>
>    [True],
>
>    [True],
>
>    [True],
>    
>    [True]])


실제로 사용할 때는 클래스를 구현해서 사용
```py
class BinaryClassifier(nn.Module) : 
    def __init__(self):
        super().__init__()
        self.linear = nn.Linear(8, 1)
        self.sigmoid = nn.Sigmoid()
        
    def forward(self, x):
        return self.sigmoid(self.linear(x))
model = BinaryClassifier()
```