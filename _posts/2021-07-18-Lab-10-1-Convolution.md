---
layout: post
title:  Convolution
subtitle:   
categories:  ai
tags: season-2
---
# Convolution?
이미지 위에서 stride값 만큼 filter(kernel)을 이동시키면서 겹쳐지는 부분의 각 원소의 값을 곱해서 모두 더한 값을 출력으로 하는 연산

![](https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcSdmUBImj4CVqkMxvMawH6XPOaTV4xEWjUChQ&usqp=CAU)
첫 번째로 filter가 input을 돌면서 계산하는 식을 보면 <br>
(1x1) + (2x0) + (3x1) + <br>
(0x0) + (1x1) + (5x0) + <br>
(1x1) + (0x0) + (2x1) = 8 이다.


- stride : filter을 한번에 얼마나 이동할 것인가
- padding : zero-padding

# Pytorch nn.Conv2d
```py
# CLASS
torch.nn.Conv2d(in_channels, out_channels, kernel_size, stride = 1, padding = 0, dilation = 1, groups = 1, bias = True)
```
예를 들어 입력채널이 1, 출력채널이 1, 커널의 크기가 3x3이면 
```py
conv = nn.Conv2d(1,1,3)
```
이다.

## 입력의 형태
- input type : torch.Tensor
- input shape : (N x C x H x W) -> (batch_size, channel, height, width)

# Convolution의 output의 크기 계산하기 예제

outputsize = $$ inputsize - filtersize + (2 * padding)\over Stride $$ + 1

예제1 ) <br>
input image size : 227 x 227 <br>
filter size : 11 x 11 <br>
stride : 4 <br>
padding : 0 <br>
output image size = (227 - 11) / 4 + 1 =55

예제2 ) <br>
input image size : 64 x 64 <br>
filter size : 7 x 7 <br>
stride : 2 <br>
padding : 0 <br>
output image size = (64 - 7) / 4 + 1 = 29.5 -> 29

예제3 ) <br>
input image size : 32 x 32 <br>
filter size : 5 x 5 <br>
stride : 1 <br>
padding : 2 <br>
output image size = {(227 - 11) + 2*2 } / 1 + 1 = 32

예제4 ) <br>
input image size : 32 x 64 <br>
filter size : 5 x 5 <br>
stride : 1 <br>
padding : 0 <br>
output image size = {(32, 64) - 5 } / 1 + 1 = (28, 60)

예제5 ) <br>
input image size : 64 x 32 <br>
filter size : 3 x 3 <br>
stride : 1 <br>
padding : 1 <br>
output image size = {(64, 32) - 3 + 2 } / 1 = (64, 32)
- - -
예제 1번을 실제로 코드에 적용을 시켜보자.
```py
import torch
import torch.nn as nn
```
```py
conv = nn.Conv2d(1,1,11,stride = 4, padding = 0)
conv
```
출력결과 : Conv2d(1, 1, kernel_size=(11, 11), stride=(4, 4))
```py
inputs = torch.Tensor(1,1,227,227)
inputs.shape
```
출력결과 : torch.Size([1, 1, 227, 227])
```py
out = conv(inputs)
out.shape
```
출력결과 : torch.Size([1, 1, 55, 55])
- - -
# Pooling
![](https://kjhov195.github.io/post_img/200110/image4.png)
위의 그림은 Max Pooling의 예시로 filter안에 들어오는 원소중 가장 큰 값을 output으로 사용하는 방식이다.
![](https://kjhov195.github.io/post_img/200110/image5.png)
위의 그림은 Average Pooling의 예시로 filter안에 들어오는 원소들의 평균값을 output으로 사용하는 방식이다.
```py
# CLASS
torch.nn.MaxPool2d(kernel_size, stride = None, padding= 0, dilation = 1, return_indices = False, ceil_mode = False)
```
```py
import torch
import torch.nn as nn
```
```py
inputs = torch.Tensor(1,1,28,28)
```
```py
conv1 = nn.Conv2d(1,5,5)
pool = nn.MaxPool2d(2)
```
```py
out = conv1(inputs)
out2 = pool(out)
```
```py
out.size()
```
출력결과 : torch.Size([1, 5, 24, 24])
```py
out2.size()
```
출력결과 : torch.Size([1, 5, 12, 12])

- - -
pytorch 공식 사이트에 보면 convolution이 아닌 cross-correlation 계산이라고 나와있다.

convolution은 이미지를 뒤집어서 계산하는 것이고 뒤집지 않고 계산하는 것을 Cross-correlation이라고 하는데 우리는 뒤집지 않았기 때문에 `Cross-Correlation`인 것이다