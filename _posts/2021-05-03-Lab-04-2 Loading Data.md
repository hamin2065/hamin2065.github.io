---
layout: post
title:  Loading Data
subtitle:   
categories:  ai
tags: season-2
---

# 학습목표
미니배치 경사하강법(Minibatch Gradient descent)를 배우고 Dataset & DataLoader 사용법에 대해 알아본다.

# 핵심키워드
- 다항 선형 회귀(Multivariable Linear regression)
- 미니배치 경사하강법(Minibatch Gradient descent)
- Dataset, DataLoader

# Data in the Real World
- 복잡한 머신러닝 모델을 학습하려면 엄청난 양의 데이터가 필요하다.
- 대부분 데이터셋은 적어도 수십만 개의 데이터를 제공한다.
ex) IMAGENET에는 14,197,122개의 이미지가 데이터로 존재한다.

Problem
- 엄청난 양의 데이터를 한번에 학습시킬 수 없다 -> 너무 느리다, 하드웨어적으로 불가능하다.
- 그렇다면 일부분의 데이터로만 학습하면 어떨까? -> 이렇게해서 나온 것이 minibatch gradient Descent이다.



Minibatch Gradient descent : 전체 데이터를 균일하게 나눠서 학습한다.
![coding](../../../assets/img/posts/pytorch_Lab04_1.png)

-> 업데이트를 좀 더 빠르게 할 수 있다.
-> 전체 데이터를 쓰지 않아서 잘못된 방향으로 업데이트를 할 수도 있다.
![coding](../../../assets/img/posts/pytorch_Lab04_2.png)

Pytorch Dataset
```py
from torch.utils.data import Dataset

class CustomDataset(Dataset):
    def __init__(self):
        self.x_data = [[73, 80, 75],
                           [93, 88, 93],
                           [89, 91, 90],
                           [96, 98, 100],
                           [73, 66, 70]]
        self.y_data = [[152], [185], [180], [196], [142]]
        
        #이 데이터셋의 총 데이터 수
        def __len__(self):
            return len(self.x_data)
        
        #어떠한 인덱스 idx를 받았을 때, 그에 상응하는 입출력 데이터 반환
        def __getitem__(self, idx):
            x = torch.FloatTensor(self.x_data[idx])
            y = torch.FloatTensor(self.y_data[idx])
            
            return x, y
        
dataset = CustomDataset()
```

Pytorch DataLoader
```py
from torch.utils.data import DataLoader

dataloader = DataLoader(
    dataset,
    batch_size=2,
    shuffle=True
)
```
- batch_size = 2
    - 각 minibatch의 크기
    - 통상적으로 2의 제곱수로 설정한다.(16, 32, 64, 128, 256, 512)

- shuffle = True
    - Epoch마다 데이터셋을 섞어서 데이터가 학습되는 순서를 바꾼다.

Full Code with Dataset and DataLoader
```python
nb_epochs = 20

for epoch in range(nb_epochs+1):
    for batch_idx, samples in enumerate(dataloader):
        x_train, y_train = samples
        #H(x) 계산
        prediction = model(x_train)
        
        #cost 계산
        cost = F.mse_loss(prediction, y_train)
        
        #cost로 H(x) 개선
        optimizer.zero_grad()
        cost.backward()
        optimizer.step()
        
        print('Epoch {:4d}/{} Batch {}/{} Cost: {:.6f}'.format(epoch, nb_epochs, batch_idx+1, len(dataloader), cost.item()))
```
- enumerate(dataloader) -> minibatch 인덱스의 데이터를 받음
- len(dataloader) -> 한 epoch당 minibatch 개수

