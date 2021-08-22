---
layout: post
title:  "[RNN] time series"
subtitle:   
categories:  ai
tags: season-2
---
# Time Series Data
Time Series Data는 일반적으로 시계열 데이터라고 해석이 된다.
시계열 데이터란 일정한 시간 간격으로 배치된 데이터를 말한다. 일정한 시간 간격이 있는 주가 데이터가 시계열 데이터에 속한다.
  
- - -

# Example

아래는 구글의 주가를 일별로 나타낸 것이다.

![time-series-goog](/assets/img/posts/time-series-goog.jpg)

구글의 주가를 RNN모델에 적용해보자. `Many to One`의 방식을 이용한다.
![time-series-rnn](/assets/img/posts/time-series-rnn.png)
이 모델은 8일차의 종가를 예측하기 위해서 7일간의 데이터를 보면 된다는 전제로 출발하고 있다.

7일간의 데이터로 8일차의 종가를 예측하기 위해서는 1dim의 값이 필요하다. 따라서 hidden state로도 1dim의 정보가 전달이 되어야하는데 그것은 모델에게 너무 큰 부담이 된다.(원래 5dim의 데이터를 하나로 압축해서 나타내야하기 때문)

따라서 일반적으로는 hidden state에 dimension을 충분히 보장해주고, 보장된 hidden state를 쭉 유통해서 출력 직전에 Fully Connected Layer에 연결에서 그 output이 종가를 맞추도록한다.

# Apply RNN : Data Reading

필요한 모듈을 불러와준다.
```py
import torch
import torch.optim as optim
import numpy as np
import matplotlib.pyplot as plt
```
```py
# Random seed to make results deterministic and reproducible
torch.manual_seed(0)
```

필요한 변수들을 설정해준다.
```py
# hyper parameters
seq_length = 7 # 7일간의 데이터
data_dim = 5 #데이터가 5개의 dim으로 구성
hidden_dim = 10 # hidden state dim을 10개로 충분하게 잡는다.ㄴ
output_dim = 1 # 마지막에 FC가 맞춰야하는 종가의 데이터
learning_rate = 0.01
iterations = 500
```

데이터를 가져와서 나누고 텐서로 바꿔준다.
```py
# load data
xy = np.loadtxt("data-02-stock_daily.csv", delimiter=",")
xy = xy[::-1]  # reverse order

# split train-test set
train_size = int(len(xy) * 0.7) # train으로 70퍼센트 사용
train_set = xy[0:train_size]
test_set = xy[train_size - seq_length:]

# scaling data
train_set = minmax_scaler(train_set)
test_set = minmax_scaler(test_set)

# make train-test dataset to input
trainX, trainY = build_dataset(train_set, seq_length)
testX, testY = build_dataset(test_set, seq_length)

# convert to tensor
trainX_tensor = torch.FloatTensor(trainX)
trainY_tensor = torch.FloatTensor(trainY)

testX_tensor = torch.FloatTensor(testX)
testY_tensor = torch.FloatTensor(testY)
```

데이터의 폭이 주가는 800정도의 숫자이고, 거래량은 1000000정도의 숫자로 너무 차이가 크기 때문에 모두 0과 1사이의 상대값으로 전환할 필요가 있다.

모델 입장에서 데이터의 값이 너무 크게 다르면 출력할 때 부담이 되기 때문에 학습시켜서 0과 1사이의 상대값으로 바꾸는 것이다.
```py
# scaling function for input data
def minmax_scaler(data):
    numerator = data - np.min(data, 0)
    denominator = np.max(data, 0) - np.min(data, 0)
    return numerator / (denominator + 1e-7)
```
```py
# make dataset to input
def build_dataset(time_series, seq_length):
    dataX = []
    dataY = []
    for i in range(0, len(time_series) - seq_length):
        _x = time_series[i:i + seq_length, :]
        _y = time_series[i + seq_length, [-1]]  # Next close price
        print(_x, "->", _y)
        dataX.append(_x)
        dataY.append(_y)
    return np.array(dataX), np.array(dataY)
```

# Apply RNN : Neural Net Setting
뉴럴 네트워크를 class로 만들어준다.
```py
class Net(torch.nn.Module):
    def __init__(self, input_dim, hidden_dim, output_dim, layers):
        super(Net, self).__init__()
        self.rnn = torch.nn.LSTM(input_dim, hidden_dim, num_layers=layers, batch_first=True)
        self.fc = torch.nn.Linear(hidden_dim, output_dim, bias=True)

    def forward(self, x):
        x, _status = self.rnn(x)
        x = self.fc(x[:, -1])
        return x


net = Net(data_dim, hidden_dim, output_dim, 1)
```
```py
# loss & optimizer setting
criterion = torch.nn.MSELoss()
optimizer = optim.Adam(net.parameters(), lr=learning_rate)
```

- - -

# Apply RNN : Training & Evaluation
실제 학습을 시킨다.
```py
# start training
for i in range(iterations):

    optimizer.zero_grad()
    outputs = net(trainX_tensor)
    loss = criterion(outputs, trainY_tensor)
    loss.backward()
    optimizer.step()
    print(i, loss.item())
```
```py
plt.plot(testY)
plt.plot(net(testX_tensor).data.numpy())
plt.legend(['original', 'prediction'])
plt.show()
```