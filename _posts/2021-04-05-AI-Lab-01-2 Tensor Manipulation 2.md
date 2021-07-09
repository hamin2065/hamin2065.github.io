---
layout: post
title:  Tensor Manipulation 2
subtitle:   
categories:  ai
tags: season-2
---

# 학습 목표
- 지난 시간에 이어서 텐서 조작(Tensor Manipulaion)에 대해 계속 알아본다.

# 핵심 키워드
- 텐서(Tensor)
- 넘파이(Numpy)
- 텐서 조작(Tensor Manipution)
- View, Squeeze, Unsqueeze, Type Casting, Concatenate, Stacking, In-place Operation

# Other Basic Ops

## View(Numpy에서 Reshape)
: 텐서의 크기(Shape)를 변경해주는 역할
```py
import numpy as np
import torch

t = np.array([[[0, 1, 2],
               [3, 4, 5]],
            
              [[6, 7, 8],
              [9, 10, 11]]])
ft = torch.FloatTensor(t)
print(ft.shape)
```
출력결과
> torch.Size([2, 2, 3])

|ft| = (2, 2, 3)

```python
print(ft.view([-1, 3])) # 앞에는 모르겠고 두 번째 차원은 3개의 element를 가질것이다.
print(ft.view([-1, 3]).shape)
```
출력결과

> tensor([[ 0.,  1.,  2.], [ 3.,  4.,  5.], [ 6.,  7.,  8.], [ 9., 10., 11.]])
>         
> torch.Size([4, 3])

원래의 |ft| = (2, 2, 3)

ft.view([-1, 3]).shape => (2*2, 3) 즉 크기는 4 by 3이 나온다.

```python
print(ft.view([-1, 1, 3]))
print(ft.view([-1, 1, 3]).shape)
```
출력결과
> tensor([[[ 0.,  1.,  2.]], [[ 3.,  4.,  5.]], [[ 6.,  7.,  8.]], [[ 9., 10., 11.]]])
>
> torch.Size([4, 1, 3])
​
## Squeeze
```python
ft = torch.FloatTensor([[0],[1],[2]])
print(ft)
print(ft.shape)
```
출력결과
> tensor([[0.],
>         [1.],
>         [2.]])
>         
> torch.Size([3, 1])

```python
print(ft.squeeze())
print(ft.squeeze().shape)
```
출력결과
> tensor([0., 1., 2.])
> torch.Size([3])

원래의 |ft| = (3, 1) => (3, )

```python
print(ft.squeeze(dim=0))
print(ft.squeeze(dim=1))
```
출력결과
> tensor([[0.],
>         [1.],
>         [2.]])
>
> tensor([0., 1., 2.])

## Unsqueeze
```py
ft = torch.Tensor([0, 1, 2])
print(ft.shape)
```
출력결과
> torch.Size([3])

```py
print(ft.unsqueeze(0)) #dim=0을 한 것과 같은 효과
print(ft.unsqueeze(0).shape)
```
출력결과
> tensor([[0., 1., 2.]])
> 
> torch.Size([1, 3])

unsqueeze(0) -> 첫 번째 dimension에 1을 넣어라

|ft| = (1, 3)

```py
print(ft.view(1, -1)) #앞에 1을 넣어라
print(ft.view(1, -1).shape)
```
출력결과

> tensor([[0., 1., 2.]])
>
> torch.Size([1, 3])

(3, ) -> (3, 1)

```py
print(ft.unsqueeze(1))
print(ft.unsqueeze(1).shape)
```
출력결과

>tensor([[0.],
>        [1.],
>        [2.]])
>
>torch.Size([3, 1])

```py
print(ft.unsqueeze(-1)) # 마지막 dimension, 즉 dim=1과 같은 의미이다.
print(ft.unsqueeze(-1).shape)
```
출력결과

> tensor([[0.],
>         [1.],
>         [2.]])
>
> torch.Size([3, 1])

Squeeze와 Unsqueeze는 element의 숫자의 개수를 바꾸는 것이 아니다.

## Type Casting
```py
lt = torch.LongTensor([1, 2, 3, 4])
print(lt)
```
출력결과

> tensor([1, 2, 3, 4])

```py
print(lt.float())
```
출력결과

> tensor([1., 2., 3., 4.])

```py
bt = torch.ByteTensor([True, False, False, True])
print(bt)
```
출력결과

> tensor([1, 0, 0, 1], dtype=torch.uint8)

```py
print(bt.long())# 정수로 바꾼다.
print(bt.float())# Float로 바꾼다.
```
출력결과
>tensor([1, 0, 0, 1])
>
>tensor([1., 0., 0., 1.])

## Concatenate
: 두 개의 텐서를 연결한다.
```py
x = torch.FloatTensor([[1, 2], [3, 4]])
y = torch.FloatTensor([[5, 6], [7, 8]])

print(torch.cat([x, y], dim=0))
print(torch.cat([x, y], dim=1))
```
출력결과
> tensor([[1., 2.],
>         [3., 4.],
>         [5., 6.],
>         [7., 8.]])
> 
> tensor([[1., 2., 5., 6.],
>         [3., 4., 7., 8.]])


|x| = |y| = (2, 2)

dim=0에 대해서 cat하는 경우 -> size는 (4, 2)

dim=1에 대해서 cat하는 경우 -> size는 (2, 4)

## Stacking
```py
x = torch.FloatTensor([1, 2])
y = torch.FloatTensor([2, 5])
z = torch.FloatTensor([3, 6])

print(torch.stack([x, y, z]))
print(torch.stack([x, y, z], dim=1))

print(torch.cat([x.unsqueeze(0), y.unsqueeze(0), z.unsqueeze(0)], dim=0))
```
출력결과

> tensor([[1., 2.],
>         [2., 5.],
>         [3., 6.]])
>
> tensor([[1., 2., 3.],
>         [2., 5., 6.]])
>
> tensor([[1., 2.],
>         [2., 5.],
>         [3., 6.]])

|x| = |y| = |z| = (2, )

torch.stack([x, y, z]) : 위로 쌓게 되면서 크기는 (3, 2)가 된다.

torch.stack([x, y, z], dim=1) : dim=1에 대해서 쌓으라는 의미 -> (2, 3)

torch.cat([x.unsqueeze(0), y.unsqueeze(0), z.unsqueeze(0)], dim=0)

x.unsqueeze(0)의 결과 : (1, 2)

y.unsqueeze(0)의 결과 : (1, 2)

z.unsqueeze(0)의 결과 : (1, 2)

dim=0에 대해서 쌓는다. -> size : (3, 2)

## Ones and Zeros

```py
x = torch.FloatTensor([[0, 1, 2], [2, 1, 0]])
print(x)

print(torch.ones_like(x))
print(torch.ones_like(x))
```
출력결과

> tensor([[0., 1., 2.],
>         [2., 1., 0.]])
>
> tensor([[1., 1., 1.],
>         [1., 1., 1.]])
>
> tensor([[1., 1., 1.],
>         [1., 1., 1.]])
​

: x랑 같은 사이즈의 1로 가득찬, 또는 0으로 가득찬 행렬만들기.
같은 디바이스에 텐서를 선언해준다..

## In-place Operation

```py
x = torch.FloatTensor([[1, 2], [3, 4]])

print(x.mul(2.)) # x * 2
print(x)
print(x.mul_(2.))# 메모리를 새로 선언하지 말고 기본텐서에 값을 넣으라는 의미의 함수
print(x)
```
출력결과

> tensor([[2., 4.],
>         [6., 8.]])
>
> tensor([[1., 2.],
>         [3., 4.]])
>
> tensor([[2., 4.],
>         [6., 8.]])
>
> tensor([[2., 4.],
>         [6., 8.]])