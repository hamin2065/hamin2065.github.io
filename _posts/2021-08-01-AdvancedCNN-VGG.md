---
layout: post
title:  VGG
subtitle:   
categories:  ai
tags: season-2
---

VGG는 CNN 모델의 한 종류로 3x3 convolution, stride와 padding을 모두 1로 갖는 것이 특징이다.

`torchvision.models.vgg`
- vgg11 ~ vgg19까지 만들 수 있도록 되어있다.
- 3 x 224 x 224 입력을 기준으로 만들도록 되어있다.

우선 필요한 모듈을 import 시킨다.
```py
import torch.nn as nn
import torch.utils.model_zoo as model_zoo
```

그리고 모델을 불러오는데 이 모델들은 이미 imagenet을 기반으로 해서 pre-training이 끝난 모델들이다.
```py
__all__ = [
    'VGG', 'vgg11', 'vgg11_bn', 'vgg13', 'vgg13_bn', 'vgg16', 'vgg16_bn',
    'vgg19_bn', 'vgg19',
]


model_urls = {
    'vgg11': 'https://download.pytorch.org/models/vgg11-bbd30ac9.pth',
    'vgg13': 'https://download.pytorch.org/models/vgg13-c768596a.pth',
    'vgg16': 'https://download.pytorch.org/models/vgg16-397923af.pth',
    'vgg19': 'https://download.pytorch.org/models/vgg19-dcbb9e9d.pth',
    'vgg11_bn': 'https://download.pytorch.org/models/vgg11_bn-6002323d.pth',
    'vgg13_bn': 'https://download.pytorch.org/models/vgg13_bn-abd245e5.pth',
    'vgg16_bn': 'https://download.pytorch.org/models/vgg16_bn-6c64b313.pth',
    'vgg19_bn': 'https://download.pytorch.org/models/vgg19_bn-c79401a0.pth',
}
```

VGG Class를 선언해준다.
```py
class VGG(nn.Module):
    def __init__(self, features, num_classes=1000, init_weights=True):
        super(VGG, self).__init__()
        
        self.features = features #convolution
        
        self.avgpool = nn.AdaptiveAvgPool2d((7, 7))
        
        self.classifier = nn.Sequential(
            nn.Linear(512 * 7 * 7, 4096),
            nn.ReLU(True),
            nn.Dropout(),
            nn.Linear(4096, 4096),
            nn.ReLU(True),
            nn.Dropout(),
            nn.Linear(4096, num_classes),
        )#FC layer
        
        if init_weights:
            self._initialize_weights()

    def forward(self, x):
        x = self.features(x) #Convolution 
        x = self.avgpool(x) # avgpool
        x = x.view(x.size(0), -1) #
        x = self.classifier(x) #FC layer
        return x

    def _initialize_weights(self):
        for m in self.modules():
            if isinstance(m, nn.Conv2d):
                nn.init.kaiming_normal_(m.weight, mode='fan_out', nonlinearity='relu')
                if m.bias is not None:
                    nn.init.constant_(m.bias, 0)
            elif isinstance(m, nn.BatchNorm2d):
                nn.init.constant_(m.weight, 1)
                nn.init.constant_(m.bias, 0)
            elif isinstance(m, nn.Linear):
                nn.init.normal_(m.weight, 0, 0.01)
                nn.init.constant_(m.bias, 0)
```
위에 들어갈 feature은 make_layers를 사용한다.
```py
def make_layers(cfg, batch_norm=False):
    layers = []
    in_channels = 3
    
    for v in cfg:
        if v == 'M':
            layers += [nn.MaxPool2d(kernel_size=2, stride=2)]
        else:
            conv2d = nn.Conv2d(in_channels, v, kernel_size=3, padding=1)
            if batch_norm:
                layers += [conv2d, nn.BatchNorm2d(v), nn.ReLU(inplace=True)]
            else:
                layers += [conv2d, nn.ReLU(inplace=True)]
            in_channels = v
                     
    return nn.Sequential(*layers)
```
```py
cfg = {
    'A': [64, 'M', 128, 'M', 256, 256, 'M', 512, 512, 'M', 512, 512, 'M'], #8 + 3 =11 == vgg11
    'B': [64, 64, 'M', 128, 128, 'M', 256, 256, 'M', 512, 512, 'M', 512, 512, 'M'], # 10 + 3 = vgg 13
    'D': [64, 64, 'M', 128, 128, 'M', 256, 256, 256, 'M', 512, 512, 512, 'M', 512, 512, 512, 'M'], #13 + 3 = vgg 16
    'E': [64, 64, 'M', 128, 128, 'M', 256, 256, 256, 256, 'M', 512, 512, 512, 512, 'M', 512, 512, 512, 512, 'M'], # 16 +3 =vgg 19
    'custom' : [64,64,64,'M',128,128,128,'M',256,256,256,'M']
}
```
위의 cfg에서 `A`에 따라서 make_layers가 어떻게 학습되는지 과정을 보면
```py
conv2d = nn.Conv2d(3, 64, kernel_size=3, padding=1) #1
nn.ReLu(inplace=True)

nn.MaxPool2d(kernel_size=2, stride=2)

conv2d = nn.Conv2d(64, 128, kernel_size=3, padding=1)#2
nn.ReLu(inplace=True)

nn.MaxPool2d(kernel_size=2, stride=2)

conv2d = nn.Conv2d(128, 256, kernel_size=3, padding=1)#3
nn.ReLu(inplace=True)

conv2d = nn.Conv2d(256, 256, kernel_size=3, padding=1)#4
nn.ReLu(inplace=True)

nn.MaxPool2d(kernel_size=2, stride=2)

conv2d = nn.Conv2d(256, 512, kernel_size=3, padding=1)#5
nn.ReLu(inplace=True)

conv2d = nn.Conv2d(512, 512, kernel_size=3, padding=1)#6
nn.ReLu(inplace=True)

nn.MaxPool2d(kernel_size=2, stride=2)

conv2d = nn.Conv2d(512, 512, kernel_size=3, padding=1)#7
nn.ReLu(inplace=True)

conv2d = nn.Conv2d(512, 512, kernel_size=3, padding=1)#8
nn.ReLu(inplace=True)

nn.MaxPool2d(kernel_size=2, stride=2)
```
이러한 과정을 토대로 이루어지는 것을 볼 수 있다. 각각의 값에 따라서 make_layers()가 실행된 과정이다.

이제 VGG Class에 값을 넣어 CNN으로 저장해준 후에 CNN을 출력해본다.
```py
CNN = VGG(make_layers(cfg['custom']), num_classes=10, init_weights=True)
```
```py
CNN
```
출력결과

> VGG(
> 
>   (features): Sequential(
> 
>    (0): Conv2d(3, 64, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1))
>
>    (1): ReLU(inplace)
>
>    (2): Conv2d(64, 64, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1))
>    
>    (3): ReLU(inplace)
>
>    (4): Conv2d(64, 64, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1))
>
>    (5): ReLU(inplace)
>
>    (6): MaxPool2d(kernel_size=2, stride=2, padding=0, dilation=1 ,ceil_mode=False)
>
>    (7): Conv2d(64, 128, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1))
>    
>    (8): ReLU(inplace)
>
>    (9): Conv2d(128, 128, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1))
>
>    (10): ReLU(inplace)
>
>    (11): Conv2d(128, 128, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1))
>
>    (12): ReLU(inplace)
>
>    (13): MaxPool2d(kernel_size=2, stride=2, padding=0, dilation=1, ceil_mode=False)
>
>    (14): Conv2d(128, 256, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1))
>
>    (15): ReLU(inplace)
>
>    (16): Conv2d(256, 256, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1))
>
>    (17): ReLU(inplace)
>
>    (18): Conv2d(256, 256, kernel_size=(3, 3), stride=(1, 1), padding=(1, 1))
>
>    (19): ReLU(inplace)
>
>    (20): MaxPool2d(kernel_size=2, stride=2, padding=0, dilation=1, > ceil_mode=False))
>
>   (avgpool): AdaptiveAvgPool2d(output_size=(7, 7))
>
>   (classifier): Sequential(
>
>    (0): Linear(in_features=25088, out_features=4096, bias=True)
>
>    (1): ReLU(inplace)
>
>    (2): Dropout(p=0.5)
>
>    (3): Linear(in_features=4096, out_features=4096, bias=True)
>
>    (4): ReLU(inplace)
>
>    (5): Dropout(p=0.5)
>
>    (6): Linear(in_features=4096, out_features=10, bias=True)
>
>   )
>
> )

[vgg.py 코드](https://github.com/deeplearningzerotoall/PyTorch/blob/master/vgg.py)