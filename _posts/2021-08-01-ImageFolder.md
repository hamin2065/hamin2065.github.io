---
layout: post
title:  Image Folder
subtitle:   
categories:  ai
tags: season-2
---

# 학습목표
사용자 데이터를 사용하는 방법에 대해서 알아본다.

# 1. 필요한 모듈을 import 시키기
```py
import torchvision
from torchvision import transforms

from torch.utils.data import DataLoader
```
```py
from matplotlib.pyplot import imshow
%matplotlib inline
```

# 2. 데이터 사이즈 조정 및 불러오기
사진의 크기를 보면 (영상에서) 256 x 256 으로 아주 큰 사이즈를 갖고 있다.

transforms.Compose()를 이용해서 사이즈를 바꿔준다.
```py
trans = transforms.Compose([
    transforms.Resize((64,128))
])

train_data = torchvision.datasets.ImageFolder(root='custom_data/origin_data', transform=trans) # 사진의 경로
```

# 4. 사진 저장하기
사이즈를 바꾼 사진을 계속 사용할 수 있도록 transform시킨 사진을 저장한다.
```py
for num, value in enumerate(train_data):
    data, label = value
    print(num, data, label)
    
    if(label == 0):
        data.save('custom_data/train_data/gray/%d_%d.jpeg'%(num, label))
    else:
        data.save('custom_data/train_data/red/%d_%d.jpeg'%(num, label))
```
- - -

# Neural Network 만들기
(Layer 1) Convolution layer = (in_c = 3, out_c = 6, kernel_size = 5, stride = 1)
(Layer 1) MaxPool layer = (kernel_size = 2, stride = 2)

(Layer 2) Convolution layer = (in_c = 6, out_c = 16, kernel_size = 5, stride = 1)
(Layer 2) MaxPool layer = (kernel_size = 2, stride = 2)

(Layer 3) view => (batch_size x [16,13,29] => batch_size x [6032])
(Layer 3) Fully_Connect layer => (input = 6032, output = 120)
(Layer 3) Fully_Connect layer => (input = 120, output = 2)

# Image Folder 학습

위의 과정에서 저장한 사진을 이용하여 학습을 진행해보자.


먼저 필요한 모듈을 import 시키고,
```py
import torch
import torch.nn as nn
import torch.nn.functional as F

import torch.optim as optim
from torch.utils.data import DataLoader

import torchvision
import torchvision.transforms as transforms
```

GPU 설정을 해준다.
```py
device = 'cuda' if torch.cuda.is_available() else 'cpu'

torch.manual_seed(777)
if device =='cuda':
    torch.cuda.manual_seed_all(777)
```

데이터를 텐서로 바꾸어서 불러온다.
```py
trans = transforms.Compose([
    transforms.ToTensor()
])

train_data = torchvision.datasets.ImageFolder(root='./custom_data/train_data', transform=trans)
```

data_loader에 저장해준다.
```py
data_loader = DataLoader(dataset = train_data, batch_size = 8, shuffle = True, num_workers=2)
```

위에서 계획한대로 Neural Network에 대한 CNN Class를 만들어준다.
```py
class CNN(nn.Module):
    def __init__(self):
        super(CNN, self).__init__()
        self.layer1 = nn.Sequential(
            nn.Conv2d(3,6,5),
            nn.ReLU(),
            nn.MaxPool2d(2),
        )
        self.layer2 = nn.Sequential(
            nn.Conv2d(6,16,5),
            nn.ReLU(),
            nn.MaxPool2d(2),
        )
        self.layer3 = nn.Sequential(
            nn.Linear(16*13*29, 120),
            nn.ReLU(),
            nn.Linear(120,2)
        )
        
    def forward(self, x):
        out = self.layer1(x)
        out = self.layer2(out)
        out = out.view(out.shape[0], -1)
        out = self.layer3(out)
        return out
```

optimzer와 loss function을 선언해준다.
```py
optimizer = optim.Adam(net.parameters(), lr=0.00005)
loss_func = nn.CrossEntropyLoss().to(device)
```

데이터를 학습시킨다.
```py
total_batch = len(data_loader)

epochs = 7
for epoch in range(epochs):
    avg_cost = 0.0
    for num, data in enumerate(data_loader):
        imgs, labels = data
        imgs = imgs.to(device)
        labels = labels.to(device)
        optimizer.zero_grad()
        out = net(imgs)
        loss = loss_func(out, labels)
        loss.backward()
        optimizer.step()
        
        avg_cost += loss / total_batch
        
    print('[Epoch:{}] cost = {}'.format(epoch+1, avg_cost))
print('Learning Finished!')
```

학습시킨 모델을 저장해준다.
```py
torch.save(net.state_dict(), "./model/model.pth")
```

학습시킨 모델로 테스트를 해보자.

우선 테스트 데이터를 불러온다.
```py
trans=torchvision.transforms.Compose([
    transforms.Resize((64,128)),
    transforms.ToTensor()
])
test_data = torchvision.datasets.ImageFolder(root='./custom_data/test_data', transform=trans)
```

test dataset를 dataloader를 사용해서 저장해둔다.
```py
test_set = DataLoader(dataset = test_data, batch_size = len(test_data))
```

실제로 테스트를 해서 정확도를 출력해본다.
```py
with torch.no_grad():
    for num, data in enumerate(test_set):
        imgs, label = data
        imgs = imgs.to(device)
        label = label.to(device)
        
        prediction = net(imgs)
        
        correct_prediction = torch.argmax(prediction, 1) == label
        
        accuracy = correct_prediction.float().mean()
        print('Accuracy:', accuracy.item())
```