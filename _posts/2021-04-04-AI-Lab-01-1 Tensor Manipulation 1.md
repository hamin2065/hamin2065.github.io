---
layout: post
title: Lab-01-1 Tensor Manipulation 1
color: rgb(242,85,44)
tags: [AI, PyTorch]
---
# 학습목표

텐서 조작(Tensor Manipulation)에 대해 알아본다.

# 핵심키워드

- 텐서(Tensor)
- 넘파이(NumPy)
- 텐서 조작(Tensor Manipulation)
- 브로드캐스팅(Broadcasting)

PyTorch Basic Tensor Manipulaion

# Vector, Matrix, and Tensor

## Vector, Matrix, and Tensor

파이토치는 넘파이와 굉장히 유사하다.

![coding](../../../assets/img/posts/pytorch_Lab01_1.png)

- 차원이 없는 값 -> 스칼라!
- 1차원 -> 벡터
- 2차원 -> 행렬
- 3차원 -> Tensor
- 4차원 -> 3차원을 위로 쌓아 올린것
- 5차원 -> 4차원을 옆으로 확장
- 6차원 -> 5차원을 뒤로 확장(깊이에 대해서)
- - -
## PyTorch Tensor Shape Convention

- 2D Tensor (Typical Simple Setting)
    - |t| = (batch size, dim) : Tensor의 크기

        -> (batch size)_64차원 * dim_256차원
- 3D Tensor (Typical Computer Vision)
    - |t| = (batch size, width, height)

      -> 하나의 이미지 -> 가로와 세로가 존재!

      -> 여러장의 이미지 -> 3차원의 텐서를 구성하게된다.
- 3D Tensor (Typical Natural Language Processing): 시계열, 시퀀셜(순차적) , NLPL
    - |t| = (batch size, length, dim)
    - dim * length -> 하나의 문장




- - -

# NumPy Review

__Numpy__ : 행렬이나 이반적으로 대규모 다차원 배열을 쉽게 처리할 수 있도록 지원하는 파이썬의 라이브러리. Numpy는 데이터 구조 외에도 수치계산을 위해 효율적으로 구현된 기능을 제공한다.

## Imports

- __1D Array with NumPy__
```python
import numpy as np
import torch
t = np.array([0., 1., 2., 3., 4., 5., 6.])
print(t)
print('Rank of t: ', t.ndim) #.ndim ->배열의 차원 수 or 배열의 축 수
print('Shape of t: ',t.shape) #.shape -> 배열 각 차원의 크기를 튜플 형태로 표현.  n행과 m열의 행렬의 경우 (n,m) 형태의 튜플
print('t[o] t[1] t[-1] = ',t[0],t[1],t[-1])#Element
print('t[2:5] t[4:-1] = ',t[2:5], t[4:-1])#Slicing
print('t[:2] t[3:]',t[:2],t[3:])#Slicing
```

출력결과
> [0. 1. 2. 3. 4. 5. 6.]
>
> Rank of t:  1
>
> Shape of t:  (7,)
>
> t[o] t[1] t[-1] =  0.0 1.0 6.0
>
> t[2:5] t[4:-1] =  [2. 3. 4.] [4. 5.]
>
> t[:2] t[3:] [0. 1.] [3. 4. 5. 6.]
- - -
- __2D Array with Numpy__

```python
t = np.array([[1., 2., 3.],[4., 5., 6.],[7., 8., 9.],[10., 11., 12.]])
print(t)
print('Rank of t: ',t.ndim)
print('Shape of t: ',t.shape)
```
출력결과
> [[ 1.  2.  3.]
> 
>  [ 4.  5.  6.]
> 
>  [ 7.  8.  9.]
> 
>  [10. 11. 12.]]
> 
> Rank of t:  2
> 
> Shape of t:  (4, 3)

- - -

- __1D Array with PyTorch__
```python
t = torch.FloatTensor([0., 1., 2., 3., 4., 5., 6.])
print(t)
print(t.dim())# rank -> 차원
print(t.shape)# shape -> 몇개의 원소?
print(t.size())# shape
print(t[0], t[1], t[-1])# Element
print(t[2:5], t[4:-1])# Slicing
print(t[:2], t[3:])# Slcing
```
출력결과
> tensor([0., 1., 2., 3., 4., 5., 6.])
> 
> 1
> 
> torch.Size([7])
> 
> torch.Size([7])
> 
> tensor(0.) tensor(1.) tensor(6.)
> 
> tensor([2., 3., 4.]) tensor([4., 5.])
> 
> tensor([0., 1.]) tensor([3., 4., 5., 6.])
- - -
- __2D Array with PyTorch__

```python
t = torch.FloatTensor([[1., 2., 3.],
                       [4., 5., 6.],
                       [7., 8., 9.],
                       [10., 11., 12.]
                      ])
print(t)
print(t.dim())# rank
print(t.size())# shape
print(t[:, 1]) # 첫 번째 차원에서는 다 가져오고 두 번째 차원에서는 1번째 값을 가져온다.
print(t[:, 1].size())
print(t[:, :-1])
```
> 출력결과
>
> tensor([[ 1.,  2.,  3.], [ 4.,  5.,  6.], [ 7.,  8.,  9.], [10., 11., 12.]])
> 
> 2
> 
> torch.Size([4, 3])
> 
> tensor([ 2.,  5.,  8., 11.])
> 
> torch.Size([4]) # 4개의 element를 가진 벡터
> 
> tensor([[ 1.,  2.], [ 4.,  5.], [ 7.,  8.], [10., 11.]])


__Broadcasting__
```python
# Same shape
m1 = torch.FloatTensor([[3, 3]])
m2 = torch.FloatTensor([[2, 2]])
print(m1 + m2)
```
출력결과
> tensor([[5., 5.]])

-> 기본적으로는 같은 크기의 matrix끼리 더하기 연산이 가능하다.
```python
# Vector + scalar
m1 = torch.FloatTensor([[1, 2]])
m2 = torch.FloatTensor([[3]])# 3 -> [[3, 3]]
print(m1 + m2)
```
출력결과
> tensor([[4., 5.]])

-> 원래는 연산을 수행할 수 없어야하지만 스칼라를 받았을 때 파이토치가 자동으로 스칼라를 matrix또는 tensor로 변환시켜서 같은 사이즈로 변환시켜서 연산을 수행한다.

|m1| = (1, 2)

|m2| = (1, ) => (1, 2) 변환!

```python
# 2 * 1 Vector + 1 * 2 Vector
m1 = torch.FloatTensor([[1, 2]])
m2 = torch.FloatTensor([[3], [4]])
print(m1 + m2)
```
출력결과
> tensor([[4., 5.],
>         [5., 6.]])

크기가 다른 matrix의 경우 파이토치가 자동으로 크기를 늘려줘서 계산을 가능하게 만든다.

|m1| = (1, 2) => (2, 2)

|m2| = (2, 1) => (2, 2)

m1 = [[1, 2]] -> [[1,2],[1,2]]

m2 = [[3], [4]] -> [[3,3],[4,4]]



*Broadcasting은 자동으로 일어나기 때문에 사용자입장에서 조심해서 사용해야한다!
- - -
# PyTorch Tensor Allocation
- - -
# Matrix Multiplication

## Multiplication vs Matrix Multiplication
```python

print('Mul vs Matmul')

m1 = torch.FloatTensor([[1, 2],[3, 4]])
m2 = torch.FloatTensor([[1],[2]])
print('Shape of Matrix 1: ', m1.shape) # 2 x 2
print('Shape of Matrix 2: ', m2.shape) # 2 x 1
print(m1.matmul(m2)) # 2 x 1

m1 = torch.FloatTensor([[1, 2],[3, 4]])
m2 = torch.FloatTensor([[1],[2]])
print('Shape of Matrix 1: ', m1.shape) # 2 x 2
print('Shape of Matrix 2: ', m2.shape) # 2 x 1 --broadcasting--> 2 x 2
print(m1 * m2) # 2 x 2
print(m1.mul(m2))
```

출력결과

> 
> Mul vs Matmul
>
> 
> Shape of Matrix 1:  torch.Size([2, 2])
> 
> Shape of Matrix 2:  torch.Size([2, 1])
> 
> tensor([[ 5.], [ 11.]])
> 
> Shape of Matrix 1:  torch.Size([2, 2])
> 
> Shape of Matrix 2:  torch.Size([2, 1])
> 
> tensor([[1., 2.],[6., 8.]])
> 
> tensor([[1., 2.],[6., 8.]])

일반 Multiplication을 수행하는 경우에는 broadcasting을 통해서 값의 크기를 변화시켜준다.

Matrix Multiplication을 하는 경우에는 (2 x 2)의 행렬과 (2 x 1)의 행렬 곱셈을 실행해서 (2 x 1)크기의 행렬이 결과로 나오게 된다.

## Mean
```python
t = torch.FloatTensor([1, 2])
print(t.mean())
```
출력결과
>  tensor(1.5000)

```python
# Can't use mean() on integers
t = torch.LongTensor([1, 2])
try:
    print(t.mean())
except Exception as exc:
    print(exc)
```
출력결과
> Can only calculate the mean of floating types. Got Long instead.
```python
t = torch.FloatTensor([[1, 2],[3, 4]])
print(t)
print(t.mean())
print(t.mean(dim=0))
print(t.mean(dim=1))
print(t.mean(dim=-1))
```
출력결과
> tensor([[1., 2.], [3., 4.]])
>
> tensor(2.5000)
> 
> tensor([2., 3.])
> 
> tensor([1.5000, 3.5000])
> 
> tensor([1.5000, 3.5000])


`dim=0` -> (2 x 2) -> (1 x 2) = (2, )

: 첫 번째 차원인 `행`을 제거하고 `열`만 남긴다.

`dim=1`

: 두 번째 차원인 `열`을 제거하고 `행`만 남긴다.

## Sum
```python
t = torch.FloatTensor([[1, 2], [3, 4]])
print(t)

print(t.sum())
print(t.sum(dim=0))
print(t.sum(dim=1))
print(t.sum(dim=-1))
```
출력결과
> tensor([[1., 2.], [3., 4.]])
> 
> tensor(10.)
> 
> tensor([4., 6.])
> 
> tensor([3., 7.])
> 
> tensor([3., 7.])

## Max and Argmax
```python
t = torch.FloatTensor([[1, 2], [3, 4]])

#인자가 없이 max함수가 불리는 경우는 max값 하나만 리턴시킨다.
print(t.max()) # Returns one value : max

# dimension이 주어지면 두 개의 값을 리턴한다.
# 첫 번째 값은 최댓값
# 두 번째 값은 argmax로 최댓값의 index이다.
print(t.max(dim=0))# Returns two values : max and argmax
print('Max : ',t.max(dim=0)[0])
print('Argmax : ',t.max(dim=0)[1])
print(t.max(dim=1))
print(t.max(dim=-1))
```

출력결과
> tensor(4.)
> 
> torch.return_types.max(values=tensor([3., 4.]),indices=tensor([1, 1]))
> 
> Max :  tensor([3., 4.])
> 
> Argmax :  tensor([1, 1])
> 
> torch.return_types.max(values=tensor([2., 4.]),indices=tensor([1, 1]))
> 
> torch.return_types.max(values=tensor([2., 4.]),indices=tensor([1, 1]))
- - -
ex)

t.max(dim=0) #행이 없어지기 때문에 열차원으로 계산

(1, 3)중에서 큰 값 -> 3

(2, 3)중에서 큰 값 -> 4



