---
layout: post
title:  "[RNN] Long sequence"
subtitle:   
categories:  ai
tags: season-2
---

저번에 쓴 'hihello'나 charseq보다 더 긴 문장을 학습시키기 위해서 어떻게 해야할까?

더 긴 문장 데이터셋은 하나의 입력으로 쓸 수 없기 때문에 `fixed size sequence`로 잘라서 써야한다.

# 긴 문장에서 sequence 만들기
```
sentence = ("if you want to build a ship, don't drum up people together to "
            "collect wood and don't assign them tasks and work, but rather "
            "teach them to long for the endless immensity of the sea.")
```
문자열을 나눌 때, 일정한 개수로 잘라서 한 칸씩 이동하는 방식을 쓴다.
1. x : "if you wan"  y : "f you want"
2. x : "f you want"  y : " you want "
3. x : " you want "  y : "you want t"
4. x : "you want t"  y : "ou want to"
5. x : "ou want to"  y : "u want to "

위의 과정을 코드로 나타내보자.
```py
# data setting
x_data = []
y_data = []

for i in range(0, len(sentence)-sequence_length):
    x_str = sentence[i:i+sequence_length]
    y_str = sentence[i+1:i+sequence_length+1]
    print(i, x_str, '->', y_str)

    # string을 index로 만들기
    x_data.append([char_dic[c] for c in x_str])
    y_data.append([char_dic[c] for c in y_str])

x_one_hot = [np.eye(dic_size)[x] for x in x_data]

#transform as torch Tensor variable
X = torch.FloatTensor(x_one_hot)
Y = torch.LongTensor(y_data)
```

- - -

__FC Layer더하고 RNN 쌓기__

![rnn](/assets/img/posts/rnn.png)

```py
class Net(torch.nn.Module):
    def __init__(self, input_dim, hidden_dim, layers):
        super(Net, self).__init__()
        self.rnn = torch.nn.RNN(input_dim, hidden_dim, num_layers = layers, batch_first = True)
        self.fc = torch.nn.Linear(hidden_dim, hidden_dim, bias = True)

    def forward(self, x):
        x, _status = self.rnn(x)
        x = self.fc(x)
        return x

net = Net(dic_size, hidden_size, 2)
```

그 외에 필요한 과정을 완성시킨다.
```py
# loss & optimizer setting
criterion = torch.nn.CrossEntropyLoss()
optimizer = optim.Adam(net.parameters(), learning_rate)

# start training
for i in range(100):
    optimizer.zero_grad()
    outputs = net(X)
    loss = criterion(outputs.view(-1, dic_size), Y.view(-1))
    loss.backward()
    optimizer.step()

    results = outputs.argmax(dim = 2)
    predict_str = ""

    for j, result in enumerate(results):
        print(i, j, ''.join([char_set[t] for t in result]), loss.item())
        # 첫 번째 경우는 모든 문자열을 더하지만 두 번째부터는 겹치는 부분을 제외하고 마지막 문자만 추가한다.
        if j == 0:
            predict_str += ''.join([char_set[t] for t in result])
        else:
            predict_str += char_set[result[-1]]
```