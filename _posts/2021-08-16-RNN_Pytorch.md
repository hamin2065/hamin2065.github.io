---
layout: post
title:  RNN - Pytorch
subtitle:   
categories:  ai
tags: season-2
---

# RNN in Pytorch
```py
rnn = torch.nn.RNN(input_size, hidden_size) #1번
outputs, _status = rnn(input_data) #2번
```
`rnn`라는 변수에 torch.nn의 뉴럴 네트워크중에서 `RNN`을 불러오고 두 개의 매개변수를 넣어주면 된다. 

위에서 선언한 `rnn`에 우리가 넣고자 하는 `데이터(input_data)`를 넣으면 된다.
이 때, `input_data`는 3차원의 shape을 가지는 텐서이다.

![](https://t1.daumcdn.net/thumb/R720x0/?fname=http://t1.daumcdn.net/brunch/service/user/IgT/image/KOUKrZNca-XlF0gNKntfOSgzsbs.png)

위 코드에서 1번줄은 셀 A를 선언하는 과정이고, 2번줄은 우리가 가지고 있는 데이터, 즉 $x_t$ 를 셀 A에 집어넣고 결과로 $h_t$ 를 반환받는 과정이다.

- - -

# Example : Input
"hello"라는 예시로 알아보자

```py
# 1-hot encoding
h = [1,0,0,0]
e = [0,1,0,0]
l = [0,0,1,0]
o = [0,0,0,1]
```
hello를 구성하는 알파벳을 모델이 인식할 수 있도록 벡터로 치환한다.

`h`라는 하나의 문자를 표현하기 위해서 4차원의 벡터가 필요하다.
따라서 `input_size = 4`이다. -> `input_data = (-,-,4)`

# Example : Hidden State

어떤 벡터 사이즈의 출력을 원하느냐에 따라서 `hidden_size`를 결정해주면 된다.
예를 들어 2의 크기를 갖는 결과를 원한다면 `ouputs shape = (-,-,2)` 

`hidden_size`와 `outputs크기`는 무슨 관련이 있길래 같은 값을 쓰는 것일까?

![hidden_state](/assets/img/posts/hidden_state.png)

셀 A의 내부구조를 보면 계산된 하나의 값이 두 갈래로 갈라져서 `hidden_state`와 `ouputs`로 나오게 되는 것이다. 즉 `ouput size`와 `hidden size`는 같다.

# Example : Sequence Length
`Sequence Length`는 말 그대로 시퀀스 데이터의 입력의 길이이다. X0부터 Xt까지의 입력 값이 있으면 데이터의 길이는 (t+1)이다.

hello에 적용하면 5개의 문자가 입력이 되기 때문에 `Sequence Length`는 5가되고 `input_data shape = (-,5,4)`이다. 하나의 입력값마다 하나의 출력값이 나오기 때문에 출력값 또한 `outputs shape = (-,5,2)`이다.

Pytorch에서는 사용자가 직접 Sequence Length를 알려주지 않아도 모델이 입력의 길이를 파악한다.

# Example : Batch Size
`h,e,l,o`로 만들 수 있는 다양한 문자열 중에서 3개를 모델에게 전달하면 `input_data shape = (3,5,4)`이고 `ouputs shape = (3,5,2)`가 된다.

Batch Size또한 Pytorch 모델이 직접 파악하기 때문에 따로 사용자가 입력하지 않아도 된다.

# Example 전체 코드
`hello, eolll, lleel` 세 개의 단어로 하나의 배치를 구성해서 `input_data`로 구성한다.
```py
import torch
import numpy as np

input_size = 4
hidden_size = 2

# 1-hot encoding
h = [1,0,0,0]
e = [0,1,0,0]
l = [0,0,1,0]
o = [0,0,0,1]
input_data_np = np.array([[h,e,l,l,o],
                            [e,o,l,l,l],
                            [l,l,e,e,l]], dtype=np.float32)

# transform as torch tensor
input_data = torch.Tensor(input_data_np)
rnn = torch.nn.RNN(input_size, hidden_size)
outputs, _status = rnn(input_data)
```