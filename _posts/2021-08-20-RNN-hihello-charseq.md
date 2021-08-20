---
layout: post
title:  "[RNN] hihello and charseq"
subtitle:   
categories:  ai
tags: season-2
---

# hihello 문제 소개
`'h', 'i', 'h', 'e', 'l', 'l', 'o'`의 문자열이 있을 때, 하나의 문자가 주어지면 다음 문자를 예측하는 문제이다.

예를 들어 `h`가 들어오면 `i` 또는 `e`를 예측해야하고, `l`이 들어오면 `l` 또는 `o`를 예측해야한다.

하나의 문자열이더라도 여러개의 출력값이 예상되기 때문에 RNN이 어디까지 진행되었는지 기록하는 `hidden state`의 역할이 중요하다.

- - -

# 문자 표현하기
각각의 캐릭터(문자)에 번호를 매기는 방법을 사용할 수 있다. -> 인덱스를 매긴다고 표현한다.

우선 학습할 문자열을 중복을 제거한 후에 인덱스로 표현한다.

`'h' -> 0`, `'i' -> 1`, `'e' -> 2`, `'l' -> 3`, `'o' -> 4`

```py
# list of available characters
char_set = ['h', 'i', 'e', 'l', 'o']
```

- - -

# One-hot encoding
순차적이지 않고 문자처럼 카테고리컬(categorical)한 데이터를 표현할 때는 원-핫 인코딩을 주로 사용한다.
```py
# 'hihello'를 각 인덱스로 표현
X_data = [[0,1,0,2,3,3]]

# one-hot encoding
x_one_hot = [[[1,0,0,0,0],
            [0,1,0,0,0],
            [1,0,0,0,0],
            [0,0,1,0,0],
            [0,0,0,1,0],
            [0,0,0,1,0]]]
y_data = [[1,0,2,3,3,4]]
```
입력으로 들어오는 `x_one_hot`코드에는 `hihello`에서 마지막 문자인 `o`가 빠져있는데 그 이유는 `o`가 마지막 문자라서 입력으로 들어가지 않기 때문이다.

마찬가지로 출력값을 나타내는 `y_data`에도 첫 번째 값인 `h`의 인덱스가 빠져있다.

- - -

# Cross Entropy Loss
categorical한 결과값이 필요할 때는 확률로 우선 표현하고 label을 해야한다.
```py
# loss & optimizer setting
criterion = torch.nn.CrossEntropyLoss()

loss = criterion(outputs.view(-1, input_size), Y.view(-1))
```
`criterion` 안에는 모델의 output과 정답 레이블을 넣어주어야한다.

- - -

# 'hihello' 코드 준비 
위에서 했던 과정을 합쳐보자.
```py
char_set = ['h', 'i', 'e', 'l', 'o']

# hyper parameters
input_size = len(char_set)
hidden_size = len(char_set)
learning_rate = 0.1

# data setting
x_data = [[0,1,0,2,3,3]] # 캐릭터 인덱스로 표현
x_one_hot = [[[1,0,0,0,0],
            [0,1,0,0,0],
            [1,0,0,0,0],
            [0,0,1,0,0],
            [0,0,0,1,0],
            [0,0,0,1,0]]]
y_data = [[1,0,2,3,3,4]]

# transform as torch tensor variable
X = torch.FloatTensor(x_one_hot)
Y = torch.LongTensor(y_data)
```

- - -

# charseq
위에서 'hihello'를 준비한 과정과 비슷하게 문자열을 준비하는 과정이다.

```py
sample = " if you want you"

# make dictionary
char_set = list(set(sample)) #주어진 문자열에서 중복을 제거하고 각 문자를 리스트에 넣음
char_dic = {c: i for i, c in enumerate(char_set)}

# hyper parameters
dic_size = len(char_dic)
hidden_size = len(char_dic)
learning_rate = 0.1

# data setting
sample_idx = [char_dic[c] for c in sample]
x_data = [sample_idx[:-1]] # 마지막을 제외한 나머지
x_one_hot = [np.eye(dic_size)[x] for x in x_data] # 원-핫 임베딩이된 matrix를 가져옴
y_data = [sample_idx[1:]] # 처음을 제외한 나머지

# transform as torch tensor variable
X = torch.FloatTensor(x_one_hot)
Y = torch.LongTensor(y_data)
```

- - -

# RNN으로 학습
위 준비과정을 토대로 sample로 선언한 문자열을 학습시켜보자.

필요한 모듈 불러오기
```py
import torch
import torch.optim as optim
import numpy as np
```

학습시킬 문자열 준비
```py
sample = " if you want you"
char_set = list(set(sample))
char_dic = {c:i for i, c in enumerate(char_set)}
```

넣어야하는 사이즈와 learning rate 설정
```py
input_size = len(char_dic)
hidden_size = len(char_dic)
learning_rate = 0.1
```

텐서로 바꿀 수 있도록 문자열 설정
```py
sample_idx = [char_dic[c] for c in sample]
x_data = [sample_idx[:-1]]
x_one_hot = [np.eye(dic_size)[x] for x in x_data]
y_data = [sample_idx[1:]]
```

RNN 모델 준비
```py
rnn = torch.nn.RNN(input_size, hidden_size, batch_first = True)
```

Loss와 Optimizer 설정
```py
criterion = torch.nn.CrossEntropyLoss()
optimizer = optim.Adam(rnn.parameters(), learning_rate)
```
텐서로 바꿔주기
```py
X = torch.FloatTensor(x_one_hot)
Y = torch.LongTensor(y_data)
```

학습
```py
for i in range(100):
    optimizer.zero_grad() # 매번 새로운 gradient 구하기
    outputs, _status = rnn(X) # _status는 다음 input 있으면 거기서 쓰이는 hidden state
    loss = criterion(outputs.view(-1, input_size), Y.view(-1))
    loss.backward()
    optimizer.step() # parameter update


    result = outputs.data.numpy().argmax(axis = 2) # 가장 큰 인덱스를 골라내준다.
    result_str = ''.join([char_set[c] for c in np.squeeze(result)]) # 축의 차원을 축소해준다.(1차원 배열로 축소)
    print(i, "loss: ",loss.item(), "prediction: ",result, "true Y: ",y_data, "prediction str: ",result_str)
```

나는 100번을 학습시킨 결과로

loss:  0.8306818008422852 prediction:  [[6 1 2 5 9 7 2 4 3 8 7 2 5 9 7]] true Y:  [[6, 1, 2, 5, 9, 7, 2, 4, 3, 8, 0, 2, 5, 9, 7]] prediction str:  if you wanu you

가 출력되었다.